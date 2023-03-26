#include <iostream>
#include "SFML/Graphics.hpp"
#include <vector>

#define _CRTDBG_MAP_ALLOC
using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(500, 500), "Hello SFML", sf::Style::Close);
	sf::Event event;

	int** heat_map = new int* [256];
	for (int i = 0; i < 256; i++)
	{
		heat_map[i] = new int[256];
	}

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			heat_map[i][j] = 0;
		}
	}

	sf::Image world_map;
	world_map.loadFromFile("world.png");

	for (int i = 0; i < world_map.getSize().x; i++)
	{
		for (int j = 0; j < world_map.getSize().y; j++)
		{
			sf::Color pixel = world_map.getPixel(i, j);
			int x = pixel.b;
			int y = std::max(pixel.r, pixel.g);
			heat_map[x][y]++;
		}
	}

	vector<int> largest_values;
	largest_values.push_back(0);
	int index = 0;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (heat_map[i][j] > largest_values[index])
			{
				index++;
				largest_values.push_back(heat_map[i][j]);
			}
		}
	}

	for (int num : largest_values)
	{
		cout << num << "\n";
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		window.clear(sf::Color(0, 0, 0));
		window.display();
	}

	for (int i = 0; i < 255; i++)
	{
		delete[] heat_map[i];
	}
	delete[] heat_map;

	return 0;
}