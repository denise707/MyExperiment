#pragma once
class InputSystem
{
public:
	InputSystem();
	~InputSystem();
	static void initialize();

private:
	InputSystem(InputSystem const&) {} //copy constructor is private
	InputSystem& operator=(InputSystem const&) {}; //assignment operator is private

	static InputSystem* sharedInstance;

public:
	static char keyPressed;
	static char transformationType;
	static int vertexSelected;
	static bool isUpdated;

public:
	static int getVertexSelected();
	static char getKeyPressed();
	static void update();
};

