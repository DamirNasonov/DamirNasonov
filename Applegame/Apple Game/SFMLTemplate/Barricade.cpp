#include "Barricade.h"
#include "Game.h"


namespace AppleGame
{
	void InitBarricade(Barricade& barricade, int index, const Game& game)
	{
		// ������������� �����������
		barricade.barricade_position = GetBarricadePosition(SCREEN_WIDTH, SCREEN_HEIGHT, index);
		barricade.barricade_direction = (index == 0) ? BarricadeDirection::Up : BarricadeDirection::Down;

		// ��������� ��������
		barricade.barricade_sprite.setTexture(game.barricade_texture);

		// ��������� ������� �����
		SetSpriteSize(barricade.barricade_sprite, BARRICADE_SIZE_X, BARRICADE_SIZE_Y);

		// ��������� ������ �������
		SetSpriteRelativeOrigin(barricade.barricade_sprite, 0.5f, 0.5f);

		barricade.barricade_sprite.setPosition(barricade.barricade_position.x, barricade.barricade_position.y);
	}

	void BarricadeMovement(Game& game, float delta_time)
	{
		// �������� ����������� ����� - ����.
		for (int i = 0; i < BARRICADE_NUM; ++i)
		{
			// ������������� �������� �����������
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

			// �������� �� ������������ ����������� � ��������� ������. ����� ����������� ������������ � ������� ��� ������ �������� ������, ����������� ��������� � �������� �����������
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
