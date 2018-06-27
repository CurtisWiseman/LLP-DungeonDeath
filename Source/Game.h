#pragma once
#include <Engine/OGLGame.h>
#include <string>
#include "Action.h"
#include <memory>

class Player;
class Enemy;
class Dungeon;
class UIPanel;
class Room;
struct Font;

namespace irrklang
{
	class ISoundEngine;
}

class DungeonDeathGame:
	public ASGE::OGLGame
{
	enum class GameState
	{
		MAIN_MENU = 0,
		PLAYING = 1,
		GAME_OVER = 2,
		EXIT = 3
	};
public:
	DungeonDeathGame();
	~DungeonDeathGame();

	// Inherited via Game
	virtual bool run() override;

	// Inherited via OGLGame
	virtual bool init();
	virtual void drawFrame();

private:
	std::unique_ptr<UIPanel> panels[5];
	std::unique_ptr<Dungeon> dungeon = nullptr;
	std::unique_ptr<Player> player_one = nullptr;
	std::unique_ptr<irrklang::ISoundEngine> audio_engine = nullptr;

	void processGameActions();
	void printToGamePanel(std::string && str);
	bool movePlayer(Room* new_room);
	void generateEnemy(Room* new_room);
	void processMoveAction(GameAction action);
	void printExits(Room* current_room);

	GameState game_state = GameState::MAIN_MENU;
	int state_callback_id = -1;
	int game_callback_id = -1;
	void stateInput(int key, int action);

	bool initAudio();

	void updateGame();
	void updateMenu();
	void updateGameOver();
};