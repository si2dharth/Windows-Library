#pragma once
#include <string>
using namespace std;

class GameObject {
	float _x, _y, _width, _height;
	int _padding;
	string _name;

	float _ox, _oy, _owidth, _oheight, _opadding;

	bool init;
protected:
	virtual void draw() = 0;
	virtual void erase() = 0;

	void setPosition(float X, float Y) { _x = X; _y = Y; }
	void setWidth(float Width) { _width = Width; }
	void setHeight(float Height) { _height = Height; }
	void setPadding(int padding) { _padding = padding; }
public:

	virtual float x() { return _ox; }
	virtual float y() { return _oy; }
	virtual float width() { return _owidth; }
	virtual float height() { return _oheight; }
	virtual int padding() { return _opadding; }
	string name() { return _name; }

	GameObject(string name, float posX, float posY, float width, float height, int padding = 0) {
		_name = name;
		setPosition(posX, posY);
		setWidth(width);
		setHeight(height);
		setPadding(0);
		init = false;
		_ox = _x;
		_oy = _y;
		_opadding = _padding;
		_owidth = _width;
		_oheight = _height;
		init = true;
	}

	virtual void updateValues() {
		erase();
		_ox = _x;
		_oy = _y;
		_opadding = _padding;
		_owidth = _width;
		_oheight = _height;
		extraUpdates();
		draw();
	}

	virtual void extraUpdates() {
		
	}

	virtual 
		void update() {
	}

	virtual bool checkHit(GameObject *otherObject) {
		if (x() > otherObject->x() + otherObject->width() + padding()) return false;
		if (y() > otherObject->y() + otherObject->height() + padding()) return false;
		if (x() + width() + padding() < otherObject->x()) return false;
		if (y() + height() + padding() < otherObject->y()) return false;
		return true;
	}

	virtual void hit(GameObject *otherObject) {

	}
};