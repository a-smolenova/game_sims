#pragma once
#include<vector>
#include<string>
#include<SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Rect.hpp>

class State {
private:
	std::string _state_name;
	double _duration;
	int _count_of_frames;
	int _curent_frame = 0;
	sf::Sprite _sprite;
	sf::Texture _texture;
public:
	State(std::string stateName, double duration, int frames_count, std::string spriteSheetPath) : _state_name(stateName), _duration(duration), _count_of_frames(frames_count) { _texture.loadFromFile(spriteSheetPath); _sprite.setTexture(_texture); nextFrame(); _sprite.setPosition(0, 0); };

	std::string getName();

	double getDuration();

	void nextFrame();

	sf::Sprite& getSprite();
};