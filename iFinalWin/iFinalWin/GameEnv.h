#pragma once
#include "GameObject.h"

class Environment {
	list<GameObject*> objects;
public:
	Environment() {}

	void addObject(GameObject* object) {
		objects.push_back(object);
	}

	void removeObject(string objectName) {
		list<GameObject*>::iterator foundItem = objects.begin();

		while (foundItem != objects.end()) {
			if ((*foundItem)->name() == objectName) break;
		}
		if (foundItem != objects.end()) objects.erase(foundItem);
	}

	virtual void update() { 
		
		for each (GameObject* object in objects) {
			for each (GameObject* otherObject in objects) {
				if (otherObject == object) continue;
				if (object->checkHit(otherObject)) object->hit(otherObject);
			}
		}

		for each (GameObject* object in objects) {
			object->updateValues();
			object->update();
		}
	}
};