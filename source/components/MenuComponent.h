#pragma once

#include "UnigineComponentSystem.h"
#include "UnigineGui.h"
#include "waiter_key_press.h"

class MenuComponent : public Unigine::ComponentBase
{
public:
    COMPONENT_DEFINE(MenuComponent, ComponentBase);
    COMPONENT_INIT(init)
    COMPONENT_UPDATE(update);

    void init();
    void update();

    // PROP_PARAM(Float, move_force, 100.0f, "Movement speed")
    // PROP_PARAM(Float, max_speed, 10.0f)

private:

    void UpdateIfWindowsResized();
    void UpdateScrollPositions();
    void ToggleMenu();

    int screen_width = 0;
	int screen_height = 0;
    bool showedMenu = false;
    Unigine::GuiPtr gui;
    Unigine::WidgetSpritePtr background;
    WaiterKeyPress keyWaiterEsc;
    Unigine::NodePtr pause_state;
    Unigine::NodePtr freeze_state;
};
