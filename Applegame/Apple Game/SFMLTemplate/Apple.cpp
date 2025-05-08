#include "Apple.h"
#include "Game.h"

namespace AppleGame
{
	void InitApple(Apple& apple, const Game& game)
	{
		// ������������� �����
		// ����� ����� �� x � y ����������
		apple.apple_position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		apple.apple_sprite.setTexture(game.apple_texture);
		
		// ��������� ������� �����
		SetSpriteSize(apple.apple_sprite, APPLE_SIZE, APPLE_SIZE);
		
		// ��������� ������ �������
		SetSpriteRelativeOrigin(apple.apple_sprite, 0.5f, 0.5f);

		apple.apple_sprite.setPosition(apple.apple_position.x, apple.apple_position.y);

	}
}
