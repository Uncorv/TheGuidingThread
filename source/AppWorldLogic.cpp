#include "AppWorldLogic.h"
#include "UnigineString.h"
#include "UnigineWorld.h"
#include <UnigineMaterials.h>
#include <UnigineGui.h>
#include <UnigineVisualizer.h>
#include <iostream>

// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

using namespace Unigine;
using namespace Math;

AppWorldLogic::AppWorldLogic()
{}

AppWorldLogic::~AppWorldLogic()
{}

int AppWorldLogic::init()
{
	// Visualizer::setEnabled(true);
	Sound::loadSettings("sound_settings.sound");

	GuiPtr gui = Gui::getCurrent();

	// set custom font
	if (!gui->setFontPath("fonts/TheGuidingThread.ttf")) {
		Log::error("Not installed font TheGuidingThread.ttf\n");
	}

	// init variables
	player = World::getNodeByName("player");
	mesh_wall = Materials::findMaterialByPath("mesh_wall.mat");
	mesh_path_enable = Materials::findMaterialByPath("mesh_path_enable.mat");
	mesh_path_disable = Materials::findMaterialByPath("mesh_path_disable.mat");
	particles_sphere_1 = Unigine::checked_ptr_cast<Unigine::ObjectParticles>(World::getNodeByName("sphera_1_particles"));

	// node for state freeze
	{
		ObjectMeshDynamicPtr object_mesh_freeze = ObjectMeshDynamic::create("core/meshes/box.mesh");
		freeze_state = object_mesh_freeze;
		freeze_state->setName("freeze_state");
		freeze_state->setWorldPosition(Vec3(-100.0f, -100.0f, -100.0f));
		m_freeze_state = false;
		freeze_state->setEnabled(false);
	}

	// node for state pause
	{
		ObjectMeshDynamicPtr object_mesh_freeze = ObjectMeshDynamic::create("core/meshes/box.mesh");
		pause_state = object_mesh_freeze;
		pause_state->setName("pause_state");
		pause_state->setWorldPosition(Vec3(-100.0f, -100.0f, -100.0f));
		pause_state->setEnabled(false);
	}

	sound_visit_index = 0;
	for (int i = 0; i < 10; i++) {
		std::string name = "sound_player_visit_" + std::to_string(i);
		Unigine::NodePtr node = World::getNodeByName(name.c_str());
		if (node) {
			Unigine::SoundSourcePtr sound_player_visit = checked_ptr_cast<Unigine::SoundSource>(node);
			sound_player_visits.push_back(sound_player_visit);
		}
	}

	{
		/*Unigine::NodePtr node = World::getNodeByName("sound_attack");
		if (node) {
			sound_attack = checked_ptr_cast<Unigine::SoundSource>(node);
		}*/
	}

	current_level = 0;
	skip_regenerate = false;
	health_display = new HealthDisplay;
	player_controller = ComponentSystem::get()->getComponent<TopDownController>(player);


	std::vector<std::string> disadle_nodes = {
		"sun",
		"enemy",
		"billboard_the_way_is_lost",
		"box_test_path_disable",
		"box_test_path_enable",
		"box_test_wall1",
		"box_test_wall2",
	};
	for (int i = 0; i < disadle_nodes.size(); i++) {
		NodePtr node = World::getNodeByName(disadle_nodes[i].c_str());
		if (node) {
			node->setEnabled(false);
		}
	}

	// levels
	m_levels.push_back(new GameLevel( 15,  15, 0.9f, 1));
	m_levels.push_back(new GameLevel( 20,  20, 0.9f, 2));
	m_levels.push_back(new GameLevel( 25,  25, 0.9f, 4));
	m_levels.push_back(new GameLevel( 30,  30, 0.9f, 8));
	m_levels.push_back(new GameLevel( 40,  40, 0.9f, 16));
	m_levels.push_back(new GameLevel( 50,  50, 0.5f, 32));
	m_levels.push_back(new GameLevel( 60,  60, 0.5f, 64));
	m_levels.push_back(new GameLevel( 70,  70, 0.5f, 128));
	m_levels.push_back(new GameLevel(100, 100, 0.5f, 256));

	tile_counter = new TileCounter();
	level_display = new LevelNumberStartDisplay();

	gui->addChild(tile_counter->getWidget(), Gui::ALIGN_LEFT);

	// temporary disbaled splashscreen
	NodePtr splashScreen = World::getNodeByName("IntroSplashScreenComponent");
	// splashScreen->setEnabled(false);

	// this->regenerateMapForCurrentLevel();
	time_fire_fontant_end = 0.0f;
	timer = 0.0f;
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
	if (pause_state->isEnabled()) {
		return 1;
	}

	timer += Game::getIFps();
    if (timer > time_fire_fontant_end) {
        particles_sphere_1->setSpawnRate(0.0f);
    }

	if (m_freeze_state == false && freeze_state->isEnabled()) {
		m_freeze_state = true;
		if (skip_regenerate) {
			std::cout << "Freeze out (skip)..." << std::endl;
			skip_regenerate = false;
		} else {
			std::cout << "Freeze out..." << std::endl;
			this->regenerateMapForCurrentLevel();
			level_display->showLevelBillbord(current_level, true);
			skip_regenerate = true;
		}
	}

	// reset state
	if (m_freeze_state == true && !freeze_state->isEnabled()) {
		m_freeze_state = false;
		std::cout << "Freeze on..." << std::endl;
		//this->stopSoundAttack();
	}

	if (tile_counter)
	{
		tile_counter->update(Game::getIFps());
	}

	level_display->update(Game::getIFps());

	if (!m_freeze_state) {
		return 1;
	}

	Vec3 playerPos = player->getWorldPosition();
	//bool attack_play = false;
	for (auto& enemy_node : m_enemies)
	{
		Vec3 enemyPos = enemy_node->getWorldPosition();
		float distance = (playerPos - enemyPos).length();
		this->soundEnemy(distance, enemy_node);

		if (distance < 0.5f)
		{
			auto enemy_component = Unigine::ComponentSystem::get()->getComponent<Enemy>(enemy_node);
			if (enemy_component)
			{
				enemy_component->attack(player);
				//attack_play = true;
				updateFireFondatEffects(120.0f, 0.7f);
			}
		}
	}

	bool close_to_wall = false;
	for (auto & wall : m_walls) {
		Vec3 wall_pos = wall->getWorldPosition();
		float distance = (playerPos - wall_pos).length();
		if (distance < 0.8f)
		{
			close_to_wall = true;
		}
	}
	if (close_to_wall) {
		updateFireFondatEffects(20.0f, 0.5f);
	}

	/*if (attack_play) {
		this->playSoundAttack();
	} else {
		this->stopSoundAttack();
	}*/

	if (player)
	{
		int flag = 0;
		if (player_controller)
		{
			if(health_display)
				health_display->setHealth(player_controller->getCurrentHealth());
			if (player_controller->getCurrentHealth() <= 0.0f)
			{
				if (flag == 0) {
					// this->regenerateMapForCurrentLevel();
					tile_counter->showDeathMessage();
					player_controller->setCurrentHealth(3);
					flag = 1;
				}
			}
		}
	}
	return 1;
}

