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

				rotate(time * 90.0f); // �ٽ� rotate �߰�
				translate(0.5f, 0.0f);
				drawFilledCircle(Colors::blue, 0.1f);		// Earth

				rotate(time * 120.0f); // rotate �߰�
				translate(0.2f, 0.0f);
				drawFilledCircle(Colors::yellow, 0.05f);	// Moon
			}
			endTransformation(); // ū �ǹ� ����? ������ update ȣ��� ������ �ʱ�ȭ?

			time += this->getTimeStep();
		}
	};
}