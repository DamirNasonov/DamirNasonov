#pragma once
#include "SFML/Graphics.hpp"


namespace AppleGame
{
	using namespace sf;

	struct UI
	{

		bool isGameOverTextVisible = false;
		bool isMainMenuTextVisible = false;
		bool isHighScoreScreenVisible = true;
		bool isExitDialogVisible = false;

		// Общие текстовые элементы
		Text score_text;
		Text input_text;

		// Элементы для диалогового окана "Вы хотите выйти?"
		Text exit_dialog_text;
		Text exit_choise_text;

		// Элементы для экрана смерти
		Text game_over_text;
		Text death_screen_help_text;
		Color game_over_text_color;

		// Текстовывый элемент для таблицы рекордов
		Text high_score_text;
		Text player_text;

		// Текстовые элементы для режимов
		Text acceleration_text;
		Text infinity_apples_text;

		// Текстовые элементы для ON/OFF
		Text acceleration_on_off;
		Text infinity_apples_on_off;

		// Текстовые элементы для главного меню, экрана рекордов
		Text main_menu_help_text;
		Text high_score_screen_help_text;
		Text press_space_start_game_text;
		
		// Элементы для паузы
		Text pause_text;
		Text pause_help_text;
		Color pause_color;

		// Оверелей для паузы
		RectangleShape pause_overlay;
	};


	void InitUI(UI& uiState, Font& font);
	void UpdateUI(UI& uiState, const struct Game& game, float delta_time);
	void DrawUI(UI& uiState, RenderWindow& window, const struct Game& game);

}