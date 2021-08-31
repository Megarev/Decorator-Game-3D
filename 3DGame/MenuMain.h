#pragma once
#include "StateMain.h"
#include "Button.h"
#include "Transitions.h"

class MenuMain : public StateMain {
public:
	Button start;
	Transitions transition;
public:
	MenuMain();

	void PostInitialize() override {}

	void Input() override;
	void Logic() override;
	void Render() override;

	void Clear();
};