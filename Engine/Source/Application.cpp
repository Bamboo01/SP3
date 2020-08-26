#include "Application.h"
#include "SceneManager.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

//Include Coordinator for ECS
#include "Coordinator.h"

//Include Renderer for rendering
#include "Renderer.h"

//Sound Controller
#include "SoundController.h"

//Include ImGui Files
#include "../Dependencies/ImGui/imgui.h"
#include "../Dependencies/ImGui/imgui_impl_glfw.h"
#include "../Dependencies/ImGui/imgui_impl_opengl3.h"


GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0,
Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0,
Application::mouse_scroll_x = 0.0, Application::mouse_scroll_y = 0.0;
double Application::camera_yaw = 0.0, Application::camera_pitch = 0.0;
int m_width, m_height;
bool Application::exitProgram;

SceneManager* SceneManager::instance;
Coordinator coordinator;
Renderer renderer;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);
}
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application::mouse_scroll_x += xoffset;
	Application::mouse_scroll_y += yoffset;
}

bool Application::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Application::IsMousePressed(unsigned short key)
{
	return glfwGetMouseButton(m_window, key) != 0;
}

int Application::GetWindowWidth()
{
	return m_width;
}

void Application::GetCursorPos(double* xpos, double* ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}

int Application::GetWindowHeight()
{
	return m_height;
}

bool Application::GetMouseUpdate()
{
	glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	//Calculate the yaw and pitch
	camera_yaw = (float)mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	/*if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width - m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height - m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}*/
	int tempxPos, tempyPos;
	int sizeX, sizeY;
	glfwGetWindowPos(m_window, &tempxPos, &tempyPos);
	glfwGetWindowSize(m_window, &sizeX, &sizeY);
	RECT WindowRect = { tempxPos,tempyPos - 30,tempxPos + sizeX - 8,tempyPos + sizeY - 15 };
	ClipCursor(&WindowRect);

	glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	//if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width - m_window_deadzone))
	//{
	//	mouse_current_x = m_window_width >> 1;
	//	glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	//}
	//if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height - m_window_deadzone))
	//{
	//	mouse_current_y = m_window_height >> 1;
	//	glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	//}

	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	return false;
}

Application::Application()
{
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	m_width = 800;
	m_height = 600;
	exitProgram = false;

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_window_width, m_window_height, "Banbutech V0.01", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glfwSetScrollCallback(m_window, scroll_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	renderer.Init();

	// Hide the cursor
	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Application::Run()
{
	//Initialise sounds
	CSoundController* cSoundController = CSoundController::GetInstance();
	cSoundController->Init();
	cSoundController->LoadSound("Sounds/keypress.ogg", 1);
	cSoundController->LoadSound("Sounds/Intro.ogg", 2);
	cSoundController->LoadSound("Sounds/IntroComplete.ogg", 3);
	cSoundController->LoadSound("Sounds/Glitch.ogg", 4);

	//Main Loop
	Scene* scene = nullptr;
	SceneManager* scenemanager = SceneManager::getInstance();
	scenemanager->Init(&scene);
	scenemanager->ChangeScene(SCENE_INTRO);
	scenemanager->Update();

	const char* glsl_version = "#version 330";

	// ImGui Init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();
	// ImGui Init

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while ((!glfwWindowShouldClose(m_window)))
	{
		if (exitProgram == true)
		{
			break;
		}
		GetMouseUpdate();
		float timer = m_timer.getElapsedTime();
		scene->EarlyUpdate(timer);
		scene->Update(timer);
		scene->LateUpdate(timer);

		if (fabs(Application::mouse_scroll_x) > 0)
		{
			Application::mouse_scroll_x = 0;
		}
		if (fabs(Application::mouse_scroll_y) > 0)
		{
			Application::mouse_scroll_y = 0;
		}

		scene->PreRender();
		scene->Render();
		scene->PostRender();

		scenemanager->Update();

		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed

	// ImGui Exit
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	// ImGui Exit

	scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
