#include "interface.h"

struct MyStore : Store {
	ActionHandler *actionHandler = nullptr;

	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startFood, int startWater) override {
		
	}

	void newClient(int food, int water, int maxWaitTime) override {
		
	}

	void advanceTo(int minute) override {
		actionHandler->onWorkerSend(0, ResourceType::food);
		actionHandler->onWorkerBack(0, ResourceType::water);
		actionHandler->onClientDepart(0, 0, 1, 2);
	}
};

Store *createStore() {
	return new MyStore();
}