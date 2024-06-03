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
	sf::Texture& _texture_lnk;
public:
	State(std::string stateName, double duration, int frames_count, std::string spriteSheetPath) : _state_name(stateName), _duration(duration), _count_of_frames(frames_count), _texture_lnk(_texture) { _texture_lnk.loadFromFile(spriteSheetPath); _sprite.setTexture(_texture_lnk); nextFrame(); _sprite.setPosition(0, 0); _sprite.setOrigin(sf::Vector2f(_texture_lnk.getSize().x / (2*_count_of_frames), _texture_lnk.getSize().y / 2)); };
	State(std::string stateName, double duration, int frames_count, sf::Texture& t) : _state_name(stateName), _duration(duration), _count_of_frames(frames_count), _texture_lnk(t) { _sprite.setTexture(_texture_lnk); nextFrame(); _sprite.setPosition(0, 0); _sprite.setOrigin(sf::Vector2f(_texture_lnk.getSize().x / (2 * _count_of_frames), _texture.getSize().y / 2)); };

	std::string getName();

	double getDuration();

	void nextFrame();

	sf::Sprite& getSprite();
};