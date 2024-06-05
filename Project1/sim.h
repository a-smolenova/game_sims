#pragma once
#include"entity.h"
#include<vector>
#include<string>
#include"animator.h"

enum class _state {WalkAround = 0, Hungry = 1};
enum class _state_anim: int {f = 0, b = 1, r = 2, l = 3};

class Sim: public Entity {
private:
	_state_anim c_s = _state_anim::f;
	_state state = _state::WalkAround;
	int _speed = 10;
	char _target = '0';
	sf::Vector2f _pos_target = sf::Vector2f(0,0);
	std::vector<sf::Vector2f> _path;


public:
	Animator _animator;

	Sim(float pos_x, float pos_y, sf::RenderWindow& rw): _animator(rw), Entity(pos_x, pos_y) {};


	void move(float x, float y) {
		Entity::x += x;
		Entity::y += y;
		if (y < 0 && _state_anim::b != c_s) {
			_animator.changeAnimState(static_cast<int>(_state_anim::b));
			 c_s = _state_anim::b;
		}
		else if (y > 0 && _state_anim::f != c_s) {
			_animator.changeAnimState(static_cast<int>(_state_anim::f));
			c_s = _state_anim::f;
		}
		else if (x < 0 && _state_anim::r != c_s) {
			_animator.changeAnimState(static_cast<int>(_state_anim::r));
			c_s = _state_anim::r;
		}
		else if (x > 0 && _state_anim::l != c_s) {
			_animator.changeAnimState(static_cast<int>(_state_anim::l));
			c_s = _state_anim::l;
		}
		_animator.move(Entity::x, Entity::y);
	}

	void move(float _count = 1) {
		if (!_path.empty()) {
			if (_path[0].x == Entity::x && _path[0].y == Entity::y) {
				_path.erase(_path.begin());
			}
			if (!_path.empty()) {
				if(abs(_path[0].x - Entity::x) <= _speed && abs(_path[0].y - Entity::y) <= _speed)
					move(_path[0].x - Entity::x,
						_path[0].y - Entity::y);
				else {
					move(int(_path[0].x - Entity::x != 0) * 10 * int(1 - 2*(_path[0].x - Entity::x < 0)),
						int(_path[0].y - Entity::y != 0) * 10 * int(1 - 2 * (_path[0].y - Entity::y < 0)));
				}
				return;
			}
			else {
				state = _state::WalkAround;
			}
		}
		else {


			if (_state_anim::b == c_s) {
				Entity::y -= _speed * _count;
				_animator.changeAnimState(static_cast<int>(_state_anim::b));

			}
			else if (_state_anim::f == c_s) {
				Entity::y += _speed * _count;
				_animator.changeAnimState(static_cast<int>(_state_anim::f));

			}
			else if (_state_anim::r == c_s) {
				Entity::x -= _speed * _count;
				_animator.changeAnimState(static_cast<int>(_state_anim::r));

			}
			else if (_state_anim::l == c_s) {
				Entity::x += _speed * _count;
				_animator.changeAnimState(static_cast<int>(_state_anim::l));

			}
		}
		_animator.move(Entity::x, Entity::y);
	}

	void changeAnimState(_state_anim n_state) {
		c_s = n_state;
	}

	void changeSimState(_state new_state) {
		state = new_state;
	}

	bool hasTarget() {
		return !_path.empty();
	}

	void setTarget(sf::Vector2f _target_pos, char _target_name) {
		_pos_target = _target_pos;
		_target = _target_name;
	}

	void setPath(std::vector<sf::Vector2f> _n_path) {
		_path = _n_path;
	}

	void nextState() {
		c_s = static_cast<_state_anim>((static_cast<int>(c_s)+1)%4);
	}

	int getAnimState() {
		return static_cast<int>(c_s);
	}

	_state getState() {
		return state;
	}

	sf::Vector2f getTargetPos() {
		return _pos_target;
	}

};