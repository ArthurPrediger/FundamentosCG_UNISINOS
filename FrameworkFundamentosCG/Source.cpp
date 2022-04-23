#include <iostream>
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Camera.h"
#include "InputGridManager.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Prot�tipos das fun��es
int setupGeometry3D(const std::vector<float>& geometry);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

Camera cam;
bool firstMouse = true;
float lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0; //para calcular o quanto que o mouse deslocou
float yaw = -90.0, pitch = 0.0;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Framework", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported " << version << std::endl;

	// Compilando e buildando o programa de shader
	Shader shader("../Shaders\\perspectiveShader_vs.txt", "../Shaders\\perspectiveShader_fs.txt");

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	Grid<float> grid(0.1f, 10, 10, 10);
	InputGridManager igm(grid);

	GLuint VAO;

	glUseProgram(shader.ID);

	//Matriz de view
	glm::mat4 view = glm::mat4(1);
	view = glm::lookAt(cam.GetPos(), glm::vec3(0.0f, 0.0f, 0.0f) + cam.GetFront(), cam.GetUp());
	shader.setMat4("view", glm::value_ptr(view));

	//Matriz de proje��o
	glm::mat4 projection = glm::mat4(1); //matriz identidade
	projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	shader.setMat4("projection", glm::value_ptr(projection));

	//Habilita teste de profundidade
	glEnable(GL_DEPTH_TEST);

	glUseProgram(shader.ID);

	float lastFrame = 0.0f;

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		float currentFrame = float(glfwGetTime());
		float dt = currentFrame - lastFrame;
		lastFrame = currentFrame;
		cam.UpdateCameraPos(window, dt);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// Limpa o buffer de cor e de profundidade
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		view = glm::lookAt(cam.GetPos(), cam.GetPos() + cam.GetFront(), cam.GetUp());
		shader.setMat4("view", glm::value_ptr(view));

		glm::mat4 model = glm::mat4(1);
		GLint modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));

		std::vector<float> triangles;

		igm.Update(window, triangles, dt);

		for (int z = 0; z < grid.GetUnitsDepth(); z++)
		{
			for (int y = 0; y < grid.GetUnitsHeight(); y++)
			{
				for (int x = 0; x < grid.GetUnitsWidth(); x++)
				{
					const int cubeIndex = z * grid.GetUnitsHeight() * grid.GetUnitsWidth() + y * grid.GetUnitsWidth() + x;

					if (!grid.RenderCube(cubeIndex))
						continue;

					const auto& vertices = grid.GetCubesVertices()[cubeIndex].vertices;
					const auto& indices = grid.GetCubesVertices()[cubeIndex].indices;

					for (int i = 0; i < indices.size(); i++)
					{
						int offset = (indices[i]) * 6;
						triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
						offset = (indices[++i]) * 6;
						triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
						offset = (indices[++i]) * 6;
						triangles.insert(triangles.end(), vertices.begin() + offset, vertices.begin() + offset + 6);
					}
				}
			}
		}

		if (triangles.size() > 0)
		{
			VAO = setupGeometry3D(triangles);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, triangles.size() / 6);
		}

		glBindVertexArray(0);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado - s� pode ter uma inst�ncia (deve ser est�tica se
// estiver dentro de uma classe) - � chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cam.SetFront(glm::normalize(front));

	//Precisamos tamb�m atualizar o cameraUp!! Pra isso, usamos o Up do mundo (y),
	//Recalculamos Right e depois o Up
	glm::vec3 right = glm::normalize(glm::cross(cam.GetFront(), glm::vec3(0.0, 1.0, 0.0)));
	cam.SetUp(glm::normalize(glm::cross(right, cam.GetFront())));

}

int setupGeometry3D(const std::vector<float>& geometry)
{
	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados
	std::vector<float> vertices = { geometry };
	GLuint VBO, VAO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices.front(), GL_STATIC_DRAW);
	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);

	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posi��o (x, y, z)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	////Atributo cor (r, g, b)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);
	return VAO;
}