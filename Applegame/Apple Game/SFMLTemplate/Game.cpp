#include "Game.h"
#include "UI.h"
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <algorithm>

namespace AppleGame
{

	// Функция для удаления дубликатов и заполнения таблиц уникальными именами
	void RemoveDuplicatesAndFill(std::vector<HighScore>& highScores, const std::string* names, int namesCount)
	{
		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			// Проверяем, есть ли дубликаты имени в таблице
			auto it = std::find_if(highScores.begin(), highScores.end(), [&highScores, i](const HighScore& hs) 
				{
					return hs.name == highScores[i].name && &hs != &highScores[i];
				});

			// Если дубликат найден, заменяем его новым именем
			while (it != highScores.end())
			{
				highScores[i].name = names[rand() % namesCount]; // Генерируем новое имя
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

		// Инициализация таблицы для режима "Без ускорения + бесконечные яблоки"
		game.highScoresNoAcceleration.resize(MAX_HIGH_SCORE);

		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			game.highScoresNoAcceleration[i] = { names[rand() % 20], rand() % 91 + 10 };
		}

		// Инициализация таблицы для режима "С ускорением + бесконечные яблоки"
		game.highScoresAcceleration.resize(MAX_HIGH_SCORE);
		
		for (int i = 0; i < MAX_HIGH_SCORE; ++i)
		{
			game.highScoresAcceleration[i] = { names[rand() % 20], rand() % 91 + 10 };
		}

		RemoveDuplicatesAndFill(game.highScoresNoAcceleration, names, 20);
		RemoveDuplicatesAndFill(game.highScoresAcceleration, names, 20);
		
		// Сортировка таблиц по убыванию очков
		std::sort(game.highScoresNoAcceleration.begin(), game.highScoresNoAcceleration.end(), [](const HighScore& a, const HighScore& b) {
			return a.score > b.score;
			});

		std::sort(game.highScoresAcceleration.begin(), game.highScoresAcceleration.end(), [](const HighScore& a, const HighScore& b) {
			return a.score > b.score;
			});
	}

	//Функция инициализации игры
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

		//Установка режимов игры по умолчанию
		EnableGameSetting(game, GameSettingsBits::Mod_No_Acceleration);
		EnableGameSetting(game, GameSettingsBits::Mod_Limited_Apples);

