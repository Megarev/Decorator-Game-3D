#pragma once
#include "olcPixelGameEngine.h"

class Transitions {
public:
	uint8_t alpha = 0;

	void Update(uint8_t speed);

	void Render(olc::PixelGameEngine* pge);

	bool IsTransitionComplete() const { return alpha >= 250; }
};