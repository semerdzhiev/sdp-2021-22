#define CATCH_CONFIG_MAIN

#include "interface.h"
#include "../../../group-G/source/common/catch.hpp"

#include <vector>

const int RESTOCK_TIME = 60;
const int RESTOCK_AMOUNT = 100;

typedef std::vector<Client> ClientList;

struct StoreEvent {
	enum Type {
		WorkerSend, WorkerBack, ClientDepart
	};

	Type type;
	int minute;

	struct Worker {
		ResourceType resource;
	} worker;

	struct Client {
		int index;
		int banana;
		int schweppes;
	} client;
};

struct TestStore : ActionHandler {
	Store *impl = nullptr;
	std::vector<StoreEvent> log;

	TestStore()
		: impl(createStore()) {
		impl->setActionHandler(this);
	}

	~TestStore() {
		delete impl;
	}

	TestStore(const TestStore &) = delete;
	TestStore &operator=(const TestStore &) = delete;

	void init(int workerCount, int startBanana, int startSchweppes) {
		impl->init(workerCount, startBanana, startSchweppes);
	}

	void advanceTo(int minute) {
		impl->advanceTo(minute);
	}

	int getBanana() const {
		return impl->getBanana();
	}

	int getSchweppes() const {
		return impl->getSchweppes();
	}

	void addClients(const ClientList &clients) {
		impl->addClients(clients.data(), clients.size());
	}

	void addClients(const Client &single) {
		impl->addClients(&single, 1);
	}

	void onWorkerSend(int minute, ResourceType resource) override {
		StoreEvent ev;
		ev.type = StoreEvent::WorkerSend;
		ev.minute = minute;
		ev.worker.resource = resource;
		log.push_back(ev);
	}

	void onWorkerBack(int minute, ResourceType resource) override {
		StoreEvent ev;
		ev.type = StoreEvent::WorkerBack;
		ev.minute = minute;
		ev.worker.resource = resource;
		log.push_back(ev);
	}

	void onClientDepart(int index, int minute, int banana, int schweppes) override {
		StoreEvent ev;
		ev.type = StoreEvent::ClientDepart;
		ev.minute = minute;
		ev.client.banana = banana;
		ev.client.schweppes = schweppes;
		ev.client.index = index;
		log.push_back(ev);
	}
};

#define LastEvent() (store.log.back())

TEST_CASE("No workers, empty store, up to one client") {
	TestStore store;
	store.init(0, 0, 0);

	SECTION("No events") {
		INFO("Without clients, no events should be generated");
		REQUIRE(store.log.size() == 0);
		store.advanceTo(0);
		REQUIRE(store.log.size() == 0);
		store.advanceTo(1);
		REQUIRE(store.log.size() == 0);

		store.advanceTo(100);
		REQUIRE(store.log.size() == 0);
	}

	SECTION("Advance before depart time") {
		store.addClients(Client{0, 1, 1, 1});
		store.advanceTo(0);
		INFO("Must not generate event before time is advanced to its time");
		REQUIRE(store.log.size() == 0);
	}

	SECTION("Depart time") {
		INFO("maxWaitTime == 1 means, client will wait 1 minute (arrive at 0, depart at 1)");
		INFO("advanceTo(<time>), should generate all events that happen up to and including <time>");
		store.addClients(Client{0, 1, 1, 1});
		store.advanceTo(1);
		REQUIRE(store.log.size() == 1);
	}

	SECTION("client without request") {
		INFO("Client with wait time 0, must generate event at the time of arrival");
		store.addClients(Client{0, 0, 0, 0});
		store.advanceTo(0);
		REQUIRE(store.log.size() == 1);

		INFO("Client without any request should depart empty - (0 banana, 0 schweppes)");
		REQUIRE(LastEvent().minute == 0);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 0);
		REQUIRE(LastEvent().client.schweppes == 0);
	}

	SECTION("advance before client departs") {
		store.addClients(Client{0, 1, 1, 10});

		store.advanceTo(3);
		INFO("client must not depart before its max wait time");
		REQUIRE(store.log.size() == 0);
	}
}

