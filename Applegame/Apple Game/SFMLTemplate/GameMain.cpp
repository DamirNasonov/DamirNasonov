#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"

using namespace std;
using namespace sf;
using namespace AppleGame;

int main()
{
	setlocale(LC_ALL, "");
	int seed = (int)time(nullptr);
	srand(seed);
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

	// Инициализация игры
	Game game;
	InitGame(game);

	// Инициализация счётчика времени
	Clock gameClock;
	float last_time = gameClock.getElapsedTime().asSeconds();

	// Основной цикл игры.
	while (window.isOpen())
	{
		// Счётчик времени кадров
		float current_time = gameClock.getElapsedTime().asSeconds();
		float delta_time = current_time - last_time;
		last_time = current_time;

		HandleInput(game, window);

		// Обработка событий
		Event close;
		while (window.pollEvent(close))
		{
			if (close.type == Event::Closed)
			{
				window.close();
			}
		}

		UpdateGame(game, delta_time);
		
		// Отрисовка экрана игры
		window.clear(); // Очистка игрового поля с прошлой итерации
		
		DrawGame(game, window);
		
		window.display(); // Обновление содержимого окна
	}
	// Деинициализация
	DeinializeGame(game);

	return 0;
}