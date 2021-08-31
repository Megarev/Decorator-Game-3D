#include "GameMain.h"

GameMain::GameMain() {}

void GameMain::PostInitialize() {
	int32_t w = EngineData::Get().w;
	int32_t h = EngineData::Get().h;

	engine.Initialize(EngineData::Get().w, EngineData::Get().h, PI / 2.0f, 0.2f, 500.0f);
	engine.render_distance = 200.0f;

	int padding = 5, size = 100;
	TextBox box{ padding, h - (size + padding), w - 2 * padding, size - 2 * padding };

	text_mgr = TextManager{ &box };
	text_mgr.Input();

	tiles = new olc::Sprite("files/images/game_tiles.png");
	answer_images = new olc::Sprite("files/images/images.png");

	s = 10.0f;

	player_pos = { -s / 2.0f, 8.0f, 5.0f };

	sphere.LoadObj("sphere.txt");
	pyramid.LoadObj("pyramid.txt");

	cube.type = ShapeType::CUBE;
	cube.mass = 0.0f;
	cube.inv_mass = 0.0f;

	cube.t = {
		{ 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f },

		{ 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f },

		{ 1.0f, 0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f },

		{ 0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f },

		{ 1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f },

		{ 0.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f }
	};

	walls = { // Position and size
		std::make_pair(vf3d{ 0.0f, 0.0f, -s }, vf3d{ 1.0f, 2.0f * s, 2.0f * s }),
		std::make_pair(vf3d{ s, 0.0f, 0.0f }, vf3d{ 1.0f, 2.0f * s, 2.0f * s }),
		std::make_pair(vf3d{ 0.0f, 0.0f, s }, vf3d{ 2.0f * s, 2.0f * s, 1.0f }),
		std::make_pair(vf3d{ -s, 0.0f, 2.0f * s }, vf3d{ 2.0f * s, 2.0f * s, 1.0f }),
		std::make_pair(vf3d{ -s, 0.0f, 0.0f }, vf3d{ 1.0f, 2.0f * s, 2.0f * s }),
		std::make_pair(vf3d{ -s, 0.0f, 0.0f }, vf3d{ 2.0f * s, 2.0f * s, 1.0f })
	};

	button_a = Button{ { 18, h - 175 }, { 32, 32 }, olc::Pixel(0, 150, 0), olc::Pixel(0, 200, 0), olc::Pixel(0, 255, 0), "A" };
	button_b = Button{ { w - 50, h - 175 }, { 32, 32 }, olc::Pixel(0, 0, 150), olc::Pixel(0, 0, 200), olc::Pixel(0, 0, 255), "B" };

	button_next = Button{ { 16, 16 }, { 32, 32 }, olc::Pixel(150, 150, 0), olc::Pixel(200, 200, 0), olc::YELLOW, ">" };

	float s2 = std::ceilf(floor_size);

	spr_wall = new olc::Sprite(32 * (int)s, 32 * (int)s);
	floor = new olc::Sprite(32 * (int)s2, 32 * (int)s2);

	for (int i = 0; i < answer_images->height / 32; i++) {
		for (int j = 0; j < answer_images->width / 32; j++) {
			images.push_back(new olc::Sprite(32, 32));
			EngineData::Get().pge->SetDrawTarget(images.back());
			EngineData::Get().pge->DrawPartialSprite(0, 0, answer_images, j * 32, i * 32, 32, 32);
		}
	}

	for (int i = 0; i < spr_wall->height / 32; i++) {
		for (int j = 0; j < spr_wall->width / 32; j++) {
			EngineData::Get().pge->SetDrawTarget(spr_wall);
			EngineData::Get().pge->DrawPartialSprite(j * 32, i * 32, tiles, 0, 0, 32, 32);
		}
	}

	for (int i = 0; i < floor->height / 32; i++) {
		for (int j = 0; j < floor->width / 32; j++) {
			EngineData::Get().pge->SetDrawTarget(floor);
			EngineData::Get().pge->DrawPartialSprite(j * 32, i * 32, tiles, 0, 32, 32, 32);
		}
	}

	EngineData::Get().pge->SetDrawTarget(nullptr);
}

