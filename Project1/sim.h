#pragma once
#include"entity.h"
#include<vector>
#include<string>
#include"animator.h"

enum class _state {WalkAround, Hungry};
enum class _state_anim: int {f = 0, b = 1, r = 2, l = 3};

class Sim: public Entity {
private:
	_state_anim c_s = _state_anim::f;
	int _speed = 10;
public:
	Animator _animator;

	Sim(float pos_x, float pos_y, sf::RenderWindow& rw): _animator(rw), Entity(pos_x, pos_y) {};


	void move(float x, float y) {
		Entity::x += x;
		Entity::y += y;
		if (y < 0 && _state_anim::b != c_s) {
			_animator.changeState(static_cast<int>(_state_anim::b));
			 c_s = _state_anim::b;
		}
		else if (y > 0 && _state_anim::f != c_s) {
			_animator.changeState(static_cast<int>(_state_anim::f));
			c_s = _state_anim::f;

		}
		else if (x < 0 && _state_anim::r != c_s) {
			_animator.changeState(static_cast<int>(_state_anim::r));
			c_s = _state_anim::r;


		}
		else if (x > 0 && _state_anim::l != c_s) {
			_animator.changeState(static_cast<int>(_state_anim::l));
			c_s = _state_anim::l;


		}
		_animator.move(Entity::x, Entity::y);
	}

	void move(float _count = 1) {

		if (_state_anim::b == c_s) {
			Entity::y -= _speed * _count;
			_animator.changeState(static_cast<int>(_state_anim::b));

		}
		else if (_state_anim::f == c_s) {
			Entity::y += _speed * _count;
			_animator.changeState(static_cast<int>(_state_anim::f));

		}
		else if (_state_anim::r == c_s) {
			Entity::x -= _speed * _count;
			_animator.changeState(static_cast<int>(_state_anim::r));

		}
		else if ( _state_anim::l == c_s) {
			Entity::x += _speed * _count;
			_animator.changeState(static_cast<int>(_state_anim::l));

		}
		_animator.move(Entity::x, Entity::y);
	}

	void changeState(_state_anim n_state) {
		c_s = n_state;
	}

	void nextState() {
		c_s = static_cast<_state_anim>((static_cast<int>(c_s)+1)%4);
	}

	int getState() {
		return static_cast<int>(c_s);
	}

};