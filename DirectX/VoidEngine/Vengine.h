#pragma once
#include "Graphics.h"

class Vengine
{


public:
	Vengine();
	~Vengine();


	static void Start();
	static void Update();
	static void Render(Graphics* gfx);
	static void Destroy();
};

