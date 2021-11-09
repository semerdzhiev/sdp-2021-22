#define CATCH_CONFIG_MAIN

#include "interface.h"
#include "catch.hpp"

struct StoreEvent {
	enum Type {
		WorkerSend, WorkerBack, ClientDepart
	};

	Type type;
	int minute;

	union {
		struct Worker {
			ResourceType resource;
		} worker;

		struct Client {
			int index;
			int food;
			int water;
		} client;
	};
};

struct TestStore : ActionHandler {
	Store *impl = nullptr;
	std::vector<StoreEvent> log;

	TestStore()
		: impl(createStore()) {
		impl->setActionHandler(this);
	}

	void init(int workerCount, int startFood, int startWater) {
		impl->init(workerCount, startFood, startWater);
	}

	void newClient(int food, int water, int maxWaitTime) {
		impl->newClient(food, water, maxWaitTime);
	}

	void advanceTo(int minute) {
		impl->advanceTo(minute);
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

	void onClientDepart(int index, int minute, int food, int water) override {
		StoreEvent ev;
		ev.type = StoreEvent::ClientDepart;
		ev.minute = minute;
		ev.client.food = food;
		ev.client.water = water;
		log.push_back(ev);
	}
};

TEST_CASE("No workers, up to one client") {
	SECTION("No clients") {
		TestStore store;
		store.init(0, 0, 0);

		REQUIRE(store.log.size() == 0);
		store.advanceTo(0);
		REQUIRE(store.log.size() == 0);
		store.advanceTo(1);
		REQUIRE(store.log.size() == 0);

		store.advanceTo(100);
		REQUIRE(store.log.size() == 0);
	}
	
	SECTION("client without request") {
		TestStore store;
		store.init(0, 0, 0);

		REQUIRE(store.log.size() == 0);

		store.newClient(0, 0, 0);

		store.advanceTo(0);
		REQUIRE(store.log.size() == 1);

		StoreEvent last = store.log.back();
		REQUIRE(last.minute == 0);
		REQUIRE(last.type == StoreEvent::ClientDepart);
		REQUIRE(last.client.food == 0);
		REQUIRE(last.client.water == 0);
	}

	SECTION("water client") {
		TestStore store;
		store.init(0, 0, 0);

		REQUIRE(store.log.size() == 0);

		store.newClient(0, 1, 10);

		store.advanceTo(3);
		REQUIRE(store.log.size() == 0);

		store.advanceTo(10);
		REQUIRE(store.log.size() == 1);

		StoreEvent last = store.log.back();
		REQUIRE(last.minute == 10);
		REQUIRE(last.type == StoreEvent::ClientDepart);
		REQUIRE(last.client.food == 0);
		REQUIRE(last.client.water == 0);
	}

	SECTION("food client") {
		TestStore store;
		store.init(0, 0, 0);

		REQUIRE(store.log.size() == 0);

		store.newClient(1, 0, 10);

		store.advanceTo(5);
		REQUIRE(store.log.size() == 0);

		store.advanceTo(10);
		REQUIRE(store.log.size() == 1);

		StoreEvent last = store.log.back();
		REQUIRE(last.minute == 10);
		REQUIRE(last.type == StoreEvent::ClientDepart);
		REQUIRE(last.client.food == 0);
		REQUIRE(last.client.water == 0);
	}
}

TEST_CASE("One worker, up to one client") {
	SECTION("food client") {
		TestStore store;
		store.init(0, 0, 0);

		REQUIRE(store.log.size() == 0);

		store.newClient(1, 0, 10);

		store.advanceTo(0);
		REQUIRE(store.log.size() == 1);

		{
			const StoreEvent last = store.log.back();
			REQUIRE(last.minute == 0);
			REQUIRE(last.type == StoreEvent::WorkerSend);
			REQUIRE(last.worker.resource == ResourceType::Food);
		}

		store.advanceTo(60);
		REQUIRE(store.log.size() == 3); // worker send + client depart + worker back

		{
			const StoreEvent last = store.log.back();
			REQUIRE(last.minute == 60);
			REQUIRE(last.type == StoreEvent::WorkerBack);
			REQUIRE(last.worker.resource == ResourceType::Food);
		}
	}
}