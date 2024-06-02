#pragma once
#include"animator.h"
class Entity{	
public:
	int id = 0;
	float x;
	float y;
	float rotation = 0;
	Animator _animator;
	
	Entity(float x, float y, sf::RenderWindow& w) : x(x), y(y), _animator(w) {};
	Entity(float x, float y, float r, sf::RenderWindow& w) : x(x), y(y), rotation(r), _animator(w) {};

	void move(float x, float y) {
		_animator.move(x, y);
	}
	
	
};