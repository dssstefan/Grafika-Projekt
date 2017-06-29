#pragma once
#include <vector>
#include <queue>
#include "Cube.h"
#include "Cone.h"
#include "Cylinder.h"
#include "Projection.h"
#include "Camera.h"
#include "SDL_events.h"
#include "Line.h"
#include "Quad.h"
#include "TextureManager.h"
#include "Options.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Draw(Camera view, Projection projection);
	void Events(const Uint8* currentKeyStates, GLfloat deltaTime);
	void MoveByRoute(GLfloat deltaTime);
	void MoveToStartingPosition();
	void Print();
	void SetRoute(std::queue<glm::vec4> route);
	void AddCube();
private:
	bool* print;
	bool isStartingPosition;
	bool deleteCubes;
	void PrintCubes();
	std::vector<PrimaryObject*> objectsToDraw;
	std::vector<PrimaryObject*> objectsX;
	std::vector<PrimaryObject*> objectsY;
	std::vector<PrimaryObject*> objectsZ;
	std::vector<Cube> cubes;
	std::queue<glm::vec4> routeQ;
	glm::vec3 headPosition;
	glm::vec3 startingPosition;
	Cylinder prowadnica_pionowa_lewa, prowadnica_pionowa_prawa;
	Cylinder prowadnica_pozioma_lewa, prowadnica_pozioma_prawa;
	Cylinder mala_prowadnica_pozioma1, mala_prowadnica_pozioma2;
	Cylinder czesc_glowicy;

	Cube stol, podloga, lozysko_poziome_lewe, lozysko_poziome_prawe, glowica;
	Cube bottom1, bottom2, bottom3, bottom4;
	Cube top1, top2, top3, top4;
	Cube middle1, middle2, middle3, middle4, middle5, middle6, middle7, middle8;
	Cube pom1, pom2;
	//Cube ziemia;
	Quad floor;
	Cone iglica;

	float cubeSize;

	Line linia;

	GLfloat movementSpeed;

	void MoveX(float velocity);
	void MoveY(float velocity);
	void MoveZ(float velocity);
};

