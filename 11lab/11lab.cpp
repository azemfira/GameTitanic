#include <iostream>
#include <stdio.h>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"//текстура қосу кітапханасы
GLuint VBO;//1- ші объект
std::vector<glm::vec3> Vertices;//1-ші объект координаттары
GLuint CBO;//1 - ші объекттің түсі
std::vector<glm::vec3> Colors;// 1-ші объект түсін беру
GLuint VBO1;//2-ші объект
std::vector<glm::vec3> Vertices1;//2-ші объекттің координаттары
GLuint CBO1;//2-ші объектінің түсі
std::vector<glm::vec3> Colors1;//2-ші объектінің түсін беру
GLuint VBO2;//3-ші объект
std::vector<glm::vec3> Vertices2;//3-ші объектінің координатасы 
GLuint CBO2;//3-ші объектінің түсі
std::vector<glm::vec3> Colors2;//3-ші объектінің түсі
GLuint TBO;	//2-ші объекттің текстурасы
std::vector<glm::vec2> Textures;//2-ші объекттің текстура координатасы
GLuint texture;//2-ші объект текстура
GLuint texture1;//1-ші объект текстура
GLuint TBO1;//1-ші объекттің текстурасы	
std::vector<glm::vec2> Textures1;//1-ші объекттің текстура координатасы
GLuint texture2;//3-ші объект текстура		
GLuint TBO2;//3-ші объекттің текстурасы		
std::vector<glm::vec2> Textures2;//3-ші объекттің текстура координатасы
GLuint TexLocation;//Шейдердегі текстураның орналасуы
GLuint gScaleLocation;
GLuint gWorldLocation;

float g = 0.0;
float px = 0;
float py = 0;
//Қиылысу фунция
bool intersection(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4)
{
	float a, b, a1, b1;
	float p1x = p1.x;
	float p1y = p1.y;
	float p2x = p3.x;
	float p2y = p3.y;
	float v1x = p2.x - p1.x;
	float v1y = p2.y - p1.y;
	float v2x = p4.x - p3.x;
	float v2y = p4.y - p3.y;
	a = (v2x * (p2y - p1y) + v2y * (p1x - p2x)) / (v2x * v1y - v1x * v2y);
	b = (v1x * (p1y - p2y) + v1y * (p2x - p1x)) / (v1x * v2y - v2x * v1y);
	if ((a >= 0 && a <= 1) && (b >= 0 && b <= 1)) {
		float x = p1x + a * v1x;
		float y = p1y + a * v1y;
		printf("%f %f\n", x, y);
		return true;
	}

	return false;
}

//Шейдерлер
static const char* pVS = "                                                    \n\
#version 430                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 Position;                                       \n\
layout (location = 1) in vec3 vColor;                                         \n\
layout (location = 2) in vec2 aTexCoord;                                         \n\
out vec3 Color;\n\
out vec2 TexCoord;\n\
uniform mat4 gWorld;\n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
	TexCoord = aTexCoord; \n\
    Color =vColor;\n\
    \n\
   gl_Position = gWorld * vec4(Position, 1.0);  \n\
}";

