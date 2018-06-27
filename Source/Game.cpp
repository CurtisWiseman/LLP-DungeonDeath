#include "Game.h"
#include "Constants.h"
#include "Font.h"
#include "Player.h"
#include "Bat.h"
#include "Room.h"
#include "Dungeon.h"
#include "Enemy.h"
#include "EnemyType.h"
#include "Die.h"

#include <iostream>
#include <sstream>
#include "Action.h"
#include <Engine/Input.h>
#include <Engine/Keys.h>
#include <Engine/Sprite.h>
#include <irrKlang.h>

//USER INTERFACE
#include "Panel.h"
#include "InputPanel.h"
#include "GamePanel.h"
#include "MapPanel.h"
#include "ViewportPanel.h"
#include "StatsPanel.h"

DungeonDeathGame::DungeonDeathGame()
{

}

DungeonDeathGame::~DungeonDeathGame()
{	
	for (auto& font : Font::fonts)
	{
		delete font;
		font = nullptr;
	}
	audio_engine->stopAllSounds();
}

bool DungeonDeathGame::run()
{
	while (!renderer->exit() && game_state != GameState::EXIT)
	{
		switch (game_state)
		{
			case GameState::MAIN_MENU:
				updateMenu();
				break;
			case GameState::PLAYING:
				updateGame();
				break;
			case GameState::GAME_OVER:
				updateGameOver();
				break;
		}
	}
	return false;
}

bool DungeonDeathGame::init()
{
	width = WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	if (!initAPI())
	{
		return false;
	}

	// load fonts
	Font::fonts[0] = new Font(renderer->loadFont("..\\..\\Resources\\Fonts\\DroidSansMono.ttf", 22), "default", 22);
	Font::fonts[1] = new Font(renderer->loadFont("..\\..\\Resources\\Fonts\\comic.ttf", 32), "heading", 32);
	Font::fonts[2] = new Font(renderer->loadFont("..\\..\\Resources\\Fonts\\comic.ttf", 16), "small", 16);

	renderer->setClearColour(ASGE::COLOURS::BLACK);

	//Init static vector
	EnemyType::load();

	//create dungeon
	dungeon = std::make_unique<Dungeon>();
	dungeon->create();

	// create player
	player_one = std::make_unique<Player>(Player::PlayerClass::BARBARIAN);
	player_one->loadAvatar(renderer);
	player_one->setRoom(dungeon->getRoom(0));

	//create enemy
	auto room = dungeon.get()->getRoom(0);
	generateEnemy(room);

	std::unique_ptr<GamePanel> game_panel;
	game_panel = std::make_unique<GamePanel>();
	game_panel->setPosX(1);
	game_panel->setPosY(70);
	game_panel->setHeight(35);
	game_panel->setWidth(35);

	std::unique_ptr<ViewportPanel> viewport_panel;
	viewport_panel = std::make_unique<ViewportPanel>();
	viewport_panel->setPosX((game_panel->getPosX() + (game_panel->getWidth() * BORDER_CELL_WIDTH) + PANEL_PADDING));
	viewport_panel->setPosY(340);
	viewport_panel->setWidth(20);
	viewport_panel->setHeight(20);
	viewport_panel->setObject(room->getEnemy());

	std::unique_ptr<StatsPanel> stats_panel;
	stats_panel = std::make_unique<StatsPanel>();
	stats_panel->setPosX(viewport_panel->getPosX());
	stats_panel->setPosY(game_panel->getPosY());
	stats_panel->setWidth(static_cast<int>(viewport_panel->getWidth()*1.8));
	stats_panel->setHeight(game_panel->getHeight() - viewport_panel->getHeight());
	stats_panel->init(player_one.get());

	std::unique_ptr<MapPanel> map_panel;
	map_panel = std::make_unique<MapPanel>();
	map_panel->setPosX(viewport_panel->getPosX() + (viewport_panel->getWidth() * BORDER_CELL_WIDTH));
	map_panel->setPosY(viewport_panel->getPosY());
	map_panel->setWidth(stats_panel->getWidth() - viewport_panel->getWidth());
	map_panel->setHeight(game_panel->getHeight() - stats_panel->getHeight());

	std::unique_ptr<InputPanel> input_panel;
	input_panel = std::make_unique<InputPanel>();
	input_panel->setPosX(0);
	input_panel->setPosY(700);

	//auto callbackid = this->inputs->addCallbackFnc(&InputPanel::input, input_panel.get());
	state_callback_id = this->inputs->addCallbackFnc(&DungeonDeathGame::stateInput, this);

	panels[0] = std::move(game_panel);
	panels[1] = std::move(viewport_panel);
	panels[2] = std::move(stats_panel);
	panels[3] = std::move(map_panel);
	panels[4] = std::move(input_panel);

	//Add intro text
	printToGamePanel("Welcome to Dungeon Death\n\n");
	printToGamePanel("You begin in " + player_one->getRoom()->getName() + "\n");
	printToGamePanel(player_one->getRoom()->getDescription() + "\n");
	printExits(player_one->getRoom());

	if (!initAudio())
	{
		return false;
	}

	return true;
}

