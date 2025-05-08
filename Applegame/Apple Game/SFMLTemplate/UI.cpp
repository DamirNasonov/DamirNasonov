#include "UI.h"
#include "Game.h"
#include <string>

namespace AppleGame
{
	void InitUI(UI& uiState, Font& font)
	{
		setlocale(LC_ALL, "Rus");

		// Инициализация счётчика очков
		uiState.score_text.setFont(font);
		uiState.score_text.setCharacterSize(24);
		uiState.score_text.setFillColor(Color::Yellow);

		// Инициализация подсказки об управлении персонажем
		uiState.input_text.setFont(font);
		uiState.input_text.setCharacterSize(24);
		uiState.input_text.setFillColor(Color::White);
		uiState.input_text.setString("Use arrow keys to move");
		uiState.input_text.setOrigin(GetTextOrigin(uiState.input_text, { 1.f, 0.f }));

		// Инициализация тексового элемента Game Over
		uiState.isGameOverTextVisible = false;
		uiState.game_over_text.setFont(font);
		uiState.game_over_text.setCharacterSize(48);
		uiState.game_over_text.setStyle(Text::Bold);
		uiState.game_over_text.setFillColor(Color::Red);
		uiState.game_over_text.setString("Game Over");
		uiState.game_over_text.setOrigin(GetTextOrigin(uiState.game_over_text, { 0.5f, 0.5f }));

		uiState.isMainMenuTextVisible = false;

		// Инициализация текстовых элементов для режимов
		uiState.acceleration_text.setFont(font);
		uiState.acceleration_text.setCharacterSize(24);
		uiState.acceleration_text.setStyle(Text::Bold);
		uiState.acceleration_text.setFillColor(Color::White);
		uiState.acceleration_text.setString("Acceleration Mode");

		uiState.infinity_apples_text.setFont(font);
		uiState.infinity_apples_text.setCharacterSize(24);
		uiState.infinity_apples_text.setStyle(Text::Bold);
		uiState.infinity_apples_text.setFillColor(Color::White);
		uiState.infinity_apples_text.setString("Infinity Apples");

		// Инициализация текстовых элементов для ON/OFF
		uiState.acceleration_on_off.setFont(font);
		uiState.acceleration_on_off.setCharacterSize(24);
		uiState.acceleration_on_off.setStyle(Text::Bold);
		uiState.acceleration_on_off.setFillColor(Color::White);
		uiState.acceleration_on_off.setString("OFF");

		uiState.infinity_apples_on_off.setFont(font);
		uiState.infinity_apples_on_off.setCharacterSize(24);
		uiState.infinity_apples_on_off.setStyle(Text::Bold);
		uiState.infinity_apples_on_off.setFillColor(Color::White);
		uiState.infinity_apples_on_off.setString("OFF");

		// Инициализация текстового элемента "Press Space to start"
		uiState.press_space_start_game_text.setFont(font);
		uiState.press_space_start_game_text.setCharacterSize(24);
		uiState.press_space_start_game_text.setStyle(Text::Bold);
		uiState.press_space_start_game_text.setFillColor(Color::White);
		uiState.press_space_start_game_text.setString("Press 'Space' to start game");

		// Инициализация текстовых подсказок в главном меню
		uiState.main_menu_help_text.setFont(font);
		uiState.main_menu_help_text.setCharacterSize(24);
		uiState.main_menu_help_text.setStyle(Text::Regular);
		uiState.main_menu_help_text.setFillColor(Color::White);
		string main_menu_help_input =
			"Help!\n"
			"Press 1: Acceleration mode\n"
			"Press 2: No Acceleration mode\n"
			"Press 3: Infinity Apples mode\n"
			"Press 4: Limited Apples mode\n\n"
			"Press 'S' - Score Screen (Only Infinity Apples Mode)\n"
			"Press 'ESC' - Exit";
		uiState.main_menu_help_text.setString(main_menu_help_input);

		// Инициализация текста в таблице рекордов
		uiState.high_score_text.setFont(font);
		uiState.high_score_text.setCharacterSize(24);
		uiState.high_score_text.setFillColor(Color::White);

		// Инициализация подсказок на экране смерти
		uiState.death_screen_help_text.setFont(font);
		uiState.death_screen_help_text.setCharacterSize(24);
		uiState.death_screen_help_text.setStyle(Text::Regular);
		uiState.death_screen_help_text.setFillColor(Color::White);
		string death_screen_help_input =
			"Help!\n"
			"Press 'Space' - Restart \n"
			"Press 'B' - Back to Main Menu\n"
			"Press 'ESC' - Exit\n";
		uiState.death_screen_help_text.setString(death_screen_help_input);

		// Инициализация подсказок на экране рекордов
		uiState.high_score_screen_help_text.setFont(font);
		uiState.high_score_screen_help_text.setCharacterSize(24);
		uiState.high_score_screen_help_text.setStyle(Text::Regular);
		uiState.high_score_screen_help_text.setFillColor(Color::White);
		string high_score_screen_help_input =
			"Help!\n"
			"Press 'B' - Back to Main Menu\n"
			"Press 'ESC' - Exit\n";
		uiState.high_score_screen_help_text.setString(high_score_screen_help_input);

		// Инициализация имени игрока
		uiState.player_text.setFont(font);
		uiState.player_text.setCharacterSize(24);

		// Общая инициализация диалогового окна "Вы хотите выйти?"
		// Инициализация текста
		uiState.exit_dialog_text.setFont(font);
		uiState.exit_dialog_text.setCharacterSize(48);
		uiState.exit_dialog_text.setStyle(Text::Bold);
		uiState.exit_dialog_text.setFillColor(Color::White);
		uiState.exit_dialog_text.setString("Do you want to exit?");
		uiState.exit_dialog_text.setOrigin(GetTextOrigin(uiState.exit_dialog_text, { 0.5f, 0.5f }));

		// Инициализация навигации в диалоговом окне "Вы хотите выйти?"
		uiState.exit_choise_text.setFont(font);
		uiState.exit_choise_text.setCharacterSize(36);
		uiState.exit_choise_text.setStyle(Text::Regular);
		uiState.exit_choise_text.setFillColor(Color::White);
		string exit_help =
			"Press 'Y' - Yes\n"
			"Press 'N' - No";
		uiState.exit_choise_text.setString(exit_help);
		uiState.exit_choise_text.setOrigin(GetTextOrigin(uiState.exit_choise_text, { 0.5f, 0.5f }));

		// Общая инициализация паузы
		// Инициалиция оверлея
		uiState.pause_overlay.setSize({SCREEN_WIDTH, SCREEN_HEIGHT});
		uiState.pause_overlay.setFillColor(Color(0, 0, 0, 150)); // Где 150 - альфа канал

		// Инициализация текста
		uiState.pause_text.setFont(font);
		uiState.pause_text.setString("Pause");
		uiState.pause_text.setCharacterSize(48);
		uiState.pause_text.setStyle(Text::Bold);
		uiState.pause_text.setFillColor(Color::Yellow);
		uiState.pause_text.setOrigin(GetTextOrigin(uiState.pause_text, { 0.5f, 0.5f }));

		// Инициализация навигации в режиме паузы
		uiState.pause_help_text.setFont(font);
		uiState.pause_help_text.setCharacterSize(24);
		uiState.pause_help_text.setStyle(Text::Regular);
		uiState.pause_help_text.setFillColor(Color::White);
		string pause_help =
			"Help!\n"
			"Press 'R' - Returne to game\n"
			"Press 'Space' - Restart\n"
			"Press 'B' - Back to main menu\n"
			"Press 'E' - Exit";
		uiState.pause_help_text.setString(pause_help);
	}

