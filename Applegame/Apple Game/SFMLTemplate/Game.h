	#pragma once
	#include "Math.h"
	#include "UI.h"
	#include "Player.h"
	#include "Constants.h"
	#include "Apple.h"
	#include "Barricade.h"

	namespace AppleGame
	{	
	
		enum GameSettingsBits
		{
			None = 0,
			Mod_Acceleration = 1 << 0,       // ��������� ������
			Mod_No_Acceleration = 1 << 1,    // ��� ���������
			Mod_Infinity_Apples = 1 << 2,    // ����������� ������
			Mod_Limited_Apples = 1 << 3      // ������������ ���������� �����
		};

		enum class GameState 
		{
			MainMenu,
			Playing,
			GameOver,
			HighScoreScreen,
			ExitDialog,
			Pause
		};

		

		struct HighScore
		{
			std::string name;
			int score = 0;
		};


		// ��������� ����
		struct Game
		{
			Player player;
			std::vector<Apple> apples;
			std::vector<Barricade> barricade;

			unsigned int gameMode = 0;

			UI uiState;

			// ������� ��������� �����, �� �� ����
			int num_eaten_apples = 0;
		
			// ���������� ���������� ��������� ���� �� GameOver
			//bool isGameOver = false;
			float timeSinceGameOver = 0.f;

			// ���������� ��������� ���� GameMenu

			GameState currentState = GameState::MainMenu;
			GameState lastState = GameState::MainMenu;

			int apple_count = 0;

			// ������
			Texture player_texture;
			Texture apple_texture;
			Texture barricade_texture;

			SoundBuffer apple_eat_buffer;
			SoundBuffer death_buffer;
		
			Sound apple_eating;
			Sound death;

			Font font;

			std::vector<HighScore> highScoresNoAcceleration;
			std::vector<HighScore> highScoresAcceleration;
		};



		void InitHighScores(Game& game);

		//������� ������������� ����
		void InitGame(Game& game);

		bool HasGameSettings(const Game& game, GameSettingsBits setting);

		void EnableGameSetting(Game& game, GameSettingsBits setting);

		void DisableGameSetting(Game& game, GameSettingsBits setting);

		void SetGameMode(Game& game, GameSettingsBits setting);

		// ���������� ����
		void RestartGame(Game& game);

		// ���� ������������
		void HandleInput(Game& game, RenderWindow& window);

		// ������� ���������� ��������� ����
		void UpdateGame(Game& game, float delta_time);

		// ������� ��������� ����
		void DrawGame(Game& game, RenderWindow& window);

		// ��������������� ����
		void DeinializeGame(Game& game);
	}

