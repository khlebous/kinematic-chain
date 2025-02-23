#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl2.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <memory>
#include <iostream>
#include <time.h> 

#include "Utils/WindowConstants.h"
#include "Scene/SceneController.h"

//
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void process_input(GLFWwindow* window);

// camera
float last_x = WindowConstants::WIDTH / 2.0f;
float last_y = WindowConstants::HEIGHT / 2.0f;

bool mouse_right_button_down = false;
bool key_o_down = false;
bool key_1_down = false;
bool key_2_down = false;
bool first_mouse = true;

// timing
float delta_time = 0.0f;
float last_frame = 0.0f;

std::shared_ptr<SceneController> sceneController;
bool show_demo_window = false;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WindowConstants::WIDTH, WindowConstants::HEIGHT, "kinematic chain", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, key_callback);

	// init ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glClearColor(0.635f, 0.682f, 0.6f, 1.0f);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	glEnable(GL_PROGRAM_POINT_SIZE);

	sceneController = std::make_shared<SceneController>();

	srand(time(NULL));

	// render loop
	// -----------
	//
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, WindowConstants::WIDTH, WindowConstants::HEIGHT);

		// render
		// ------
		sceneController->Update(delta_time);
		sceneController->Render();


		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// input
		// -----
		if ((!ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive()))
			process_input(window);

		if (show_demo_window)
			ImGui::ShowDemoWindow();

		// ImGui Rendering
		sceneController->RenderImGui();

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	WindowConstants::WIDTH = width;
	WindowConstants::HEIGHT = height;

	sceneController->ProcessWindowResize();
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (first_mouse)
	{
		last_x = xpos;
		last_y = ypos;
		first_mouse = false;
	}

	float xoffset = xpos - last_x;
	float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top

	last_x = xpos;
	last_y = ypos;

	if (mouse_right_button_down)
	{
		if (key_o_down)
			sceneController->ProcessObstacle(xpos, ypos);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action == GLFW_PRESS)
		{
			mouse_right_button_down = true;
			if (key_1_down)
				sceneController->ProcessFirstConfiguration(last_x, last_y);
			else if (key_2_down)
				sceneController->ProcessSecondConfiguration(last_x, last_y);
		}
		else if (action == GLFW_RELEASE)
		{
			mouse_right_button_down = false;
			sceneController->OnRightMouseUp();
		}
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_O)
	{
		if (action == GLFW_PRESS)
		{
			key_o_down = true;
		}
		else if (action == GLFW_RELEASE)
		{
			key_o_down = false;
		}
	}

	if (key == GLFW_KEY_1)
	{
		if (action == GLFW_PRESS) key_1_down = true;
		else if (action == GLFW_RELEASE) key_1_down = false;
	}

	if (key == GLFW_KEY_Q)
	{
		if (action == GLFW_PRESS)
		{
			if (!mouse_right_button_down)
				sceneController->ProcessAlternativeFirstConfiguration();
		}
	}

	if (key == GLFW_KEY_2)
	{
		if (action == GLFW_PRESS) key_2_down = true;
		else if (action == GLFW_RELEASE) key_2_down = false;
	}

	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
		{
			if (!mouse_right_button_down)
				sceneController->ProcessAlternativeSecondConfiguration();
		}
	}

	if (key == GLFW_KEY_U)
	{
		if (action == GLFW_PRESS)
		{
			sceneController->UpdateConfigurationSpace();
		}
	}

	if (key == GLFW_KEY_F)
	{
		if (action == GLFW_PRESS)
		{
			sceneController->DoFloodFill();
		}
	}
}
