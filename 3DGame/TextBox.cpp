#include "TextBox.h"

void TextBox::DrawBox(olc::PixelGameEngine* pge) {

	// TextBox
	pge->FillRect(position, size, text_box_color);
	pge->DrawRect(position, size, olc::WHITE);

	// TopBox
	pge->FillRect({ position.x, position.y - (8 * scale) }, scale * pge->GetTextSize(top_text), olc::WHITE);
	pge->DrawRect({ position.x, position.y - (8 * scale) }, scale * pge->GetTextSize(top_text), olc::Pixel(0, 0, 100));
}

void TextBox::RenderText(olc::PixelGameEngine* pge) {

	const olc::vi2d& width = pge->GetTextSize(text) * scale;

	int n_lines = (int)(width.x / size.x) + 1;
	int n_chars = size.x / (scale * 8);

	// Top text
	pge->DrawString({ position.x, position.y - (8 * scale) }, top_text, olc::BLUE, scale);

	std::string render_text = text.substr(0, text_pos);
	std::istringstream iss(render_text);
	std::string str;
	std::vector<std::string> strings;
	while (iss >> str) strings.push_back(str);

	olc::vu2d pos;
	int n = 0, count = 0;

	while (strings.size()) {
		bool is_space = false;
		if (n > strings[count].size() - 1) {
			n = 0; count++;
			if (count > strings.size() - 1) break;

			is_space = true;
			if (pos.x + strings[count].size() > n_chars) {
				is_space = false;
				pos.x = 0;
				pos.y++;
			}
		}

		if (pos.x > n_chars) {
			is_space = false;
			pos.x = 0;
			pos.y++;
		}

		pge->DrawString(position.x + scale * 8 * pos.x, position.y + scale * 8 * pos.y, is_space ? " " : "" + strings[count].substr(n++, 1), olc::WHITE, scale);
		pos.x++;
	}
}

void TextBox::Update(float dt) {

	if (IsTextComplete()) return;

	accumulator = std::fminf(accumulator + dt, delay);
	
	while (accumulator > inv_FPS) {
		accumulator -= inv_FPS;
		text_pos++;
	}
}

bool TextBox::IsTextComplete() {
	return text_pos > text.size();
}

void TextBox::Draw(olc::PixelGameEngine* pge) {
	DrawBox(pge);
	RenderText(pge);
}