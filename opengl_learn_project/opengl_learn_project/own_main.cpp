//#include <stb_image.h>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "camera.h"
//#include "shader.h"
//#include "model.h"
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;	// time between current frame and last frame
//float lastFrame = 0.0f;
//
//
//glm::vec3 lightPos(1.2f, 0.0f, 2.0f);
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//														 // glfw window creation
//														 // --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile our shader zprogram
//	// ------------------------------------
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		// positions          // normals           // texture coords
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//	};
//	// world space positions of our cubes
//	glm::vec3 cubePositions[] = {
//		glm::vec3(0.0f,  0.0f,  0.0f),
//		glm::vec3(2.0f,  5.0f, -15.0f),
//		glm::vec3(-1.5f, -2.2f, -2.5f),
//		glm::vec3(-3.8f, -2.0f, -12.3f),
//		glm::vec3(2.4f, -0.4f, -3.5f),
//		glm::vec3(-1.7f,  3.0f, -7.5f),
//		glm::vec3(1.3f, -2.0f, -2.5f),
//		glm::vec3(1.5f,  2.0f, -2.5f),
//		glm::vec3(1.5f,  0.2f, -1.5f),
//		glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//	unsigned int VBO, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	unsigned int VAO_LIGHT;
//	glGenVertexArrays(1, &VAO_LIGHT);
//	glBindVertexArray(VAO_LIGHT);
//	unsigned int VBO_LIGHT;
//	glGenBuffers(1, &VBO_LIGHT);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_LIGHT);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	//// load and create a texture 
//	//// -------------------------
//	//unsigned int texture1, texture2;
//	//// texture 1
//	//// ---------
//	//glGenTextures(1, &texture1);
//	//glBindTexture(GL_TEXTURE_2D, texture1);
//	//// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//// load image, create texture and generate mipmaps
//	//int width, height, nrChannels;
//	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	//unsigned char *data = stbi_load("resource/container.jpg", &width, &height, &nrChannels, 0);
//	//if (data)
//	//{
//	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	//	glGenerateMipmap(GL_TEXTURE_2D);
//	//}
//	//else
//	//{
//	//	std::cout << "Failed to load texture" << std::endl;
//	//}
//	//stbi_image_free(data);
//	//// texture 2
//	//// ---------
//	//glGenTextures(1, &texture2);
//	//glBindTexture(GL_TEXTURE_2D, texture2);
//	//// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//// load image, create texture and generate mipmaps
//	//data = stbi_load("resource/awesomeface.png", &width, &height, &nrChannels, 0);
//	//if (data)
//	//{
//	//	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//	//	glGenerateMipmap(GL_TEXTURE_2D);
//	//}
//	//else
//	//{
//	//	std::cout << "Failed to load texture" << std::endl;
//	//}
//	//stbi_image_free(data);
//
//	unsigned int texture;
//
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	int width, height, nrChannels;
//	unsigned char * data = stbi_load("resource/container2.png", &width, &height, &nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		std::cout << "cannot load image" << std::endl;
//	}
//	stbi_image_free(data);
//
//	unsigned int texture_spec;
//	glGenTextures(1, &texture_spec);
//	glBindTexture(GL_TEXTURE_2D, texture_spec);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	data = stbi_load("resource/container2_specular.png", &width, &height, &nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		std::cout << "cannot load texture 2" << std::endl;
//	}
//	stbi_image_free(data);
//
//	unsigned int texture_emission;
//	glGenTextures(1, &texture_emission);
//	glBindTexture(GL_TEXTURE_2D, texture_emission);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	data = stbi_load("resource/matrix.jpg", &width, &height, &nrChannels, 0);
//	if (data) {
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	else {
//		std::cout << "cannot load texture 3" << std::endl;
//	}
//	stbi_image_free(data);
//
//	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//	// -------------------------------------------------------------------------------------------
//	Shader ourShader("shader.vs", "shader.ps");
//	ourShader.use();
//	ourShader.setInt("material.diffuse", 0);
//	ourShader.setInt("material.specular", 1);
//	ourShader.setInt("material.emission", 2);
//
//	Shader lightShader("shader.vs", "shader_light.ps");
//
//
//	glm::vec3 pointLightPositions[] = {
//		glm::vec3(0.7f,  0.2f,  2.0f),
//		glm::vec3(2.3f, -3.3f, -4.0f),
//		glm::vec3(-4.0f,  2.0f, -12.0f),
//		glm::vec3(0.0f,  0.0f, -3.0f)
//	};
//
//
//	Model ourModel("resource/nanosuit/naosuit.obj");
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		ourShader.use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		ourShader.setMat4("projection", projection);
//		ourShader.setMat4("view", view);
//
//		// render the loaded model
//		glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
//		ourShader.setMat4("model", model);
//		ourModel.Draw(ourShader);
//
//		// bind textures on corresponding texture units
//		//glActiveTexture(GL_TEXTURE0);
//		//glBindTexture(GL_TEXTURE_2D, texture);
//		//glActiveTexture(GL_TEXTURE1);
//		//glBindTexture(GL_TEXTURE_2D, texture_spec);
//		//glActiveTexture(GL_TEXTURE2);
//		//glBindTexture(GL_TEXTURE_2D, texture_emission);
//		//// activate shader
//		//ourShader.use();
//
//		//// pass projection matrix to shader (note that in this case it could change every frame)
//		//glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		//ourShader.setMat4("projection", glm::value_ptr(projection));
//
//		//// camera/view transformation
//		//glm::mat4 view = camera.GetViewMatrix();
//		//ourShader.setMat4("view", glm::value_ptr(view));
//		//ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//		//ourShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
//		//ourShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
//		//ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//		//ourShader.setVec3("light.position", lightPos);
//		//ourShader.setFloat("light.constant", 1.0f);
//		//ourShader.setFloat("light.linear", 0.09f);
//		//ourShader.setFloat("light.quadratic", 0.032f);
//		//ourShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
//		//ourShader.setFloat("light.outerCutOff", glm::cos(glm::radians(16.5f)));
//		//ourShader.setFloat("light.quadratic", 0.032f);
//		//ourShader.setVec3("light.direction", camera.Front);
//
//		//ourShader.setVec3("dirLight.direction", camera.Front);
//		//ourShader.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
//		//ourShader.setVec3("dirLight.diffuse", 0.5f, 0.5f, 0.5f); // 将光照调暗了一些以搭配场景
//		//ourShader.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
//
//		//char uniformName[30];
//		//for (int i = 0; i < 4; ++i) {
//		//	sprintf_s(uniformName, "pointLights[%d].position", i);
//		//	ourShader.setVec3(uniformName, pointLightPositions[i]);
//
//		//	sprintf_s(uniformName, "pointLights[%d].ambient", i);
//		//	ourShader.setVec3(uniformName, 0.05f, 0.05f, 0.05f);
//		//	sprintf_s(uniformName, "pointLights[%d].diffuse", i);
//		//	ourShader.setVec3(uniformName, 0.8f, 0.8f, 0.8f);
//		//	sprintf_s(uniformName, "pointLights[%d].specular", i);
//		//	ourShader.setVec3(uniformName, 1.0f, 1.0f, 1.0f);
//		//	sprintf_s(uniformName, "pointLights[%d].constant", i);
//		//	ourShader.setFloat(uniformName, 1.0f);
//		//	sprintf_s(uniformName, "pointLights[%d].linear", i);
//		//	ourShader.setFloat(uniformName, 0.09);
//		//	sprintf_s(uniformName, "pointLights[%d].quadratic", i);
//		//	ourShader.setFloat(uniformName, 0.032);
//		//}
//
//
//		//ourShader.setVec3("viewPos", camera.Position);
//		//ourShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//		//ourShader.setFloat("material.shininess", 32.0f);
//
//		//// render boxes
//		//glBindVertexArray(VAO);
//		//for (unsigned int i = 0; i < 10; i++)
//		//{
//		//	//	// calculate the model matrix for each object and pass it to shader before drawing
//		//	//	glm::mat4 model;
//		//	//	model = glm::translate(model, cubePositions[i]);
//		//	//	float angle = 20.0f * i;
//		//	//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		//	//	ourShader.setMat4("model", glm::value_ptr(model));
//
//		//	//	glDrawArrays(GL_TRIANGLES, 0, 36);
//		//	//}
//
//		//	glm::mat4 model;
//		//	model = glm::translate(model, cubePositions[i]);
//		//	float angle = 20.0f * i;
//		//	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//		//	ourShader.setMat4("model", glm::value_ptr(model));
//		//	ourShader.setMat3("normal_trans", glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(model)))));
//
//
//		//	glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		//}
//
//		//glBindVertexArray(VAO_LIGHT);
//		//glm::mat4 model_light;
//		//model_light = glm::translate(model_light, lightPos);
//		//model_light = glm::scale(model_light, glm::vec3(0.2f));
//		//lightShader.use();
//		//lightShader.setMat4("view", glm::value_ptr(view));
//		//lightShader.setMat4("projection", glm::value_ptr(projection));
//		//lightShader.setMat4("model", glm::value_ptr(model_light));
//		//glDrawArrays(GL_TRIANGLES, 0, 36);
//		//glBindVertexArray(0);
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}