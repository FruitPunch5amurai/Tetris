#pragma once
#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <GLSLProgram.h>
#include <Vertex.h>
#include <vector>
#include <SpriteBatch.h>
#include <InputManager.h>

class TetrisContainer;

class TetrisController {
public:
	TetrisController();
	~TetrisController();

	void Init(Rasengine::InputManager& inputManager);
	void CreateTetrisContainer(const glm::vec2& position, const glm::vec2& dims, const Rasengine::ColorRGBA8& color);
	void Draw(Rasengine::SpriteBatch& spriteBatch);
	bool Update(float deltaTime);

	int GetPoints();
private:
	float m_addRate=10.0f;
	float m_frameCounter = 0.0f;

	Rasengine::InputManager* m_inputManager;
	TetrisContainer* m_tetrisContainer = nullptr;
	
};