#pragma once
#include "olcPixelGameEngine.h"
#include "engine.h"
#include "TextBox.h"
#include "physics.h"
#include "TextManager.h"
#include "Transitions.h"
#include "Button.h"
#include "StateMain.h"

class GameMain : public StateMain {
public:
	Engine3D engine;
	vf3d player_pos;
	Mesh cube, sphere, pyramid;
	float s = 10.0f, floor_size = 21.5f;

	Transitions transition;

	TextManager text_mgr;

	//olc::PixelGameEngine* pge = nullptr;
	std::vector<std::pair<vf3d, vf3d>> walls;

	std::vector<std::pair<Mesh, int>> answers;
	int question = 0, n_questions = 5;

	// Level Data
	olc::Sprite* tiles = nullptr, *answer_images = nullptr;
	olc::Sprite* spr_wall = nullptr, *floor = nullptr;

	std::vector<olc::Sprite*> images;

	Button button_a, button_b, button_next;
public:
	GameMain();

	void PostInitialize() override;

	void Input() override;
	void Logic() override;
	void Render() override;

	void ProcessAnswer();

	void Clear();
};