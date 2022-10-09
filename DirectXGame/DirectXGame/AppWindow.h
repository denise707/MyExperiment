#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
private:
	SwapChain* m_swap_chain;
	//VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	//ConstantBuffer* m_cb;

private:
	void updateAnimation();
	Quad* quad;
	char pressed = ' ';
	int selected = 0;
	bool isUpdated = false;
	bool alreadyPressed = false;
};
