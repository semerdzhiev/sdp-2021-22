#include "store.h"

#include <iostream>
#include <vector>

int main() {
	struct Printer : ActionHandler {
		static const char *resourceName(ResourceType type) {
			return type == ResourceType::banana ? "banana" : "schweppes";
		}
		virtual void onWorkerSend(int minute, ResourceType resource) override {
			std::cout << 'W' << ' ' << minute << ' ' << resourceName(resource) << '\n';
		}
		virtual void onWorkerBack(int minute, ResourceType resource) override {
			std::cout << 'D' << ' ' << minute << ' ' << resourceName(resource) << '\n';
		}
		virtual void onClientDepart(int index, int minute, int banana, int schweppes) override {
			std::cout << index << ' ' << minute << ' ' << banana << ' ' << schweppes << '\n';
		}
	};

	int workerCount, clientCount;
	std::cin >> workerCount >> clientCount;

	Printer coutPrinter;
	MyStore store;
	store.setActionHandler(&coutPrinter);
	store.init(workerCount, 0, 0);

	{
		std::vector<Client> clients(clientCount);
		for (int c = 0; c < clientCount; c++) {
			Client &client = clients[c];
			std::cin >> client.arriveMinute >> client.banana >> client.schweppes >> client.maxWaitTime;
		}
		store.addClients(clients.data(), int(clients.size()));
	}

	store.advanceTo(store.getLastEventTime());

	return 0;
}
