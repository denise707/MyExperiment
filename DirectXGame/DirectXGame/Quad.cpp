#include "Quad.h"
#include <iostream>
#include "DeviceContext.h"
#include "EngineTime.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"

__declspec(align(16))
struct constant
{
	float m_angle;
};

Quad::Quad(vertex list[], UINT size_list)
{
	//Vertex Shader
	GraphicsEngine::get()->getVertexShaderData(&shader_byte_code, &size_shader);
	vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	vertexBuffer->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	constant cc;
	cc.m_angle = 0;

	//Constant Buffer
	constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(constant));

	//Experiment
	for(int i = 0; i < 4; i++)
	{
		vertex newVertex = list[i];
		storedList[i] = newVertex;
	}

	for (int i = 0; i < 4; i++) {
		tempList[i] = storedList[i];
	}
}

Quad::~Quad()
{
	
}

void Quad::updateAnimation()
{
	//#1
	ticks += EngineTime::getDeltaTime();
	changeSpeedTicks += EngineTime::getDeltaTime();

	if (changeSpeedTicks > CHANGE_SPEED_INTERVAL) {

		if (increaseSpeed) {
			direction = -1.0f;
			increaseSpeed = false;
		}

		else {
			direction = 1.0f;
			increaseSpeed = true;
		}

		changeSpeedTicks = 0.0f;
	}

	if (ticks > INTERVAL) {
		if (speed > 0)
		{
			speed += direction;
		}
		ticks = 0.0f;
	}

	m_delta_time += EngineTime::getDeltaTime() * speed;

	//#2
	//m_delta_time += EngineTime::getDeltaTime();
}

void Quad::update()
{
	//updateAnimation();
	vertexSelected = InputSystem::getVertexSelected();
	transType = InputSystem::transformationType;
	if (!InputSystem::isUpdated) {
		//Translate
		if (transType == 'Q') {
			switch (InputSystem::getKeyPressed()) {
			case 'W':
				for (int i = 0; i < 4; i++) {
					storedList[i] = { {storedList[i].position.x, storedList[i].position.y + 0.01f, storedList[i].position.z}, storedList[i].position1, storedList[i].color, storedList[i].color };
				}
				break;
			case 'S':
				for (int i = 0; i < 4; i++) {
					storedList[i] = { {storedList[i].position.x, storedList[i].position.y - 0.01f, storedList[i].position.z}, storedList[i].position1, storedList[i].color, storedList[i].color };
				}
				break;
			case 'A':
				for (int i = 0; i < 4; i++) {
					storedList[i] = { {storedList[i].position.x - 0.01f, storedList[i].position.y, storedList[i].position.z}, storedList[i].position1, storedList[i].color, storedList[i].color };
				}
				break;
			case 'D':
				for (int i = 0; i < 4; i++) {
					storedList[i] = { {storedList[i].position.x + 0.01f, storedList[i].position.y, storedList[i].position.z}, storedList[i].position1, storedList[i].color, storedList[i].color };
				}
				break;
			}
		}

		//Scale
		if (transType == 'E') {
			switch (InputSystem::getKeyPressed()) {
			case 'W':
				storedList[vertexSelected - 1] = { {storedList[vertexSelected - 1].position.x, storedList[vertexSelected - 1].position.y + 0.01f, storedList[vertexSelected - 1].position.z},
				storedList[vertexSelected - 1].position1, storedList[vertexSelected - 1].color, storedList[vertexSelected - 1].color };
				break;
			case 'S':
				storedList[vertexSelected - 1] = { {storedList[vertexSelected - 1].position.x, storedList[vertexSelected - 1].position.y - 0.01f, storedList[vertexSelected - 1].position.z},
				storedList[vertexSelected - 1].position1, storedList[vertexSelected - 1].color, storedList[vertexSelected - 1].color };
				break;
			case 'A':
				storedList[vertexSelected - 1] = { {storedList[vertexSelected - 1].position.x - 0.01f, storedList[vertexSelected - 1].position.y, storedList[vertexSelected - 1].position.z},
				storedList[vertexSelected - 1].position1, storedList[vertexSelected - 1].color, storedList[vertexSelected - 1].color };
				break;
			case 'D':
				storedList[vertexSelected - 1] = { {storedList[vertexSelected - 1].position.x + 0.01f, storedList[vertexSelected - 1].position.y, storedList[vertexSelected - 1].position.z},
				storedList[vertexSelected - 1].position1, storedList[vertexSelected - 1].color, storedList[vertexSelected - 1].color };
				break;
			}
		}
		
		vertexBuffer->load(storedList, sizeof(vertex), ARRAYSIZE(storedList), shader_byte_code, size_shader);
		InputSystem::isUpdated = true;
		InputSystem::keyPressed = ' ';
	}
}

void Quad::draw(VertexShader* vertexShader, PixelShader* pixelShader)
{
	//Constant Buffer
	constant cc;
	cc.m_angle = m_delta_time;
	constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	DeviceContext* deviceContext = GraphicsEngine::get()->getImmediateDeviceContext();
	deviceContext->setVertexBuffer(vertexBuffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Quad::release()
{
	vertexBuffer->release();
	delete this;
}