TEST_CASE("No workers, full store") {
	TestStore store;
	store.init(0, 1000, 1000);
	const ClientList three = {
		Client{0, 0, 10, 10},
		Client{0, 10, 0, 3},
		Client{0, 10, 10, 5}
	};

	SECTION("Non waiting client") {
		store.addClients(Client{0, 10, 0, 0});
		store.advanceTo(0);
		INFO("Client must depart same at the time of arrival when store has enough resources");
		REQUIRE(store.log.size() == 1);
		REQUIRE(store.log[0].type == StoreEvent::ClientDepart);
	}

	SECTION("Client with wait time") {
		store.addClients(Client{0, 10, 0, 10});
		store.advanceTo(0);
		INFO("Client must depart same at the time of arrival when store has enough resources");
		REQUIRE(store.log.size() == 1);
		REQUIRE(store.log[0].type == StoreEvent::ClientDepart);
	}

	SECTION("Multiple clients") {
		store.addClients(three);
		store.advanceTo(0);
		INFO("Client must depart same at the time of arrival when store has enough resources");
		REQUIRE(store.log.size() == 3);
		REQUIRE(store.log[0].type == StoreEvent::ClientDepart);
		REQUIRE(store.log[1].type == StoreEvent::ClientDepart);
		REQUIRE(store.log[2].type == StoreEvent::ClientDepart);
	}

	SECTION("Client indices") {
		store.addClients(three);
		store.advanceTo(0);
		INFO("Indices must be correct");
		REQUIRE(store.log[0].client.index == 0);
		REQUIRE(store.log[1].client.index == 1);
		REQUIRE(store.log[2].client.index == 2);
	}
}

TEST_CASE("Multiple stores") {
	TestStore bananaStore;
	bananaStore.init(0, 100, 0);
	TestStore schweppesStore;
	schweppesStore.init(0, 0, 100);

	SECTION("Two stores") {
		INFO("Multiple stores must be ebable to exist at the same time");

		REQUIRE(bananaStore.getBanana() == 100);
		REQUIRE(bananaStore.getSchweppes() == 0);

		REQUIRE(schweppesStore.getBanana() == 0);
		REQUIRE(schweppesStore.getSchweppes() == 100);
	}

	SECTION("Clients to one of the stores") {
		bananaStore.addClients(Client{0, 10, 0, 10});
		bananaStore.advanceTo(0);
		schweppesStore.advanceTo(0);

		INFO("New client to one store must not generate event in the other store");
		REQUIRE(bananaStore.log.size() == 1);
		REQUIRE(schweppesStore.log.size() == 0);
	}

	SECTION("Clients to both stores") {
		bananaStore.addClients(Client{0, 5, 0, 0});
		schweppesStore.addClients(Client{0, 0, 10, 0});

		bananaStore.advanceTo(0);
		schweppesStore.advanceTo(0);

		INFO("Both stores should generate valid evenets");
		REQUIRE(bananaStore.log.back().type == StoreEvent::ClientDepart);
		REQUIRE(bananaStore.log.back().client.banana == 5);

		REQUIRE(schweppesStore.log.back().type == StoreEvent::ClientDepart);
		REQUIRE(schweppesStore.log.back().client.schweppes == 10);
	}
}

