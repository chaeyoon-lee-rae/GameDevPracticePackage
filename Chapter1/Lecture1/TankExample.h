#pragma once

#include "Game2D.h"
#include <vector>
#include <deque>

namespace jm
{
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f); // 회전하는 기능

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt;
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		// 총알이 발사가 되었을 때에만 존재 -> 포인터
		MyBullet *bullet = nullptr;
		//TODO: allow multiple bullets
		std::vector<MyBullet*> vBulletPtr;
		//TODO: delete bullets when they go out of the screen

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			//vBulletPtr.reserve(100);
		}

		~TankExample()
		{
			if (vBulletPtr.size()) {
				for (int idx = 0; idx < vBulletPtr.size(); ++idx)
					delete vBulletPtr[idx];
			}
		}

		void update() override
		{
			// move tank
			// 왼화살표 키가 눌렸는지?
			// 게임 개발 API를 사용하거나 GUI 프로그래밍 할 때에는 콜백 함수들을 많이 사용
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep(); 
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			// 눌렸다가 떨어졌는지? 등등 update함수가 호출되면서 매번 체크
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE)) 
			{
				bullet = new MyBullet;
				bullet->center = tank.center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;
				bullet->velocity = vec2(2.0f, 0.0f);
				vBulletPtr.push_back(bullet);
			}

			if (vBulletPtr.size()) 
			{
				int cnt=0;
				for (int idx=0; idx < vBulletPtr.size(); ++idx)
				{
					vBulletPtr[idx]->update(getTimeStep());
					// **TODO: GUI 속성 사용해서 화면 가장자리를 벗어나면 없어지게끔 하기
					if (vBulletPtr[idx]->center.x > 5) 
						delete vBulletPtr[idx], ++cnt;
				}
				vBulletPtr.erase(vBulletPtr.begin(), vBulletPtr.begin() + cnt);
			}

			// rendering
			tank.draw();
			if (vBulletPtr.size()) {
				for (int idx = 0; idx < vBulletPtr.size(); ++idx)
					vBulletPtr[idx]->draw();
			}
		}
	};
}