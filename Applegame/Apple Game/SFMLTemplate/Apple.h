	#pragma once
	#include<SFML/Graphics.hpp>
	#include "Math.h"
	#include "Constants.h"

	using namespace sf;

	namespace AppleGame
	{
		struct Apple
		{
			// Данные яблок
			Position2D apple_position;
			Sprite apple_sprite;
			bool isActive = true;
		};

		struct Game;

		void InitApple(Apple& apple, const Game& game);
	}