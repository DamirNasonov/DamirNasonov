#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"

using namespace sf;

namespace AppleGame
{
	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		// Данные игрока
		Position2D player_position;
		float player_speed = INITIAL_SPEED;
		PlayerDirection player_direction = PlayerDirection::Right;
		Sprite player_sprite;
		bool isDead = false;

	};

	struct Game;

	void InitPlayer(Player& player, const Game& game);
	void UpdatePlayer(Player& player, float delta_time);
	void PlayerMovemetn(Player& player);
	bool IsScreenBorderCollide(const Player& player);
	void DrawPlayer(Player& player, RenderWindow& window);

}