#include "TopDownController.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"
#include "UnigineInput.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(TopDownController);

void TopDownController::init()
{
    freeze_state = World::getNodeByName("freeze_state");
    node = World::getNodeByName("player");
    node_sphere_1 = World::getNodeByName("sphere_1");
    body = node->getObjectBodyRigid();
    body->setLinearDamping(17.0f);
    body->setAngularDamping(17.0f);
    current_health = max_health;
}

void TopDownController::update()
{
    input_direction = Vec2(0.0f);
    if (!freeze_state->isEnabled())
    {
        return;
    }
    input_direction.y = static_cast<float>(
        Input::isKeyPressed(Input::KEY_W) || Input::isKeyPressed(Input::KEY_UP) ? 1 :
        Input::isKeyPressed(Input::KEY_S) || Input::isKeyPressed(Input::KEY_DOWN) ? -1 : 0);
    input_direction.x = static_cast<float>(
        Input::isKeyPressed(Input::KEY_D) || Input::isKeyPressed(Input::KEY_RIGHT) ? 1 :
        Input::isKeyPressed(Input::KEY_A) || Input::isKeyPressed(Input::KEY_LEFT) ? -1 : 0);

    body->setMaxLinearVelocity(max_speed);

    float rotation_speed = 10.0f;
    Math::quat r = node_sphere_1->getWorldRotation();
    node_sphere_1->setWorldRotation(r * quat(
        r.x + rotation_speed * input_direction.x,
        r.y + rotation_speed * input_direction.y,
        0.0f
        // r.z + rotation_speed * input_direction.x * input_direction.y
    ));
}

void TopDownController::updatePhysics()
{

    if (length(input_direction) > 0.0f)
    {
        Vec3 force_dir = Vec3(input_direction.x, input_direction.y, 0.0f);
        force_dir.normalize();

        body->addForce(force_dir * move_force);
    }
}

void TopDownController::applyDamage(int damage)
{
    Unigine::NodePtr node = World::getNodeByName("sound_attack");
    if (node) {
        sound_attack = checked_ptr_cast<Unigine::SoundSource>(node);
        if (!sound_attack->isPlaying())
        {
            sound_attack->play();
        }
    }
    current_health -= damage;
    if (current_health < 0.0f)
        current_health = 0.0f;
}

int TopDownController::getCurrentHealth() const
{
    return current_health;
}

void TopDownController::setCurrentHealth(int health)
{
    current_health = health;
}