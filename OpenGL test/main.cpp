#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Errors.h"
#include "Shaders.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
//------------------------------------------SCENE GRAPH------------------------------------------
struct Node {
	std::string name;
	//glm::mat4 transform;
	glm::vec3 pos;
	std::vector<Node> children;
};

std::vector<Node> parentNodes;
Node rootNode, rootNode2;

void DrawNode(Node& node) {
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	bool node_open = ImGui::TreeNodeEx(node.name.c_str(), node_flags);
	if (ImGui::IsItemClicked()) {
		// do something when the node is clicked
	}
	if (node_open) {
		for (auto& child : node.children) {
			ImGui::PushID(&child);
			bool child_node_open = ImGui::TreeNodeEx(child.name.c_str(), node_flags);

			if (ImGui::IsItemClicked()) {
				// do something when the child node is clicked
			}

			if (child_node_open) {

				ImGui::Text("Child Properties");
				ImGui::SliderFloat("X", &child.pos.x, -1.0f, 1.0f);
				
				ImGui::TreePop();
			}

			ImGui::PopID();
		}

		ImGui::TreePop();
	}
	
	for (const auto& child : node.children) 
	{
		glUseProgram(renderingProgram);
		glPointSize(30.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_POINTS, 0, 1);
		glUniform3f(glad_glGetUniformLocation(renderingProgram, "aPos"), child.pos.x, child.pos.y, child.pos.z);
	}

}

void RenderScene() {
	// render the scene graph
	for (auto& parent : parentNodes)
	{
		DrawNode(parent);
	}
}
//------------------------------------------SCENE GRAPH------------------------------------------
GLuint createShaderProgram()
{

	GLint vertCompiled;
	GLint fragCompiled;
	GLint linked;

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

	string vertShaderStr = readShaderSource("vertShader.glsl");
	string fragShaderStr = readShaderSource("fragShader.glsl");

	const char* vertShaderSrc = vertShaderStr.c_str();
	const char* fragShaderSrc = fragShaderStr.c_str();

	glShaderSource(vShader, 1, &vertShaderSrc, NULL);
	glShaderSource(fShader, 1, &fragShaderSrc, NULL);

	// Compile vertex shader
	glCompileShader(vShader);
	checkOpenGLError();
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
	if (vertCompiled != 1)
	{
		cout << "Vertex compilation failed! " << endl;
		printlShaderLog(vShader);
	}

	// Compile fragment shader
	glCompileShader(fShader);
	checkOpenGLError();
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
	if (fragCompiled != 1)
	{
		cout << "Fragment compilation failed! " << endl;
		printlShaderLog(fShader);
	}

	// Link shaders
	GLuint vfProgram = glCreateProgram();
	glAttachShader(vfProgram, vShader);
	glAttachShader(vfProgram, fShader);
	glLinkProgram(vfProgram);

	checkOpenGLError();
	glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		cout << "Linking failed!" << endl;
		printlProgramLog(vfProgram);
	}

	return vfProgram;
}


void init(GLFWwindow* window) 
{
	renderingProgram = createShaderProgram();
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
}

void display(GLFWwindow* window, double currentTime)
{
	//glClearColor(1.0, 0.0, 0.0, 1.0);
	glUseProgram(renderingProgram);
	glPointSize(30.0f);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glDrawArrays(GL_POINTS, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	
}

int main(void)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	GLFWwindow* window = glfwCreateWindow(600, 600, "Test GUI", NULL, NULL);
	glfwMakeContextCurrent(window);
	// Initialize OpenGL loader using glad
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1); // V-SYNC ON

	init(window);

	// Setup ImGui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");


	// create the scene graph nodes
	rootNode.name = "Parent object 1";
	//rootNode.transform = glm::mat4(1.0f);
	rootNode2.name = "Parent object 2";
	//rootNode2.transform = glm::mat4(1.0f);

	// Create children nodes
	Node child1;
	child1.name = "Child object 1";
	//child1.transform = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	child1.pos = glm::vec3(0.5f, 0.0f, 0.0f);
	rootNode.children.push_back(child1);
	Node child2;
	child2.name = "Child object 2";
	//child2.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	child2.pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rootNode.children.push_back(child2);
	Node child3;
	child3.name = "Child object 3";
	//child3.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	child3.pos = glm::vec3(-0.5f, 0.0f, 0.0f);
	rootNode2.children.push_back(child3);

	// Parent nodes must be pushed back after all children
	parentNodes.push_back(rootNode);	
	parentNodes.push_back(rootNode2);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();

		// Start a new ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//display(window, glfwGetTime());

		// render the scene
		RenderScene();

		
		ImGui::Render();

		ImGui::EndFrame();
		// Clear the screen and render ImGui draw commands using OpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



		glfwSwapBuffers(window);
		
	}

	// Clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}  