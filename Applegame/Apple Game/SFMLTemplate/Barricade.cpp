#include "Barricade.h"
#include "Game.h"


namespace AppleGame
{
	void InitBarricade(Barricade& barricade, int index, const Game& game)
	{
		// Инициализация препятствий
		barricade.barricade_position = GetBarricadePosition(SCREEN_WIDTH, SCREEN_HEIGHT, index);
		barricade.barricade_direction = (index == 0) ? BarricadeDirection::Up : BarricadeDirection::Down;

		// Установка текстуры
		barricade.barricade_sprite.setTexture(game.barricade_texture);

		// Установка размера яблок
		SetSpriteSize(barricade.barricade_sprite, BARRICADE_SIZE_X, BARRICADE_SIZE_Y);

		// Установка центра спрайта
		SetSpriteRelativeOrigin(barricade.barricade_sprite, 0.5f, 0.5f);

		barricade.barricade_sprite.setPosition(barricade.barricade_position.x, barricade.barricade_position.y);
	}

	void BarricadeMovement(Game& game, float delta_time)
	{
		// Движение препятствий вверх - вниз.
		for (int i = 0; i < BARRICADE_NUM; ++i)
		{
			// Инициализация скорости препятствий
			switch (game.barricade[i].barricade_direction)
			{
			case BarricadeDirection::Up:
			{
				game.barricade[i].barricade_position.y -= BARRICADE_SPEED * delta_time;
				break;
			}
			case BarricadeDirection::Down:
			{
				game.barricade[i].barricade_position.y += BARRICADE_SPEED * delta_time;
				break;
			}
			}

			// Проверки на столкновение препятствий с границами экрана. Когда препятствие сталкивается с верхней или низшей границей экрана, препятствия двигаются в обратном направлении
			if (game.barricade[i].barricade_position.y - BARRICADE_SIZE_Y / 2.f <= 0.f)
			{
				game.barricade[i].barricade_direction = BarricadeDirection::Down;
			}
			else if (game.barricade[i].barricade_position.y + BARRICADE_SIZE_Y / 2.f >= SCREEN_HEIGHT)
			{
				game.barricade[i].barricade_direction = BarricadeDirection::Up;
			}

			game.barricade[i].barricade_sprite.setPosition(game.barricade[i].barricade_position.x, game.barricade[i].barricade_position.y);
		}


	}
}
