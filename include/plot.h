#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED

//This header requires glew and glfw3 and std complex headerfile

class plot
{
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	std::vector<vec2> vertices;
	std::vector<GLuint> indices;

public:
	plot()
	{
		glGenVertexArrays(1, &VAO);
	 	glGenBuffers(1, &VBO);
	 	glGenBuffer(1,&EBO);
	}
	void prepare()
	{
		// 1. Bind Vertex Array Object
		glBindVertexArray(VAO);
		    // 2. Copy our vertices array in a vertex buffer for OpenGL to use
		    glBindBuffer(GL_ARRAY_BUFFER, VBO);
		    glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices.front(), GL_STATIC_DRAW);
		    // 3. Copy our index array in a element buffer for OpenGL to use
		    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices.front(), GL_STATIC_DRAW);
		    // 3. Then set the vertex attributes pointers
		    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		    glEnableVertexAttribArray(0);  
		// 4. Unbind VAO (NOT the EBO)
		glBindVertexArray(0);

	}
	void loadFrame(std::complex<GLfloat> UL, std::complex<GLfloat> BR, int hslots, int vslots) //To get a wireframe object
	{	
		GLfloat width = std:real(UL)-std:real(BR);
		GLfloat height = std:imag(UL)-std:imag(BR);
		GLfloat hstep = width/hslots;
		GLfloat vstep = height/vslots;
	}
	
};






#endif // PLOT_H_INCLUDED