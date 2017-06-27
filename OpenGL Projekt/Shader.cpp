#include "Shader.h"
#include <iostream>
#include <fstream>
#include "Options.h"
//static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
//static std::string LoadShader(const std::string & fileName);
//static GLuint CreateShader(const std::string & text, GLenum shaderType);

Shader::Shader()
{
	dirLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	dirLight.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	dirLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

	pointLight.ambient = &Options::GetInstance().GetLightColor().ambient;
	pointLight.diffuse = &Options::GetInstance().GetLightColor().diffuse;
	pointLight.specular = &Options::GetInstance().GetLightColor().specular;
	pointLight.position = glm::vec3(1.5f, 3.5f, 1.5f);
	pointLight.constant = 1.0f;
	pointLight.linear = 0.09f;
	pointLight.quadratic = 0.032f;

	Initialize();
}


Shader::~Shader()
{
	//glDeleteProgram(m_program);
}

void Shader::Initialize(const std::string& fileName)
{
	program = glCreateProgram();
	GLuint vert = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	GLuint frag = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	glAttachShader(program, vert);
	glAttachShader(program, frag);

	glBindAttribLocation(program, 0, "position");
	glLinkProgram(program);
	CheckShaderError(program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(program);
	CheckShaderError(program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	glDeleteShader(frag);
	glDeleteShader(vert);

}


void Shader::Update(const Transform& model, const Camera& camera, const Projection& projection, const Material material)
{
	Material lightColor = Options::GetInstance().GetLightColor();
	uniforms[MODEL_U] = glGetUniformLocation(program, "model");
	uniforms[VIEW_U] = glGetUniformLocation(program, "view");
	uniforms[PROJECTION_U] = glGetUniformLocation(program, "projection");
	uniforms[VIEWPOS_U] = glGetUniformLocation(program, "viewPos");

	uniforms[M_AMBIENT_U] = glGetUniformLocation(program, "material.ambient");
	uniforms[M_DIFFUSE_U] = glGetUniformLocation(program, "material.diffuse");
	uniforms[M_SPECULAR_U] = glGetUniformLocation(program, "material.specular");
	uniforms[M_SHININESS_U] = glGetUniformLocation(program, "material.shininess");

	uniforms[L_DIRECTION_U] = glGetUniformLocation(program, "dirLight.direction");
	uniforms[L_AMBIENT_U] = glGetUniformLocation(program, "dirLight.ambient");
	uniforms[L_DIFFUSE_U] = glGetUniformLocation(program, "dirLight.diffuse");
	uniforms[L_SPECULAR_U] = glGetUniformLocation(program, "dirLight.specular");

	uniforms[L_POSITION_0_U] = glGetUniformLocation(program, "pointLights[0].position");
	uniforms[L_AMBIENT_0_U] = glGetUniformLocation(program, "pointLights[0].ambient");
	uniforms[L_DIFFUSE_0_U] = glGetUniformLocation(program, "pointLights[0].diffuse");
	uniforms[L_SPECULAR_0_U] = glGetUniformLocation(program, "pointLights[0].specular");
	uniforms[L_CONSTANT_0_U] = glGetUniformLocation(program, "pointLights[0].constant");
	uniforms[L_LINEAR_0_U] = glGetUniformLocation(program, "pointLights[0].linear");
	uniforms[L_QUADRATIC_0_U] = glGetUniformLocation(program, "pointLights[0].quadratic");

	uniforms[L_POSITION_1_U] = glGetUniformLocation(program, "pointLights[1].position");
	uniforms[L_AMBIENT_1_U] = glGetUniformLocation(program, "pointLights[1].ambient");
	uniforms[L_DIFFUSE_1_U] = glGetUniformLocation(program, "pointLights[1].diffuse");
	uniforms[L_SPECULAR_1_U] = glGetUniformLocation(program, "pointLights[1].specular");
	uniforms[L_CONSTANT_1_U] = glGetUniformLocation(program, "pointLights[1].constant");
	uniforms[L_LINEAR_1_U] = glGetUniformLocation(program, "pointLights[1].linear");
	uniforms[L_QUADRATIC_1_U] = glGetUniformLocation(program, "pointLights[1].quadratic");

	uniforms[L_POSITION_2_U] = glGetUniformLocation(program, "pointLights[2].position");
	uniforms[L_AMBIENT_2_U] = glGetUniformLocation(program, "pointLights[2].ambient");
	uniforms[L_DIFFUSE_2_U] = glGetUniformLocation(program, "pointLights[2].diffuse");
	uniforms[L_SPECULAR_2_U] = glGetUniformLocation(program, "pointLights[2].specular");
	uniforms[L_CONSTANT_2_U] = glGetUniformLocation(program, "pointLights[2].constant");
	uniforms[L_LINEAR_2_U] = glGetUniformLocation(program, "pointLights[2].linear");
	uniforms[L_QUADRATIC_2_U] = glGetUniformLocation(program, "pointLights[2].quadratic");

	uniforms[L_POSITION_3_U] = glGetUniformLocation(program, "pointLights[3].position");
	uniforms[L_AMBIENT_3_U] = glGetUniformLocation(program, "pointLights[3].ambient");
	uniforms[L_DIFFUSE_3_U] = glGetUniformLocation(program, "pointLights[3].diffuse");
	uniforms[L_SPECULAR_3_U] = glGetUniformLocation(program, "pointLights[3].specular");
	uniforms[L_CONSTANT_3_U] = glGetUniformLocation(program, "pointLights[3].constant");
	uniforms[L_LINEAR_3_U] = glGetUniformLocation(program, "pointLights[3].linear");
	uniforms[L_QUADRATIC_3_U] = glGetUniformLocation(program, "pointLights[3].quadratic");

	if (material.diffuseTexture != nullptr) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance().textures[0]);
		glUniform1i(glGetUniformLocation(program, "diffuseTex"), 0);
		glUniform1i(glGetUniformLocation(program, "hasDiffuseMap"), true);
	}
	else {
		glUniform1i(glGetUniformLocation(program, "hasDiffuseMap"), false);
	}

	if (material.normalMap != nullptr) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance().textures[1]);
		glUniform1i(glGetUniformLocation(program, "hasNormalMap"), true);
		glUniform1i(glGetUniformLocation(program, "normalMap"), 1);
	}
	else {
		glUniform1i(glGetUniformLocation(program, "hasNormalMap"), false);
	}

	if (material.specularTexture != nullptr) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, TextureManager::GetInstance().textures[2]);
		glUniform1i(glGetUniformLocation(program, "specularTex"),2);
		glUniform1i(glGetUniformLocation(program, "hasSpecularMap"), true);
	}
	else {
		glUniform1i(glGetUniformLocation(program, "hasSpecularMap"), false);
	}

	glUniformMatrix4fv(uniforms[MODEL_U], 1, GL_FALSE, glm::value_ptr(model.GetModel()));
	glUniformMatrix4fv(uniforms[VIEW_U], 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
	glUniformMatrix4fv(uniforms[PROJECTION_U], 1, GL_FALSE, glm::value_ptr(projection.GetProjection()));
	glUniform3f(uniforms[VIEWPOS_U], camera.m_position.x, camera.m_position.y, camera.m_position.z);
	glUniform3f(uniforms[M_AMBIENT_U], material.ambient.x, material.ambient.y, material.ambient.z);
	glUniform3f(uniforms[M_DIFFUSE_U], material.diffuse.x, material.diffuse.y, material.diffuse.z);
	glUniform3f(uniforms[M_SPECULAR_U], material.specular.x, material.specular.y, material.specular.z);
	glUniform1f(uniforms[M_SHININESS_U], material.shininess);

	glUniform3f(uniforms[L_DIRECTION_U], dirLight.direction.x, dirLight.direction.y, dirLight.direction.z);
	glUniform3f(uniforms[L_AMBIENT_U], dirLight.ambient.x, dirLight.ambient.y, dirLight.ambient.z);
	glUniform3f(uniforms[L_DIFFUSE_U], dirLight.diffuse.x, dirLight.diffuse.y, dirLight.diffuse.z);
	glUniform3f(uniforms[L_SPECULAR_U], dirLight.specular.x, dirLight.specular.y, dirLight.specular.z);

	glUniform3f(uniforms[L_POSITION_0_U], pointLight.position.x, pointLight.position.y, pointLight.position.z);
	glUniform3f(uniforms[L_AMBIENT_0_U], pointLight.ambient->x, pointLight.ambient->y, pointLight.ambient->z);
	glUniform3f(uniforms[L_DIFFUSE_0_U], pointLight.diffuse->x, pointLight.diffuse->y, pointLight.diffuse->z);
	glUniform3f(uniforms[L_SPECULAR_0_U], pointLight.specular->x, pointLight.specular->y, pointLight.specular->z);
	glUniform1f(uniforms[L_CONSTANT_0_U], pointLight.constant);
	glUniform1f(uniforms[L_LINEAR_0_U], pointLight.linear);
	glUniform1f(uniforms[L_QUADRATIC_0_U], pointLight.quadratic);

	glUniform3f(uniforms[L_POSITION_1_U], pointLight.position.x - 3.0f, pointLight.position.y, pointLight.position.z);
	glUniform3f(uniforms[L_AMBIENT_1_U], pointLight.ambient->x, pointLight.ambient->y, pointLight.ambient->z);
	glUniform3f(uniforms[L_DIFFUSE_1_U], pointLight.diffuse->x, pointLight.diffuse->y, pointLight.diffuse->z);
	glUniform3f(uniforms[L_SPECULAR_1_U], pointLight.specular->x, pointLight.specular->y, pointLight.specular->z);
	glUniform1f(uniforms[L_CONSTANT_1_U], pointLight.constant);
	glUniform1f(uniforms[L_LINEAR_1_U], pointLight.linear);
	glUniform1f(uniforms[L_QUADRATIC_1_U], pointLight.quadratic);

	glUniform3f(uniforms[L_POSITION_2_U], pointLight.position.x, pointLight.position.y, pointLight.position.z - 3.0f);
	glUniform3f(uniforms[L_AMBIENT_2_U], pointLight.ambient->x, pointLight.ambient->y, pointLight.ambient->z);
	glUniform3f(uniforms[L_DIFFUSE_2_U], pointLight.diffuse->x, pointLight.diffuse->y, pointLight.diffuse->z);
	glUniform3f(uniforms[L_SPECULAR_2_U], pointLight.specular->x, pointLight.specular->y, pointLight.specular->z);
	glUniform1f(uniforms[L_CONSTANT_2_U], pointLight.constant);
	glUniform1f(uniforms[L_LINEAR_2_U], pointLight.linear);
	glUniform1f(uniforms[L_QUADRATIC_2_U], pointLight.quadratic);

	glUniform3f(uniforms[L_POSITION_3_U], pointLight.position.x - 3.0f, pointLight.position.y, pointLight.position.z - 3.0f);
	glUniform3f(uniforms[L_AMBIENT_3_U], pointLight.ambient->x, pointLight.ambient->y, pointLight.ambient->z);
	glUniform3f(uniforms[L_DIFFUSE_3_U], pointLight.diffuse->x, pointLight.diffuse->y, pointLight.diffuse->z);
	glUniform3f(uniforms[L_SPECULAR_3_U], pointLight.specular->x, pointLight.specular->y, pointLight.specular->z);
	glUniform1f(uniforms[L_CONSTANT_3_U], pointLight.constant);
	glUniform1f(uniforms[L_LINEAR_3_U], pointLight.linear);
	glUniform1f(uniforms[L_QUADRATIC_3_U], pointLight.quadratic);
}


void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": " << error << "'" << std::endl;
	}
}

std::string Shader::LoadShader(const std::string & fileName)
{
	std::fstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.good())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

GLuint Shader::CreateShader(const std::string & text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: shader creation failed!" << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

	return shader;
}
