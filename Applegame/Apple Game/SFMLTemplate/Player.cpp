#include "Player.h"
#include "Game.h"


namespace AppleGame
{
	using namespace std;

	void InitPlayer(Player& player, const Game& game)
	{
		// ������������� ���������� ������
		player.player_position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.player_speed = INITIAL_SPEED;
		player.player_direction = PlayerDirection::Right;

		// ������������� ������� ������
		player.player_sprite.setTexture(game.player_texture);
		
		// ��������� ������� �������
		SetSpriteSize(player.player_sprite, PLAYER_SIZE, PLAYER_SIZE);
		
		// ��������� ������ �������
		SetSpriteRelativeOrigin(player.player_sprite, 0.5f, 0.5f);

		player.isDead = false;
	}

	void UpdatePlayer(Player& player, float delta_time)
	{
		// ���������� ��������� ������.
		switch (player.player_direction)
		{
			case PlayerDirection::Right:
			{
				player.player_position.x += player.player_speed * delta_time;
				break;
			}
			case PlayerDirection::Up:
			{
				player.player_position.y -= player.player_speed * delta_time;
				break;
			}
			case PlayerDirection::Left:
			{
				player.player_position.x -= player.player_speed * delta_time;
				break;
			}
			case PlayerDirection::Down:
			{
				player.player_position.y += player.player_speed * delta_time;
				break;
			}
		}

	}

	void PlayerMovemetn(Player& player)
	{
		// ���� ������������
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.player_direction = PlayerDirection::Right;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.player_direction = PlayerDirection::Up;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.player_direction = PlayerDirection::Left;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
		player.player_direction = PlayerDirection::Down;
		}
	}

	bool IsScreenBorderCollide(const Player& player)
	{
		return player.player_position.x - PLAYER_SIZE / 2.f < 0.f || player.player_position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
				 player.player_position.y - PLAYER_SIZE / 2.f < 0.f || player.player_position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT;
	}



	void DrawPlayer(Player& player, RenderWindow& window)
	{
	
		// �������� ������� ������� �������
		Vector2f scale = player.player_sprite.getScale();
		
		// �������������� ������� �� ��� X � Y � �������� ���������� ��������. ��� ������������ ��������� ������������ ��������� �������.
		scale.x = abs(scale.x);
		scale.y = abs(scale.y);

		if (!player.isDead)
		{
			// ������������ ������ �������� �������� ������
			switch (player.player_direction)
			{
				case PlayerDirection::Right:
				{
					player.player_sprite.setScale(scale.x, scale.y);
					player.player_sprite.setRotation(0.f);
					break;
				}
				case PlayerDirection::Up:
				{
					player.player_sprite.setScale(scale.x, scale.y);
					player.player_sprite.setRotation(-90.f);
					break;
				}
				case PlayerDirection::Left:
				{
					player.player_sprite.setScale(-scale.x, scale.y);
					player.player_sprite.setRotation(0.f);
					break;
				}
				case PlayerDirection::Down:
				{
					player.player_sprite.setScale(scale.x, scale.y);
					player.player_sprite.setRotation(90.f);
					break;
				}
			}
		}		
		
		// ��������� ������� ��������� � ������ ������ ����
		player.player_sprite.setPosition(player.player_position.x, player.player_position.y); 
		
		// ��������� ���������
		window.draw(player.player_sprite); 
	}
}

