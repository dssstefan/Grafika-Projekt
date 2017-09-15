#include "ObjectManager.h"



ObjectManager::ObjectManager(): iglica(100)
{
	isStartingPosition = true;
	deleteCubes = false;
	print = &Options::GetInstance().printing;
	cubeSize = 0.1f;
	movementSpeed = 1.0f;
	headPosition = glm::vec3(0.0, WS_Y_MAX, 0.0);
	startingPosition = headPosition;

	floor.SetScale(glm::vec3(30.0f, 30.0f, 1.0f));
	floor.Model().GetPos().y = -1.0f;
	floor.Model().GetRot().x = -1.57f;
	floor.SetMaterial(Material::white);
	
	TextureManager::GetInstance().LoadTexture("res/hex_2_dif.png");
	TextureManager::GetInstance().LoadTexture("res/hex_2_nor.png");
	TextureManager::GetInstance().LoadTexture("res/hex_2_spec.png");
	
	floor.material.diffuseTexture = &TextureManager::GetInstance().textures[0];
	floor.material.normalMap = &TextureManager::GetInstance().textures[1];
	floor.material.specularTexture = &TextureManager::GetInstance().textures[2];


	stol.SetScale(glm::vec3(3.0f, 0.1f, 3.0f));
	stol.SetPos(glm::vec3(0.0f, 1.89f, 0.0f));

	pom1.SetScale(glm::vec3(0.01f, 0.50f, 3.25f));
	pom1.SetPos(glm::vec3(-1.585f, -0.75f, 0.0f));

	podloga.SetScale(glm::vec3(3.18f, 0.5f, 3.25f));
	podloga.Model().GetPos().y = -0.75f;

	prowadnica_pionowa_lewa.Model().GetPos().x = -1.4f;
	prowadnica_pionowa_lewa.SetScale(glm::vec3(0.1f, 4.0f, 0.1f));
	prowadnica_pionowa_lewa.Model().GetPos().y = 1.5f;

	prowadnica_pionowa_prawa.Model().GetPos().x = 1.4f;
	prowadnica_pionowa_prawa.SetScale(glm::vec3(0.1f, 4.0f, 0.1f));
	prowadnica_pionowa_prawa.Model().GetPos().y = 1.5f;

	prowadnica_pozioma_lewa.Model().GetPos().x = -1.2f;
	prowadnica_pozioma_lewa.SetScale(glm::vec3(0.1f, 3.2f, 0.1f));
	prowadnica_pozioma_lewa.Model().GetPos().y = 2.5f;
	prowadnica_pozioma_lewa.Model().GetRot().x = 1.57f;

	prowadnica_pozioma_prawa.Model().GetPos().x = 1.2f;
	prowadnica_pozioma_prawa.SetScale(glm::vec3(0.1f, 3.2f, 0.1f));
	prowadnica_pozioma_prawa.Model().GetPos().y = 2.5f;
	prowadnica_pozioma_prawa.Model().GetRot().x = 1.57f;

	mala_prowadnica_pozioma1.SetScale(glm::vec3(0.05f, 2.5f, 0.05f));
	mala_prowadnica_pozioma1.Model().GetRot().z = 1.57f;
	mala_prowadnica_pozioma1.Model().GetPos().y = 2.5f;
	mala_prowadnica_pozioma1.Model().GetPos().z = 0.1f;

	mala_prowadnica_pozioma2.SetScale(glm::vec3(0.05f, 2.5f, 0.05f));
	mala_prowadnica_pozioma2.Model().GetRot().z = 1.57f;
	mala_prowadnica_pozioma2.Model().GetPos().y = 2.5f;
	mala_prowadnica_pozioma2.Model().GetPos().z = -0.1f;

	lozysko_poziome_lewe.SetScale(glm::vec3(0.2f, 0.2f, 0.4f));
	lozysko_poziome_lewe.Model().GetPos().x = -1.2f;
	lozysko_poziome_lewe.Model().GetPos().y = 2.5f;

	lozysko_poziome_prawe.SetScale(glm::vec3(0.2f, 0.2f, 0.4f));
	lozysko_poziome_prawe.Model().GetPos().x = 1.2f;
	lozysko_poziome_prawe.Model().GetPos().y = 2.5f;

	glowica.SetScale(glm::vec3(0.6f, 0.7f, 0.6f));
	glowica.Model().GetPos().y = 2.5f;

	bottom1.Model().GetPos().z = 1.6f;
	bottom1.Model().GetPos().y = 3.3f;
	bottom1.SetScale(glm::vec3(3.238f, 0.5f, 0.1f));

	bottom2.Model().GetRot().y = 1.57f;
	bottom2.Model().GetPos().x = 1.57f;
	bottom2.Model().GetPos().y = 3.3f;
	bottom2.SetScale(glm::vec3(3.12f, 0.5f, 0.1f));

	pom2.SetScale(glm::vec3(0.01f, 0.55f, 3.3f));
	pom2.SetPos(glm::vec3(-1.62f, 3.32f, 0.0f));

	bottom3.Model().GetRot().y = 1.57f;
	bottom3.Model().GetPos().x = -1.57f;
	bottom3.Model().GetPos().y = 3.3f;
	bottom3.SetScale(glm::vec3(3.12f, 0.5f, 0.1f));

	bottom4.Model().GetPos().z = -1.6f;
	bottom4.Model().GetPos().y = 3.3f;
	bottom4.SetScale(glm::vec3(3.238f, 0.5f, 0.1f));

	middle1.Model().GetPos().z = 1.6f;
	middle1.Model().GetPos().x = -1.34f;
	middle1.Model().GetPos().y = 1.32f;
	middle1.Model().GetRot().z = 1.57f;
	middle1.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle2.Model().GetPos().z = 1.6f;
	middle2.Model().GetPos().x = 1.342f;
	middle2.Model().GetPos().y = 1.32f;
	middle2.Model().GetRot().z = 1.57f;
	middle2.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle3.Model().GetPos().z = -1.6f;
	middle3.Model().GetPos().x = -1.3385f;
	middle3.Model().GetPos().y = 1.32f;
	middle3.Model().GetRot().z = 1.57f;
	middle3.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle4.Model().GetPos().z = -1.6f;
	middle4.Model().GetPos().x = 1.342f;
	middle4.Model().GetPos().y = 1.32f;
	middle4.Model().GetRot().z = 1.57f;
	middle4.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle5.Model().GetPos().z = 1.325f;
	middle5.Model().GetPos().x = -1.564f;
	middle5.Model().GetPos().y = 1.32f;
	middle5.Model().GetRot().z = 1.57f;
	middle5.Model().GetRot().x = 1.57f;
	middle5.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle6.Model().GetPos().z = -1.325f;
	middle6.Model().GetPos().x = -1.564f;
	middle6.Model().GetPos().y = 1.32f;
	middle6.Model().GetRot().z = 1.57f;
	middle6.Model().GetRot().x = 1.57f;
	middle6.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle7.Model().GetPos().z = 1.325f;
	middle7.Model().GetPos().x = 1.57f;
	middle7.Model().GetPos().y = 1.32f;
	middle7.Model().GetRot().z = 1.57f;
	middle7.Model().GetRot().x = 1.57f;
	middle7.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	middle8.Model().GetPos().z = -1.325f;
	middle8.Model().GetPos().x = 1.57f;
	middle8.Model().GetPos().y = 1.32f;
	middle8.Model().GetRot().z = 1.57f;
	middle8.Model().GetRot().x = 1.57f;
	middle8.SetScale(glm::vec3(3.65f, 0.5f, 0.05f));

	top1.Model().GetPos().y = 3.57f;
	top1.Model().GetPos().z = 1.45f;
	top1.Model().GetRot().x = 1.57f;	
	top1.SetScale(glm::vec3(3.238f, 0.4f, 0.05f));

	top2.Model().GetPos().y = 3.57f;
	top2.Model().GetPos().z = -1.45f;
	top2.Model().GetRot().x = 1.57f;
	top2.SetScale(glm::vec3(3.238f, 0.4f, 0.05f));

	top3.Model().GetPos().y = 3.57f;
	top3.Model().GetPos().x = 1.42f;
	top3.Model().GetRot().x = 1.57f;
	top3.Model().GetRot().y = 1.57f;
	top3.SetScale(glm::vec3(2.838f, 0.4f, 0.05f));

	top4.Model().GetPos().y = 3.57f;
	top4.Model().GetPos().x = -1.42f;
	top4.Model().GetRot().x = 1.57f;
	top4.Model().GetRot().y = 1.57f;
	top4.SetScale(glm::vec3(2.838f, 0.4f, 0.05f));

	czesc_glowicy.SetScale(glm::vec3(0.2f, 0.05f, 0.2f));
	czesc_glowicy.Model().GetPos().y = 2.14f;

	iglica.SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	iglica.Model().GetPos().y = 2.05f;

	objectsToDraw.push_back(&pom1);
	objectsToDraw.push_back(&pom2);
	objectsToDraw.push_back(&floor);
	objectsToDraw.push_back(&podloga);
	objectsToDraw.push_back(&stol);
	objectsToDraw.push_back(&bottom1);
	objectsToDraw.push_back(&bottom2);
	objectsToDraw.push_back(&bottom3);
	objectsToDraw.push_back(&bottom4);
	objectsToDraw.push_back(&middle1);
	objectsToDraw.push_back(&middle2);
	objectsToDraw.push_back(&middle3);
	objectsToDraw.push_back(&middle4);
	objectsToDraw.push_back(&middle5);
	objectsToDraw.push_back(&middle6);
	objectsToDraw.push_back(&middle7);
	objectsToDraw.push_back(&middle8);
	objectsToDraw.push_back(&lozysko_poziome_lewe);
	objectsToDraw.push_back(&lozysko_poziome_prawe);
	objectsToDraw.push_back(&glowica);
	objectsToDraw.push_back(&top1);
	objectsToDraw.push_back(&top2);
	objectsToDraw.push_back(&top3);
	objectsToDraw.push_back(&top4);
	objectsToDraw.push_back(&iglica);
	objectsToDraw.push_back(&czesc_glowicy);

	objectsToDraw.push_back(&prowadnica_pionowa_lewa);
	objectsToDraw.push_back(&prowadnica_pionowa_prawa);
	objectsToDraw.push_back(&prowadnica_pozioma_lewa);
	objectsToDraw.push_back(&prowadnica_pozioma_prawa);
	objectsToDraw.push_back(&mala_prowadnica_pozioma1);
	objectsToDraw.push_back(&mala_prowadnica_pozioma2);

	objectsY.push_back(&stol);
	objectsX.push_back(&glowica);
	objectsX.push_back(&iglica);
	objectsX.push_back(&czesc_glowicy);
	objectsZ.push_back(&glowica);
	objectsZ.push_back(&iglica);
	objectsZ.push_back(&czesc_glowicy);
	objectsZ.push_back(&mala_prowadnica_pozioma1);
	objectsZ.push_back(&mala_prowadnica_pozioma2);
	objectsZ.push_back(&lozysko_poziome_lewe);
	objectsZ.push_back(&lozysko_poziome_prawe);
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::Draw(Camera view, Projection projection)
{
	for (int i = 0; i < objectsToDraw.size(); i++)
	{
		objectsToDraw[i]->Draw(view, projection);
	}
	for (int i = 0; i < cubes.size(); i++)
	{
		cubes[i].Update();
		cubes[i].Draw(view, projection);
	}
}

void ObjectManager::Events(const Uint8 * currentKeyStates, GLfloat deltaTime)
{
	GLfloat velocity = movementSpeed * deltaTime;
	glm::vec3 newPosition = headPosition;

	if (currentKeyStates[SDL_SCANCODE_D])
	{
		if (glowica.Model().GetPos().x < 0.8)
		{
			MoveX(velocity);

			newPosition.x += velocity;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_A])
	{
		if (glowica.Model().GetPos().x > -0.8)
		{
			MoveX(-velocity);

			newPosition.x -= velocity;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_W])
	{
		if (glowica.Model().GetPos().z > -1.31)
		{
			MoveZ(-velocity);

			
			newPosition.z -= velocity;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		if (glowica.Model().GetPos().z < 1.31)
		{
			MoveZ(velocity);
			
			newPosition.z += velocity;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_Q])
	{
		if (stol.Model().GetPos().y < 1.88)
		{
			MoveY(velocity);

			newPosition.y -= velocity;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_E])
	{
		if (stol.Model().GetPos().y > -0.45)
		{
			MoveY(-velocity);

			newPosition.y += velocity;
		}
	}
}

void ObjectManager::MoveToStartingPosition()
{
	if (startingPosition != headPosition && *print == true)
	{
		glm::vec3 offset = startingPosition - headPosition;
		glm::vec3 velocity = glm::vec3(cubeSize, cubeSize, cubeSize);
		offset.x > 0 ? velocity.x : velocity.x *= -1;
		offset.y > 0 ? velocity.y : velocity.y *= -1;
		offset.z > 0 ? velocity.z : velocity.z *= -1;

		if (offset.x != 0)
		{
			if (offset.x < cubeSize && offset.x > -cubeSize)
			{
				MoveX(offset.x);
			}
			else
			{
				MoveX(velocity.x);
			}
		}
		if (offset.z != 0)
		{
			if (offset.z < cubeSize && offset.z > -cubeSize)
			{
				MoveZ(offset.z);
			}
			else
			{
				MoveZ(velocity.z);
			}
		}
		if (offset.y != 0)
		{
			if (offset.y < cubeSize && offset.y > -cubeSize)
			{
				MoveY(offset.y);
			}
			else
			{
				MoveY(velocity.y);
			}
		}
	}
	else
	{
		isStartingPosition = true;
	}
}

void ObjectManager::Print()
{
	if (Options::GetInstance().newRoute)
	{
		SetRoute(Options::GetInstance().GetCurrRoute());
		isStartingPosition = false;
		Options::GetInstance().newRoute = false;
		deleteCubes = true;
	}

	if (!isStartingPosition)
	{
		if (deleteCubes && *print == true)
		{
			cubes.clear();
			deleteCubes = false;
		}
		MoveToStartingPosition();

	}
	else
	{
		PrintCubes();
	}


}

void ObjectManager::PrintCubes()
{
	glm::vec3 velocity = glm::vec3(cubeSize);
	if (*print)
	{
		if (!routeQ.empty())
		{
			glm::vec4 item = routeQ.front();
			item.x > 0 ? velocity.x : velocity.x *= -1;
			item.y > 0 ? velocity.y *= -1 : velocity.y;
			item.z > 0 ? velocity.z : velocity.z *= -1;

			if (item.x != 0 && item.y != 0)
			{
				MoveX(velocity.x);
				MoveY(velocity.y);
				routeQ.pop();
			}
			else if (item.x != 0 && item.z != 0)
			{
				MoveX(velocity.x);
				MoveZ(velocity.z);
				routeQ.pop();
			}
			else if (item.y != 0 && item.z != 0)
			{
				MoveZ(velocity.z);
				MoveY(velocity.y);
				routeQ.pop();
			}
			else if (item.x != 0)
			{
				MoveX(velocity.x);
				item.x > 0 ? routeQ.front().x -= 1 : routeQ.front().x += 1;
				if (routeQ.front().x < 0.5f && routeQ.front().x > -0.5f)
				{
					routeQ.pop();
				}
			}
			else if (item.y != 0)
			{
				MoveY(velocity.y);
				item.y > 0 ? routeQ.front().y -= 1 : routeQ.front().y += 1;
				if (routeQ.front().y < 0.5f && routeQ.front().y > -0.5f)
				{
					routeQ.pop();
				}
			}
			else if (item.z != 0)
			{
				MoveZ(velocity.z);
				item.z > 0 ? routeQ.front().z -= 1 : routeQ.front().z += 1;
				if (routeQ.front().z < 0.5f && routeQ.front().z > -0.5f)
				{
					routeQ.pop();
				}
			}
			if (item.w == 1)
			{
				AddCube();
			}

		}
		else
		{
			Options::GetInstance().Print(false);
		}
	}
}

void ObjectManager::SetRoute(std::queue<glm::vec4> route)
{
	this->routeQ = route;
}

void ObjectManager::AddCube()
{
	
	Cube* cube;
	cube = new Cube();
	cube->material = Options::GetInstance().GetLineColor();
	cube->SetPos(glm::vec3(headPosition.x, WS_Y_MAX, headPosition.z));
	cube->SetScale(glm::vec3(0.1, 0.1, 0.1));
	cubes.push_back(*cube);
	delete cube;
	
}

void ObjectManager::MoveX(float velocity)
{
	for (int i = 0; i < objectsX.size(); i++)
		objectsX[i]->Model().GetPos().x += velocity;

	headPosition.x += velocity;
}

void ObjectManager::MoveY(float velocity)
{
	for (int i = 0; i < objectsY.size(); i++)
	{
		objectsY[i]->Model().GetPos().y += velocity;
	}
	for (int i = 0; i < cubes.size(); i++)
	{
		cubes[i].Model().GetPos().y += velocity;
	}

	headPosition.y += velocity;
}

void ObjectManager::MoveZ(float velocity)
{
	for (int i = 0; i < objectsZ.size(); i++)
		objectsZ[i]->Model().GetPos().z += velocity;

	headPosition.z += velocity;
}
