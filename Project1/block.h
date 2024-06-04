#pragma once
#include"entity.h"
#include"animator.h"


class Block : public Entity {
private:
	bool _is_collide = true;
public:
	Animator _animator;
	Block(float pos_x, float pos_y, sf::RenderWindow& w) : Entity(pos_x, pos_y), _animator(w) {};

	bool isCollide() {
		return _is_collide;
	}

	void setCollide(bool b) {
		_is_collide = b;
	}
};