int AppWorldLogic::postUpdate()
{
	if (!freeze_state->isEnabled()) {
		return 1;
	}
	Vec3 pos = player->getPosition();
	int x = pos.x + 0.5f;
	int y = pos.y + 0.5f;
	if (!game_state.isVisited(x, y)) {
		std::string name = "path_x" + std::to_string(x) + "_y" + std::to_string(y);
		NodePtr nodePath = World::getNodeByName(name.c_str());
		if (nodePath) {
			ObjectMeshDynamicPtr object_mesh = checked_ptr_cast<ObjectMeshDynamic>(nodePath);
			object_mesh->setMaterial(mesh_path_enable, "*");
		}
		if (game_state.updateVisited(x, y, true)) {
			int visited = game_state.getVisitedCount();
			if (visited > 1) {
				playSoundVisit();
				updateFireFondatEffects(200.0f, 0.7f);
			}
			int total = game_state.getAllCount();
			if (tile_counter)
				tile_counter->updateCounter(visited);

			// std::cout << game_state.getVisitedCount() << "/" << game_state.getAllCount() << std::endl;
			if (game_state.getVisitedCount() == game_state.getAllCount()) {
				current_level += 1; // next level
				player_controller->setCurrentHealth(3);

				// ad-hoc for reset level
				m_freeze_state = false;
				freeze_state->setEnabled(true);
				// this->regenerateMapForCurrentLevel();
			}
		}
	}
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	delete tile_counter;
	tile_counter = nullptr;
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	UNIGINE_UNUSED(stream);
	return 1;
}

