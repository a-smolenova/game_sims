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
	_sprite.setTextureRect(sf::IntRect((_texture_lnk.getSize().x / _count_of_frames)*_curent_frame, 0, _texture_lnk.getSize().x/ _count_of_frames, _texture_lnk.getSize().y));
}

void State::setFrame(int f)
{
	_curent_frame = 0;
	_sprite.setTextureRect(sf::IntRect((_texture_lnk.getSize().x / _count_of_frames) * _curent_frame, 0, _texture_lnk.getSize().x / _count_of_frames, _texture_lnk.getSize().y));

}

sf::Sprite& State::getSprite()
{
	return _sprite;
}
