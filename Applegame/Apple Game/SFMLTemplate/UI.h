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

		// ����� ��������� ��������
		Text score_text;
		Text input_text;

		// �������� ��� ����������� ����� "�� ������ �����?"
		Text exit_dialog_text;
		Text exit_choise_text;

		// �������� ��� ������ ������
		Text game_over_text;
		Text death_screen_help_text;
		Color game_over_text_color;

		// ����������� ������� ��� ������� ��������
		Text high_score_text;
		Text player_text;

		// ��������� �������� ��� �������
		Text acceleration_text;
		Text infinity_apples_text;

		// ��������� �������� ��� ON/OFF
		Text acceleration_on_off;
		Text infinity_apples_on_off;

		// ��������� �������� ��� �������� ����, ������ ��������
		Text main_menu_help_text;
		Text high_score_screen_help_text;
		Text press_space_start_game_text;
		
		// �������� ��� �����
		Text pause_text;
		Text pause_help_text;
		Color pause_color;

		// �������� ��� �����
		RectangleShape pause_overlay;
	};


	void InitUI(UI& uiState, Font& font);
	void UpdateUI(UI& uiState, const struct Game& game, float delta_time);
	void DrawUI(UI& uiState, RenderWindow& window, const struct Game& game);

}