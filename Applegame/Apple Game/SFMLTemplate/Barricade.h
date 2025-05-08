#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

using namespace sf;

namespace AppleGame
{
	enum class BarricadeDirection
	{
		Down = 0,
		Up
	};

	struct Barricade
	{
		// ������ �����������
		Position2D barricade_position;
		BarricadeDirection barricade_direction = BarricadeDirection::Up;

		Sprite barricade_sprite;
	};

	struct Game;
	
	// ������������� �����������
	void InitBarricade(Barricade& barricade, int index, const Game& game);
	
	// ����������� �����������
	void BarricadeMovement(Game& game, float delta_time);
}