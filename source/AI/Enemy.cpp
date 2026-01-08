#include "Enemy.h"
#include "../controller/TopDownController.h"
#include <UnigineGame.h>
#include <UnigineWorld.h>
#include <UnigineVisualizer.h>

using namespace Unigine;
using namespace Math;

REGISTER_COMPONENT(Enemy);

void Enemy::init()
{
	freeze_state = World::getNodeByName("freeze_state");
	body = node->getObjectBodyRigid();
	if (body)
	{
		body->setLinearDamping(17.0f);
		body->setAngularDamping(17.0f);
		body->setMaxLinearVelocity(5.0f);
	}
	current_state = EnemyState::PATROL;
	patrol_target_point = getRandomPatrolPoint();
}

void Enemy::update(TopDownController *player)
{

}

void Enemy::updatePhysics(TopDownController *player)
{
	if (!freeze_state->isEnabled())
	{
        return;
    }
	switch (current_state)
	{
	case EnemyState::PATROL:
		//Log::error("SpiderState::PATROL\n");
		updatePatrol();
		break;
	case EnemyState::CHASE:
		//Log::error("SpiderState::Chase\n");
		updateChase();
		break;
	case EnemyState::SEARCH:
		//Log::error("SpiderState::SEARCH\n");
		updateSearch();
		break;
	case EnemyState::RETURN:
		//Log::error("SpiderState::RETURN\n");
		updateReturn();
		break;
	}

	checkTransitions();

	damage_cooldown -= Game::getIFps();
}

void Enemy::attack(NodePtr player_node)
{
	auto player_controller = Unigine::ComponentSystem::get()->getComponent<TopDownController>(player_node);
	if (player_controller)
	{
		if (damage_cooldown <= 0.0f)
		{
			player_controller->applyDamage(1);
			damage_cooldown = damage_interval;
		}
	}
}

void Enemy::updatePatrol() 
{
	move(patrol_target_point, patrol_force);

	if ((patrol_target_point - node->getWorldPosition()).length() < patrol_reach_threshold)
	{
		patrol_timer += Game::getIFps();
		if (patrol_timer >= patrol_interval)
		{
			patrol_target_point = getRandomPatrolPoint();
			patrol_timer = 0.0f;
		}
	}
}

void Enemy::updateChase()
{
	if (player_node) 
	{
		Vec3 player_pos = player_node->getWorldPosition();
		move(player_pos, chase_force);
		last_seen_player_pos = player_pos;
	}
}

void Enemy::updateSearch()
{
	move(last_seen_player_pos, patrol_force);
}

void Enemy::updateReturn()
{
	move(patrol_point, patrol_force);
}

void Enemy::checkTransitions()
{
	distance_to_player =  (player_node->getWorldPosition() - node->getWorldPosition()).length();
	bool sees_player = (distance_to_player < vision_range);

	if (distance_to_player < vision_range)
	{
		current_state = EnemyState::CHASE;
		return;
	}

	switch (current_state)
	{
	case EnemyState::PATROL:
		if (sees_player)
			current_state = EnemyState::CHASE;
		break;

	case EnemyState::CHASE:
		if (!sees_player)
			current_state = EnemyState::SEARCH;
		break;

	case EnemyState::SEARCH:
		if ((last_seen_player_pos - node->getWorldPosition()).length() < 0.5f)
			current_state = EnemyState::RETURN;
		else if (sees_player)
			current_state = EnemyState::CHASE;
		break;

	case EnemyState::RETURN:
		if ((patrol_point - node->getWorldPosition()).length() < 0.5f)
			current_state = EnemyState::PATROL;
		else if (sees_player)
			current_state = EnemyState::CHASE;
		break;
	}
}

void Enemy::move(const Math::Vec3& target_pos, float force)
{
	if (!body)
		return;

	Vec3 direction = (target_pos - node->getWorldPosition());
	direction.z = 0.0f; 
	direction.normalize();

	body->addForce(direction * force);
}

Math::Vec3 Enemy::getRandomPatrolPoint()
{
	const float PI = 3.14159265f;
	const float TWO_PI = PI * 2.0f;

	float angle = Game::getRandomFloat(0.0f, TWO_PI);

	float distance = Game::getRandomFloat(0.0f, patrol_radius);

	float offset_x = Math::cos(angle) * distance;
	float offset_y = Math::sin(angle) * distance;

	Math::Vec3 current_pos = node->getWorldPosition();

	return Math::Vec3(current_pos.x + offset_x, current_pos.y + offset_y, current_pos.z);
}