void DungeonDeathGame::drawFrame()
{
	renderer->setFont(Font::fonts[1]->id);
	renderer->renderText("Dungeon Death 2016", 0, 30, 1.0, ASGE::COLOURS::DARKORANGE);

	renderer->setFont(Font::fonts[0]->id);
	for (auto& panel : panels)
	{
		panel->render(renderer);
	}
}

void DungeonDeathGame::processGameActions()
{
	auto room = player_one->getRoom();
	if (game_action == GameAction::ATTACK)
	{
		if (room->getEnemy()->isAlive() && player_one->isAlive())
		{
			auto dmg = player_one->attack(room->getEnemy());
			printToGamePanel("\n'ave at ye!");
			audio_engine->play2D("..\\..\\Resources\\Audio\\dspunch.wav", false);
			std::string dstr("You deal ");
			dstr += std::to_string(dmg);
			dstr += " damage";
			printToGamePanel(std::move(dstr));

			if (!room->getEnemy()->isAlive())
			{
				printToGamePanel(room->getEnemy()->getDeadStr());
				audio_engine->play2D("..\\..\\Resources\\Audio\\dsntdth.wav", false);
			}
			else
			{
				printToGamePanel(room->getEnemy()->getAttackStr());
				auto dmg = room->getEnemy()->attack(player_one.get());
				std::string dstr("You take ");
				dstr += std::to_string(dmg);
				dstr += " damage";
				printToGamePanel(std::move(dstr));
			}

			if (player_one->getHealth() <= 0)
			{
				printToGamePanel("\nNice job hero, you died.");
			}
		}
		else if (!player_one->isAlive())
		{
			printToGamePanel("\nDead heroes can't attack, silly.");
		}
	}
	else if (game_action == GameAction::NORTH)
	{
		processMoveAction(GameAction::NORTH);
	}
	else if (game_action == GameAction::SOUTH)
	{
		processMoveAction(GameAction::SOUTH);
	}
	else if (game_action == GameAction::EAST)
	{
		processMoveAction(GameAction::EAST);
	}
	else if (game_action == GameAction::WEST)
	{
		processMoveAction(GameAction::WEST);
	}
	else if (game_action == GameAction::INVENTORY)
	{
		printToGamePanel(player_one->getInventoryAsString());
	}
	else if (game_action == GameAction::PRINT_HELP)
	{
		for (const auto& verbs : help_strings)
		{
			std::stringstream ss;
			ss << verbs.first << ": \t" << verbs.second;
			printToGamePanel(ss.str());
		}
	}

	if (game_action == GameAction::INVALID)
	{
		printToGamePanel("I can't let you do that, sly fox.");
	}

	game_action = GameAction::NONE;

	if (player_one.get()->getHealth() <= 0)
	{
		audio_engine->play2D("..\\..\\Resources\\Audio\\dspdiehi.wav", false);

		this->inputs->unregisterCallback(game_callback_id);
		game_state = GameState::GAME_OVER;
	}
}

void DungeonDeathGame::printToGamePanel(std::string && str)
{
	auto panel = static_cast<GamePanel*>(panels[0].get());
	if (panel)
	{
		panel->addOutput(std::move(str));
	}
}

