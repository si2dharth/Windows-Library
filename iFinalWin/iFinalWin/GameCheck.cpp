#include "iBase.h"
#include "PhysicsObject.h"
#include "GameEnv.h"


namespace GameCheck {
	class Wall : public GameObject {
		Window *containingWindow;
	public:
		Wall(Window *W, string name, int x, int y, int width, int height, int padding) : GameObject(name, x, y, width, height, padding) { containingWindow = W;  };
		
		virtual void draw() {
			containingWindow->SetBackColor(0, 0, 0);
			containingWindow->SetColor(0, 0, 0);
			containingWindow->DrawRectangle(x(), y(), x() + width(), y() + height());
		}

		virtual void erase() {};

		virtual bool checkHit(GameObject*) { return false; }
	};

	class Ball : public PhysicsObject {
		Window *containingWindow;
	public:
		float mass;
		Ball(Window *W, string name, int x, int y, int width, int height, int padding) : PhysicsObject(name, x, y, width, height, padding) {
			containingWindow = W;
			mass = 1;
			 setAy(0.1);
		}

		virtual void draw() {
			containingWindow->SetBackColor(0, 0, 0);
			containingWindow->SetColor(0, 0, 0);
			containingWindow->DrawEllipse(x(), y(), width(), height());
		}

		virtual void erase() {
			containingWindow->SetBackColor(255, 255, 255);
			containingWindow->SetColor(255, 255, 255);
			containingWindow->DrawEllipse(x(), y(), width(), height());
		}

		virtual void hit(GameObject *object) {
			if (object->name() == "floor" || object->name() == "ceiling") setVy(-(vy())); else
				if (object->name() == "ball2" || object->name() == "ball") hit((Ball*)object); else setVx(-vx());
		}

		virtual void hit(Ball *object) {
			setVx(object->vx()*object->mass / mass); object->setVx(vx() *mass / object->mass);
			setVy(object->vy()*object->mass / mass); object->setVy(vy()*mass / object->mass);
		}

		void changeDir(Window *W, KeyEventParams *KE) {
			if (KE->key == 'W') setVy(vy() - 0.5);
			if (KE->key == 'S') setVy(vy() + 0.5);
			if (KE->key == 'D') setVx(vx() + 0.5);
			if (KE->key == 'A') setVx(vx() - 0.5);
		}
	};

	Environment *GE;

	void updateEnv() {
		GE->update();
	}

	void drawEnv() {
		//GE->draw();
	}


	int Run(char args[]){
		Window W;
		Environment E;
		Ball *B = new Ball(&W, "ball", W.GetWidth() / 2, 100, 30, 30, 5);
		Ball *B2 = new Ball(&W, "ball2", W.GetWidth() / 2 + 50, 90, 50, 50, 5);
		B2->mass = 2;
		GE = &E;
		E.addObject(B);
		E.addObject(B2);
		E.addObject(new Wall(&W, "floor", 0, W.GetHeight() - 200, W.GetWidth(), 50, 5));
		E.addObject(new Wall(&W, "left", 0, 0, 50, W.GetHeight(), 5));
		E.addObject(new Wall(&W, "right", W.GetWidth() - 65, 0, 50, W.GetHeight(), 5));
		E.addObject(new Wall(&W, "ceiling", 0, 0, W.GetWidth(), 50, 5));
		W.handler(EventName::KeyUp)->addHandler(B, &Ball::changeDir);
		W.handler(Timer)->addHandler(updateEnv);
		W.CreateTimer(5);
		//W.handler(Timer)->addHandler(drawEnv);
		//W.CreateTimer(33)
		Window::Run();
		return 0;
	}
}


int Run(char args[]) {
	return GameCheck::Run(args);
}