void GameMain::ProcessAnswer() {

	Mesh m;
	int spr_index = 0;

	switch (question) {
	case 0: // Q1
		m = cube;
		m.pos = { -s + 0.1f, 0.5f * s - 1.0f, 0.25f * s };
		m.Scale(1.0f, 0.5f * s, s);

		if (text_mgr.answer == 1) spr_index = 0;
		else spr_index = 1;
		answers.push_back(std::make_pair(m, spr_index));
		
		break;
	case 1: // Q2
		if (text_mgr.answer == 1) m = sphere;
		else m = pyramid;
		m.pos = { 0.8f * s, 0.5f * s - 1.0f, 1.8f * s };
		m.Scale(0.25f * s);

		if (text_mgr.answer == 1) spr_index = 2;
		else spr_index = 3;

		answers.push_back(std::make_pair(m, spr_index));
		
		m.pos = { 0.8f * s, 0.5f * s, 1.8f * s };
		answers.push_back(std::make_pair(m, spr_index));

		m = cube;
		m.pos = { 0.8f * s, 0.5f * s, 1.8f * s };
		m.Scale(0.25f, -4.0f, 0.25f);
		answers.push_back(std::make_pair(m, -1));

		break;
	case 2: // Q3
		m = cube;
		m.Scale(0.25f * s);

		if (text_mgr.answer == 1) spr_index = 4;
		else spr_index = 5;

		m.pos = { -0.89f * s, 1.25f, 1.5f * s };
		answers.push_back(std::make_pair(m, spr_index));
		m.pos = { -0.89f * s, s / 2.0f - 1.25f, 1.75f * s };
		answers.push_back(std::make_pair(m, spr_index));
		m.pos = { -0.75f * s, 1.25f, 1.75f * s };
		answers.push_back(std::make_pair(m, spr_index));

		break;
	case 3: // Q4
		m = cube;
		m.Scale(0.25f * s, 0.25f * s, 1.0f);

		if (text_mgr.answer == 1) spr_index = 6;
		else spr_index = 7;

		m.pos = { 0.5f * s, 0.5f * s, 1.99f * s };
		answers.push_back(std::make_pair(m, spr_index));
		m.pos = { -0.5f * s, 0.5f * s, 1.99f * s };
		answers.push_back(std::make_pair(m, spr_index));

		m = cube;
		m.Scale(1.0f, 0.5f * s, 0.25f * s);

		if (text_mgr.answer == 1) spr_index = 8;
		else spr_index = 9;

		m.pos = { 0.99f * s, 1.0f, 1.5f * s };
		answers.push_back(std::make_pair(m, spr_index));

		break;
	case 4: // Q5
		Mesh sofa("scene_data/sofa.obj");
		sofa.pos = { -2.0f, 1.0f, 5.0f };

		if (text_mgr.answer == 1) sofa.color = olc::CYAN;
		else sofa.color = olc::VERY_DARK_GREEN;

		answers.push_back(std::make_pair(sofa, -1));

		Mesh table("scene_data/table.obj");
		table.pos = { -5.0f, 1.0f, 5.0f };

		if (text_mgr.answer == 1) table.color = olc::CYAN;
		else table.color = olc::VERY_DARK_GREEN;

		answers.push_back(std::make_pair(table, -1));

		break;
	}
}

