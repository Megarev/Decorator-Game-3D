#pragma once
#include "olcPixelGameEngine.h"
#include "TextBox.h"

struct Text {
	std::vector<std::string> lines;
	int index = 0;
	olc::Pixel color;

	bool IsAllLinesComplete();
	bool Step(int text_pos);
};

struct Text_1 : public Text { Text_1(); };
struct Text_2 : public Text { Text_2(); };
struct Text_3 : public Text { Text_3(); };
struct Text_4 : public Text { Text_4(); };
struct Text_5 : public Text { Text_5(); };
struct Text_Complete : public Text { Text_Complete(); };

class TextManager {
public:
	std::unique_ptr<Text> level; // At each level
	int level_index = 0;
	TextBox box;
	int text_index = 0;
	bool yn = true;
	uint8_t answer = 0;

	// TextBox stepping
	float accumulator = 0.0f, speed = 5.0f, delay = 1.0f;
public:
	TextManager() {}
	TextManager(const TextBox* _box) {
		box = *_box;
		level = std::make_unique<Text_1>();
	}

	void Input();
	bool Logic(float dt);
	void Render(olc::PixelGameEngine* pge);

	void Next();

	bool GetComplete();
	bool IsUpdate(float dt);
};