	void UpdateUI(UI& uiState, const Game& game, float delta_time)
	{
		// Обновление счётчика очков
		uiState.score_text.setString("Apple eaten: " + to_string(game.num_eaten_apples));

		// Мигающий цвет для текстового элемента "Game Over"
		if (game.currentState == GameState::GameOver)
		{
			uiState.game_over_text_color = (int)game.timeSinceGameOver % 2 ? Color::Red : Color::Yellow;
			uiState.game_over_text.setFillColor(uiState.game_over_text_color);
		}

		// Мигающий цвет для текстового элемента "Pause"
		if (game.currentState == GameState::Pause)
		{
			uiState.pause_color = (int)game.timeSinceGameOver % 2 ? Color::Yellow : Color::Green;
			uiState.pause_text.setFillColor(uiState.pause_color);
		}

		// Обновление текста ON/OFF для режимов
		// Если выбран режим игры с ускорением, тогда отмечаем Acceleration Mode как ON
		if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
		{
			uiState.acceleration_on_off.setString("ON");
			uiState.acceleration_on_off.setFillColor(Color::Green);
		}
		//Если выбран режим игры с ускорением, тогда отмечаем Acceleration Mode как OFF
		else
		{
			uiState.acceleration_on_off.setString("OFF");
			uiState.acceleration_on_off.setFillColor(Color::White);
		}
		// Если выбран режим игры c бесконечным количеством яблок, тогда отмечаем Infinity Apple как ON
		if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
		{
			uiState.infinity_apples_on_off.setString("ON");
			uiState.infinity_apples_on_off.setFillColor(Color::Green);
		}
		// Если выбран режим игры c ограниченым количеством яблок, тогда отмечаем Infinity Apple как ON
		else
		{
			uiState.infinity_apples_on_off.setString("OFF");
			uiState.infinity_apples_on_off.setFillColor(Color::White);
		}
	}

