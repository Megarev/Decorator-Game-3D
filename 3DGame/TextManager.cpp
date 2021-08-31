#include "TextManager.h"

void TextManager::Input() {
	box.text = level->lines[level->index];
	box.top_text = "Decorator";
}

bool TextManager::GetComplete() {
	return level->IsAllLinesComplete() && box.IsTextComplete();
}

void TextManager::Next() {

	switch (level_index) {
	case 0:
		level = std::make_unique<Text_2>();
		level_index++;
		break;
	case 1:
		level = std::make_unique<Text_3>();
		level_index++;
		break;
	case 2:
		level = std::make_unique<Text_4>();
		level_index++;
		break;
	case 3:
		level = std::make_unique<Text_5>();
		level_index++;
		break;
	case 4:
		level = std::make_unique<Text_Complete>();
		level_index++;
		break;
	}
}

bool TextManager::IsUpdate(float dt) {

	if (box.text_pos > level->lines[level->index].size() - 1) {
		accumulator += speed * dt;

		if (accumulator > delay) {
			accumulator = 0.0f;
			if (level->Step(box.text_pos)) {
				Input();
				box.text_pos = 0;
			}
		
			return true;
		}
	}
	
	return false;
}

bool TextManager::Logic(float dt) {
	if (box.IsTextComplete()) return false;
	box.Update(dt);
	return true;
}

void TextManager::Render(olc::PixelGameEngine* pge) {
	box.Draw(pge);
}

bool Text::IsAllLinesComplete() {
	return index >= lines.size() - 1;
}

bool Text::Step(int text_pos) {
	if (text_pos > lines[index].size()) {
		if (index < lines.size() - 1) {
			index++;
			return true;
		}
	}
	return false;
}

Text_1::Text_1() {
	lines = {
		"Hi, nice to meet you!",
		" ", // Pause
		"Q1: What do you like, tranquility or chaos?"
	};
}

Text_2::Text_2() {
	lines = {
		" ", // Pause
		"Ok, good!",
		"Q2: Do you prefer round or pointy?"
	};
}


Text_3::Text_3() {
	lines = {
		" ", // Pause
		"The new addition is looking pretty cute!",
		"Q3: Do you fancy wood or concrete?"
	};
}

Text_4::Text_4() {
	lines = {
		" ", // Pause
		"Almost there!",
		"How about adding some fresh air?",
		"Q4: Do you like the modern world or the simple life?"
	};
}

Text_5::Text_5() {
	lines = {
		" ", // Pause
		"We're done!",
		"Just one more question",
		"Q5: Do you enjoy bright or dark colors?"
	};
}

Text_Complete::Text_Complete() {

	lines = {
		" ", // Pause
		"So, how was my small decoration quiz?",
		"There are many more ways in which you can decorate",
		"Try to get them all",
		"Thanks for playing!"
	};
}