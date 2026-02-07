#include "ProgressComponent.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"
#include "UnigineInput.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(ProgressComponent);

void ProgressComponent::init() {
    Unigine::Log::warning("ProgressComponent::init");
    gui = Unigine::Gui::getCurrent();
}

void ProgressComponent::update() {
    UpdateIfWindowsResized();
}

void ProgressComponent::UpdateIfWindowsResized() {
    if (screen_width != gui->getWidth() || screen_height != gui->getHeight()) {
        Unigine::Log::message("ProgressComponent::UpdateIfWindowsResized resized\n");
        screen_width = gui->getWidth();
        screen_height = gui->getHeight();
    }
}
