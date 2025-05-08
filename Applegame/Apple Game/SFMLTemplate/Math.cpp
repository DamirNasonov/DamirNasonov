	#include "Math.h"
	#include <SFML/Graphics.hpp>
	#include <cstdlib>


	namespace AppleGame
	{
	

		Position2D GetRandomPositionInScreen(float screen_width, float screen_height)
		{
			Position2D result;
			result.x = rand() / (float)RAND_MAX * screen_width;
			result.y = rand() / (float)RAND_MAX * screen_height;

			return result;
		}

		Position2D GetBarricadePosition(float screen_width, float screen_height, int index)
		{
			Position2D result;

			result.x = screen_width / 2.f + ((index == 0) ? -250 : 250);
			result.y = screen_height / 2.f;

			return result;
		}

		bool IsBarricadeleCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
		{
			float dx = fabs(rect1Position.x - rect2Position.x);
			float dy = fabs(rect1Position.y - rect2Position.y);

			return (dx <= (rect1Size.x + rect2Size.x) / 2.f) &&
				(dy <= (rect1Size.y + rect2Size.y) / 2.f);
		}

		bool IsAppleCollide(Position2D playerPosition, float playerRadius, Position2D applePosition, float appleRadius)
		{

			float sqr_distance = (playerPosition.x - applePosition.x) * (playerPosition.x - applePosition.x) + (playerPosition.y - applePosition.y) * (playerPosition.y - applePosition.y);
			float sqr_radius_sum = (playerRadius + appleRadius) * (playerRadius + appleRadius);

			return sqr_distance <= sqr_radius_sum;
		}
	
		void SetSpriteSize(Sprite& sprite, float desired_width, float deisred_height)
		{
			using namespace sf;

			FloatRect spriteRect	= sprite.getLocalBounds();
			Vector2f scale = { desired_width / spriteRect.width, deisred_height /spriteRect.height };
			sprite.setScale(scale);

		}

		void SetSpriteRelativeOrigin(Sprite& sprite, float origin_x, float origin_y)
		{
			FloatRect spriteRect = sprite.getLocalBounds();

			sprite.setOrigin(origin_x * spriteRect.width , origin_y * spriteRect.height);
		}

		Vector2f GetTextOrigin(const Text& text, const Vector2D& relativePosition)
		{
			FloatRect text_size = text.getLocalBounds();
			return
			{

			(text_size.left + text_size.width) * relativePosition.x, (text_size.top + text_size.height) * relativePosition.y,

			};
		}
	}

