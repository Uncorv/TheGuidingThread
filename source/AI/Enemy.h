#pragma once

#include <UnigineComponentSystem.h>
#include <UnigineNodes.h>

class TopDownController;

using namespace Unigine;

enum class EnemyState {
	PATROL,
	CHASE,
	SEARCH,
	RETURN
};

class Enemy : public ComponentBase
{
public:
	COMPONENT_DEFINE(Enemy, ComponentBase)
	COMPONENT_INIT(init)
	COMPONENT_UPDATE(update)
	COMPONENT_UPDATE_PHYSICS(updatePhysics)

	PROP_PARAM(Node, player_node)

	PROP_PARAM(Float, patrol_radius, 10.0f);
	PROP_PARAM(Float, vision_range, 5.0f);
	PROP_PARAM(Float, patrol_force, 10.0f);
	PROP_PARAM(Float, chase_force, 20.0f);
	PROP_PARAM(Float, patrol_interval, 2.0f);

	void init();
	void update(TopDownController *player);
	void updatePhysics(TopDownController *player);

	void attack(NodePtr player_node);

private:
	EnemyState current_state;

	void updatePatrol();
	void updateChase();
	void updateSearch();
	void updateReturn();
	void checkTransitions();

	void move(const Math::Vec3 &target_pos, float force);

	Math::Vec3 getRandomPatrolPoint();

	Math::Vec3 patrol_point = Math::Vec3(0.0f, 0.0f, 0.0f);
	Math::Vec3 last_seen_player_pos;
	float distance_to_player;
	Math::Vec3 patrol_target_point;
	float patrol_reach_threshold = 0.5f;
	float patrol_timer = 0.0f;
	float damage_cooldown = 0.0f;
	const float damage_interval = 3.0f;

	Unigine::BodyRigidPtr body;
	Unigine::NodePtr freeze_state;
};