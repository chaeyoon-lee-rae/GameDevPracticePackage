#pragma once

#include "Game2D.h"

/*
OpenGL로 춘식이 그리기
*/

namespace jm
{

	class FaceExample : public Game2D
	{
	private:
		struct choonsikColor
		{
			const RGB black		{ 44, 46, 47 };
			const RGB yellow	{ 251, 212, 114 };
			const RGB pink		{ 247, 147, 98 };
			const RGB red		{ 210, 75, 46 };
			const RGB white		{ 255, 255, 255 };
		};
		choonsikColor csColor;
		
		struct drawParam
		{
			RGB color;
			float size;
			vec2 tran;
			float rot;
			vec2 scaleSize;
			float outline;

			drawParam(const RGB& color = RGB{0.0f, 0.0f, 0.0f},
					  const float& size = 1.0f, 
					  const vec2& tran = {0.0f,0.0f},
					  const float& rot = 0.0f, 
					  const vec2& scaleSize = {1.0f, 1.0f},
					  const float& outline=0.0f)
			: color(color), size(size), tran(tran), rot(rot), 
				scaleSize(scaleSize), outline(outline) 
			{}

			friend std::ostream& operator << (std::ostream& out, const drawParam& dp) 
			{
				//out << "color : " << dp.color << '\n';
				out << "size : " << dp.size << '\n';
				out << "tran : " << dp.tran << '\n';
				out << "rot : " << dp.rot << '\n';
				out << "scaleSize : " << dp.scaleSize << '\n';
				out << "outline : " << dp.outline << '\n';
				return out;
			}
		};

		struct PosXY
		{
			float posX;
			float posY;
		};

		const float outlineThick;

		drawParam faceParam;
		drawParam earParam;
		drawParam eyeParam;
		drawParam blushParam;
		drawParam mouthParam;
		drawParam snoutParam;
		drawParam snoutParam2;
		drawParam whiskParam;

		float earRot;
		PosXY earPos;
		PosXY eyePos;
		PosXY blushPos;
		PosXY snoutPos;
		float snoutRot;
		PosXY whiskPos;
		float whiskRot;

	public:
		FaceExample() 
			: outlineThick(0.03f)
		{
			initialize();
			std::cout << "initialized" << std::endl;
		}

		void initialize() {
			faceParam.size = 0.75;
			faceParam.scaleSize = { 1.1f,1.0f };

			earParam.size = 0.2f;
			earParam.scaleSize = { 1.5f,1.0f };
			earRot = 60.f;
			earPos = { 0.4f, 0.43f };

			eyeParam.color = csColor.black;
			eyeParam.size = 0.05f;
			eyePos = { 0.28f, 0.2f };

			blushParam.color = csColor.pink;
			blushParam.size = 0.2f;
			blushParam.scaleSize = { 1.13f, 1.0f };
			blushPos = { 0.4f, -0.1f };

			mouthParam.size = 0.08f;
			mouthParam.scaleSize = { 1.0f, 1.4f };
			mouthParam.tran = { 0.0f, -0.2f };

			snoutParam.size = 0.11f;
			snoutParam.scaleSize = { 1.25f, 1.0f };
			snoutRot = 30.0f;
			snoutPos = { -0.1f, -0.1f };

			snoutParam2.size = 0.05f;
			snoutParam2.scaleSize = { 2.4f, 1.0f };
			snoutParam2.tran = { 0.0f, -0.02f };

			whiskParam.color = csColor.black;
			whiskParam.size = 0.025f;
			whiskParam.scaleSize = { 15.0f, 1.0f };
			whiskParam.tran = { 0.0f, -0.1f };
			whiskRot = 20.0f;
		}

		void update() override
		{
			//draw face outline
			faceParam.color = csColor.black;
			faceParam.outline = outlineThick;
			drawGeo(faceParam);

			// draw ear outline
			// update function -> 계속 값을 넣어줘야함
			earParam.color = csColor.black;
			earParam.outline = outlineThick; 
			earParam.tran = { earPos.posX, earPos.posY }; 
			earParam.rot = earRot;
			drawGeo(earParam);

			earParam.tran = { -earPos.posX, earPos.posY };
			earParam.rot = -earRot;
			drawGeo(earParam);

			// draw face
			faceParam.color = csColor.yellow;
			faceParam.outline = 0.0f;
			drawGeo(faceParam);

			// draw ear
			earParam.color = csColor.yellow;
			earParam.outline = 0.0f;
			earParam.tran = { earPos.posX, earPos.posY };
			earParam.rot = earRot;
			drawGeo(earParam);

			earParam.tran = { -earPos.posX, earPos.posY };
			earParam.rot = -earRot;
			drawGeo(earParam);

			// draw eyes
			eyeParam.tran = { eyePos.posX, eyePos.posY };
			drawGeo(eyeParam);

			eyeParam.tran = { -eyePos.posX, eyePos.posY };
			drawGeo(eyeParam);

			// draw blush
			blushParam.tran = { blushPos.posX, blushPos.posY };
			drawGeo(blushParam);

			blushParam.tran = { -blushPos.posX, blushPos.posY };
			drawGeo(blushParam);

			// draw mouth outline
			mouthParam.color = csColor.black;
			mouthParam.outline = outlineThick;
			drawGeo(mouthParam);

			// draw mouth
			mouthParam.color = csColor.red;
			mouthParam.outline = 0.0f;
			drawGeo(mouthParam);

			// draw whiskers
			whiskParam.rot = whiskRot;
			drawGeo(whiskParam);

			whiskParam.rot = -whiskRot;
			drawGeo(whiskParam);

			// draw snout outline
			snoutParam.color = csColor.black;
			snoutParam.outline = outlineThick;
			snoutParam.rot = snoutRot;
			snoutParam.tran = { snoutPos.posX, snoutPos.posY };
			drawGeo(snoutParam);

			snoutParam.rot = -snoutRot;
			snoutParam.tran = { -snoutPos.posX, snoutPos.posY };
			drawGeo(snoutParam);

			snoutParam2.color = csColor.black;
			snoutParam2.outline = outlineThick;
			drawGeo(snoutParam2);

			// draw snout
			snoutParam.color = csColor.white;
			snoutParam.outline = 0.0f;
			snoutParam.rot = snoutRot;
			snoutParam.tran = { snoutPos.posX, snoutPos.posY };
			drawGeo(snoutParam);

			snoutParam.rot = -snoutRot;
			snoutParam.tran = { -snoutPos.posX, snoutPos.posY };
			drawGeo(snoutParam);

			snoutParam2.color = csColor.white;
			snoutParam2.outline = 0.0f;
			drawGeo(snoutParam2);
		}

		void drawGeo(const drawParam& dp)
		{
			beginTransformation();
			{
				drawCircle(dp);
			}
			endTransformation();
		}

		void drawCircle(const drawParam& dp) 
		{
			translate(dp.tran);
			rotate(dp.rot);
			scale(dp.scaleSize);
			drawFilledCircle(dp.color, dp.size + dp.outline);
		}
	};
}