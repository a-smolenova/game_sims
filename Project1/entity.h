#pragma once
class Entity{	
public:
	int id = 0;
	float x;
	float y;
	float rotation = 0;
	
	Entity(float x, float y) : x(x), y(y){};
	Entity(float x, float y, float r) : x(x), y(y), rotation(r) {};

};