#include "Transitions.h"

void Transitions::Update(uint8_t speed) {
	if (IsTransitionComplete()) {
		return;
	}
	alpha += speed;
}

void Transitions::Render(olc::PixelGameEngine* pge) {
	pge->SetPixelMode(olc::Pixel::ALPHA);
	pge->FillRectDecal({ 0.0f, 0.0f }, { (float)pge->ScreenWidth(), (float)pge->ScreenHeight() }, olc::Pixel(0, 0, 0, alpha));
	pge->SetPixelMode(olc::Pixel::NORMAL);
}