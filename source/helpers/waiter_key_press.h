#pragma once

#include "UnigineInput.h"

class WaiterKeyPress
{
public:
    WaiterKeyPress();
    void setWaitSec(float wait_sec);
    void setKey(Unigine::Input::KEY key);

    bool isPressed();

private:
    float wait_sec;
    float timer_sec;
    float prev_ifps;
    Unigine::Input::KEY key;
};