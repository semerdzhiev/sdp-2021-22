#include "interface.h"
#include "store.h"
#include "../../../group-G/source/common/catch.hpp"

#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <cassert>

const int RESTOCK_TIME = 60;
const int RESTOCK_AMOUNT = 100;

Store *createStore() {
	return new MyStore();
}

int& ResourceStorage::operator[](ResourceType type) {
	return amount[int(type)];
}

int ResourceStorage::operator[](ResourceType type) const {
	return amount[int(type)];
}

bool ResourceStorage::isEmpty() const {
	return amount[0] == 0 && amount[1] == 0;
}

void MyStore::addWaitingClient(WaitList& waitList, int clientIndex) const {
	const WaitingClient client{clientIndex, time + clients[clientIndex].maxWaitTime};
	WaitList::const_reverse_iterator it = waitList.crbegin();
	for (; it != waitList.crend(); ++it) {
		if (it->departTime <= client.departTime) {
			break;
		}
	}
	waitList.insert(it.base(), client);
}

void MyStore::returnWorkers() {
	while (!sentWorkers.empty() && sentWorkers.front().returnTime == time) {
		const WorkerDescriptor &descriptor = sentWorkers.front();
		resources[descriptor.resource] += RESTOCK_AMOUNT;
		actionHandler->onWorkerBack(time, descriptor.resource);
		sentWorkers.pop_front();
	}
}

bool MyStore::canServeNow(int clientIndex) const {
	const Client &client = clients[clientIndex];
	if (client.banana <= getBanana() && client.schweppes <= getSchweppes()) {
		return true;
	}
	return false;
}

MyStore::DepartedClient MyStore::processDepartingClient(int clientIndex) {
	const Client &client = clients[clientIndex];
	DepartedClient departLog;
	departLog.client = clientIndex;

	departLog.resources[ResourceType::banana] = std::min(client.banana, getBanana());
	resources[ResourceType::banana] -= departLog.resources[ResourceType::banana];

	departLog.resources[ResourceType::schweppes] = std::min(client.schweppes, getSchweppes());
	resources[ResourceType::schweppes] -= departLog.resources[ResourceType::schweppes];

	return departLog;
}

void MyStore::acceptClients() {
	assert(departed.empty());
	for (int c = lastServed + 1; c < clients.size() && clients[c].arriveMinute == time; c++) {
		if (canServeNow(c)) {
			// don't save the DepartedClient info, if client departs now, they get all resources
			processDepartingClient(c);
			departed.push_back(c);
		} else {
			// ensure newArrivals is sorted so that it can be merged with main queue
			addWaitingClient(newArrivals, c);
		}
		lastServed = c;
	}
}

void MyStore::departClients() {
	// first all clients that arrived and can be served same minute
	for (int c = 0; c < departed.size(); c++) {
		const int index = departed[c];
		const Client &client = clients[index];
		actionHandler->onClientDepart(index, time, client.banana, client.schweppes);
	}
	departed.clear();

	waiting.merge(newArrivals);
	newArrivals.clear();

	if (!waiting.empty()) {
		assert(waiting.begin()->departTime >= time);
	}

	WaitList::const_iterator it = waiting.cbegin();
	while (it != waiting.cend()) {
		const bool processClient = it->departTime <= time || canServeNow(it->client);
		if (!processClient) {
			++it;
			continue;
		}
		const DepartedClient departLog = processDepartingClient(it->client);
		actionHandler->onClientDepart(
			departLog.client, time,
			departLog.resources[ResourceType::banana],
			departLog.resources[ResourceType::schweppes]
		);
		it = waiting.erase(it);
	}
}

ResourceStorage MyStore::getMissingResources(int clientIndex) const {
	ResourceStorage missing;
	const Client &client = clients[clientIndex];
	missing[ResourceType::banana] = client.banana;
	missing[ResourceType::schweppes] = client.schweppes;

	missing[ResourceType::banana] = std::max(0, client.banana - getBanana() - restock[ResourceType::banana]);
	missing[ResourceType::schweppes] = std::max(0, client.schweppes - getSchweppes() - restock[ResourceType::schweppes]);
	return missing;
}

int MyStore::idleWorkers() const {
	const int idleCount = workerCount - int(sentWorkers.size());
	assert(idleCount >= 0);
	return idleCount;
}

ResourceType MyStore::resourcePriority(ResourceStorage resource) {
	if (resource[ResourceType::banana] > resource[ResourceType::schweppes]) {
		return ResourceType::banana;
	} else if (resource[ResourceType::schweppes] > resource[ResourceType::banana]) {
		return ResourceType::schweppes;
	} else {
		return ResourceType::banana;
	}
}

void MyStore::sendWorkers() {
	for (WaitList::const_iterator it = newArrivals.cbegin(); it != newArrivals.cend(); ++it) {
		ResourceStorage missing = getMissingResources(it->client);

		while (!missing.isEmpty() && idleWorkers()) {
			const ResourceType sendType = resourcePriority(missing);
			const WorkerDescriptor worker = {time + RESTOCK_TIME, sendType};
			sentWorkers.push_back(worker);
			missing[sendType] = std::max(0, missing[sendType] - RESTOCK_AMOUNT);
			actionHandler->onWorkerSend(time, sendType);
			restock[sendType] += RESTOCK_AMOUNT;
		}
	}
}

int MyStore::getNextEventTime() const {
	assert(newArrivals.empty());
	int first = INT_MAX;
	if (!waiting.empty()) {
		first = std::min(first, waiting.front().departTime);
	}

	if (lastServed + 1 < clients.size()) {
		first = std::min(first, clients[lastServed + 1].arriveMinute);
	}

	if (!sentWorkers.empty()) {
		first = std::min(first, sentWorkers.front().returnTime);
	}
	return first;
}

int MyStore::getLastEventTime() const {
	int largest = 0;
	for (ClientList::const_iterator it = clients.cbegin(); it != clients.cend(); ++it) {
		const Client &client = *it;
		largest = std::max(largest, client.arriveMinute + client.maxWaitTime);
		largest = std::max(largest, client.arriveMinute + RESTOCK_TIME);
	}
	return largest;
}

void MyStore::advanceTo(int minute) {
	while (time < minute) {
		// simulate only minutes where events will happen
		const int nextEvent = getNextEventTime();
		// if there is no next event, fast forward to requested time
		time = std::min(nextEvent, minute);
		acceptClients();
		sendWorkers();
		returnWorkers();
		departClients();
	}
}

void MyStore::setActionHandler(ActionHandler* handler) {
	actionHandler = handler;
}

void MyStore::init(int startWorkerCount, int startBanana, int startSchweppes) {
	resources[ResourceType::banana] = startBanana;
	resources[ResourceType::schweppes] = startSchweppes;
	workerCount = startWorkerCount;
}

void MyStore::addClients(const Client* newClients, int count) {
	clients.reserve(clients.size() + count);
	for (int c = 0; c < count; c++) {
		clients.push_back(newClients[c]);
	}
}

int MyStore::getBanana() const {
	return resources[ResourceType::banana];
}

int MyStore::getSchweppes() const {
	return resources[ResourceType::schweppes];
}
