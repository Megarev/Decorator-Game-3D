#pragma once
#include "olcPixelGameEngine.h"

class TextBox {
public:
	olc::vi2d position, size;

	std::string top_text, text;
	uint32_t text_pos = 0;
	int32_t scale = 2u;

	olc::Pixel text_box_color = olc::Pixel(rand() % 256, rand() % 256, rand() % 256);

	float inv_FPS = 1.0f / 15.0f;
	float accumulator = 0.0f, delay = 0.1f;
private:
	void DrawBox(olc::PixelGameEngine* pge);
	void RenderText(olc::PixelGameEngine* pge);
public:
	TextBox() {}
	TextBox(const olc::vi2d& p, const olc::vi2d& s)
		: position(p), size(s) {}
	TextBox(int px, int py, int sx, int sy)
		: position(px, py), size(sx, sy) {}

	bool IsTextComplete();

	void Update(float dt);
	void Draw(olc::PixelGameEngine* pge);
};