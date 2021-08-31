#define OLC_PGE_APPLICATION
#define VF3D_STATIC
#define AUDIO_LISTENER_IMPLEMENTATION
#define AUDIO_SOURCE_IMPLEMENTATION
#include "GameMain.h"
#include "MenuMain.h"

class Game : public olc::PixelGameEngine {
private:
	std::unique_ptr<StateMain> state;
	bool is_pause = false;
	bool is_play_music = true;
public:
	Game() {
		sAppName = "Decorator - olcCodeJam 2021";
	}

	bool OnUserCreate() override {

		EngineData::Get().pge = this;
		EngineData::Get().w = ScreenWidth();
		EngineData::Get().h = ScreenHeight();

		state = std::make_unique<MenuMain>();
		state->PostInitialize();

		EngineData::Get().src_music.Play(1.0f, 1.0f, true);

		return true;
	}

	bool OnUserUpdate(float dt) override {

		// States

		if (state->is_change_state) {
			state->is_change_state = false;

			switch (state->state) {
			case State::MENU:
				state = std::make_unique<MenuMain>();
				state->PostInitialize();
				break;
			case State::GAME:
				state = std::make_unique<GameMain>();
				state->PostInitialize();
				break;
			}
		}

		// Input
		state->Input();
		if (GetKey(olc::ENTER).bPressed) is_pause = !is_pause;
		if (GetKey(olc::M).bPressed) {
			is_play_music = !is_play_music;
			if (is_play_music) EngineData::Get().src_music.Play(1.0f, 1.0f, true, false);
			else EngineData::Get().src_music.Stop();
		}

		// Logic
		if (!is_pause) state->Logic();
		
		// Render
		Clear(olc::BLACK);
		state->Render();

		return true;
	}

	bool OnUserDestroy() override {

		state->Clear();
		EngineData::Get().al.AudioSystemDestroy();

		return true;
	}
};

int main() {
	
	srand((unsigned)time(0));

	Game game;
	if (game.Construct(200, 200, 2, 2, false, true)) {
		game.Start();
	}
	
	return 0;
}