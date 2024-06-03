#pragma once
#include"entity.h"
#include<vector>
#include<string>
#include"animator.h"

enum class _state {WalkAround, Hungry};

class Sim: protected Entity {
private:
	//TO DO
public:
	Animator _animator;

	Sim(float pos_x, float pos_y, sf::RenderWindow& rw): _animator(rw), Entity(pos_x, pos_y) {};


	void move(float x, float y) {
		Entity::x += x;
		Entity::y += y;
		_animator.move(x, y);
	}
};