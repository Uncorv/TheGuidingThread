#pragma once

#include "UnigineComponentSystem.h"

class TopDownController : public Unigine::ComponentBase
{
public:
    COMPONENT_DEFINE(TopDownController, ComponentBase);
    COMPONENT_INIT(init)
    COMPONENT_UPDATE(update);
    COMPONENT_UPDATE_PHYSICS(updatePhysics)

    void init();
    void update();
    void updatePhysics();


    PROP_PARAM(Float, move_force, 100.0f, "Movement speed")
    PROP_PARAM(Float, max_speed, 10.0f)

    void applyDamage(int damage);
    int getCurrentHealth() const;
    void setCurrentHealth(int health);

private:
    Unigine::BodyRigidPtr body;
    Unigine::NodePtr node;
    Unigine::NodePtr node_sphere_1;
    Unigine::Math::Vec2 input_direction;
    Unigine::NodePtr freeze_state;
    Unigine::SoundSourcePtr sound_attack;


    int current_health;
    const int max_health = 3;
};