TEST_CASE("Example") {
	TestStore store;
	store.init(5, 0, 0);

	store.addClients({
		Client{0, 10, 0, 10},
		Client{45, 35, 0, 30},
		Client{46, 30, 20, 100},
		Client{200, 10, 10, 1}
	});

	SECTION("First client") {
		store.advanceTo(0);
		INFO("First client will trigger 1 worker");
		REQUIRE(store.log.size() == 1);
		REQUIRE(LastEvent().type == StoreEvent::WorkerSend);
	}

	SECTION("First client") {
		store.advanceTo(10);
		INFO("First client must depart without anything");
		REQUIRE(store.log.size() == 2);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 0);
	}

	SECTION("Last client") {
		store.advanceTo(200);
		INFO("Last client departs same time as arrival");
		REQUIRE(store.log.size() == 8);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 10);
		REQUIRE(LastEvent().client.schweppes == 10);
	}

	SECTION("Remaining resources") {
		store.advanceTo(500);
		int bananas = 0;
		int schweppes = 0;
		for (int c = 0; c < store.log.size(); c++) {
			const StoreEvent &ev = store.log[c];
			if (ev.type == StoreEvent::WorkerBack) {
				REQUIRE(store.log[c].worker.resource >= ResourceType::banana);
				REQUIRE(store.log[c].worker.resource <= ResourceType::schweppes);
				if (ev.worker.resource == ResourceType::banana) {
					bananas += RESTOCK_AMOUNT;
				} else if (ev.worker.resource == ResourceType::schweppes) {
					schweppes += RESTOCK_AMOUNT;
				}
			} else if (ev.type == StoreEvent::ClientDepart) {
				bananas -= ev.client.banana;
				schweppes -= ev.client.schweppes;
			}
		}

		INFO("Stock amount - client depart amounth must be what is left in the store");
		REQUIRE(store.getBanana() == bananas);
		REQUIRE(store.getSchweppes() == schweppes);
	}
}

TEST_CASE("Workers can be sent out only when needed") {
	TestStore store;
	store.init(1, 100, 0);

	store.addClients({
		Client{0, 100, 0, 1}, // this client will get everything
		Client{10, 1, 0, 1}
	});


	SECTION("Before second client") {
		store.advanceTo(9);

		INFO("Worker must not be sent before client arrives");
		REQUIRE(store.log.size() == 1);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(store.getBanana() == 0);
	}

	SECTION("After second client") {
		store.advanceTo(10);

		INFO("Worker must be sent the same minute second clients arrives");
		REQUIRE(store.log.size() == 2);
		REQUIRE(LastEvent().type == StoreEvent::WorkerSend);
		REQUIRE(LastEvent().minute == 10);
	}
}

TEST_CASE("Workers must not be sent if resource will be available before client departs") {
	TestStore store;
	store.init(2, 0, 0);

	store.addClients({
		Client{0, 10, 0, 200},
		Client{10, 10, 0, 200}
	});

	SECTION("First client must trigger a worker") {
		store.advanceTo(5);
		REQUIRE(store.log.size() == 1);
	}

	SECTION("Second client must not trigger a worker") {
		store.advanceTo(15);
		REQUIRE(store.log.size() == 1);
	}
}

TEST_CASE("Clients depart and take what they can") {
	TestStore store;
	store.init(5, 10, 0);

	store.addClients({
		Client{0, 0, 10, 0}, // Trigger worker sent for schweppes
		Client{1, 20, 0, 5}
	});

	SECTION("Sent out workers") {
		store.advanceTo(3);
		INFO("Store must send 2 workers, and 1 client has departed");
		REQUIRE(store.log.size() == 3);
	}

	SECTION("Client departs with only part of requirement") {
		store.advanceTo(1 + 5);

		INFO("Client must take whatever is available");
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 10);
		REQUIRE(LastEvent().client.schweppes == 0);
	}
}

TEST_CASE("Clients arrive/depart in mixed order") {
	TestStore store;
	store.init(2, 10, 0);

	store.addClients({
		Client{0, 10, 10, 20},
		Client{10, 10, 0, 0}
	});

	SECTION("One worker must be sent") {
		store.advanceTo(0);

		INFO("First client must trigger a worker to restock schweppes");
		REQUIRE(store.log.size() == 1);
		REQUIRE(LastEvent().type == StoreEvent::WorkerSend);
		REQUIRE(LastEvent().worker.resource == ResourceType::schweppes);
	}

	SECTION("Second client") {
		store.advanceTo(10);

		INFO("Second client comes at min 10, but waits 0, departs at min 10");
		REQUIRE(store.log.size() == 2);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 10);
		REQUIRE(LastEvent().client.index == 1);
	}

	SECTION("First client") {
		store.advanceTo(20);

		INFO("First client departs nothing after second client");
		REQUIRE(store.log.size() == 3);
		REQUIRE(LastEvent().type == StoreEvent::ClientDepart);
		REQUIRE(LastEvent().client.banana == 0);
		REQUIRE(LastEvent().client.index == 0);
	}
}
