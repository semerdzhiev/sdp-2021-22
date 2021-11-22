#include "interface.h"

/// This is sample empty implementation you can place your solution here or delete this and include tests to your solution


struct MyStore : Store {
	ActionHandler *actionHandler = nullptr;

	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override {
		
	}

	void addClients(const Client *clients, int count) override {
		
	}

	void advanceTo(int minute) override {
		actionHandler->onWorkerSend(0, ResourceType::banana);
		actionHandler->onWorkerBack(0, ResourceType::schweppes);
		actionHandler->onClientDepart(0, 0, 1, 2);
	}

	virtual int getBanana() const {
		return 0;
	}

	virtual int getSchweppes() const {
		return 0;
	}
};

Store *createStore() {
	return new MyStore();
}