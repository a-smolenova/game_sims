#pragma once
#include"state.h"

class Animator {
private:
	std::vector<State> _all_states;
	int _current_state = 0;
	bool _drawable = false;
	sf::RenderWindow& window;
public:
	Animator(sf::RenderWindow& w) : window(w) {};
	void addState(State st) {
		_all_states.push_back(st);
	}

	void update() {
		_all_states[_current_state].nextFrame();
	}
	void draw() {
		window.draw(_all_states[_current_state].getSprite());
	}


	sf::Sprite& getSprite() {
		return _all_states[_current_state].getSprite();
	}

	void move(float x, float y) {
		getSprite().setPosition(x, y);
	}
};