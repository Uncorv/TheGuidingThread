#include "TopDownController.h"

#include "UnigineConsole.h"
#include "UnigineGame.h"
#include "UnigineInput.h"
#include "UnigineVisualizer.h"

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(TopDownController);

void TopDownController::init()
{
    timer = 0.0f;
    freeze_state = World::getNodeByName("freeze_state");
    pause_state = World::getNodeByName("pause_state");
    node = World::getNodeByName("player");
    node_sphere_1 = World::getNodeByName("sphere_1");
    particles_sphere_1 = Unigine::checked_ptr_cast<Unigine::ObjectParticles>(World::getNodeByName("sphera_1_particles"));

    body = node->getObjectBodyRigid();
    body->setLinearDamping(17.0f);
    body->setAngularDamping(17.0f);
    current_health = max_health;
    body->setMaxLinearVelocity(max_speed);
}

void TopDownController::update()
{
    if (pause_state->isEnabled())
	{
		return;
	}

    timer += Game::getIFps();

    input_direction = Vec2(0.0f);
    if (!freeze_state->isEnabled())
    {
        return;
    }
    input_direction.y =
        Input::isKeyPressed(Input::KEY_W) || Input::isKeyPressed(Input::KEY_UP) ? 1.0f :
        Input::isKeyPressed(Input::KEY_S) || Input::isKeyPressed(Input::KEY_DOWN) ? -1.0f : 0.0f;
    input_direction.x =
        Input::isKeyPressed(Input::KEY_D) || Input::isKeyPressed(Input::KEY_RIGHT) ? 1.0f :
        Input::isKeyPressed(Input::KEY_A) || Input::isKeyPressed(Input::KEY_LEFT) ? -1.0f : 0.0f;

    jump = Input::isKeyPressed(Input::KEY_SPACE) ? 1.0f : 0.0f;

    Math::quat r = node_sphere_1->getWorldRotation();
    node_sphere_1->setWorldRotation(r * quat(
        r.x + rotation_speed * input_direction.x,
        r.y + rotation_speed * input_direction.y,
        0.0f
        // r.z + rotation_speed * input_direction.x * input_direction.y
    ));


    // Visualizer::renderBoundBox(node_sphere_1->getWorldBoundBox(), Mat4_identity, vec4_blue);
}

void TopDownController::updatePhysics()
{
    if (jump > 0.0f) {
        jump = 0.0f;
        force_z = 1.0f;
    }

    force_z = 0.0f;

    Vec3 force_dir = Vec3(input_direction.x * 1.f, input_direction.y * 1.f, force_z);
    force_dir.normalize();
    body->addForce(force_dir * move_force);

    if (force_z > 0.0f) {
        force_z = -1.0f;
    }
}

void TopDownController::applyDamage(int damage)
{
    Unigine::NodePtr node = World::getNodeByName("sound_attack");
    if (node) {
        sound_attack = checked_ptr_cast<Unigine::SoundSource>(node);
        if (!sound_attack->isPlaying())
        {
            // sphera_1_particles
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