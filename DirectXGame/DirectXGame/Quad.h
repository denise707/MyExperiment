#pragma once
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "VertexShader.h"

struct vec3
{
	float x, y, z;
};

struct vec2
{
	float x, y;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

class Quad
{
public:
	Quad(vertex list[], UINT size_list);
	~Quad();

	void update();
	void draw(VertexShader* vertexShader, PixelShader* pixelShader);
	void release();

protected:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

//-----For Animation-----
private:
	void updateAnimation();
private:
	float m_delta_time = 0;

	float speed = 3;
	float ticks = 0.0f;
	float INTERVAL = 1.0;
	float changeSpeedTicks = 0.0f;
	float CHANGE_SPEED_INTERVAL = 10.0f;
	bool increaseSpeed = true;
	float direction = 1.0f;

//-----For Experiment------
private:
	vertex storedList[4];
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
public:
	int vertexSelected = 1;
	char keyPressed = ' ';
	vertex newList[4];
	bool isUpdated = false;
	char transType = 'Q';
	vertex tempList[4];
	float angle = 0.01f;
private:

};

