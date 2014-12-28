#pragma once
#include "GameObject.h"

class PhysicsObject : public GameObject {
	float _vx, _vy, _ax, _ay;
	string _name;
	float _ovx, _ovy, _oax, _oay;
protected:
	virtual void draw() = 0;
	virtual void erase() = 0;

	virtual float vx() { return _ovx; }
	virtual float vy() { return _ovy; }
	virtual float ax() { return _oax; }
	virtual float ay() { return _oay; }
	
	void setVx(float vx) { _vx = vx; }
	void setVy(float vy) { _vy = vy; }
	void setAx(float ax) { _ax = ax; }
	void setAy(float ay) { _ay = ay; }
public:

	string name() { return _name; }

	PhysicsObject(string name, int posX, int posY, int width, int height, int padding = 0) : GameObject(name, posX, posY, width,height) {
		setVx(0);
		setVy(0);
		setAx(0);
		setAy(0);
		_ovx = _vx;
		_ovy = _vy;
		_oax = _ax;
		_oay = _ay;
	}

	virtual void updateValues() {
		GameObject::updateValues();
		_ovx = _vx;
		_ovy = _vy;
		_oax = _ax;
		_oay = _ay;
	}

	void update() {
		setPosition(x() + vx(), y() + vy() );
		setVx(vx() + ax());
		setVy(vy() + ay());
	}

	virtual bool checkHit(GameObject* otherObject) {

		if (!GameObject::checkHit(otherObject)) return false;

		if (vx() > 0) if (x() < otherObject->x()) return true;
		if (vx() < 0) if (x() + width() > otherObject->x() + otherObject->width()) return true;
		if (vy() > 0) if (y() < otherObject->y()) return  true;
		if (vy() < 0) if (y() + height() > otherObject->y() + otherObject->height()) return true;
		return false;
	}
};