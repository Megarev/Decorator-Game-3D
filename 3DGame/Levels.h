#pragma once
#include "engine.h"
#include "physics.h"
#include "Transitions.h"

class LevelData {
private:
	LevelData() {}
public:
	bool is_next = false, is_transition = false;

	static LevelData& Get() {
		static LevelData level_data;
		return level_data;
	}
};

class Levels {
protected:
	olc::PixelGameEngine* pge = nullptr;
	Transitions transition;
public:
	std::string top_text, box_text;

	void Initialize(olc::PixelGameEngine* p) {
		pge = p;
	}

	virtual void Input(Engine3D& engine, vf3d& player_pos) {}
	virtual void Logic(Mesh& cube, Engine3D& engine, vf3d& player_pos, float dt) = 0;
	virtual void Render(Engine3D& engine) = 0;

	virtual void Clear() = 0;
};

class Level_1 : public Levels {
private:
	Mesh pyramid;
	float phase_angle = 0.0f;
	int color_dir = 1;
public:
	Level_1();
	void Input(Engine3D& engine, vf3d& player_pos) override;
	void Logic(Mesh& cube, Engine3D& engine, vf3d& player_pos, float dt) override;
	void Render(Engine3D& engine) override;

	void Clear() override {}
};