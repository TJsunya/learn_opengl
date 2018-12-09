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
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//unsigned int loadCubemap(std::vector<std::string> &);
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
//	glDepthFunc(GL_LESS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))
//	glEnable(GL_STENCIL_TEST);
//	glStencilMask(0xFF);
//
//	// build and compile shaders
//	// -------------------------
//	Shader shader("depth_testing.vs", "depth_testing.ps");
//	Shader stencil_shader("stencil_test.vs", "stencil_test.ps");
//	Shader framebuffer_shader("framebuffer.vs", "framebuffer.ps");
//	Shader skybox_shader("skybox.vs", "skybox.ps");
//	Shader reflect_shader("reflect.vs", "reflect.ps");
//	Shader gaussian_blur_shader("gaussian_blur.vs", "gaussian_blur.ps");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float cubeVertices[] = {
//		// positions          // texture Coords
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//	float planeVertices[] = {
//		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
//	};
//	// cube VAO
//	unsigned int cubeVAO, cubeVBO;
//	glGenVertexArrays(1, &cubeVAO);
//	glGenBuffers(1, &cubeVBO);
//	glBindVertexArray(cubeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//	// plane VAO
//	unsigned int planeVAO, planeVBO;
//	glGenVertexArrays(1, &planeVAO);
//	glGenBuffers(1, &planeVBO);
//	glBindVertexArray(planeVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glBindVertexArray(0);
//
//	// load textures
//	// -------------
//	unsigned int cubeTexture = loadTexture("resource/container.jpg");
//	unsigned int floorTexture = loadTexture("resource/wall.jpg");
//	unsigned int grassTexture = loadTexture("resource/blending_transparent_window.png");
//
//	vector<glm::vec3> vegetation;
//	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
//	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
//	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
//	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
//	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
//
//	float grassVertexs[] = {
//		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
//		0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
//		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
//		1.0f, 0.5f, 0.0f, 1.0f, 0.0f
//	};
//
//	unsigned int grassIndexs[] = {
//		0,1,2,
//		0, 2,3
//	};
//
//	float screenVertexs[] = {
//		-1.0f, 1.0f, 0.0f, 1.0f,
//		-1.0f, -1.0f, 0.0f, 0.0f,
//		1.0f, -1.0f, 1.0f, 0.0f,
//		1.0f, 1.0f, 1.0f, 1.0f
//	};
//
//	unsigned int VAO_GRASS, VBO_GRASS, VEO_GRASS;
//	glGenVertexArrays(1, &VAO_GRASS);
//	glBindVertexArray(VAO_GRASS);
//	glGenBuffers(1, &VBO_GRASS);
//	glGenBuffers(1, &VEO_GRASS);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_GRASS);
//	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(grassVertexs), &grassVertexs, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO_GRASS);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &grassIndexs, GL_STATIC_DRAW);
//	glBindVertexArray(0);
//
//
//	unsigned int framebuffer;
//	glGenFramebuffers(1, &framebuffer);
//	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//	unsigned int texColorBuffer;
//	glGenTextures(1, &texColorBuffer);
//	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
//
//	unsigned int secondColorTexture;
//	glGenTextures(1, &secondColorTexture);
//	glBindTexture(GL_TEXTURE_2D, secondColorTexture);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, secondColorTexture, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	GLuint attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
//	glDrawBuffers(2, attachments);
//
//
//	unsigned int rbo;
//	glGenRenderbuffers(1, &rbo);
//	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//	glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//		std::cout << "ERROR::FRAMEBUFF:: framebuffer is not complete" << std::endl;
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//	unsigned int VAO_SCREEN, VEO_SCRREN, VBO_SCRREN;
//	glGenVertexArrays(1, &VAO_SCREEN);
//	glBindVertexArray(VAO_SCREEN);
//
//	glGenBuffers(1, &VBO_SCRREN);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_SCRREN);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(screenVertexs), &screenVertexs, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 2, GL_FLOAT, FALSE, 4 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glGenBuffers(1, &VEO_SCRREN);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO_SCRREN);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(grassIndexs), &grassIndexs, GL_STATIC_DRAW);
//	glBindVertexArray(0);
//
//	vector<std::string> faces
//	{
//		"resource/right.jpg",
//		"resource/left.jpg",
//		"resource/top.jpg",
//		"resource/bottom.jpg",
//		"resource/front.jpg",
//		"resource/back.jpg"
//	};
//	
//	float skyboxVertices[] = {
//		// positions          
//		-1.0f,  1.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//
//		-1.0f, -1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f,
//		-1.0f, -1.0f,  1.0f,
//
//		-1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f, -1.0f,
//		1.0f,  1.0f,  1.0f,
//		1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f,  1.0f,
//		-1.0f,  1.0f, -1.0f,
//
//		-1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f, -1.0f,
//		1.0f, -1.0f, -1.0f,
//		-1.0f, -1.0f,  1.0f,
//		1.0f, -1.0f,  1.0f
//	};
//
//	unsigned int cubemap_texture = loadCubemap(faces);
//	unsigned int sky_vao, sky_vbo;
//	glGenVertexArrays(1, &sky_vao);
//	glBindVertexArray(sky_vao);
//	glGenBuffers(1, &sky_vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, sky_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//
//	float reflect_vertices[] = {
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
//
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
//
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
//
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
//		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
//
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
//	};
//
//	unsigned int test_buffer;
//	glGenBuffers(1, &test_buffer);
//	glBindBuffer(GL_ARRAY_BUFFER, test_buffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(reflect_vertices), reflect_vertices, GL_STATIC_DRAW);
//
//	unsigned int reflect_vao, reflect_vbo;
//	glGenVertexArrays(1, &reflect_vao);
//	glBindVertexArray(reflect_vao);
//	glGenBuffers(1, &reflect_vbo);
//	glBindBuffer(GL_COPY_WRITE_BUFFER, reflect_vbo);
//	glBufferData(GL_COPY_WRITE_BUFFER, sizeof(reflect_vertices), NULL, GL_STATIC_COPY);
//	// 使用copy方式来进行buffer的数据交互
//	glCopyBufferSubData(GL_ARRAY_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, sizeof(reflect_vertices));
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(reflect_vertices), reflect_vertices, GL_STATIC_DRAW);
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(reflect_vertices), NULL, GL_DYNAMIC_DRAW);
//	//// 进行部分数据设置
//	////glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(reflect_vertices), reflect_vertices);
//
//	//// 已指针的方式进行数据回填
//	//void *ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
//	//memcpy(ptr, reflect_vertices, sizeof(reflect_vertices));
//	//glUnmapBuffer(GL_ARRAY_BUFFER);
//	glBindBuffer(GL_ARRAY_BUFFER, reflect_vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));
//	glEnableVertexAttribArray(1);
//	glBindVertexArray(0);
//
//	GLuint pingpongFBO[2];
//	GLuint pingpongBuffer[2];
//	glGenFramebuffers(2, pingpongFBO);
//	glGenTextures(2, pingpongBuffer);
//	for (GLuint i = 0; i < 2; i++)
//	{
//		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
//		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[i]);
//		glTexImage2D(
//			GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL
//		);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glFramebufferTexture2D(
//			GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongBuffer[i], 0
//		);
//	}
//
//
//	// shader configuration
//	// --------------------
//	shader.use();
//	shader.setInt("texture1", 0);
//
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
//		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_STENCIL_TEST);
//		glStencilMask(0xff);
//		// render
//		// ------
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glDepthMask(true);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
//
//		glm::mat4 model;
//	
//		reflect_shader.use();
//		//glEnable(GL_PROGRAM_POINT_SIZE);
//		glBindVertexArray(reflect_vao);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(-3.0f, 0.0f, -3.0f));
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//
//
//		unsigned int ubo;
//		glGenBuffers(1, &ubo);
//		glBindBuffer(GL_UNIFORM_BUFFER, ubo);
//		glBufferData(GL_UNIFORM_BUFFER, 128, NULL, GL_STATIC_DRAW);
//		glBufferSubData(GL_UNIFORM_BUFFER, 0, 64, glm::value_ptr(view));
//		glBufferSubData(GL_UNIFORM_BUFFER, 64, 64, glm::value_ptr(projection));
//
//		glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);
//		
//		glBindBuffer(GL_UNIFORM_BUFFER, 0);
//		//使用uniform block 即uniform object
//		unsigned int matrices_index = glGetUniformBlockIndex(reflect_shader.ID, "Matrices");
//		glUniformBlockBinding(reflect_shader.ID, matrices_index, 0);
//
//		reflect_shader.setMat4("model", model);
//		reflect_shader.setVec3("cameraPos", camera.Position);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		//glDisable(GL_PROGRAM_POINT_SIZE);
//
//		glEnable(GL_STENCIL_TEST);
//		glStencilFunc(GL_ALWAYS, 1, 0XFF);
//		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//		shader.use();
//		/*unsigned int shader_block_index = glGetUniformBlockIndex(shader.ID, "TMatrices");
//		glUniformBlockBinding(shader.ID, shader_block_index, 0);*/
//
//		shader.setMat4("view", view);
//		shader.setMat4("projection", projection);
//	
//		// cubes
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		model = glm::mat4();
//		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//		shader.setMat4("model", model);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
//		glStencilMask(0x0);
//		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//		
//		stencil_shader.use();
//		unsigned int tmatrix_index = glGetUniformBlockIndex(stencil_shader.ID, "TMatrices");
//		glUniformBlockBinding(stencil_shader.ID, tmatrix_index, 0);
//
//	/*	stencil_shader.setMat4("view", view);
//		stencil_shader.setMat4("projection", projection);*/
//		glm::mat4 model_stencil;
//		glBindVertexArray(cubeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, cubeTexture);
//		
//		model_stencil = glm::translate(model_stencil, glm::vec3(-1.0f, 0.0f, -1.0f));
//		model_stencil = glm::scale(model_stencil, glm::vec3(1.1f, 1.1f, 1.1f));
//		stencil_shader.setMat4("model", model_stencil);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//
//		model_stencil = glm::mat4();
//	
//		model_stencil = glm::translate(model_stencil, glm::vec3(2.0f, 0.0f, 0.0f));
//		model_stencil = glm::scale(model_stencil, glm::vec3(1.1f, 1.1f, 1.1f));
//		stencil_shader.setMat4("model", model_stencil);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		
//		glDisable(GL_STENCIL_TEST);
//		glEnable(GL_DEPTH_TEST);
//		shader.use();
//		// floor
//		glBindVertexArray(planeVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, floorTexture);
//		shader.setMat4("model", glm::mat4());
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		glBindVertexArray(0);
//
//		glEnable(GL_STENCIL_TEST);
//		glDepthMask(GL_FALSE);
//		glDepthFunc(GL_LEQUAL);
//	
//		skybox_shader.use();
//		glm::mat4 skybox_view;
//		skybox_view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//		skybox_shader.setMat4("view", skybox_view);
//		skybox_shader.setMat4("projection", projection);
//		glBindVertexArray(sky_vao);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_texture);
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		
//
//		glDisable(GL_STENCIL_TEST);
//		glBindVertexArray(VAO_GRASS);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, grassTexture);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glEnable(GL_BLEND);
//		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
//		glBlendEquation(GL_FUNC_ADD);
//		shader.use();
//		std::map<float, glm::vec3> sorted;
//		for (int i = 0; i < vegetation.size(); ++i) {
//			float distance = glm::length(camera.Position - vegetation[i]);
//			sorted[distance] = vegetation[i];
//		}
//
//		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
//
//			glm::mat4 model_grass;
//			model_grass = glm::translate(model_grass, it->second);
//			shader.setMat4("model", model_grass);
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		}
//	
//	
//		glBindVertexArray(0);
//
//		glDepthMask(GL_TRUE);
//		glDepthFunc(GL_LESS);
//
//		glBindVertexArray(0);
//
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		GLboolean horizontal = true, first_iteration = true;
//		GLuint amount = 10;
//		gaussian_blur_shader.use();
//		for (GLuint i = 0; i < amount; i++)
//		{
//			glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
//			glUniform1i(glGetUniformLocation(gaussian_blur_shader.ID, "horizontal"), horizontal);
//			glBindTexture(
//				GL_TEXTURE_2D, first_iteration ? secondColorTexture : pingpongBuffer[!horizontal]
//			);
//			glBindVertexArray(VAO_SCREEN);
//			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//			glBindVertexArray(0);
//			horizontal = !horizontal;
//			if (first_iteration)
//				first_iteration = false;
//		}
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//		glDisable(GL_DEPTH_TEST);
//		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
//
//		framebuffer_shader.use();
//		framebuffer_shader.setInt("screenTexture", 0);
//		framebuffer_shader.setInt("blur_texture", 1);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, pingpongBuffer[1]);
//		glBindVertexArray(VAO_SCREEN);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &cubeVAO);
//	glDeleteVertexArrays(1, &planeVAO);
//	glDeleteBuffers(1, &cubeVBO);
//	glDeleteBuffers(1, &planeVBO);
//
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