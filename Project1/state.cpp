#include "state.h"

std::string State::getName()
{
	return _state_name;
}

double State::getDuration()
{
	return _duration/_count_of_frames;
}

void State::nextFrame()
{
	_curent_frame = (_curent_frame + 1) % _count_of_frames;
	//_sprite.setTextureRect(sf::IntRect(233, 0, 233, 283));
	_sprite.setTextureRect(sf::IntRect((_texture.getSize().x / 4)*_curent_frame, 0, _texture.getSize().x/4, _texture.getSize().y));
}

sf::Sprite& State::getSprite()
{
	return _sprite;
}
