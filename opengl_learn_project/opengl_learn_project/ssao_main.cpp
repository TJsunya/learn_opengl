//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <learnopengl/shader.h>
//#include <learnopengl/camera.h>
//#include <learnopengl/model.h>
//
//#include <iostream>
//#include <random>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//unsigned int loadCubemap(std::vector<std::string> &);
//void RenderCube();
//void RenderQuad();
//
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//GLuint draw_mode = 1;
//
//GLfloat lerp(GLfloat a, GLfloat b, GLfloat f)
//{
//	return a + f * (b - a);
//}
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
//	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//	glEnable(GL_DEPTH_TEST);
//	
//	// Setup and compile our shaders
//	Shader shaderGeometryPass("ssao_gbuffer.vs", "ssao_gbuffer.ps");
//	Shader shaderLightingPass("ssao_lighting.vs", "ssao_lighting.ps");
//	Shader shaderSSAO("ssao_ssao.vs", "ssao_ssao.ps");
//	Shader shaderSSAOBlur("ssao_blur.vs", "ssao_blur.ps");
//
//	shaderLightingPass.use();
//	glUniform1i(glGetUniformLocation(shaderLightingPass.ID, "gPositionDepth"), 0);
//	glUniform1i(glGetUniformLocation(shaderLightingPass.ID, "gNormal"), 1);
//	glUniform1i(glGetUniformLocation(shaderLightingPass.ID, "gAlbedo"), 2);
//	glUniform1i(glGetUniformLocation(shaderLightingPass.ID, "ssao"), 3);
//	shaderSSAO.use();
//	glUniform1i(glGetUniformLocation(shaderSSAO.ID, "gPositionDepth"), 0);
//	glUniform1i(glGetUniformLocation(shaderSSAO.ID, "gNormal"), 1);
//	glUniform1i(glGetUniformLocation(shaderSSAO.ID, "texNoise"), 2);
//
//	Model nanosuit("resource/nanosuit/nanosuit.obj");
//
//	// Lights
//	glm::vec3 lightPos = glm::vec3(2.0, 4.0, -2.0);
//	glm::vec3 lightColor = glm::vec3(0.2, 0.2, 0.7);
//
//
//	GLuint gBuffer;
//	glGenFramebuffers(1, &gBuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//	GLuint gPositionDepth, gNormal, gAlbedo;
//	// - Position + linear depth color buffer
//	glGenTextures(1, &gPositionDepth);
//	glBindTexture(GL_TEXTURE_2D, gPositionDepth);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPositionDepth, 0);
//	// - Normal color buffer
//	glGenTextures(1, &gNormal);
//	glBindTexture(GL_TEXTURE_2D, gNormal);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
//	// - Albedo color buffer
//	glGenTextures(1, &gAlbedo);
//	glBindTexture(GL_TEXTURE_2D, gAlbedo);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
//	// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
//	glDrawBuffers(3, attachments);
//
//	GLuint rboDepth;
//	glGenRenderbuffers(1, &rboDepth);
//	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//	// - Finally check if framebuffer is complete
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "GBuffer Framebuffer not complete!" << std::endl;
//
//	GLuint ssaoFBO, ssaoBlurFBO;
//	glGenFramebuffers(1, &ssaoFBO);  glGenFramebuffers(1, &ssaoBlurFBO);
//	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//	GLuint ssaoColorBuffer, ssaoColorBufferBlur;
//	// - SSAO color buffer
//	glGenTextures(1, &ssaoColorBuffer);
//	glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "SSAO Framebuffer not complete!" << std::endl;
//	// - and blur stage
//	glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//	glGenTextures(1, &ssaoColorBufferBlur);
//	glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "SSAO Blur Framebuffer not complete!" << std::endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	// Sample kernel
//	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
//	std::default_random_engine generator;
//	std::vector<glm::vec3> ssaoKernel;
//	for (GLuint i = 0; i < 64; ++i)
//	{
//		glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
//		sample = glm::normalize(sample);
//		sample *= randomFloats(generator);
//		GLfloat scale = GLfloat(i) / 64.0;
//
//		// Scale samples s.t. they're more aligned to center of kernel
//		scale = lerp(0.1f, 1.0f, scale * scale);
//		sample *= scale;
//		ssaoKernel.push_back(sample);
//	}
//	// Noise texture
//	std::vector<glm::vec3> ssaoNoise;
//	for (GLuint i = 0; i < 16; i++)
//	{
//		glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
//		ssaoNoise.push_back(noise);
//	}
//	GLuint noiseTexture; glGenTextures(1, &noiseTexture);
//	glBindTexture(GL_TEXTURE_2D, noiseTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
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
//		// 1. Geometry Pass: render scene's geometry/color data into gbuffer
//		glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 50.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model;
//		shaderGeometryPass.use();
//		glUniformMatrix4fv(glGetUniformLocation(shaderGeometryPass.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		glUniformMatrix4fv(glGetUniformLocation(shaderGeometryPass.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
//		// Floor cube
//		model = glm::translate(model, glm::vec3(0.0, -1.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 20.0f));
//		glUniformMatrix4fv(glGetUniformLocation(shaderGeometryPass.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		RenderCube();
//		// Nanosuit model on the floor
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.0));
//		model = glm::rotate(model, -80.0f, glm::vec3(1.0, 0.0, 0.0));
//		model = glm::scale(model, glm::vec3(0.5f));
//		glUniformMatrix4fv(glGetUniformLocation(shaderGeometryPass.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		nanosuit.Draw(shaderGeometryPass);
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	
//
//
//		// 2. Create SSAO texture
//		glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
//		glClear(GL_COLOR_BUFFER_BIT);
//		shaderSSAO.use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, gPositionDepth);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, gNormal);
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, noiseTexture);
//		// Send kernel + rotation 
//		for (GLuint i = 0; i < 64; ++i)
//			glUniform3fv(glGetUniformLocation(shaderSSAO.ID, ("samples[" + std::to_string(i) + "]").c_str()), 1, &ssaoKernel[i][0]);
//		glUniformMatrix4fv(glGetUniformLocation(shaderSSAO.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//		RenderQuad();
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		// 3. Blur SSAO texture to remove noise
//		glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
//		glClear(GL_COLOR_BUFFER_BIT);
//		shaderSSAOBlur.use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);
//		RenderQuad();
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		// 4. Lighting Pass: traditional deferred Blinn-Phong lighting now with added screen-space ambient occlusion
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		shaderLightingPass.use();
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, gPositionDepth);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, gNormal);
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, gAlbedo);
//		glActiveTexture(GL_TEXTURE3); // Add extra SSAO texture to lighting pass
//		glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);
//		// Also send light relevant uniforms
//		glm::vec3 lightPosView = glm::vec3(camera.GetViewMatrix() * glm::vec4(lightPos, 1.0));
//		glUniform3fv(glGetUniformLocation(shaderLightingPass.ID, "light.Position"), 1, &lightPosView[0]);
//		glUniform3fv(glGetUniformLocation(shaderLightingPass.ID, "light.Color"), 1, &lightColor[0]);
//		// Update attenuation parameters
//		const GLfloat constant = 1.0; // Note that we don't send this to the shader, we assume it is always 1.0 (in our case)
//		const GLfloat linear = 0.09;
//		const GLfloat quadratic = 0.032;
//		glUniform1f(glGetUniformLocation(shaderLightingPass.ID, "light.Linear"), linear);
//		glUniform1f(glGetUniformLocation(shaderLightingPass.ID, "light.Quadratic"), quadratic);
//		glUniform1i(glGetUniformLocation(shaderLightingPass.ID, "draw_mode"), draw_mode);
//		RenderQuad();
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//
//	glfwTerminate();
//	return 0;
//}
//// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
//// and post-processing effects.
//GLuint quadVAO = 0;
//GLuint quadVBO;
//void RenderQuad()
//{
//	if (quadVAO == 0)
//	{
//		GLfloat quadVertices[] = {
//			// Positions        // Texture Coords
//			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
//			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
//			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
//			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
//		};
//		// Setup plane VAO
//		glGenVertexArrays(1, &quadVAO);
//		glGenBuffers(1, &quadVBO);
//		glBindVertexArray(quadVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	}
//	glBindVertexArray(quadVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	glBindVertexArray(0);
//}
//
//// RenderCube() Renders a 1x1 3D cube in NDC.
//GLuint cubeVAO = 0;
//GLuint cubeVBO = 0;
//void RenderCube()
//{
//	// Initialize (if necessary)
//	if (cubeVAO == 0)
//	{
//		GLfloat vertices[] = {
//			// Back face
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
//			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
//															  // Front face
//															  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//															  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
//															  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
//															  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
//															  -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
//															  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
//																												 // Left face
//																												 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//																												 -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
//																												 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
//																												 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
//																												 -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
//																												 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//																																								   // Right face
//																																								   0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
//																																								   0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
//																																								   0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
//																																								   0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
//																																								   0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
//																																								   0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
//																																																					// Bottom face
//																																																					-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//																																																					0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
//																																																					0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
//																																																					0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
//																																																					-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
//																																																					-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//																																																																		// Top face
//																																																																		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//																																																																		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//																																																																		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
//																																																																		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//																																																																		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//																																																																		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left        
//		};
//		glGenVertexArrays(1, &cubeVAO);
//		glGenBuffers(1, &cubeVBO);
//		// Fill buffer
//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		// Link vertex attributes
//		glBindVertexArray(cubeVAO);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//	// Render Cube
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
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
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const *path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//
//unsigned int loadCubemap(std::vector<std::string> & faces) {
//	unsigned int cube_texture;
//	glGenTextures(1, &cube_texture);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_texture);
//
//	int width, height, nrChannels;
//	for (unsigned int i = 0; i < faces.size(); ++i) {
//		unsigned char * data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
//
//		if (data) {
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else {
//			cout << "cannot load image" << faces[i] << std::endl;
//		}
//	}
//
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	return cube_texture;
//
//}