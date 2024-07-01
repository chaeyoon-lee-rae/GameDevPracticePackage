#pragma once

#include "Game2D.h"

namespace jm
{
	class SolarSystem : public Game2D
	{
		float time = 0.0f;

	public:
		void update() override
		{
			beginTransformation(); 
			{
				drawFilledStar(Colors::gold, 0.2f, 0.13f);	// Sun

				rotate(time * 90.0f); // 다시 rotate 추가
				translate(0.5f, 0.0f);
				drawFilledCircle(Colors::blue, 0.1f);		// Earth

				rotate(time * 120.0f); // rotate 추가
				translate(0.2f, 0.0f);
				drawFilledCircle(Colors::yellow, 0.05f);	// Moon
			}
			endTransformation(); // 큰 의미 없음? 어차피 update 호출될 때마다 초기화?

			time += this->getTimeStep();
		}
	};
}