#include "Game.h"
#include "UI.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace AppleGame
{

	// ������� ��� �������� ���������� � ���������� ������ ����������� �������
	void RemoveDuplicatesAndFill(std::vector<HighScore>& highScores, const std::string* names, int namesCount)
	{
		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			// ���������, ���� �� ��������� ����� � �������
			auto it = std::find_if(highScores.begin(), highScores.end(), [&highScores, i](const HighScore& hs) 
				{
					return hs.name == highScores[i].name && &hs != &highScores[i];
				});

			// ���� �������� ������, �������� ��� ����� ������
			while (it != highScores.end())
			{
				highScores[i].name = names[rand() % namesCount]; // ���������� ����� ���
				it = std::find_if(highScores.begin(), highScores.end(),
					[&highScores, i](const HighScore& hs) 
					{
						return hs.name == highScores[i].name && &hs != &highScores[i];
					});
			}
		}
	}

	void InitHighScores(Game& game)
	{
		const std::string names[20] = {
			 "Alice", "Bob", "Charlie", "Dave", "Eve", "Frank", "Grace", "Heidi", "Ivan", "Judy",
			 "Karl", "Linda", "Mallory", "Niaj", "Olivia", "Peggy", "Quentin", "Randy", "Sybil", "Trent"
		};

		// ������������� ������� ��� ������ "��� ��������� + ����������� ������"
		game.highScoresNoAcceleration.resize(MAX_HIGH_SCORE);

		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			game.highScoresNoAcceleration[i] = { names[rand() % 20], rand() % 91 + 10 };
		}

		// ������������� ������� ��� ������ "� ���������� + ����������� ������"
		game.highScoresAcceleration.resize(MAX_HIGH_SCORE);
		
		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			game.highScoresAcceleration[i] = { names[rand() % 20], rand() % 91 + 10 };
		}

		RemoveDuplicatesAndFill(game.highScoresNoAcceleration, names, 20);
		RemoveDuplicatesAndFill(game.highScoresAcceleration, names, 20);
		
		// ���������� ������ �� �������� �����
		std::sort(game.highScoresNoAcceleration.begin(), game.highScoresNoAcceleration.end(), [](const HighScore& a, const HighScore& b) {
			return a.score > b.score;
			});

		std::sort(game.highScoresAcceleration.begin(), game.highScoresAcceleration.end(), [](const HighScore& a, const HighScore& b) {
			return a.score > b.score;
			});
	}

	//������� ������������� ����
	void InitGame(Game& game)
	{
		srand(static_cast<unsigned>(time(nullptr)));

		assert(game.player_texture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
		assert(game.apple_texture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
		assert(game.barricade_texture.loadFromFile(RESOURCES_PATH + "\\Barricade.png"));
		assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts/Roboto-Regular.ttf"));
		
		game.apple_eat_buffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav");
		game.death_buffer.loadFromFile(RESOURCES_PATH + "\\Death.wav");

		game.apple_eating.setBuffer(game.apple_eat_buffer);
		game.death.setBuffer(game.death_buffer);

		InitUI(game.uiState, game.font);
		game.currentState = GameState::MainMenu;

		game.barricade.resize(BARRICADE_NUM);

		//��������� ������� ���� �� ���������
		EnableGameSetting(game, GameSettingsBits::Mod_No_Acceleration);
		EnableGameSetting(game, GameSettingsBits::Mod_Limited_Apples);

		InitHighScores(game);
	}

	/*
		 ������� HasGameSettings ���������, ���������� �� ���������� ������� �����, �������������� ����� � ���������� ����.

		 ���������:
		 - game: ����������� ������ �� ������ Game, ������� �������� ���������� � ������� ������ ����.
			������������ ��� ������� � ���� gameMode, � ������� �������� ������� ��������� ����.
		 - setting: �������� ���� GameSettingsBits, �������������� ���������� ��� (����� ����), ������� ����� ���������.

		 ������������ ��������:
		 ������� ���������� true (������), ���� ��������� ��� (����� ����) ���������� � game.gameMode, ����� ���������� false (����).
	*/
	bool HasGameSettings(const Game& game, GameSettingsBits setting)
	{
		return (game.gameMode & static_cast<int>(setting)) != 0;
	}

	// ������� �������� ����� ����
	void EnableGameSetting(Game& game, GameSettingsBits setting)
	{
		game.gameMode |= static_cast<int>(setting);
	}

	// ������� ��������� ����� ����
	void DisableGameSetting(Game& game, GameSettingsBits setting)
	{
		game.gameMode &= ~static_cast<int>(setting);
	}

	/*
		 ������� ����������� ������� ������.
		 �������� 4 ������:
		 1. ��������� + ����������� ������;
		 2. ��� ��������� + ����������� ������;
		 3. ��������� + ������������ ������;
		 4. ��� ��������� + ������������ ������.

		 ����� ������ "���������" � "��� ���������", ��� "����������� ������" � "������������ ������" ����������.
		 �������� �������� ��� ���������� �������������� ��������.
	*/
	void SetGameMode(Game& game, GameSettingsBits setting)
	{
		// ���� ����� �������� ����� "���������", ��������� ����� "��� ���������"
		if (setting & GameSettingsBits::Mod_Acceleration)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_No_Acceleration);
		}
		// ���� ����� �������� ����� "��� ���������", ��������� ����� "���������"
		else if (setting & GameSettingsBits::Mod_No_Acceleration)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Acceleration);
		}

		// ���� ����� �������� ����� "����������� ������", ��������� ����� "������������ ������"
		if (setting & GameSettingsBits::Mod_Infinity_Apples)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Limited_Apples);
		}
		// ���� ����� �������� ����� "������������ ������, ��������� ����� "����������� ������"
		else if (setting & GameSettingsBits::Mod_Limited_Apples)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Infinity_Apples);
		}

		// ������������� ��������� �����
		EnableGameSetting(game, setting);
	}


	void RestartGame(Game& game)
	{
		// ����� ������ � ����� ����
		game.currentState = GameState::Playing;

		game.num_eaten_apples = 0;
		
		game.timeSinceGameOver = 0.f;

		game.apple_count = rand() % 11 + 20; 

		InitPlayer(game.player, game);

		//����� ����� � ������� ��������. ���� ���� ��������� �� ��������� ������������� ��������� ���������.
		game.apples.clear();

		// C���� �����
		game.apples.resize(game.apple_count);
		for (int i = 0; i < game.apple_count; ++i)
		{
			InitApple(game.apples[i], game);
		}

		// ����� �����������
		for (int i = 0; i < BARRICADE_NUM; ++i)
		{
			InitBarricade(game.barricade[i], i, game);
		}
	}

	void HandleInput(Game& game, RenderWindow& window)
	{

		// ����� ������ ����, ���������������� ������� � ����, �������� ��� ����������� ���� ������
		switch (game.currentState)
		{
		case GameState::MainMenu:

			/* ��������� ������� ����
			Num 1 - ����� ���� � ����������
			Num 2 - ����� ���� ��� ���������
			Num 3 - ����� ���� � ������������ ��������
			Num 4 - ����� ���� � ������������� ��������
			*/
			if (Keyboard::isKeyPressed(Keyboard::Num1)) SetGameMode(game, GameSettingsBits::Mod_Acceleration);
			if (Keyboard::isKeyPressed(Keyboard::Num2)) SetGameMode(game, GameSettingsBits::Mod_No_Acceleration);
			if (Keyboard::isKeyPressed(Keyboard::Num3)) SetGameMode(game, GameSettingsBits::Mod_Infinity_Apples);
			if (Keyboard::isKeyPressed(Keyboard::Num4)) SetGameMode(game, GameSettingsBits::Mod_Limited_Apples);

			// ������� � ������� ��������
			if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
			{
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					game.currentState = GameState::HighScoreScreen;
				}
			}

			// ������� � ����������� ���� ������
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}

			// ������� � ����
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				RestartGame(game);
				game.currentState = GameState::Playing;
			}

			break;

			// ������� � �������� ���������, �� �� ������ ����
		case GameState::Playing:

			// ���������� ������
			PlayerMovemetn(game.player);

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.currentState = GameState::Pause;
			}
			break;
		
			// ������� � ��������� �����
		case GameState::Pause:
			
			// ��� ������� �� "R" ���������� ������� � ���� 
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				game.currentState = GameState::Playing;
			}

			// ��� ������� �� "Space" ���������� ���������� ����
			else if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				RestartGame(game);
				game.currentState = GameState::Playing;
			}

			// ��� ������� �� "B" ���������� ������� � ������� ����
			else if (Keyboard::isKeyPressed(Keyboard::B))
			{
				game.currentState = GameState::MainMenu;
			}

			// ��� ������� �� "E" ���������� ����� ����������� ���� "�� ������ �����?"
			else if (Keyboard::isKeyPressed(Keyboard::E))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}
			break;

			// ������� � ��������� "���� ��������", ������ ��� ����� ������ ������ ��� ������� �� Space ��� ��������� � ������� ���� ��� ������� �� B
		case GameState::GameOver:
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				RestartGame(game);
				GameState::Playing;
			}
			else if (Keyboard::isKeyPressed(Keyboard::B))
			{
				game.currentState = GameState::MainMenu;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}
			break;

			// ������� � ��������� ������� ��������, ������ ����� ����� ������ ����� � ������� ���� ��� ������� �� B
		case GameState::HighScoreScreen:

			if (Keyboard::isKeyPressed(Keyboard::B))
			{
				game.currentState = GameState::MainMenu;
			}

			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}
			break;
			
			// ������� � ����������� ���� "�� ������ �����?"
		case GameState::ExitDialog:
			if (Keyboard::isKeyPressed(Keyboard::Y))
			{
				window.close(); // ��������� ����
			}
			else if (Keyboard::isKeyPressed(Keyboard::N))
			{
				game.currentState = game.lastState;
			}
		}
	}

	void UpdateHighScore(Game& game)
	{
		 std::vector<HighScore>* currentHighScore = nullptr;

		// �������� ������� � ����������� �� ������ ����
		if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
		{
			if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
			{
				currentHighScore = &game.highScoresAcceleration;
			}
			else
			{
				currentHighScore = &game.highScoresNoAcceleration;
			}

			if (game.num_eaten_apples > 0)
			{
				// ���������, �������� �� ��������� ������ � ������� ��������
				for (int i = 0; i < currentHighScore -> size(); ++i)
				{			
					if (game.num_eaten_apples >= (*currentHighScore)[i].score)
					{
						// �������� ��������� ������ � ������� ����
						for (int j = currentHighScore->size() - 1; j > i; --j)
						{
							(*currentHighScore)[j] = (*currentHighScore)[j - 1];
						}
						// ��������� ��������� ������
						(*currentHighScore)[i] = { "Player", game.num_eaten_apples };
						break;
					}
				}
			}
		}
	}

	// ������� ���������� ��������� ����
	void UpdateGame(Game& game, float delta_time)
	{
		
		if (game.currentState == GameState::Playing && game.currentState != GameState::GameOver)
		{
			UpdatePlayer(game.player, delta_time);

			BarricadeMovement(game, delta_time);
			
			// ���� ��������� �� ���������� �� ����� � �������
			for (int i = 0; i < game.apple_count; ++i)
			{
				// ���� ����� ���������� ������, ���������� ����� ������ ������ � ��������� ����� �� ������ ����
				if (IsAppleCollide(game.player.player_position, PLAYER_SIZE / 2.f, game.apples[i].apple_position, APPLE_SIZE / 2.f))
				{
					++game.num_eaten_apples;
					game.apple_eating.play();

					// ���� ������� ����� "� ����������", ����������� ��������
					if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
					{
						game.player.player_speed += ACCLERATION_SPEED;
					}

					// ���� ������� ����� "����������� ������", �������������� ����� ������
					if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
					{
						InitApple(game.apples[i], game);
					}
					// ���� ������� ����� "������������ ������", ������� ������ ����� �� ����������� �������
					else if (HasGameSettings(game, GameSettingsBits::Mod_Limited_Apples))
					{
						for (int j = i; j < game.apple_count - 1; ++j)
						{
							game.apples[j] = game.apples[j + 1];
						}
						--game.apple_count;

						// ���� ����� ��� ������, ������������� �������� ���������� isGameMenu true � ���������� ������ � ���� 
						if (game.apple_count == 0)
						{
							GameState::MainMenu;
							return;
						}
					}
				}
			}

			// ���� ��������� �� ���������� �� ����� � ������������
			for(int j = 0; j < BARRICADE_NUM; ++j)
			{
				// �������� �� ������������ � ������������ � ���������� ����.
				if (IsBarricadeleCollide(game.player.player_position, { PLAYER_SIZE, PLAYER_SIZE }, game.barricade[j].barricade_position, { BARRICADE_SIZE_X, BARRICADE_SIZE_Y }))
				{
					game.death.play();
					game.currentState = GameState::GameOver;
					game.player.isDead = true;
					game.timeSinceGameOver = 0.f;
					UpdateHighScore(game);
				}
			}

			// ��������: ���� ������ ������ ������� �� ������� ������ �� ����� �� ������ (�����, ������, ������ ��� �����), ����� ���� ���������������)
			if (IsScreenBorderCollide(game.player))
			{
				game.death.play();
				game.currentState = GameState::GameOver;
				game.player.isDead = true;
				game.timeSinceGameOver = 0.f;
				UpdateHighScore(game);
			}
		}
		
		game.timeSinceGameOver += delta_time;

		// ���������� ����������������� ����������
		UpdateUI(game.uiState, game, delta_time);
	}

	// ������� ��������� ����
	void DrawGame(Game& game, RenderWindow& window)
	{
		if (game.currentState == GameState::Playing && game.currentState != GameState::GameOver)
		{
			DrawPlayer(game.player, window);

			// ���� �������������� �������� ���������� ���-�� �����
			for (int i = 0; i < game.apple_count; ++i)
			{
				// ��������� �����
				window.draw(game.apples[i].apple_sprite);

			}

			// ���� �������������� �������� ���������� ���-�� �����������
			for (int i = 0; i < BARRICADE_NUM; ++i)
			{
				// ��������� �����������
				window.draw(game.barricade[i].barricade_sprite);
			}
		}
			// ��������� ����������������� ����������
			DrawUI(game.uiState, window, game);
	}

	void DeinializeGame(Game& game)
	{

	}

}