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
			Mod_Acceleration = 1 << 0,       // Ускорение игрока
			Mod_No_Acceleration = 1 << 1,    // Без ускорения
			Mod_Infinity_Apples = 1 << 2,    // Бесконечные яблоки
			Mod_Limited_Apples = 1 << 3      // Ограниченное количество яблок
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


		// Структура игры
		struct Game
		{
			Player player;
			std::vector<Apple> apples;
			std::vector<Barricade> barricade;

			unsigned int gameMode = 0;

			UI uiState;

			// Подсчёт съеденных яблок, он же счёт
			int num_eaten_apples = 0;
		
			// Переменная изменяющая состояние игры на GameOver
			//bool isGameOver = false;
			float timeSinceGameOver = 0.f;

			// Переменная состояния игры GameMenu

			GameState currentState = GameState::MainMenu;
			GameState lastState = GameState::MainMenu;

			int apple_count = 0;

			// Ассеты
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

		//Функция инициализации игры
		void InitGame(Game& game);

		bool HasGameSettings(const Game& game, GameSettingsBits setting);

		void EnableGameSetting(Game& game, GameSettingsBits setting);

		void DisableGameSetting(Game& game, GameSettingsBits setting);

		void SetGameMode(Game& game, GameSettingsBits setting);

		// Перезапуск игры
		void RestartGame(Game& game);

		// Ввод передвижения
		void HandleInput(Game& game, RenderWindow& window);

		// Функция обновления состояния игры
		void UpdateGame(Game& game, float delta_time);

		// Функция отрисовки игры
		void DrawGame(Game& game, RenderWindow& window);

		// Деинициализация игры
		void DeinializeGame(Game& game);
	}

