#pragma once
#include "olcPixelGameEngine.h"
#include "olcPGEX_AudioListener.h"
#include "olcPGEX_AudioSource.h"

class EngineData {
private:
	EngineData() {
		al.AudioSystemInit();
		src_key.AL = &al;
		src_music.AL = &al;
		LoadSounds();
	}

	void LoadSounds() {
		src_key.LoadAudioSample(0, "files/sounds/keypress.mp3");
		src_music.LoadAudioSample(1, "files/sounds/music.mp3");
	}
public:
	int32_t w = 0, h = 0;
	olc::PixelGameEngine* pge = nullptr;
	olcPGEX_AudioListener al;
	olcPGEX_AudioSource src_key, src_music;
	
	static EngineData& Get() {
		static EngineData e;
		return e;
	}
};

enum class State {
	MENU,
	GAME
};

class StateMain {
public:
	State state = State::MENU;
	bool is_change_state = false;
public:
	virtual void PostInitialize() = 0;

	virtual void Input() = 0;
	virtual void Logic() = 0;
	virtual void Render() = 0;

	virtual void Clear() = 0;
};