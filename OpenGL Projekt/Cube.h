#pragma once
#include "PrimaryObject.h"
#include <iostream>

class Cube : public PrimaryObject
{
public:
	Cube(const std::string & shaderName = "basicShader");
	~Cube();

private:
	
};

