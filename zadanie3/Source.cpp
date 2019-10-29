#include <algorithm>
#include "Window.h"
#include "Cube.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#pragma comment(lib, "glfw3")
#pragma comment(lib, "glew32")
#pragma comment(lib, "opengl32")

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glewExperimental = GL_TRUE;

	auto wnd = std::shared_ptr<Window>(new Window(512,512, "zadanie3", false));
	glfwSetFramebufferSizeCallback(wnd->getWnd(), framebuffer_size_callback);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(wnd->getWnd(), true);
	ImGui_ImplOpenGL3_Init("#version 330 core");

	auto defaultShader = std::shared_ptr<Shader>(new Shader("shader.vert", "shader.frag"));

	int width = 512;
	int height = 512;

	Cube cube = Cube();
	cube.setup(glm::vec2(width, height), defaultShader->getShaderProgram());

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	int quality = 1;
	int red = 0;
	int green = 0;
	int blue = 0;

	float *rgb = new float[3];
	rgb[0] = 0;
	rgb[1] = 0;
	rgb[2] = 0;

	float cyan = 0;
	float magenta = 0;
	float yellow = 0;
	float key = 0;

	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	while (!wnd->isRunning()) {
		glfwPollEvents();

		glClearColor(0.2f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("RGB color picker");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::SliderInt("Quality", &quality, 1, 100);
			if (ImGui::ColorPicker3("Color", rgb,  ImGuiColorEditFlags_DisplayRGB)) {
				key = 1 - std::max(std::max(rgb[0], rgb[1]), rgb[2]); //1-max(r,g,b) // {0 - 1}
				cyan = (1 - rgb[0] - key) / (1 - key);	// (1-red-key)/(1-key)
				magenta = (1 - rgb[1] - key) / (1 - key); //(1-green-key)/(1-key)
				yellow = (1 - rgb[2] - key) / (1 - key);  //(1-blue-key)/(1-key)
			}
			ImGui::End();

			ImGui::Begin("CMYK");
			if (ImGui::InputFloat("Cyan", &cyan)) {
				rgb[0] = (1 - cyan) * (1 - key);
			}
			if (ImGui::InputFloat("Magenta", &magenta)) {
				rgb[1] = (1 - magenta)*(1 - key);
			}
			if (ImGui::InputFloat("Yellow", &yellow)) {
				rgb[2] = (1 - yellow)*(1 - key);
			}
			if (ImGui::InputFloat("Key", &key)) {
				rgb[0] = (1 - cyan) * (1 - key);
				rgb[1] = (1 - magenta) * (1 - key);
				rgb[2] = (1 - yellow) * (1 - key);
			}
			ImGui::End();
		}

		defaultShader->bind();
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(1.f), glm::vec3(1, 1, 0));
		Uniforms::sendUniform4fv(defaultShader->getShaderProgram(), "rotationMatrix", rotationMatrix);
		cube.draw();
		defaultShader->unbind();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(wnd->getWnd());
	}

	delete rgb;

	return 0;
}