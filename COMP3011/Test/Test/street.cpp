#include "street.h"
#include "road.h"
#include <random>
#include <iostream>


Street::Street(std::vector<Object*>* o, std::vector<LightSource*>* l) {

	srand(static_cast<unsigned>(time(NULL)));

	objects = o;

	lights = l;


	testHouse.SetScale(glm::vec3(0.1f));
	rustyHouse.SetScale(glm::vec3(0.05f));


	Object* car = new Object(
		"objs/source/car_obj/K1AGJVQ50VCSD2UOPBS13FD0S.obj",
		"objs/source/car_obj/"
	);
	car->SetPosition(glm::vec3(0, 2.5, 0));
	car->SetScale(glm::vec3(10));

	objects->push_back(car);




	Object* car3 = new Object(
		"objs/source/chevelle/WTDIMTYHY1OX052LSDDZ1WH0V.obj",
		"objs/source/chevelle/"
	);

	car3->SetPosition(glm::vec3(40,2.8, 10));
	car3->SetScale(glm::vec3(10));

	objects->push_back(car3);



	


}


void Street::DrawStreet(GLuint program, int length) {



	

	//!! fix and move into generate
	road.DrawRoad(program, glm::vec3(-15.0, 0.0, 0.0));

	//terrain

	
	
	terrain.GenerateTerrain(program); 


}


void Street::GenerateStreet(GLuint program, int length) {

	terrain.SetupTerrain(length);

	road.SetLength(length);

	//Start of street
	Object* barrier = new Object(
		"objs/source/barrier/1TMCXKTP3PCW5BDH9EYHV8DJX.obj",
		"objs/source/barrier/");

	barrier->SetRotation(180);
	barrier->SetPosition(glm::vec3(-20, 3, 5));
	barrier->SetScale(glm::vec3(8.0f));

	objects->push_back(barrier);


	for (int i = 0; i < length; i++) {

		


		if (i >= nextHouseLeft) {
			
			CreateHouse(i, false);
		}
		if (i >= nextHouseRight) {

			CreateHouse(i, true);
		}


		if (i % 8 == 0) {
			LightSource* light = new LightSource(
				glm::vec3(10.0f *i, 10.0f, 0.0f),
				glm::vec3(0.5f, 0.5f, 1.0f)
			);


			lights->push_back(light);

		}


		//generate 
		
	}


	


	//Start of street
	Object* barrier2 = new Object(
		"objs/source/barrier/1TMCXKTP3PCW5BDH9EYHV8DJX.obj",
		"objs/source/barrier/");

	
	barrier2->SetScale(glm::vec3(8.0f));
	barrier2->SetPosition(glm::vec3(10 * (length -3), 3, 5));

	objects->push_back(barrier2);

}


void Street::CreateHouse(int pos, bool rSide) {


	
	Object* nextHouse;
	

	if (!rSide) {

		int random = rand() % 4;

		

		if (random >0) {
			nextHouse = testHouse.Clone();
			nextHouse->SetPosition(glm::vec3(10 * pos, -1, -20));
			nextHouseLeft += 2;

		}
		else {
			nextHouse = rustyHouse.Clone();
			nextHouse->SetPosition(glm::vec3(10 * pos +10 , -1, -20));
			nextHouseLeft += 4;
		}
		

		

		objects->push_back(nextHouse);

		

	}
	else {



		int random = rand() % 4;

		

		if (random > 0) {
			nextHouse = testHouse.Clone();
			nextHouse->SetRotation(180);
			nextHouse->SetPosition(glm::vec3(10 * pos, -1, 30));
			nextHouseRight += 2;

		}
		else {
			nextHouse = rustyHouse.Clone();
			nextHouse->SetRotation(180);
			nextHouse->SetPosition(glm::vec3(10 * pos + 10, -1, 30));
			nextHouseRight += 4;
		}




		objects->push_back(nextHouse);

		
		
	}


	
	
}