static const char* pFS = "                                                    \n\
#version 430                                                                  \n\
                                                                              \n\
in vec3 Color;\n\
in vec2 TexCoord;\n\
\n\
out vec4 FragColor;                                                           \n\
uniform sampler2D tex; \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    FragColor = vec4(Color.r, Color.gb, 1.0);                                             \n\
	FragColor = texture(tex,TexCoord);													\n\
}";
//1-ші объект
static void CreateVertexBuffer()
{
	Vertices.push_back(glm::vec3(-0.9f, 0.3f, 0.0f));
	Vertices.push_back(glm::vec3(-0.85f, 0.2f, 0.0f));
	Vertices.push_back(glm::vec3(-0.8f, 0.3f, 0.0f));

	Vertices.push_back(glm::vec3(-0.85f, 0.2f, 0.0f));
	Vertices.push_back(glm::vec3(-0.8f, 0.3f, 0.0f));
	Vertices.push_back(glm::vec3(-0.75, 0.2f, 0.0f));

	Vertices.push_back(glm::vec3(-0.8f, 0.3f, 0.0f));
	Vertices.push_back(glm::vec3(-0.75f, 0.2f, 0.0f));
	Vertices.push_back(glm::vec3(-0.7f, 0.3f, 0.0f));

	Vertices.push_back(glm::vec3(-0.8f, 0.3f, 0.0f));
	Vertices.push_back(glm::vec3(-0.8f, 0.4f, 0.0f));
	Vertices.push_back(glm::vec3(-0.75f, 0.35f, 0.0f));

	Textures1.push_back(glm::vec2(0.0f, 0.5f));
	Textures1.push_back(glm::vec2(0.25f, 0.2f));
	Textures1.push_back(glm::vec2(0.5f, 0.5f));

	Textures1.push_back(glm::vec2(0.25f, 0.2f));
	Textures1.push_back(glm::vec2(0.5f, 0.5f));
	Textures1.push_back(glm::vec2(0.75f, 0.2f));

	Textures1.push_back(glm::vec2(0.5f, 0.5f));
	Textures1.push_back(glm::vec2(0.75f, 0.2f));
	Textures1.push_back(glm::vec2(0.95f, 0.5f));

	Textures1.push_back(glm::vec2(0.0f, 0.5f));
	Textures1.push_back(glm::vec2(0.0f, 0.9f));
	Textures1.push_back(glm::vec2(0.75f, 0.95f));

	glGenBuffers(1, &VBO);//Объектіні генерациялайтын функция
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//Байланыстыру функциясы
	//Деректермен толтыру функция
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors.size(), Colors.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &TBO1);
	glBindBuffer(GL_ARRAY_BUFFER, TBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Textures1.size(), Textures1.data(), GL_STATIC_DRAW);

	//Текстураны жариялау
	stbi_set_flip_vertically_on_load(true);
	int w, h, c;
	unsigned char* image = stbi_load("titanik.jpg", &w, &h, &c, STBI_rgb);

	std::cout << w << " " << h << " " << c << std::endl;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

}
//1-ші объектке түс беру
static void CreateColorBuffer()
{
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));

	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));

	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors.push_back(glm::vec3(0.1f, 0.5f, 0.5f));


	Colors.push_back(glm::vec3(0.1f, 0.1f, 0.9f));
	Colors.push_back(glm::vec3(0.1f, 0.1f, 0.9f));
	Colors.push_back(glm::vec3(0.1f, 0.1f, 0.9f));
	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors.size(), Colors.data(), GL_STATIC_DRAW);
}
//2-ші объект
static void CreateVertexBuffer1()
{

	//1
	Vertices1.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(0.0f, 0.3f, 0.0f));
	Vertices1.push_back(glm::vec3(0.2f, 0.3f, 0.0f));

	Vertices1.push_back(glm::vec3(0.2f, 1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(0.2f, 0.3f, 0.0f));
	//2
	Vertices1.push_back(glm::vec3(-0.3f, 0.3f, 0.0f));
	Vertices1.push_back(glm::vec3(-0.5f, 0.3f, 0.0f));
	Vertices1.push_back(glm::vec3(-0.5f, -1.0f, 0.0f));

	Vertices1.push_back(glm::vec3(-0.3f, 0.3f, 0.0f));
	Vertices1.push_back(glm::vec3(-0.3f, -1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(-0.5f, -1.0f, 0.0f));
	//3
	Vertices1.push_back(glm::vec3(0.3f, -0.1f, 0.0f));
	Vertices1.push_back(glm::vec3(0.3f, -1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(0.5f, -1.0f, 0.0f));

	Vertices1.push_back(glm::vec3(0.3f, -0.1f, 0.0f));
	Vertices1.push_back(glm::vec3(0.5f, -0.1f, 0.0f));
	Vertices1.push_back(glm::vec3(0.5f, -1.0f, 0.0f));
	//4
	Vertices1.push_back(glm::vec3(0.6f, 0.2f, 0.0f));
	Vertices1.push_back(glm::vec3(0.6f, 1.0f, 0.0f));
	Vertices1.push_back(glm::vec3(0.8f, 1.0f, 0.0f));

	Vertices1.push_back(glm::vec3(0.6f, 0.2f, 0.0f));
	Vertices1.push_back(glm::vec3(0.8f, 0.2f, 0.0f));
	Vertices1.push_back(glm::vec3(0.8f, 1.0f, 0.0f));
	//1
	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(0.0f, 0.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));

	Textures.push_back(glm::vec2(1.0f, 1.0f));
	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));
	//2
	Textures.push_back(glm::vec2(1.0f, 1.0f));
	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(0.0f, 0.0f));

	Textures.push_back(glm::vec2(1.0f, 1.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));
	Textures.push_back(glm::vec2(0.0f, 0.0f));
	//3
	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(0.0f, 0.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));

	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(1.0f, 1.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));
	//4
	Textures.push_back(glm::vec2(0.0f, 0.0f));
	Textures.push_back(glm::vec2(0.0f, 1.0f));
	Textures.push_back(glm::vec2(1.0f, 1.0f));

	Textures.push_back(glm::vec2(0.0f, 0.0f));
	Textures.push_back(glm::vec2(1.0f, 0.0f));
	Textures.push_back(glm::vec2(1.0f, 1.0f));



	glGenBuffers(1, &VBO1);//Генерация функциясы
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);//Байланыстыру функциясы
	//Деректермен толтыру функциясы
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Vertices1.size(), Vertices1.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &CBO1);
	glBindBuffer(GL_ARRAY_BUFFER, CBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors1.size(), Colors1.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Textures.size(), Textures.data(), GL_STATIC_DRAW);

	//Инизиализация текстура
	stbi_set_flip_vertically_on_load(true);
	int w, h, c;
	unsigned char* image1 = stbi_load("ice.jpeg", &w, &h, &c, STBI_rgb);

	std::cout << w << " " << h << " " << c << std::endl;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);

}
//2-ші объектке түс беру
static void CreateColorBuffer1()
{
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	Colors1.push_back(glm::vec3(0.0f, 0.0f, 0.0f));


	glGenBuffers(1, &CBO1);
	glBindBuffer(GL_ARRAY_BUFFER, CBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors1.size(), Colors1.data(), GL_STATIC_DRAW);
}
//3-ші объект
static void CreateVertexBuffer2()
{
	Vertices2.push_back(glm::vec3(-1.0f, 1.0f, 0.0f));
	Vertices2.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	Vertices2.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	Vertices2.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

	Textures2.push_back(glm::vec2(0.0f, 1.0f));
	Textures2.push_back(glm::vec2(0.0f, 0.0f));
	Textures2.push_back(glm::vec2(1.0f, 0.0f));
	Textures2.push_back(glm::vec2(1.0f, 1.0f));
	glGenBuffers(1, &VBO2);//Генерациялау функциясы
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);//Байланыстыру функция
	//Толтыру функциясы
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Vertices2.size(), Vertices2.data(), GL_STATIC_DRAW);
	glGenBuffers(1, &CBO2);
	glBindBuffer(GL_ARRAY_BUFFER, CBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors2.size(), Colors2.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &TBO2);
	glBindBuffer(GL_ARRAY_BUFFER, TBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * Textures2.size(), Textures2.data(), GL_STATIC_DRAW);

	//Инизиализация текстура

	stbi_set_flip_vertically_on_load(true);
	int w, h, c;
	unsigned char* image2 = stbi_load("e.jpg", &w, &h, &c, STBI_rgb);

	std::cout << w << " " << h << " " << c << std::endl;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);

}
//3-ші объектке түс беру
static void CreateColorBuffer2()
{
	Colors2.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors2.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors2.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	Colors2.push_back(glm::vec3(0.1f, 0.5f, 0.5f));




	glGenBuffers(1, &CBO2);
	glBindBuffer(GL_ARRAY_BUFFER, CBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * Colors2.size(), Colors2.data(), GL_STATIC_DRAW);
}
//Салу функциясы
static void RenderSceneCB()
{
	//3-ші объект үшін
	glm::mat4 FWorld2;
	FWorld2[0][0] = 1.0f;       FWorld2[0][1] = 0.0f;          FWorld2[0][2] = 0.0f;     FWorld2[0][3] = 0.0f;
	FWorld2[1][0] = 0.0f;       FWorld2[1][1] = 1.0f;          FWorld2[1][2] = 0.0f;     FWorld2[1][3] = 0.0f;
	FWorld2[2][0] = 0.0f;       FWorld2[2][1] = 0.0f;          FWorld2[2][2] = 1.0f;     FWorld2[2][3] = 0.0f;
	FWorld2[3][0] = 0.0f;       FWorld2[3][1] = 0.0f;          FWorld2[3][2] = 0.0f;     FWorld2[3][3] = 1.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);


	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &FWorld2[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, CBO2);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, TBO2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(TexLocation, 0);
	glDrawArrays(GL_QUADS, 0, Vertices2.size());

	static float Scale = 0.0f;
	Scale += 0.0001f;
	float k = 1.0;
	py += g;
	g -= 0.000001f;
	printf("%f \r", g);
	if (py <= -0.8f) {
		py = -0.8;
	}
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//1-ші объект үшін
	glm::mat4 FWorld;
	FWorld[0][0] = 1.0f;		FWorld[0][1] = 0.0f;		FWorld[0][2] = 0.0f;        FWorld[0][3] = Scale;
	FWorld[1][0] = 0.0f;		FWorld[1][1] = 1.0f;		FWorld[1][2] = 0.0f;        FWorld[1][3] = py;
	FWorld[2][0] = 0.0f;		FWorld[2][1] = 0.0f;		FWorld[2][2] = 1.0f;		FWorld[2][3] = 0.0f;
	FWorld[3][0] = 0.0f;		FWorld[3][1] = 0.0f;		FWorld[3][2] = 0.0f;        FWorld[3][3] = 1.0f;


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &FWorld[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, TBO1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(TexLocation, 0);
	glDrawArrays(GL_TRIANGLES, 0, Vertices.size());
	//2-ші объект үшін	
	static float Scale1 = 0.0f;
	Scale1 += 0.009f;
	float k1 = 1.0;
	glm::mat4 FWorld1;

	FWorld1[0][0] = 1.0f;       FWorld1[0][1] = 0.0f;          FWorld1[0][2] = 0.0f;     FWorld1[0][3] = 0.0f;
	FWorld1[1][0] = sin(Scale1);       FWorld1[1][1] = 1.0f;          FWorld1[1][2] = 0.0f;     FWorld1[1][3] = 0.0f;
	FWorld1[2][0] = 0.0f;       FWorld1[2][1] = 0.0f;          FWorld1[2][2] = 1.0f;     FWorld1[2][3] = 0.0f;
	FWorld1[3][0] = 0.0f;       FWorld1[3][1] = 0.0f;          FWorld1[3][2] = 0.0f;     FWorld1[3][3] = 1.0f;


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &FWorld1[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, CBO1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(TexLocation, 0);
	glDrawArrays(GL_TRIANGLES, 0, Vertices1.size());
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	//қиылысуға нүктелер
	glm::vec3 p11 = glm::vec4(Vertices[6], 1.0) * FWorld;
	glm::vec3 p12 = glm::vec4(Vertices[7], 1.0) * FWorld;

	glm::vec3 p31 = glm::vec4(Vertices[10], 1.0) * FWorld;
	glm::vec3 p32 = glm::vec4(Vertices[11], 1.0) * FWorld;

	glm::vec3 p33 = glm::vec4(Vertices[4], 1.0) * FWorld;
	glm::vec3 p34 = glm::vec4(Vertices[5], 1.0) * FWorld;

	glm::vec3 p21 = glm::vec4(Vertices1[0], 1.0) * FWorld1;
	glm::vec3 p22 = glm::vec4(Vertices1[1], 1.0) * FWorld1;

	glm::vec3 p41 = glm::vec4(Vertices1[1], 1.0) * FWorld1;
	glm::vec3 p42 = glm::vec4(Vertices1[2], 1.0) * FWorld1;

	glm::vec3 p23 = glm::vec4(Vertices1[7], 1.0) * FWorld1;
	glm::vec3 p24 = glm::vec4(Vertices1[8], 1.0) * FWorld1;

	glm::vec3 p43 = glm::vec4(Vertices1[7], 1.0) * FWorld1;
	glm::vec3 p44 = glm::vec4(Vertices1[6], 1.0) * FWorld1;

	glm::vec3 p25 = glm::vec4(Vertices1[12], 1.0) * FWorld1;
	glm::vec3 p26 = glm::vec4(Vertices1[13], 1.0) * FWorld1;

	glm::vec3 p45 = glm::vec4(Vertices1[12], 1.0) * FWorld1;
	glm::vec3 p46 = glm::vec4(Vertices1[14], 1.0) * FWorld1;

	glm::vec3 p27 = glm::vec4(Vertices1[18], 1.0) * FWorld1;
	glm::vec3 p28 = glm::vec4(Vertices1[19], 1.0) * FWorld1;

	glm::vec3 p47 = glm::vec4(Vertices1[21], 1.0) * FWorld1;
	glm::vec3 p48 = glm::vec4(Vertices1[22], 1.0) * FWorld1;
	//қиылысуды тексеру 
	if (intersection(p11, p12, p23, p24)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p33, p34, p43, p44)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p31, p32, p41, p42)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p11, p12, p21, p22)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p33, p34, p45, p46)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p11, p12, p25, p26)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p31, p32, p47, p48)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	else if (intersection(p11, p12, p27, p28)) {
		printf("GAME OVER!\n");
		system("pause");
	}
	glutSwapBuffers();
}
//Тінтуір арқылы басқару
void MouseCB(int button, int state, int x, int y) {

	g = 0.0005f;

}
static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
	glutIdleFunc(RenderSceneCB);
	glutMouseFunc(MouseCB);
}
static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	GLuint ShaderObj = glCreateShader(ShaderType);
	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
		exit(0);
	}
	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	glShaderSource(ShaderObj, 1, p, Lengths);
	glCompileShader(ShaderObj);
	GLint success;
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		exit(1);
	}
	glAttachShader(ShaderProgram, ShaderObj);
}
//Шейдерді компиляциялау
static void CompileShaders()
{
	GLuint ShaderProgram = glCreateProgram();
	if (ShaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
		exit(1);
	}

	AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
	AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		exit(1);
	}
	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		exit(1);
	}
	glUseProgram(ShaderProgram);
	gWorldLocation = glGetUniformLocation(ShaderProgram, "gWorld");
	assert(gWorldLocation != 0xFFFFFFFF);
	TexLocation = glGetUniformLocation(ShaderProgram, "tex");
	assert(TexLocation != 0xFFFFFFFF);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GAME TITANIK");
	InitializeGlutCallbacks();
	GLenum res = glewInit();
	if (res != GLEW_OK) {
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}
	glClearColor(1.0f, 0.7f, 0.7f, 0.5f);
	CreateVertexBuffer2();
	CreateColorBuffer2();
	CreateVertexBuffer();
	CreateVertexBuffer1();
	CreateColorBuffer1();
	CreateColorBuffer();
	CompileShaders();
	glutMainLoop();
	return 0;
}
