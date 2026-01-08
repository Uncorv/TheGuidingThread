#include "MenuComponent.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"
#include "UnigineInput.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(MenuComponent);

void MenuComponent::init() {
    Unigine::Log::warning("MenuComponent::init");

    keyWaiterEsc.setWaitSec(0.7f);
	keyWaiterEsc.setKey(Input::KEY_ESC);

    freeze_state = World::getNodeByName("freeze_state");
    pause_state = World::getNodeByName("pause_state");

    gui = Unigine::Gui::getCurrent();

    // Black background
    background = WidgetSprite::create(gui, "mane_background");
    // background.Texture = "menu_background0.png";
    background->setColor(vec4(0.0f, 0.0f, 0.0f, 0.8f));
    background->setPosition(0, 0);
    background->setWidth(gui->getWidth());
    background->setHeight(gui->getHeight());
    background->setHidden(!showedMenu);
    background->setOrder(1000);
    // background->arrange();
    gui->addChild(background, Gui::ALIGN_OVERLAP | Gui::ALIGN_EXPAND);
    // background.Lifetime = Widget.LIFETIME.WORLD;
}

void MenuComponent::update() {
    UpdateIfWindowsResized();

    if (!freeze_state->isEnabled()) {
        return;
    }

    if (keyWaiterEsc.isPressed()) {
        ToggleMenu();
    }

    Unigine::Input::setMouseGrab(!showedMenu);

    if (Unigine::Input::isMouseGrab())
        return;
}

void MenuComponent::UpdateIfWindowsResized() {
    if (screen_width != gui->getWidth() || screen_height != gui->getHeight()) {
        Unigine::Log::message("UpdateIfWindowsResized resized\n");
        screen_width = gui->getWidth();
        screen_height = gui->getHeight();

        background->setWidth(screen_width);
        background->setHeight(screen_height);

        UpdateScrollPositions();
    }
}


void MenuComponent::UpdateScrollPositions() {
    // TODO
}

void MenuComponent::ToggleMenu() {
    Unigine::Log::warning("MenuComponent::ToggleMenu()\n");

	showedMenu = !showedMenu;

    pause_state->setEnabled(showedMenu);

    background->setHidden(!showedMenu);

 	Unigine::Input::setMouseGrab(!showedMenu);
}
