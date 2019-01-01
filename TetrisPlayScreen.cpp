#include <iostream>
#include <IMainGame.h>

#include "TetrisPlayScreen.h"

Uint32 previousTicks = SDL_GetTicks();
const float DESIRED_FPS = 60.0f; // FPS the game is designed to run at
const int MAX_PHYSICS_STEPS = 6; // Max number of physics steps per frame
const float MS_PER_SECOND = 1000; // Number of milliseconds in a second
const float DESIRED_FRAMETIME = MS_PER_SECOND / DESIRED_FPS; // The desired frame time per frame
const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime

TetrisPlayScreen::TetrisPlayScreen(Rasengine::Window* window) :m_window(window)
{

}


TetrisPlayScreen::~TetrisPlayScreen()
{
}
int TetrisPlayScreen::GetNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}
int TetrisPlayScreen::GetPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void TetrisPlayScreen::Build()
{

}

void TetrisPlayScreen::Destroy()
{
}
void TetrisPlayScreen::OnEntry()
{
	std::cout << "On Entry\n";

	//Init Camera
	m_camera.Init(m_window->getScreenWidth(), m_window->getScreenHeight());
	//m_camera.SetScale(32.0f);	
	//// Point the camera to the center of the screen
	m_camera.SetPosition(glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f));

	//Create Tetris Controller
	m_tetrisController.Init(m_game->inputManager);
	//Create Tetris Controller
	m_tetrisController.CreateTetrisContainer(glm::vec2(m_window->getScreenWidth() / 2.0f,
		m_window->getScreenHeight() / 2.0f),
		glm::vec2(240.0f, 480.0f),
		Rasengine::ColorRGBA8(30.0f, 30.0f, 30.0f, 255.0f));

	//Init SpriteBatch
	m_spriteBatch.Init();
	// Compile our color shaders
	m_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.AddAttribute("vertexPosition");
	m_textureProgram.AddAttribute("vertexColor");
	m_textureProgram.AddAttribute("vertexUV");
	m_textureProgram.LinkShaders();

	/*GUI*/
	m_gui.Init("GUI");
	m_gui.LoadScheme("AlfiskoSkin.scheme");
	m_gui.LoadFont("DejaVuSans-10");
	m_score = static_cast<CEGUI::MultiLineEditbox*>(
		m_gui.CreateWidget("AlfiskoSkin/Label",
			glm::vec4(0.8f,0.2f,0.13f,0.04f),
			glm::vec4(0.0f),"Test"));
	m_score->setText("Score : ");
}

void TetrisPlayScreen::OnExit()
{
}
void TetrisPlayScreen::Update()
{
	m_camera.Update();
	CheckInput();

	// Calculate the frameTime in milliseconds
		Uint32 newTicks = SDL_GetTicks();
	Uint32 frameTime = newTicks - previousTicks;
	previousTicks = newTicks; // Store newTicks in previousTicks so we can use it next frame
							  // Get the total delta time

	float totalDeltaTime = (float)frameTime / DESIRED_FRAMETIME;

	int i = 0; // This counter makes sure we don't spiral to death!
			   // Loop while we still have steps to process.

	while (totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS) {
		// The deltaTime should be the the smaller of the totalDeltaTime and MAX_DELTA_TIME
		float deltaTime = min(totalDeltaTime, MAX_DELTA_TIME);

		m_tetrisController.Update(deltaTime);

		// Since we just took a step that is length deltaTime, subtract from totalDeltaTime
		totalDeltaTime -= deltaTime;
		// Increment our frame counter so we can limit steps to MAX_PHYSICS_STEPS
		i++;
	}
}

void TetrisPlayScreen::Draw()
{
	// Set the base depth to 1.0
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_textureProgram.Use();

	//Upload Texture Uniform
	GLint texutreUniform = m_textureProgram.GetUnifromLocation("mySampler");
	glUniform1i(texutreUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	glm::mat4 projectionMatrix = m_camera.GetCameraMatrix();
	GLint pUniform = m_textureProgram.GetUnifromLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);


	m_spriteBatch.Begin();

	m_tetrisController.Draw(m_spriteBatch);

	m_spriteBatch.End();
	m_spriteBatch.RenderBatch();

	m_textureProgram.Unuse();

	//Draw Gui
	m_gui.Draw();
	m_score->setText("Score : " + std::to_string(m_tetrisController.GetPoints()));
}
void TetrisPlayScreen::CheckInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt))
	{
		m_game->OnSDLEvent(evnt);
	}
}
