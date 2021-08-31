#include "MenuMain.h"

MenuMain::MenuMain() {
	start = Button{ { EngineData::Get().w / 2 - 64, EngineData::Get().h / 2 }, { 128, 32 }, olc::Pixel(0, 100, 100), olc::Pixel(0, 150, 150), olc::WHITE, "Start" };
	transition.alpha = 0;
}

void MenuMain::Input() {
	start.Input(EngineData::Get().pge);
}

void MenuMain::Logic() {
	if (start.is_pressed) {
		transition.Update(2);
		if (transition.IsTransitionComplete()) {
			EngineData::Get().src_key.Play();
			transition.alpha = 0;
			start.is_pressed = false;
			state = State::GAME;
			is_change_state = true;
		}
	}
}

void MenuMain::Render() {
	EngineData::Get().pge->Clear(olc::VERY_DARK_RED);
	EngineData::Get().pge->FillRect(EngineData::Get().w / 2 - 64, 0, 128, EngineData::Get().h, olc::VERY_DARK_CYAN);
	EngineData::Get().pge->DrawString(EngineData::Get().w / 2 - 70, 64, "Decorator", olc::WHITE, 2);
	EngineData::Get().pge->DrawRect(EngineData::Get().w / 2 - 75, EngineData::Get().h / 2 - 100, EngineData::Get().w - 50, 128, olc::WHITE);

	EngineData::Get().pge->DrawString(EngineData::Get().w / 2 - 60, EngineData::Get().h - 10, "Game by Megarev");

	start.Render(EngineData::Get().pge, { 25, 10 });

	transition.Render(EngineData::Get().pge);
}

void MenuMain::Clear() {}