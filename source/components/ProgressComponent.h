#pragma once

#include "UnigineComponentSystem.h"
#include "UnigineGui.h"
#include "waiter_key_press.h"

class ProgressComponent : public Unigine::ComponentBase
{
public:
    COMPONENT_DEFINE(ProgressComponent, ComponentBase);
    COMPONENT_INIT(init)
    COMPONENT_UPDATE(update);

    void init();
    void update();

private:

    void UpdateIfWindowsResized();

    int screen_width = 0;
	int screen_height = 0;
    Unigine::GuiPtr gui;
};
