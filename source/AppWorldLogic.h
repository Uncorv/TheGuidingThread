#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <vector>
#include "UI/TileCounter.h"
#include "UI/LevelNumberStartDisplay.h"
#include "GameState.h"
#include "GameLevel.h"
#include "GridMap.h"
#include "Roads2DGenerator.h"
#include "controller/TopDownController.h"
#include "AI/Enemy.h"
#include "UI/HealthDisplay.h"

class AppWorldLogic : public Unigine::WorldLogic
{

public:
	AppWorldLogic();
	~AppWorldLogic() override;

	int init() override;

	int update() override;
	int postUpdate() override;
	int updatePhysics() override;

	int shutdown() override;

	int save(const Unigine::StreamPtr &stream) override;
	int restore(const Unigine::StreamPtr &stream) override;
private:
	void regenerateMapForCurrentLevel();

	void addWall(int x, int y);
	void addPath(int x, int y);
	void addShapeOfBox(Unigine::ObjectMeshDynamicPtr object_mesh);
	void playSoundVisit();
	void playSoundAttack();
	void stopSoundAttack();
	void soundEnemy(float distance, Unigine::NodePtr enemy_node);
	void updateFireFondatEffects(float rate, float time);
	float time_fire_fontant_end;
	float timer;

	std::vector<Unigine::NodePtr> m_walls;
	std::vector<Unigine::NodePtr> m_paths;
	std::vector<Unigine::NodePtr> m_enemies;
	std::vector<GameLevel *> m_levels;

	Roads2DGeneratorPseudoRandom rand;
	GridMap grid_map;
	GameState game_state;
	int current_level;

	Unigine::NodePtr player;
	Unigine::NodePtr freeze_state;
	bool m_freeze_state;
	Unigine::NodePtr pause_state;
	bool skip_regenerate;
	Unigine::MaterialPtr mesh_wall;
	Unigine::MaterialPtr mesh_path_enable;
	Unigine::MaterialPtr mesh_path_disable;
	std::vector<Unigine::SoundSourcePtr> sound_player_visits;
	Unigine::SoundSourcePtr sound_attack;
	Unigine::ObjectParticlesPtr particles_sphere_1;
	int sound_visit_index;

	TileCounter *tile_counter = nullptr;
	LevelNumberStartDisplay *level_display = nullptr;
	HealthDisplay *health_display;
	TopDownController *player_controller;

};

#endif // __APP_WORLD_LOGIC_H__