void DungeonDeathGame::printExits(Room* new_room)
{
	if (new_room->getRoomLinkDescription(Room::Direction::NORTH) != "Dead End")
	{
		printToGamePanel(std::string(new_room->
						 getRoomLinkDescription(Room::Direction::NORTH)));
	}
	if (new_room->getRoomLinkDescription(Room::Direction::SOUTH) != "Dead End")
	{
		printToGamePanel(std::string(new_room->
						 getRoomLinkDescription(Room::Direction::SOUTH)));
	}
	if (new_room->getRoomLinkDescription(Room::Direction::EAST) != "Dead End")
	{
		printToGamePanel(std::string(new_room->
						 getRoomLinkDescription(Room::Direction::EAST)));
	}
	if (new_room->getRoomLinkDescription(Room::Direction::WEST) != "Dead End")
	{
		printToGamePanel(std::string(new_room->
						 getRoomLinkDescription(Room::Direction::WEST)));
	}
	printToGamePanel("\n");
}

bool DungeonDeathGame::movePlayer(Room* new_room)
{
	if (!new_room)
	{
		return false;
	}

	player_one->setRoom(new_room);
	printToGamePanel("\n");
	printToGamePanel("You enter " + new_room->getName());
	printToGamePanel(std::string(new_room->getDescription()));
	printExits(new_room);

	generateEnemy(new_room);

	auto viewport = static_cast<ViewportPanel*>(panels[1].get());
	viewport->setObject(player_one->getRoom()->getEnemy());

	return true;
}

void DungeonDeathGame::processMoveAction(GameAction action)
{
	if (action == GameAction::NORTH)
	{
		auto& new_room = player_one->getRoom()->
			getRoomLink(Room::Direction::NORTH).room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move north");
		}
	}
	if (action == GameAction::SOUTH)
	{
		auto& new_room = player_one->getRoom()->
			getRoomLink(Room::Direction::SOUTH).room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move south");
		}
	}
	if (action == GameAction::EAST)
	{
		auto& new_room = player_one->getRoom()->
			getRoomLink(Room::Direction::EAST).room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move east");
		}
	}
	if (action == GameAction::WEST)
	{
		auto& new_room = player_one->getRoom()->
			getRoomLink(Room::Direction::WEST).room;
		if (!movePlayer(new_room))
		{
			printToGamePanel("You cannot move west");
		}
	}
}

bool DungeonDeathGame::initAudio()
{
	using namespace irrklang;
	audio_engine.reset(createIrrKlangDevice());

	if (!audio_engine)
	{
		return false;
	}
	return true;
}

void DungeonDeathGame::updateMenu()
{
	beginFrame();
	renderer->setFont(Font::fonts[1]->id);

	renderer->renderText("Dungeon Death 2016 Version",
						 0, 30, 1.0, ASGE::COLOURS::DARKORANGE);

	renderer->renderText("Welcome.\nAre you spooker or spookee?",
						 200, 200, ASGE::COLOURS::STEELBLUE);
	endFrame();
}

void DungeonDeathGame::updateGame()
{
	processGameActions();
	beginFrame();
	drawFrame();
	endFrame();
}

void DungeonDeathGame::updateGameOver()
{
	beginFrame();
	drawFrame();
	endFrame();
}

void DungeonDeathGame::stateInput(int key, int action)
{
	if (action == ASGE::KEYS::KEY_ESCAPE)
	{
		game_state = GameState::EXIT;
		auto input_panel = 
			static_cast<InputPanel*>(panels[4].get());
		game_callback_id = 
			this->inputs->addCallbackFnc
			(&InputPanel::input, input_panel);
	}
	else if (action == ASGE::KEYS::KEY_PRESS 
		&& game_state == GameState::MAIN_MENU)
	{
		game_state = GameState::PLAYING;
		auto input_panel = 
			static_cast<InputPanel*>(panels[4].get());
		game_callback_id = 
			this->inputs->addCallbackFnc
			(&InputPanel::input, input_panel);
	}
	else if (action == ASGE::KEYS::KEY_PRESS 
		&& game_state == GameState::GAME_OVER)
	{
		game_state = GameState::EXIT;
		auto input_panel = 
			static_cast<InputPanel*>(panels[4].get());
		game_callback_id = 
			this->inputs->addCallbackFnc
			(&InputPanel::input, input_panel);
	}
}

void DungeonDeathGame::generateEnemy(Room* new_room)
{
	if (new_room->getEnemy() == nullptr)
	{
		static Die spawn(100);
		if (spawn.rollDie() > 50)
		{
			static Die enem_type(3);
			new_room->setEnemy(
				EnemyType::enemy_types[enem_type.rollDie() - 1]
				.createEnemy());
		}
	}
}