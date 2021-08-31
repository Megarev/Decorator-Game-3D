#include "Button.h"

Button::Button(const olc::vi2d& p, const olc::vi2d& s, const olc::Pixel& col1, const olc::Pixel& col2, const olc::Pixel& col3, const std::string& str)
	: position(p), size(s), text(str) {
	color[0] = col1;
	color[1] = col2;
	color[2] = col3;
}

void Button::Input(olc::PixelGameEngine* pge) {
	const olc::vi2d& m_pos = pge->GetMousePos();
	current = color[0];

	if (m_pos.x > position.x && m_pos.x < position.x + size.x &&
		m_pos.y > position.y && m_pos.y < position.y + size.y) {
		current = color[1];

		if (pge->GetMouse(0).bHeld) {
			current = color[2];
		}

		if (pge->GetMouse(0).bReleased) {
			is_pressed = true;
		}
	}
}

void Button::Render(olc::PixelGameEngine* pge) {
	int32_t scale = 2;
	pge->FillRect(position, size, current);
	pge->DrawString(position + size / 2.0f - olc::vi2d{ 2 * scale, 2 * scale }, text, olc::WHITE, 2);
}

void Button::Render(olc::PixelGameEngine* pge, const olc::vi2d& text_pos) {
	int32_t scale = 2;
	pge->FillRect(position, size, current);
	pge->DrawString(position + text_pos, text, olc::WHITE, 2);
}
