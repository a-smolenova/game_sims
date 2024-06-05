#pragma once
#include<vector>
#include<fstream>
#include"block.h"
#include<queue>

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

	std::vector<sf::Vector2f> pathSearch(int _x, int _y, int _to_x, int _to_y) {

		std::queue<sf::Vector2i> q;

		sf::Vector2i p_h(-1,1);
		std::vector<std::vector<sf::Vector2i>> path(_map.size(), std::vector<sf::Vector2i>(_map[0].size(), sf::Vector2i(-1,-1)));
		std::vector<std::vector<bool>> used(_map.size(), std::vector<bool>(_map[0].size(), false));
		q.push(sf::Vector2i(_x/360,_y/360));

		while (!q.empty()) {
			sf::Vector2i v = q.front();
			q.pop();
			if (v.y + 1 < _map.size() && !_map[v.y + 1][v.x].isCollide() && used[v.y + 1][v.x] == false) {
				path[v.y + 1][v.x] = v;
				used[v.y + 1][v.x] = true;
				q.push(sf::Vector2i(v.x, v.y+1));
			}
			if (v.y - 1 > 0 && !_map[v.y - 1][v.x].isCollide() && used[v.y - 1][v.x] == false) {
				path[v.y - 1][v.x] = v;
				used[v.y - 1][v.x] = true;
				q.push(sf::Vector2i(v.x , v.y- 1));

			}
			if (v.x + 1 < _map.size() && !_map[v.y][v.x+1].isCollide() && used[v.y][v.x + 1] == false) {
				path[v.y][v.x + 1] = v;
				used[v.y][v.x + 1]  = true;
				q.push(sf::Vector2i(v.x+1, v.y));

			}
			if (v.x - 1 > 0 && !_map[v.y][v.x - 1].isCollide() && used[v.y][v.x - 1] == false) {
				path[v.y][v.x - 1] = v;
				used[v.y][v.x - 1] = true;
				q.push(sf::Vector2i(v.x-1, v.y));

			}
		}

		// если пути не существует, возвращаем пустой vector
		if (used[_to_y/360][_to_x/360] == false) {
			return {};
		}

		std::vector<sf::Vector2f> res_path;
		sf::Vector2i t(_to_x/360, _to_y/360);
		while (t.x != _x/360 || t.y != _y/360) {
			res_path.push_back(sf::Vector2f(t.x*360, t.y*360));
			t = path[t.y][t.x];
		}

		// путь был рассмотрен в обратном порядке, поэтому его нужно перевернуть
		reverse(res_path.begin(), res_path.end());
		return res_path;
	}

};