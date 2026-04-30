#pragma once
#include "inc.h"
#include "Object.h"
#include "light_source.h"
#include "road.h"
#include "terrain.h"



class Street
{

	std::vector<Object*>* objects;

	std::vector<LightSource*>* lights;

	//Define when next house can be chosen
	int nextHouseLeft = 0;
	int nextHouseRight = 0;





	Road road;

	Terrain terrain;

	Object testHouse = Object(
		"objs/source/single_room_building/single_room_building.obj",
		"objs/source/single_room_building/");

	Object rustyHouse = Object(
		"objs/source/rusty_house/HOUSERUSTY.obj",
		"objs/source/rusty_house/");



public:
	Street(std::vector<Object*>* o, std::vector<LightSource*>* l);

	void GenerateStreet(GLuint program, int length);

	void DrawStreet(GLuint program, int length);


	void CreateHouse(int pos, bool rSide);
};