void AppWorldLogic::regenerateMapForCurrentLevel() {
	std::cout << "regenerateMapForCurrentLevel " << current_level << std::endl;
	// remove previously nodes
	game_state.reset();
	for (int i = 0; i < m_walls.size(); i++) {
		m_walls[i].deleteLater();
	}
	m_walls.clear();

	for (int i = 0; i < m_paths.size(); i++) {
		m_paths[i].deleteLater();
	}
	m_paths.clear();

	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->setEnabled(false);
		m_enemies[i].deleteLater();
	}
	m_enemies.clear();

	if (current_level < m_levels.size()) {
		int width = m_levels[current_level]->getWidth();
		int height = m_levels[current_level]->getHeight();
		int enemis = m_levels[current_level]->getEnemis();
		float gen = m_levels[current_level]->getGen();

		// std::cout << "width = " << width << ", height = " << height << std::endl;

		grid_map.generate(width, height, gen);
		const std::vector<GridMap::Cell> &free_cells = grid_map.getFreeCells();
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				if (!grid_map.isWalkable(x, y))
				{
					this->addWall(x,y);
				} else {
					this->addPath(x,y);
				}
			}
		}

		if (free_cells.empty())
			return;

		player->setWorldPosition(Vec3(float(free_cells[0].x), float(free_cells[0].y), 0.55f));
		NodePtr playerCamera = World::getNodeByName("PlayerDummy");
		Vec3 pos = playerCamera->getWorldPosition();
		playerCamera->setWorldPosition(Vec3(float(free_cells[0].x), float(free_cells[0].y) - 1.8f, pos.z));

		if (tile_counter)
			tile_counter ->setLevel(current_level + 1, game_state.getAllCount());

		NodePtr enemy_parent = World::getNodeByName("enemy");
		for (int i = 0; i < enemis; i++) {
			NodePtr enemy = enemy_parent->clone();
			soundEnemy(100.0f, enemy);
			enemy->setEnabled(true);
			m_enemies.push_back(enemy);

			int idx = rand.getNextRandom() % free_cells.size();

			enemy->setWorldPosition(Vec3(float(free_cells[idx].x), float(free_cells[idx].y), 0.55f));
		}

	} else {
		// TODO player is win
	}
}

void AppWorldLogic::addWall(int x, int y)
{
	ObjectMeshDynamicPtr object_mesh = ObjectMeshDynamic::create("core/meshes/box.mesh");
	NodePtr node = object_mesh;
	node->setWorldPosition(Vec3(float(x), float(y), 0.5f));
	this->addShapeOfBox(object_mesh);

	// material
	object_mesh->setMaterial(mesh_wall, "*");

	// need for remove and recrating map
	m_walls.push_back(node);
}

void AppWorldLogic::addPath(int x, int y)
{
	game_state.addPath(x, y);

	ObjectMeshDynamicPtr object_mesh = ObjectMeshDynamic::create("core/meshes/box.mesh");
	NodePtr node = object_mesh;
	std::string name = "path_x" + std::to_string(x) + "_y" + std::to_string(y);
	node->setName(name.c_str());
	node->setWorldPosition(Vec3(float(x), float(y), -0.45f));
	this->addShapeOfBox(object_mesh);

	// material
	object_mesh->setMaterial(mesh_path_disable, "*");


	// need for remove and recrating map
	m_paths.push_back(node);
}

void AppWorldLogic::addShapeOfBox(ObjectMeshDynamicPtr object_mesh) {
	BodyDummyPtr body = BodyDummy::create(object_mesh);
	ShapeBoxPtr shape_box = ShapeBox::create();
	shape_box->setBody(body);
	shape_box->setSize(object_mesh->getScale());
	shape_box->setPosition(object_mesh->getWorldPosition());
	shape_box->setMass(100.0f);
	shape_box->setDensity(100.0f);
	shape_box->setFriction(0.1f);
	shape_box->setRestitution(0.2f);
}

void AppWorldLogic::playSoundVisit() {
	// std::cout << "sound_visit_index: " << sound_visit_index << std::endl;
	Unigine::SoundSourcePtr sound = sound_player_visits[sound_visit_index];
	if (sound->isPlaying()) {
		sound->stop();
	}
	sound->play();
	sound_visit_index++;
	sound_visit_index = sound_visit_index % sound_player_visits.size();
}

void AppWorldLogic::playSoundAttack()
{
	if (!sound_attack->isPlaying())
	{
		sound_attack->play();
	}
}

void AppWorldLogic::stopSoundAttack()
{
	if (sound_attack->isPlaying())
	{
		sound_attack->stop();
	}
}

void AppWorldLogic::soundEnemy(float distance, Unigine::NodePtr enemy_node) {
	Unigine::NodePtr sound_enemy_node = enemy_node->findNode("sound_enemy");
	Unigine::SoundSourcePtr sound_enemy = checked_ptr_cast<Unigine::SoundSource>(sound_enemy_node);
	if (!freeze_state->isEnabled()) {
		sound_enemy->setGain(0.0f);
		sound_enemy->setEnabled(false);
		return;
	}
	const float max_distance = 5.0f;
	if (distance > max_distance) {
		sound_enemy->setGain(0.0f);
		sound_enemy_node->setEnabled(false);
		return;
	}
	float gain_max = 0.5f;
	float val = 1.0f - (distance / max_distance);
	sound_enemy->setGain(val * gain_max);
	if (!sound_enemy_node->isEnabled()) {
		sound_enemy_node->setEnabled(true);
	}
}

void AppWorldLogic::updateFireFondatEffects(float rate, float time) {
	if (timer + time >= time_fire_fontant_end) {
		particles_sphere_1->setSpawnRate(rate);
		time_fire_fontant_end = timer + time;
	}
}
