#include "waiter_key_press.h"

#include "UnigineInput.h"
#include "UnigineGame.h"
#include <string>

WaiterKeyPress::WaiterKeyPress() : wait_sec(0.1f), prev_ifps(0.0f), timer_sec(0.0f) {
}

void WaiterKeyPress::setWaitSec(float wait_sec)
{
    this->wait_sec = wait_sec; // ms to sec
}

void WaiterKeyPress::setKey(Unigine::Input::KEY key)
{
    this->key = key;
}

bool WaiterKeyPress::isPressed()
{
    timer_sec += Unigine::Game::getIFps();
    bool ret = false;
	if (Unigine::Input::isKeyPressed(key) && (timer_sec - prev_ifps) > wait_sec)
    {
        prev_ifps = timer_sec;
        return true;
    }
    return false;
}