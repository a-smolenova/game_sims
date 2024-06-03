#pragma once
#include"SFML/Graphics/View.hpp"
#include"entity.h"
#include<iostream>

class Camera {
private:
	sf::View cam;
	sf::Vector2f _last_pos = sf::Vector2f(0,0);

	double _x = 0;
	double _y = 0;
	int _zoom = 1;
public:;


	sf::View& getView() {
		return cam;
	}

	void setLastPosition(sf::Vector2i _target) {
		_last_pos = sf::Vector2f(_target.x, _target.y);
	}
	
	void setLastPosition(sf::Vector2f _target) {
		_last_pos = _target;
	}
	void update(sf::Vector2i& _target) {
		//cam.move();
		sf::Vector2f deltaP(_last_pos.x - _target.x, _last_pos.y - _target.y);
		//if(abs(deltaP.x) + abs(deltaP.y) >= 5)
			cam.move(deltaP * 1.5f*(cam.getSize().x/800));

		_last_pos = sf::Vector2f(_target.x, _target.y);
	}
	void update() {
		cam.setCenter(_last_pos);
	}

	void updateZoom(int number) {
		if (number > 0 && _zoom <= 100) {
			_zoom += number;
			cam.zoom(abs(number) / 50.0f + 1);
		}
		else if (number < 0 && _zoom >= -20) {
			_zoom += number;
			cam.zoom(1- abs(number)/ 50.0f );
		}
	}
};