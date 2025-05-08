#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

 
namespace sf
{
	class Sprite;
}

namespace AppleGame
{
	using namespace sf;
	struct Vector2D
	{
		float x = 0.f;
		float y = 0.f;
	};

	typedef Vector2D Position2D;

	Position2D GetRandomPositionInScreen(float screen_wight, float screen_height);

	Position2D GetBarricadePosition(float screen_wight, float screen_height, int index);

	bool IsBarricadeleCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size);

	bool IsAppleCollide(Position2D playerPosition, float playerRadius, Position2D applePosition, float appleRadius);

	void SetSpriteSize(Sprite& sprite, float desired_wight, float deisred_height);

	void SetSpriteRelativeOrigin(Sprite& sprite, float origin_x, float origin_y);

	Vector2f GetTextOrigin(const Text& text, const Vector2D& relativePosition);
}