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
//void renderSphere();
//void renderCube();
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
//	glfwWindowHint(GLFW_SAMPLES, 4);
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
//	glDepthFunc(GL_LEQUAL);  
//	Shader shader("pbr_simple.vs", "pbr_simple.ps");
//	Shader equirectangularToCubemapShader("pbr_cubemap.vs", "pbr_cubemap.ps");
//	Shader backgroundShader("pbr_cubemap_background.vs", "pbr_cubemap_background.ps");
//	Shader irradianceShader("pbr_cubemap.vs", "pbr_cubemap_convolute.ps");
//
//	irradianceShader.use();
//	irradianceShader.setInt("environmentMap", 0);
//
//	backgroundShader.use();
//	backgroundShader.setInt("environmentMap", 0);
//
//	shader.use();
//	shader.setInt("albedoMap", 0);
//	shader.setInt("normalMap", 1);
//	shader.setInt("metallicMap", 2);
//	shader.setInt("roughnessMap", 3);
//	shader.setInt("irradianceMap", 4);
//	//shader.setInt("aoMap", 4);
//
//	// load PBR material textures
//	// --------------------------
//	unsigned int albedo = loadTexture("resource/rustediron2_basecolor.png");
//	unsigned int normal = loadTexture("resource/rustediron2_normal.png");
//	unsigned int metallic = loadTexture("resource/rustediron2_metallic.png");
//	unsigned int roughness = loadTexture("resource/rustediron2_roughness.png");
//	//unsigned int ao = loadTexture(FileSystem::getPath("resources/textures/pbr/rusted_iron/ao.png").c_str());
//
//	// lights
//	// ------
//	glm::vec3 lightPositions[] = {
//		glm::vec3(-10.0f,  10.0f, 10.0f),
//		glm::vec3(10.0f,  10.0f, 10.0f),
//		glm::vec3(-10.0f, -10.0f, 10.0f),
//		glm::vec3(10.0f, -10.0f, 10.0f),
//	};
//	glm::vec3 lightColors[] = {
//		glm::vec3(300.0f, 300.0f, 300.0f),
//		glm::vec3(300.0f, 300.0f, 300.0f),
//		glm::vec3(300.0f, 300.0f, 300.0f),
//		glm::vec3(300.0f, 300.0f, 300.0f)
//	};
//	int nrRows = 7;
//	int nrColumns = 7;
//	float spacing = 2.5;
//
//	unsigned int captureFBO;
//	unsigned int captureRBO;
//	glGenFramebuffers(1, &captureFBO);
//	glGenRenderbuffers(1, &captureRBO);
//
//	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
//	glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);
//
//	stbi_set_flip_vertically_on_load(true);
//	int width, height, nrComponents;
//	float *data = stbi_loadf("resource/newport_loft.hdr", &width, &height, &nrComponents, 0);
//	unsigned int hdrTexture;
//	if (data) {
//		glGenTextures(1, &hdrTexture);
//		glBindTexture(GL_TEXTURE_2D, hdrTexture);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);
//		
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else {
//		std::cout << "fail to load hdr image" << std::endl;
//	}
//
//	unsigned int envCubeMap;
//	glGenTextures(1, &envCubeMap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
//	for (unsigned int i = 0; i < 6; ++i) {
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 512, 512, 0, GL_RGB, GL_FLOAT, NULL);
//
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
//	glm::mat4 captureViews[] =
//	{
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
//		glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
//	};
//
//	equirectangularToCubemapShader.use();
//	equirectangularToCubemapShader.setInt("equirectangularMap", 0);
//	equirectangularToCubemapShader.setMat4("projection", captureProjection);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, hdrTexture);
//
//	glViewport(0, 0, 512, 512); // don't forget to configure the viewport to the capture dimensions.
//	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
//	for (unsigned int i = 0; i < 6; ++i)
//	{
//		equirectangularToCubemapShader.setMat4("view", captureViews[i]);
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubeMap, 0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		renderCube();
//	}
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//
//	unsigned int irradianceMap;
//	glGenTextures(1, &irradianceMap);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
//	for (int i = 0; i < 6; ++i) {
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, NULL);
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	
//	glViewport(0, 0, 32, 32);
//	glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
//	irradianceShader.use();
//	irradianceShader.setInt("environmentMap", 0);
//	irradianceShader.setMat4("projection", captureProjection);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
//	
//	for (unsigned int i = 0; i < 6; ++i) {
//		irradianceShader.setMat4("view", captureViews[i]);
//		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMap, 0);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		renderCube();
//	}
//
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	// initialize static shader uniforms before rendering
//	// --------------------------------------------------
//	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//	shader.use();
//	shader.setMat4("projection", projection);
//	backgroundShader.use();
//	backgroundShader.setMat4("projection", projection);
//
//	// then before rendering, configure the viewport to the original framebuffer's screen dimensions
//	int scrWidth, scrHeight;
//	glfwGetFramebufferSize(window, &scrWidth, &scrHeight);
//	glViewport(0, 0, scrWidth, scrHeight);
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
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		glm::mat4 view = camera.GetViewMatrix();
//		shader.setMat4("view", view);
//		shader.setVec3("camPos", camera.Position);
//
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, albedo);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, normal);
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, metallic);
//		glActiveTexture(GL_TEXTURE3);
//		glBindTexture(GL_TEXTURE_2D, roughness);
//		glActiveTexture(GL_TEXTURE4);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceMap);
//		/*glActiveTexture(GL_TEXTURE4);
//		glBindTexture(GL_TEXTURE_2D, ao);*/
//
//		// render rows*column number of spheres with material properties defined by textures (they all have the same material properties)
//		glm::mat4 model;
//		for (int row = 0; row < nrRows; ++row)
//		{
//			for (int col = 0; col < nrColumns; ++col)
//			{
//				model = glm::mat4();
//				model = glm::translate(model, glm::vec3(
//					(float)(col - (nrColumns / 2)) * spacing,
//					(float)(row - (nrRows / 2)) * spacing,
//					0.0f
//				));
//				shader.setMat4("model", model);
//				renderSphere();
//			}
//		}
//
//		// render light source (simply re-render sphere at light positions)
//		// this looks a bit off as we use the same shader, but it'll make their positions obvious and 
//		// keeps the codeprint small.
//		for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
//		{
//			glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
//			newPos = lightPositions[i];
//			shader.setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
//			shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
//
//			model = glm::mat4();
//			model = glm::translate(model, newPos);
//			model = glm::scale(model, glm::vec3(0.5f));
//			shader.setMat4("model", model);
//			renderSphere();
//		}
//
//		backgroundShader.use();
//		backgroundShader.setMat4("view", view);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, envCubeMap);
//		renderCube();
//
//		// input
//		// -----
//		processInput(window);
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
//
//// renderCube() renders a 1x1 3D cube in NDC.
//// -------------------------------------------------
//unsigned int cubeVAO = 0;
//unsigned int cubeVBO = 0;
//void renderCube()
//{
//	// initialize (if necessary)
//	if (cubeVAO == 0)
//	{
//		float vertices[] = {
//			// back face
//			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//			1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
//			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
//																  // front face
//																  -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//																  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
//																  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//																  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
//																  -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
//																  -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
//																														// left face
//																														-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//																														-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
//																														-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//																														-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
//																														-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//																														-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
//																																											  // right face
//																																											  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//																																											  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//																																											  1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
//																																											  1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
//																																											  1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
//																																											  1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
//																																																								   // bottom face
//																																																								   -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//																																																								   1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
//																																																								   1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//																																																								   1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
//																																																								   -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
//																																																								   -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
//																																																																						 // top face
//																																																																						 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//																																																																						 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//																																																																						 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
//																																																																						 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
//																																																																						 -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
//																																																																						 -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
//		};
//		glGenVertexArrays(1, &cubeVAO);
//		glGenBuffers(1, &cubeVBO);
//		// fill buffer
//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		// link vertex attributes
//		glBindVertexArray(cubeVAO);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//	// render Cube
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//}
//
//// renders (and builds at first invocation) a sphere
//// -------------------------------------------------
//unsigned int sphereVAO = 0;
//unsigned int indexCount;
//void renderSphere()
//{
//	if (sphereVAO == 0)
//	{
//		glGenVertexArrays(1, &sphereVAO);
//
//		unsigned int vbo, ebo;
//		glGenBuffers(1, &vbo);
//		glGenBuffers(1, &ebo);
//
//		std::vector<glm::vec3> positions;
//		std::vector<glm::vec2> uv;
//		std::vector<glm::vec3> normals;
//		std::vector<unsigned int> indices;
//
//		const unsigned int X_SEGMENTS = 64;
//		const unsigned int Y_SEGMENTS = 64;
//		const float PI = 3.14159265359;
//		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//		{
//			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//			{
//				float xSegment = (float)x / (float)X_SEGMENTS;
//				float ySegment = (float)y / (float)Y_SEGMENTS;
//				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//				float yPos = std::cos(ySegment * PI);
//				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//
//				positions.push_back(glm::vec3(xPos, yPos, zPos));
//				uv.push_back(glm::vec2(xSegment, ySegment));
//				normals.push_back(glm::vec3(xPos, yPos, zPos));
//			}
//		}
//
//		bool oddRow = false;
//		for (int y = 0; y < Y_SEGMENTS; ++y)
//		{
//			if (!oddRow) // even rows: y == 0, y == 2; and so on
//			{
//				for (int x = 0; x <= X_SEGMENTS; ++x)
//				{
//					indices.push_back(y       * (X_SEGMENTS + 1) + x);
//					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//				}
//			}
//			else
//			{
//				for (int x = X_SEGMENTS; x >= 0; --x)
//				{
//					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//					indices.push_back(y       * (X_SEGMENTS + 1) + x);
//				}
//			}
//			oddRow = !oddRow;
//		}
//		indexCount = indices.size();
//
//		std::vector<float> data;
//		for (int i = 0; i < positions.size(); ++i)
//		{
//			data.push_back(positions[i].x);
//			data.push_back(positions[i].y);
//			data.push_back(positions[i].z);
//			if (uv.size() > 0)
//			{
//				data.push_back(uv[i].x);
//				data.push_back(uv[i].y);
//			}
//			if (normals.size() > 0)
//			{
//				data.push_back(normals[i].x);
//				data.push_back(normals[i].y);
//				data.push_back(normals[i].z);
//			}
//		}
//		glBindVertexArray(sphereVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//		float stride = (3 + 2 + 3) * sizeof(float);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
//	}
//
//	glBindVertexArray(sphereVAO);
//	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
//}
//
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