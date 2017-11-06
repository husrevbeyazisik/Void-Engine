#pragma once
#include "Vengine.h"



Vengine::Vengine()
{
}



Vengine::~Vengine()
{
}

float y, ySpeed;

void Vengine::Start()
{
	y = 0.0;
	ySpeed = 0.0f;
}
void Vengine::Update()
{
	ySpeed += 1.0f;
	y += ySpeed;
	if (y > 600)
	{
		y = 600;
		ySpeed = -30.0f;
	}
}
void Vengine::Render(Graphics* gfx)
{
	gfx->ClearScreen(0.0f, 0.0f, 0.5f);

	gfx->DrawCircle(375.0f, y, 50.0f, 1.0f, 0.0, 0.0, 1.0);

}
void Vengine::Destroy()
{

}
