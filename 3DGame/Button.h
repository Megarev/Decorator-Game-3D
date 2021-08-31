#pragma once
#include "olcPixelGameEngine.h"

class Button {
public:
	olc::vi2d position, size;
	bool is_render = false;
	olc::Pixel color[3];
	olc::Pixel current;
	bool is_pressed = false;
	std::string text;
public:
	Button() {}
	Button(const olc::vi2d& p, const olc::vi2d& s, const olc::Pixel& col1, const olc::Pixel& col2, const olc::Pixel& col3, const std::string& str);

	void Input(olc::PixelGameEngine* pge);

	void Render(olc::PixelGameEngine* pge);
	void Render(olc::PixelGameEngine* pge, const olc::vi2d& text_pos);
};
