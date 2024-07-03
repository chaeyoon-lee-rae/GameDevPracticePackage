#pragma once

#include "Game2D.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/

	class Person
	{
	private:
		vec2 center = { 0.0f, 0.0f };
		
		void _drawHeadAndBody() const
		{
			// gold face
			beginTransformation();
			translate(center);
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::gold, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f); // while eye
			endTransformation();

			// red body
			beginTransformation();
			translate(center);
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();
		}
	public:
		void setCenter(const int& order)
		{
			center = { -1.0f + order * 0.5f, 0.0f };
		}

		void shoot(const float& time) const
		{
			_drawHeadAndBody();

			// yellow arm front
			beginTransformation();
			translate(center);
			rotate(90.0f);
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::yellow, 0.05f, 0.36f);
			endTransformation();

			// green leg front
			beginTransformation();
			translate(center);
			translate(0.0f, -0.6f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			// beam
			beginTransformation();
			translate(center);
			translate(0.39f + 0.4f * 5 * time, 0.01f);
			//scale(1.1f * 5 * time, 1.0f);
			drawFilledBox(Colors::skyblue, 0.8f * 5 * time, 0.1f);
			endTransformation();

		}

		void walk(const float& time) const
		{
			// yellow arm back
			beginTransformation();
			translate(center);
			rotate(-sin(time * 5.0f) * 30.0f);					// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::yellow, 0.05f, 0.36f);
			endTransformation();

			// green leg back
			beginTransformation();
			translate(center);
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(-sinf(time * 5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			_drawHeadAndBody();

			// yellow arm front
			beginTransformation();
			translate(center);
			rotate(sin(time * 5.0f) * 30.0f);					// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::yellow, 0.05f, 0.36f);
			endTransformation();

			// green leg front
			beginTransformation();
			translate(center);
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time * 5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();
		}
	};

	class WalkingPerson : public Game2D
	{
		float time, timeShoot;
		std::vector<Person*> vPerson;
		int numPerson;

	public:
		WalkingPerson()
			: time(0.0f), timeShoot(0.0f), numPerson(0)
		{
			vPerson.reserve(50);
		}

		~WalkingPerson()
		{
			if (vPerson.size())
				for (int i = 0; i < vPerson.size(); ++i)
					delete vPerson[i];
		}

		void update() override
		{
			if (isKeyPressedAndReleased(GLFW_KEY_TAB)) {
				Person* prsn = new Person;
				vPerson.push_back(prsn);
				vPerson[numPerson]->setCenter(numPerson);
				++numPerson;
			}

			if (isKeyPressed(GLFW_KEY_SPACE))
			{
				time = 0.0f;
				for (int i = 0; i < vPerson.size(); ++i)
					vPerson[i]->shoot(timeShoot);
				timeShoot += this->getTimeStep();
			}
			else 
			{
				timeShoot = 0.0f;
				for (int i = 0; i < vPerson.size(); ++i)
					vPerson[i]->walk(time);
				time += this->getTimeStep();
			}
		}
	};
}