void GameMain::Input() {
	if (!text_mgr.yn) {
		engine.Input(EngineData::Get().pge, EngineData::Get().pge->GetElapsedTime(), 1.0f, 5.0f);

		float speed = 0.1f;
		float direction = -(EngineData::Get().pge->GetKey(olc::S).bHeld - EngineData::Get().pge->GetKey(olc::W).bHeld);
		player_pos.x += direction * engine.look_dir.x * speed;
		player_pos.z += direction * engine.look_dir.z * speed;

		engine.cam_pos = engine.GetNearPoint(player_pos) + vf3d{ 0.5f, 0.5f, 0.5f };
		button_next.Input(EngineData::Get().pge);

		if (button_next.is_pressed) {
			button_next.is_pressed = false;
			text_mgr.yn = true;
			text_mgr.Next();
		}
	}
	else {
		if (text_mgr.GetComplete()) {
			if (question < n_questions) {
				button_a.Input(EngineData::Get().pge);
				button_b.Input(EngineData::Get().pge);

				if (text_mgr.answer == 0 && button_a.is_pressed) text_mgr.answer = 1;
				if (text_mgr.answer == 0 && button_b.is_pressed) text_mgr.answer = 2;

				if (text_mgr.answer != 0) {
					transition.Update(2);

					if (transition.IsTransitionComplete()) {
						EngineData::Get().src_key.Play();

						text_mgr.yn = false;
						transition.alpha = 0;
						ProcessAnswer();
						text_mgr.answer = 0;
						question++;

						button_a.is_pressed = false;
						button_b.is_pressed = false;
					}
				}
			}
			else {
				transition.Update(2);
				if (transition.IsTransitionComplete()) {
					transition.alpha = 0;
					state = State::MENU;
					is_change_state = true;
				}
			}
		}
	}
}

void GameMain::Logic() {
	if (!text_mgr.yn) {
		for (auto& w : walls) {
			Mesh wall = cube;
			wall.pos = w.first;
			wall.Scale(w.second.x, w.second.y, w.second.z);

			Mesh player = cube;
			player.pos = player_pos;
			player.mass = 1.0f;

			if (Collisions::AABB(player, wall, engine)) {
				Resolutions::AABB(player, wall, engine);
				player_pos = player.pos;
			}
		}

		engine.light_dir = -engine.look_dir;
		engine.Update(EngineData::Get().pge->GetElapsedTime());
	}
	else {
		if (text_mgr.IsUpdate(EngineData::Get().pge->GetElapsedTime())) {
			text_mgr.Input();
		}

		bool is_type = text_mgr.Logic(EngineData::Get().pge->GetElapsedTime()); // bool for debug
	}
}

void GameMain::Render() {

	if (!text_mgr.yn) {
		for (auto& w : walls) {
			Mesh wall = cube;
			wall.pos = w.first;
			wall.Scale(w.second.x, w.second.y, w.second.z);

			engine.DrawSprite(EngineData::Get().pge, wall, spr_wall);
		}

		Mesh cuboid = cube;
		cuboid.Scale(floor_size, 1.0f, floor_size);

		cuboid.pos = { -(floor_size / 2.0f), 0.0f, 0.0f };
		engine.DrawSprite(EngineData::Get().pge, cuboid, floor);

		cuboid.pos = { -(floor_size / 2.0f), 10.0f, 0.0f };
		engine.DrawSprite(EngineData::Get().pge, cuboid, floor);

		for (auto& a : answers) {
			if (a.second < 0) engine.DrawMesh(EngineData::Get().pge, a.first);
			else engine.DrawSprite(EngineData::Get().pge, a.first, images[a.second]);
		}

		if (question < n_questions + 1) button_next.Render(EngineData::Get().pge);
	}
	else {
		// GUI
		text_mgr.Render(EngineData::Get().pge);
		if (text_mgr.GetComplete() && question < n_questions) {
			button_a.Render(EngineData::Get().pge);
			button_b.Render(EngineData::Get().pge);
		}
	}

	if (!transition.IsTransitionComplete()) transition.Render(EngineData::Get().pge);
}

void GameMain::Clear() {
	engine.ClearDepthMemory();
	delete tiles, floor, spr_wall, answer_images;
	for (auto& spr : images) delete spr;
	images.clear();
}