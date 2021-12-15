#pragma once

#include "interface.h"

#include <list>
#include <vector>

/// Wrapper over resources info, 0 initialized
struct ResourceStorage {
	int amount[2] = {0, 0};

	/// Get resource by type
	int &operator[](ResourceType type);

	/// Get resource by type
	int operator[](ResourceType type) const;

	/// Check if all resources have 0 quantity
	bool isEmpty() const;
};

struct MyStore : Store {

	/// Info for arrived client waiting to depart
	struct WaitingClient {
		int client = -1; ///< Client index
		int departTime = -1; ///< Time of departure

		bool operator<(const WaitingClient &other) const {
			return departTime < other.departTime;
		}
	};

	/// Info for sent out worker
	struct WorkerDescriptor {
		int returnTime = -1; ///< Minute at which this worker will deliver resources
		ResourceType resource; ///< The resource this worker is restocking
	};

	/// Info for a client that was served at same time they arrived
	struct DepartedClient {
		int client = -1; ///< Client index
		ResourceStorage resources; ///< Resources client got
	};

	typedef std::vector<Client> ClientList;
	typedef std::list<WaitingClient> WaitList;
	typedef std::vector<int> ClientIndices;
	typedef std::vector<int> DepartLog;
	typedef std::list<WorkerDescriptor> SentWorkers;

	ActionHandler *actionHandler = nullptr;

	ResourceStorage resources; ///< Available resources
	ClientList clients; ///< All clients as they are added to the store
	int lastServed = -1; ///< Index of the last served client, used in advanceTo to skip already processed clients

	int workerCount = -1; ///< Number of available workers
	SentWorkers sentWorkers; ///< Workers sent out, ordered by return time
	ResourceStorage restock; ///< Resources in workers sent out

	int time = -1; ///< Current simulation time

	WaitList waiting; ///< List of clients, ordered by depart time
	WaitList newArrivals; ///< List of all clients that arrived this minute
	DepartLog departed; ///< List of clients that departed the same minute they arrived

	/// Add client to waiting queue, ordered by depart time
	void addWaitingClient(WaitList &waitList, int clientIndex) const;

	/// Process all workers that are returning at current time
	void returnWorkers();

	/// Check if there is enough resources to serve the client now
	bool canServeNow(int clientIndex) const;

	/// Deduct resources for a client and return info of what client departs with
	DepartedClient processDepartingClient(int clientIndex);

	/// Accept all clients starting from last served until all clients with arrive time == current
	void acceptClients();

	/// Handle all departing clients
	///	- All clients that arrived and departed same minute
	///	- All clients that can be served from the waiting list
	void departClients();

	/// Get needed resources for a client
	ResourceStorage getMissingResources(int clientIndex) const;

	/// Get number of workers currently in the store
	int idleWorkers() const;

	/// Choose the priority resource based on quantity
	static ResourceType resourcePriority(ResourceStorage resource);

	/// Process all clients that arrived this minute and send workers if needed
	void sendWorkers();

	/// Find the first minute an event will happen, or return INT_MAX
	int getNextEventTime() const;

	/// Find the last minute an event will happen
	int getLastEventTime() const;

	/// From: Store

	/// Advance the simulation up to a given time
	void advanceTo(int minute) override;

	void setActionHandler(ActionHandler *handler) override;

	void init(int startWorkerCount, int startBanana, int startSchweppes) override;

	void addClients(const Client *newClients, int count) override;

	int getBanana() const override;

	int getSchweppes() const override;
};