		InitHighScores(game);
	}

	/*
		 Функция HasGameSettings проверяет, установлен ли конкретный игровой режим, представленный битом в настройках игры.

		 Параметры:
		 - game: Константная ссылка на объект Game, который содержит информацию о текущем режиме игры.
			Используется для доступа к полю gameMode, в котором хранятся битовые настройки игры.
		 - setting: Значение типа GameSettingsBits, представляющее конкретный бит (режим игры), который нужно проверить.

		 Возвращаемое значение:
		 Функция возвращает true (истина), если указанный бит (режим игры) установлен в game.gameMode, иначе возвращает false (ложь).
	*/
	bool HasGameSettings(const Game& game, GameSettingsBits setting)
	{
		return (game.gameMode & static_cast<int>(setting)) != 0;
	}

	// Функция включает режим игры
	void EnableGameSetting(Game& game, GameSettingsBits setting)
	{
		game.gameMode |= static_cast<int>(setting);
	}

	// Функция отключает режим игры
	void DisableGameSetting(Game& game, GameSettingsBits setting)
	{
		game.gameMode &= ~static_cast<int>(setting);
	}

	/*
		 Функция комбинирует игровые режимы.
		 Доступны 4 режима:
		 1. Ускорение + бесконечные яблоки;
		 2. Без ускорения + бесконечные яблоки;
		 3. Ускорение + ограниченные яблоки;
		 4. Без ускорения + ограниченные яблоки.

		 Выбор режима "Ускорение" и "Без ускорения", или "Бесконечные яблоки" и "Ограниченные яблоки" невозможен.
		 Включены проверки для исключения противоречивых настроек.
	*/
	void SetGameMode(Game& game, GameSettingsBits setting)
	{
		// Если игрок выбирает режим "Ускорение", отключаем режим "без ускорения"
		if (setting & GameSettingsBits::Mod_Acceleration)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_No_Acceleration);
		}
		// Если игрок выбирает режим "Без ускорения", отключаем режим "Ускорение"
		else if (setting & GameSettingsBits::Mod_No_Acceleration)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Acceleration);
		}

		// Если игрок выбирает режим "Бесконечные яблоки", отключаем режим "Ограниченные яблоки"
		if (setting & GameSettingsBits::Mod_Infinity_Apples)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Limited_Apples);
		}
		// Если игрок выбирает режим "Ограниченные яблоки, отключаем режим "Бесконечные яблоки"
		else if (setting & GameSettingsBits::Mod_Limited_Apples)
		{
			DisableGameSetting(game, GameSettingsBits::Mod_Infinity_Apples);
		}

		// Устанавливаем выбранный режим
		EnableGameSetting(game, setting);
	}


	void RestartGame(Game& game)
	{
		// Сброс уровня и Новая игра
		game.currentState = GameState::Playing;

		game.num_eaten_apples = 0;
		
		game.timeSinceGameOver = 0.f;

		game.apple_count = rand() % 11 + 20; 

		InitPlayer(game.player, game);

		//Сброс яблок в нулевое значение. Этот цикл необходим во избежание неккоректного поведения программы.
		game.apples.clear();

		// Cпавн яблок
		game.apples.resize(game.apple_count);
		for (int i = 0; i < game.apple_count; ++i)
		{
			InitApple(game.apples[i], game);
		}

		// Спавн препятствий
		for (int i = 0; i < BARRICADE_NUM; ++i)
		{
			InitBarricade(game.barricade[i], i, game);
		}
	}

	void HandleInput(Game& game, RenderWindow& window)
	{

		// Выбор режима игры, непосредственный переход к игре, рекордам или диалоговому окну выхода
		switch (game.currentState)
		{
		case GameState::MainMenu:

			/* Установка режимов игры
			Num 1 - Режим игры с ускорением
			Num 2 - Режим игры без ускорения
			Num 3 - Режим игры с бесконечными яблоками
			Num 4 - Режим игры с ограниченными яблоками
			*/
			if (Keyboard::isKeyPressed(Keyboard::Num1)) SetGameMode(game, GameSettingsBits::Mod_Acceleration);
			if (Keyboard::isKeyPressed(Keyboard::Num2)) SetGameMode(game, GameSettingsBits::Mod_No_Acceleration);
			if (Keyboard::isKeyPressed(Keyboard::Num3)) SetGameMode(game, GameSettingsBits::Mod_Infinity_Apples);
			if (Keyboard::isKeyPressed(Keyboard::Num4)) SetGameMode(game, GameSettingsBits::Mod_Limited_Apples);

			// Переход к таблице рекордов
			if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
			{
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					game.currentState = GameState::HighScoreScreen;
				}
			}

			// Переход к диалоговому окну выхода
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}

			// Переход к игре
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				RestartGame(game);
				game.currentState = GameState::Playing;
			}

			break;

			// Переход к игровому состоянию, он же запуск игры
		case GameState::Playing:

			// Управление игрока
			PlayerMovemetn(game.player);

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				game.currentState = GameState::Pause;
			}
			break;
		
			// Переход к состоянию паузы
		case GameState::Pause:
			
			// При нажатии на "R" происходит возврат в игру 
			if (Keyboard::isKeyPressed(Keyboard::R))
			{
				game.currentState = GameState::Playing;
			}

			// При нажатии на "Space" происходит перезапуск игры
			else if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				RestartGame(game);
				game.currentState = GameState::Playing;
			}

			// При нажатии на "B" происходит возврат в главное меню
			else if (Keyboard::isKeyPressed(Keyboard::B))
			{
				game.currentState = GameState::MainMenu;
			}

			// При нажатии на "E" происходит вызов диалогового окна "Вы хотите выйти?"
			else if (Keyboard::isKeyPressed(Keyboard::E))
			{
				game.lastState = game.currentState;
				game.currentState = GameState::ExitDialog;
			}
			break;

			// Переход к состоянию "Игра окночена", игроку дан выбор начать заново при нажатии на Space или вернуться в главное меню при нажатии на B
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

			// Переход к просмотру таблицы рекордов, отсюда игрок может только выйти в главное меню при нажатии на B
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
			
			// Переход к диалоговому окну "Вы хотите выйти?"
		case GameState::ExitDialog:
			if (Keyboard::isKeyPressed(Keyboard::Y))
			{
				window.close(); // Закрываем окно
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

		// Выбираем таблицу в зависимости от режима игры
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
				// Проверяем, попадает ли результат игрока в таблицу рекордов
				for (int i = 0; i < currentHighScore -> size(); ++i)
				{			
					if (game.num_eaten_apples >= (*currentHighScore)[i].score)
					{
						// Сдвигаем остальные записи в таблице вниз
						for (int j = currentHighScore->size() - 1; j > i; --j)
						{
							(*currentHighScore)[j] = (*currentHighScore)[j - 1];
						}
						// Вставляем результат игрока
						(*currentHighScore)[i] = { "Player", game.num_eaten_apples };
						break;
					}
				}
			}
		}
	}

	// Функция обновления состояния игры
	void UpdateGame(Game& game, float delta_time)
	{
		
		if (game.currentState == GameState::Playing && game.currentState != GameState::GameOver)
		{
			UpdatePlayer(game.player, delta_time);

			BarricadeMovement(game, delta_time);
			
			// Цикл проверяет не столкнулся ли игрок с яблоком
			for (int i = 0; i < game.apple_count; ++i)
			{
				// Если игрок пересекает яблоко, происходит спавн нового яблока в случайном месте на экране игры
				if (IsAppleCollide(game.player.player_position, PLAYER_SIZE / 2.f, game.apples[i].apple_position, APPLE_SIZE / 2.f))
				{
					++game.num_eaten_apples;
					game.apple_eating.play();

					// Если включён режим "С ускорением", увеличиваем скорость
					if (HasGameSettings(game, GameSettingsBits::Mod_Acceleration))
					{
						game.player.player_speed += ACCLERATION_SPEED;
					}

					// Если включён режим "Бесконечные яблоки", инициализируем новое яблоко
					if (HasGameSettings(game, GameSettingsBits::Mod_Infinity_Apples))
					{
						InitApple(game.apples[i], game);
					}
					// Если включен режим "Ограниченные яблоки", удаляем яблоки после их пересечения игроком
					else if (HasGameSettings(game, GameSettingsBits::Mod_Limited_Apples))
					{
						for (int j = i; j < game.apple_count - 1; ++j)
						{
							game.apples[j] = game.apples[j + 1];
						}
						--game.apple_count;

						// Если съели все яблоки, устанавливаем значение переменной isGameMenu true и отправляем игрока в меню 
						if (game.apple_count == 0)
						{
							GameState::MainMenu;
							return;
						}
					}
				}
			}

			// Цикл проверяет не столкнулся ли игрок с препятствием
			for(int j = 0; j < BARRICADE_NUM; ++j)
			{
				// Проверки на столкновение с препятствием и перезапуск игры.
				if (IsBarricadeleCollide(game.player.player_position, { PLAYER_SIZE, PLAYER_SIZE }, game.barricade[j].barricade_position, { BARRICADE_SIZE_X, BARRICADE_SIZE_Y }))
				{
					game.death.play();
					game.currentState = GameState::GameOver;
					game.player.isDead = true;
					game.timeSinceGameOver = 0.f;
					UpdateHighScore(game);
				}
			}

			// Проверка: Если объект игрока выходит за границы экрана по любой из сторон (слева, справа, сверху или снизу), тогда игра перезапускается)
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

		// Обновление пользовательского интерфейса
		UpdateUI(game.uiState, game, delta_time);
	}

	// Функция отрисовки игры
	void DrawGame(Game& game, RenderWindow& window)
	{
		if (game.currentState == GameState::Playing && game.currentState != GameState::GameOver)
		{
			DrawPlayer(game.player, window);

			// Цикл отрисовывающий заданное константой кол-во яблок
			for (int i = 0; i < game.apple_count; ++i)
			{
				// Отрисовка яблок
				window.draw(game.apples[i].apple_sprite);

			}

			// Цикл отрисовывающий заданное константой кол-во препятствий
			for (int i = 0; i < BARRICADE_NUM; ++i)
			{
				// Отрисовка препятствий
				window.draw(game.barricade[i].barricade_sprite);
			}
		}
			// Отрисовка пользовательского интерфейса
			DrawUI(game.uiState, window, game);
	}

	void DeinializeGame(Game& game)
	{

	}

}