#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = NULL;
char InputSystem::keyPressed = ' ';
char InputSystem::transformationType = ' ';
int InputSystem::vertexSelected = 1;
bool InputSystem::isUpdated = false;

InputSystem::InputSystem()
{
	
}

InputSystem::~InputSystem()
{
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::update()
{
	//SELECT VERTEX TO MOVE
	if (GetAsyncKeyState('1') && vertexSelected != 1)
		vertexSelected = 1;
	else if (GetAsyncKeyState('2') && vertexSelected != 2)
		vertexSelected = 2;
	else if (GetAsyncKeyState('3') && vertexSelected != 3)
		vertexSelected = 3;
	else if (GetAsyncKeyState('4') && vertexSelected != 4)
		vertexSelected = 4;

	//GET KEY PRESSED
	if (GetAsyncKeyState('W') && keyPressed != 'W') 
	{
		keyPressed = 'W';
		isUpdated = false;
	}
	if (GetAsyncKeyState('S') && keyPressed != 'S')
	{
		keyPressed = 'S';
		isUpdated = false;
	}
	if (GetAsyncKeyState('A') && keyPressed != 'A')
	{
		keyPressed = 'A';
		isUpdated = false;
	}
	if (GetAsyncKeyState('D') && keyPressed != 'D')
	{
		keyPressed = 'D';
		isUpdated = false;
	}
	//Transform type
	if (GetAsyncKeyState('Q') && transformationType != 'Q')
	{
		transformationType = 'Q';
		isUpdated = false;
	}
	if (GetAsyncKeyState('E') && transformationType != 'E')
	{
		transformationType = 'E';
		isUpdated = false;
	}
	if (GetAsyncKeyState('R') && transformationType != 'R')
	{
		transformationType = 'R';
		isUpdated = false;
	}
}

char InputSystem::getKeyPressed()
{
	return sharedInstance->keyPressed;
}

int InputSystem::getVertexSelected()
{
	return sharedInstance->vertexSelected;
}

