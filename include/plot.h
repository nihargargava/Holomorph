#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED

#define PLOT_TESS 0.003f

//This header requires glew and glfw3 and std complex headerfile

struct coordinate
{	GLfloat x;
	GLfloat y;

};

class plot
{
	
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	

public:
	std::vector<coordinate> vertices;
	std::vector<GLuint> indices;
	plot()
	{
		glGenVertexArrays(1, &VAO);
	 	glGenBuffers(1, &VBO);
	 	glGenBuffers(1,&EBO);
	}
	void prepare()
	{


		// 1. Bind Vertex Array Object
		glBindVertexArray(VAO);
		    // 2. Copy our vertices array in a vertex buffer for OpenGL to use
		    glBindBuffer(GL_ARRAY_BUFFER, VBO);
		    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(coordinate), &vertices.front(), GL_STATIC_DRAW);
		    // 3. Copy our index array in a element buffer for OpenGL to use
		    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), &indices.front(), GL_STATIC_DRAW);
		    // 3. Then set the vertex attributes pointers
		    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		    glEnableVertexAttribArray(0);  

		    glLineWidth(1.50f);
		// 4. Unbind VAO (NOT the EBO)
		glBindVertexArray(0);

		

	}
	void loadFrame(std::complex<GLfloat> UL, std::complex<GLfloat> BR, int hslots, int vslots) //To get a wireframe object
	{	
		GLfloat width = std::real(UL)-std::real(BR);
		GLfloat height = std::imag(UL)-std::imag(BR);
		GLfloat hstep = width/(hslots);
		GLfloat vstep = height/(vslots);
		GLuint h_tess = fabs( hstep/PLOT_TESS );
		GLuint v_tess = fabs( vstep/PLOT_TESS );
		GLfloat hsstep = hstep/(h_tess);
		GLfloat vsstep = vstep/(v_tess);
		GLuint v_attach=0;
		std::vector<GLuint> h_attach;
		GLuint current_attach;

		
		for (int i = 0; i < hslots+1 ; i++)
		{
			for(int j=0; j< vslots+1; j++)
			{
				coordinate z;
				z.x=std::real(UL) + i*(hstep);
				z.y=std::imag(UL) - j*(vstep);
				vertices.push_back(z);
				current_attach = vertices.size()-1;
				if(!(i==0)  )
				{	indices.push_back(current_attach);
					indices.push_back(h_attach.at(j));
				}

				if(!(i==hslots))
				{	//std::cout<<"\nGoing in for loop. h_tess:"<<h_tess;
					for ( int ia =1; ia < h_tess ; ia++)
					{
						//std::cout<<"\nLooking at ia:"<<ia;
						z.x = vertices[current_attach].x + ia*hsstep; 
						z.y = vertices[current_attach].y;
						vertices.push_back(z);
						if(ia ==1)
						{
							indices.push_back(current_attach);
							indices.push_back(vertices.size()-1);
						}
						else
						{
							indices.push_back(vertices.size()-2);
							indices.push_back(vertices.size()-1);
						}	
						//std::cout<<"\nLooking at ia:"<<ia;
						if(ia==h_tess-1)
						{	//std::cout<<"\nLooking at i";
							
							if(i==0)
							{
								h_attach.push_back(vertices.size()-1);
								//std::cout<<"\n Adding at "<<j;
							}
							else
							{
								h_attach.at(j)=vertices.size()-1;
							}
						}
					}

				}
				if(!(j==0) )
				{	
					indices.push_back(current_attach);
					indices.push_back(v_attach);
				}

				if(!(j==vslots))
				{
					for ( int ja =1; ja < v_tess ; ja++)
					{
						z.x = vertices[current_attach].x; 
						z.y = vertices[current_attach].y - ja*vsstep;
						vertices.push_back(z);
						if(ja ==1)
						{
							indices.push_back(current_attach);
							indices.push_back(vertices.size()-1);
						}
						else
						{	
							indices.push_back(vertices.size()-2);
							indices.push_back(vertices.size()-1);
						}	

						if(ja==v_tess-1)
						{
							
							v_attach=vertices.size()-1;
						}
					}

				}
				
				
			}


		}



	}
	void draw()
	{
        glBindVertexArray(VAO);
        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT , 0);
        glBindVertexArray(0);
	}

	void kill()
	{
		glDeleteVertexArrays(1, &VAO);
  		glDeleteBuffers(1, &VBO);
	}

	
};






#endif // PLOT_H_INCLUDED