	void DrawUI(UI& uiState, RenderWindow& window, const Game& game)
	{
		if (game.currentState == GameState::Playing)
		{
			// Отрисовка счётчика очков
			uiState.score_text.setPosition(10.f, 10.f);
			window.draw(uiState.score_text);

			// Отрисовка подсказки управления персонажем
			uiState.input_text.setPosition(window.getSize().x - 10.f, 10.f);
			window.draw(uiState.input_text);
		}
		
		// Отрисовка экрана паузы
		if (game.currentState == GameState::Pause)
		{
			// Отрисовка текста "Pause"
			uiState.pause_text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 200.f);
			window.draw(uiState.pause_text);

			// Отрисовка навигации в меню паузы
			uiState.pause_help_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - (-100.f));
			window.draw(uiState.pause_help_text);
		}

		// Если персонаж столкнулся с препятствием или границей экрана, отрисовываем надпись GAME OVER
		// Отрисовка экрана смерти
		if (game.currentState == GameState::GameOver)
		{
			// Отрисовка текста "Game Over"
			uiState.game_over_text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 200.f);
			window.draw(uiState.game_over_text);

			// Отрисовка таблицы рекордов (только если выбрана комбинация "Бесконечные яблоки")
			if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
			{
				string highScoreString;
				const std::vector<HighScore>* currentHighScore = nullptr;

				// Выбор таблицы рекордов в зависимости от режима
				if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
				{
					currentHighScore = &game.highScoresAcceleration;
					highScoreString = "High Scores (Acceleration Mode):\n\n";
				}
				else
				{
					currentHighScore = &game.highScoresNoAcceleration;
					highScoreString = "High Scores (No Acceleration Mode):\n\n";
				}

				if (currentHighScore != nullptr && !currentHighScore->empty())
				{
					float yOffset = window.getSize().y / 2.f - 125.f;

					// 1. Определяем наибольший счёт игрока Player
					int maxPlayerScore = -1;
					for (const auto score : *currentHighScore)
					{
						if (score.name == "Player")
						{
							maxPlayerScore = std::max(maxPlayerScore, score.score);
						}
					}

					// 2. Отрисовка рекордов
					for (const auto score : *currentHighScore)
					{
						// 3. Если этот `Player` — с максимальным счётом, выделяем его зелёным
						if (score.name == "Player" && score.score == maxPlayerScore)
						{
							uiState.high_score_text.setFillColor(Color::Green);
						}
						else
						{
							uiState.high_score_text.setFillColor(Color::White);
						}

						// Устанавливаем текст и рисуем
						uiState.high_score_text.setString(score.name + ":  " + std::to_string(score.score));
						uiState.high_score_text.setPosition(window.getSize().x / 2.f - 150.f, yOffset);
						window.draw(uiState.high_score_text);

						yOffset += 30.f;
					}
				}
			}
			
			//Отрисовка навигации на экране смерти
			uiState.death_screen_help_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f + 100.f);
			window.draw(uiState.death_screen_help_text);

		}
		
		// Если персонаж находится в главном меню тогда отрисовываем надписи режимов и их состояния ON или OFF
		if (game.currentState == GameState::MainMenu)
		{
			// Отрисовка текстовых элементов для режимов
			uiState.acceleration_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 150.f);
			window.draw(uiState.acceleration_text);

			uiState.acceleration_on_off.setPosition(window.getSize().x / 2.f + 150.f, window.getSize().y / 2.f - 150.f);
			window.draw(uiState.acceleration_on_off);

			uiState.infinity_apples_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 115.f);
			window.draw(uiState.infinity_apples_text);

			uiState.infinity_apples_on_off.setPosition(window.getSize().x / 2.f + 150.f, window.getSize().y / 2.f - 115.f);
			window.draw(uiState.infinity_apples_on_off);

			// Отрисовка текстового элемента "Press Space to start"
			uiState.press_space_start_game_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - 50.f);
			window.draw(uiState.press_space_start_game_text);

			// Отрисовка подсказки с выбором режима игры
			uiState.main_menu_help_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f - (-50.f));
			window.draw(uiState.main_menu_help_text);
		}

		// Отрисовка экрана рекордов
		if (game.currentState == GameState::HighScoreScreen)
		{
			if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
			{
				string highScoreString;
				const std::vector<HighScore>* currentHighScore = nullptr;

				// Выбор таблицы рекордов в зависимости от режима
				if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
				{
					if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
					{
						currentHighScore = &game.highScoresAcceleration;
						highScoreString = "High Scores (Acceleration Mode):\n\n";
					}
					else if (HasGameSettings(game, GameSettingsBits::Mod_No_Acceleration))
					{
						currentHighScore = &game.highScoresNoAcceleration;
						highScoreString = "High Scores (No Acceleration Mode):\n\n";
					}

					if (currentHighScore != nullptr && !currentHighScore->empty())
					{
						float yOffset = window.getSize().y / 2.f - 125.f;

						// 1. Определяем наибольший счёт игрока Player
						int maxPlayerScore = -1;
						for (const auto& score : *currentHighScore)
						{
							if (score.name == "Player")
							{
								maxPlayerScore = std::max(maxPlayerScore, score.score);
							}
						}

						// 2. Отрисовка рекордов
						for (const auto& score : *currentHighScore)
						{
							// 3. Если этот `Player` — с максимальным счётом, выделяем его зелёным
							if (score.name == "Player" && score.score == maxPlayerScore)
							{
								uiState.high_score_text.setFillColor(Color::Green);
							}
							else
							{
								uiState.high_score_text.setFillColor(Color::White);
							}

							// Устанавливаем текст и рисуем
							uiState.high_score_text.setString(score.name + ":  " + std::to_string(score.score));
							uiState.high_score_text.setPosition(window.getSize().x / 2.f - 150.f, yOffset);
							window.draw(uiState.high_score_text);

							yOffset += 30.f;
						}
					}
				}

				// Отрисовка навигации на экране рекордов 
				uiState.high_score_screen_help_text.setPosition(window.getSize().x / 2.f - 150.f, window.getSize().y / 2.f + 100.f);
				window.draw(uiState.high_score_screen_help_text);
			}
		}

		// Отрисовка диалогового окна "Вы хотите выйти?"
		if (game.currentState == GameState::ExitDialog)
		{
			uiState.exit_dialog_text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f - 100.f);
			window.draw(uiState.exit_dialog_text);


			uiState.exit_choise_text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f + 50.f);
			window.draw(uiState.exit_choise_text);
		}
	}
}