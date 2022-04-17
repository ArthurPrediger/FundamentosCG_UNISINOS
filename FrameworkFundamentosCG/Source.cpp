#include <iostream>
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Square.h"
#include <random>

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
int setupGeometry(const std::vector<float>& geometry);

glm::ivec2 handleInput(GLFWwindow* window, glm::ivec2& posArr, int maxX, int maxY, int colorsArr[], int& selectedColor, float& dt);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

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

	// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Compilando e buildando o programa de shader
	Shader shader("../Shaders\\ortho_vs.txt", "../Shaders\\ortho_fs.txt");

	float squareSideLength = 40.0f;
	std::vector<float> square = Square::Make(squareSideLength);
	for (int i = 6; i < 9; i++)
	{
		std::swap(square[i], square[size_t(i + 3)]);
	}
	GLuint VAO = setupGeometry(square);;

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
	// que n�o est� nos buffers
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);
	float ratio;
	float xMin = -1.0, xMax = 1.0, yMin = -1.0, yMax = 1.0;
	float zNear = -1.0, zFar = 1.0;
	if (width >= height)
	{
		ratio = width / (float)height;
		projection = glm::ortho(xMin * ratio, xMax * ratio, yMin,
			yMax, zNear, zFar);
	}
	else
	{
		ratio = height / (float)width;
		projection = glm::ortho(xMin, xMax, yMin * ratio,
			yMax * ratio, zNear, zFar);
	}

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(projection));

	glm::mat4 model = glm::mat4(1);

	enum Colors { White, Black, Blue, Orange, Green, Yellow, Magenta, Purple };

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> colorDist(0, 5);

	const int nSquaresGridSides = 8;
	const int nSquares = nSquaresGridSides * nSquaresGridSides;

	int colorsArr[nSquares] = {};
	for (int i = 0; i < nSquares; i++)
	{
		colorsArr[i] = 0;
	}

	int selectedSquare;
	int selectedColor = 0;
	glm::ivec2 posArr = { 0, 0 };
	float lastFrame = 0.0f;
	float dt = 0.0f;;

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		glViewport(0, 0, WIDTH, HEIGHT);

		// Limpa o buffer de cor
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		float currentFrame = glfwGetTime();
		dt += currentFrame - lastFrame;
		lastFrame = currentFrame;

		int offset = nSquaresGridSides + 2;
		handleInput(window, posArr, offset - 1, nSquaresGridSides - 1, colorsArr, selectedColor, dt);
		selectedSquare = posArr.y * offset + posArr.x;

		for (int y = 0; y < nSquaresGridSides; y++)
		{
			for (int x = 0; x < offset; x++)
			{
				if (x == offset - 2)
					continue;

				model = glm::mat4(1);
				model = glm::translate(model, {float(x - nSquaresGridSides / 2) * squareSideLength * ratio / (float(width) / 2.0f), 
					float(y - nSquaresGridSides / 2) * squareSideLength / (float(height) / 2.0f), 0.0f });
				model = glm::scale(model, { 1.0f * ratio / (float(width) / 2.0f), 1.0f / (float(height) / 2.0f), 1.0f });

				GLint modelLoc = glGetUniformLocation(shader.ID, "model");
				glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));

				switch ((x < nSquaresGridSides) ? colorsArr[y * nSquaresGridSides + x] : y)
				{
				case Colors::White:
					glUniform4f(colorLoc, 1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case Colors::Black:
					glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
					break;
				case Colors::Blue:
					glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
					break;
				case Colors::Orange:
					glUniform4f(colorLoc, 1.0f, 153.0f / 255.0f, 51.0f / 255.0f, 1.0f);
					break;
				case Colors::Green:
					glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case Colors::Yellow:
					glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
					break;
				case Colors::Magenta:
					glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
					break;
				case Colors::Purple:
					glUniform4f(colorLoc, 102.0f / 255.0f, 0.0f, 204.0f / 255.0f, 1.0f);
					break;
				default:
					glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
					break;
				}
				
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
				glDrawArrays(GL_TRIANGLES, 2, 5);
				glLineWidth(1);
				glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
				glDrawArrays(GL_LINE_LOOP, 0, 4);

				if ((y * offset + x) == selectedSquare)
				{
					glLineWidth(4);
					glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
					glDrawArrays(GL_LINE_LOOP, 0, 4);
				}
			}
		}

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

// Esta fun��o est� bastante harcoded - objetivo � criar os buffers que armazenam a 
// geometria de um tri�ngulo
// Apenas atributo coordenada nos v�rtices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A fun��o retorna o identificador do VAO
int setupGeometry(const std::vector<float>& geometry)
{
	// Aqui setamos as coordenadas x, y e z do tri�ngulo e as armazenamos de forma
	// sequencial, j� visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do v�rtice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO �nico ou em VBOs separados

	std::vector<GLfloat> vertices = { geometry };

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

glm::ivec2 handleInput(GLFWwindow* window, glm::ivec2& posArr, int maxX, int maxY, int colorsArr[], int& selectedColor, float& dt)
{
	if (dt > 0.1f)
	{
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			(posArr.x + 1 > maxX) ? posArr.x = 0 : posArr.x++;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			(posArr.x - 1 < 0) ? posArr.x = maxX : posArr.x--;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			(posArr.y + 1 > maxY) ? posArr.y = 0 : posArr.y++;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			(posArr.y - 1 < 0) ? posArr.y = maxY : posArr.y--;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			if (posArr.x == maxX)
			{
				selectedColor = posArr.y;
			}
			else if (posArr.x < maxX - 1)
			{
				colorsArr[posArr.y * (maxX - 1) + posArr.x] = selectedColor;
			}
		}
		dt = 0.0f;
	}

	return posArr;
};