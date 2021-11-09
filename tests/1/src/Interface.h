#pragma once

enum class ResourceType {
	food, water
};

struct ActionHandler {
	virtual void onWorkerSend(int minute, ResourceType resource) = 0;
	virtual void onWorkerBack(int minute, ResourceType resource) = 0;
	virtual void onClientDepart(int index, int minute, int food, int water) = 0;
};

struct Store {
	virtual void setActionHandler(ActionHandler *handler) = 0;
	virtual void init(int workerCount, int startFood, int startWater) = 0;
	virtual void newClient(int food, int water, int maxWaitTime) = 0;
	virtual void advanceTo(int minute) = 0;
};

Store *createStore();
