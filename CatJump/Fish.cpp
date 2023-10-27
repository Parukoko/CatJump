#include <chrono>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Animation.h"
#include "Global.h"
#include "MapManager.h"
#include "Fish.h"

Fish::Fish(const float i_x, const float i_y) :
	dead(0),
	horizontal_direction(1),
	vertical_speed(0),
	x(i_x),
	y(i_y),
	start_y(i_y)
{
	texture.loadFromFile("Resources/fish.png");
}

bool Fish::get_dead() const
{
	return dead;
}

void Fish::draw(const unsigned i_view_x, sf::RenderWindow& i_window)
{
	if (-CELL_SIZE < round(y) && round(x) > static_cast<int>(i_view_x) - CELL_SIZE && round(x) < SCREEN_WIDTH + i_view_x && round(y) < SCREEN_HEIGHT)
	{
		sprite.setPosition(round(x), round(y));
		sprite.setTexture(texture);

		i_window.draw(sprite);
	}
}

void Fish::set_dead(const bool i_value)
{
	dead = i_value;
}

void Fish::update(const unsigned i_view_x, const MapManager& i_map_manager)
{

	if (0 == dead)
	{
		if (-CELL_SIZE < y && x >= static_cast<int>(i_view_x) - CELL_SIZE - ENTITY_UPDATE_AREA && x < ENTITY_UPDATE_AREA + SCREEN_WIDTH + i_view_x && y < SCREEN_HEIGHT)
		{
			if (y > start_y - CELL_SIZE)
			{
				y -= FISH_SPEED;

				if (y <= start_y - CELL_SIZE)
				{
					y = start_y - CELL_SIZE;

					start_y = 2 * SCREEN_HEIGHT;
				}
			}
			else
			{
				std::vector<unsigned char> collision;

				sf::FloatRect horizontal_hit_box;

				vertical_speed = std::min(GRAVITY + vertical_speed, MAX_VERTICAL_SPEED);

				collision = i_map_manager.map_collision({ Cell::ActivatedQuestionBlock, Cell::Brick, Cell::Pipe, Cell::QuestionBlock, Cell::Wall }, sf::FloatRect(x, vertical_speed + y, CELL_SIZE, CELL_SIZE));

				if (0 == std::all_of(collision.begin(), collision.end(), [](const unsigned char i_value)
					{
						return 0 == i_value;
					}))
				{
					if (0 > vertical_speed)
					{
						y = CELL_SIZE * (1 + floor((vertical_speed + y) / CELL_SIZE));
					}
					else
					{
						y = CELL_SIZE * (ceil((vertical_speed + y) / CELL_SIZE) - 1);
					}

					vertical_speed = 0;
				}
				else
				{
					y += vertical_speed;
				}

				horizontal_hit_box = { FISH_SPEED * horizontal_direction + x, y, CELL_SIZE, CELL_SIZE };

				collision = i_map_manager.map_collision({ Cell::ActivatedQuestionBlock, Cell::Brick, Cell::Pipe, Cell::QuestionBlock, Cell::Wall }, horizontal_hit_box);

				if (0 == std::all_of(collision.begin(), collision.end(), [](const unsigned char i_value)
					{
						return 0 == i_value;
					}))
				{
					if (0 < horizontal_direction)
					{
						x = CELL_SIZE * (ceil((FISH_SPEED * horizontal_direction + x) / CELL_SIZE) - 1);
					}
					else
					{
						x = CELL_SIZE * (1 + floor((FISH_SPEED * horizontal_direction + x) / CELL_SIZE));
					}

					horizontal_direction *= -1;
				}
				else
				{
					x += FISH_SPEED * horizontal_direction;
				}
			}
		}

		if (SCREEN_HEIGHT <= y)
		{
			dead = 1;
		}
	}
}

sf::FloatRect Fish::get_hit_box() const
{
	return sf::FloatRect(x, y, CELL_SIZE, CELL_SIZE);
}