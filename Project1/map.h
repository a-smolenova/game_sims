#pragma once
#include<vector>
#include<fstream>
#include"block.h"


class Map {
private:
	std::vector<std::vector<Block>> _map;
	sf::Texture _texture;
public:
	Map(std::string _map_name, sf::RenderWindow& rw)
	{
		_texture.loadFromFile("Sprites/floor.png");
		std::ifstream file;
		file.open(_map_name);
		int i = 0;
		int j = 0;
		_map.push_back(std::vector<Block>());
		while (file.is_open() && !file.eof()) {
			char in_char;
			file >> in_char;
			if (in_char == 'f') {
				_map[i].push_back(Block(0,0, rw));
				_map[i][j]._animator.addState(State("idle", 0, 2, _texture));
				_map[i][j].setCollide(false);
				_map[i][j].x = j * 360;
				_map[i][j].y = i * 360;
				_map[i][j]._animator.move(j * 360, i * 360);
				_map[i][j]._animator.update();
				++j;
			}
			else if (in_char == 'w') {
				_map[i].push_back(Block(0,0, rw));
				_map[i][j]._animator.addState(State("idle", 0, 2, _texture));
				_map[i][j].x = j * 360;
				_map[i][j].y = i * 360;
				_map[i][j]._animator.move(j * 360, i * 360);
				++j;
			}
			else if (in_char == ' ') {
				_map[i].push_back(Block(0,0,rw));
			}
			else if (in_char == '/') {
				_map.push_back(std::vector<Block>());
				++i;
				j = 0;
			}
		}
	};

	void draw_map() {
		for (int i = 0; i < _map.size(); ++i) {
			for (int j = 0; j < _map[i].size(); ++j) {
				_map[i][j]._animator.draw();
			}
		}
	}


	bool isColide(float x, float y, sf::Vector2i size) {
		for (int i = 0; i < _map.size(); ++i) {
			for (int j = 0; j < _map[i].size(); ++j) {
				/*x -= _map[i][j].x;
				y -= _map[i][j].y;*/
				/*std::cout << int(_map[i][j]._animator.getSprite().getTextureRect().contains(x + size.x / 2, y - size.y / 2)) << " - " << int(_map[i][j]._animator.getSprite().getTextureRect().contains(x - size.x / 2, y + size.y / 2)) << " - "
					<< int(_map[i][j]._animator.getSprite().getTextureRect().contains(x + size.x, y + size.y / 2)) << " - " << int(_map[i][j]._animator.getSprite().getTextureRect().contains(x - size.x, y + size.y / 2)) << "\n";*/
				//std::cout << _map[i][j]._animator.getSprite().getPosition().x << " - " << _map[i][j]._animator.getSprite().getPosition().y << "\n";
				//std::cout << x << " - " << y << '\n';
				if (_map[i][j].isCollide() && (_map[i][j]._animator.getSprite().getGlobalBounds().contains(x + size.x/2, y) || _map[i][j]._animator.getSprite().getGlobalBounds().contains(x - size.x/2, y) ||
					_map[i][j]._animator.getSprite().getGlobalBounds().contains(x, y - size.y/2) || _map[i][j]._animator.getSprite().getGlobalBounds().contains(x, y + size.y/2)))
					return true;
			}
		}
		return false;
	}

};