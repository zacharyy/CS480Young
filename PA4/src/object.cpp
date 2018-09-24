#include "object.h"
#include<fstream>
struct material {
		glm::vec3 color;
		std::string name;
};
Object::Object()
{  
  /*
    # Blender File for a Cube
    o Cube
    v 1.000000 -1.000000 -1.000000
    v 1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 1.000000
    v -1.000000 -1.000000 -1.000000
    v 1.000000 1.000000 -0.999999
    v 0.999999 1.000000 1.000001
    v -1.000000 1.000000 1.000000
    v -1.000000 1.000000 -1.000000
    s off
    f 2 3 4
    f 8 7 6
    f 1 5 6
    f 2 6 7
    f 7 8 4
    f 1 4 8
    f 1 2 4
    f 5 8 6
    f 2 1 6
    f 3 2 7
    f 3 7 4
    f 5 1 8
  */
/*
  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };

  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };*/
	angle = 0.0f;

	
	//"../assets/board.mtl"
	//"../assets/board.obj"
	std::string objectName, materialName;
	std::cout << "Enter the file names for files located in assets\n";
	std::cout << "Enter the object file name (example: dragon.obj)\n";
	std::cin >> objectName;
	std::cout << "Enter the material file name (example: dragon.mtl)\n";
	std::cin >> materialName;
	if(!loadOBJ("../assets/" + objectName ,"../assets/" + materialName))
		exit(1);

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt)
{

}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

bool Object::loadOBJ(std::string objF, std::string mtlF)
{
	srand (time(NULL));

	bool randColor = false;
	std::ifstream mtlFile;
	std::ifstream objFile;
	objFile.open(objF);
	mtlFile.open(mtlF);
	if(!objFile.is_open()) 
	{
		std::cout << "Error opening obj file." << std::endl;
		return false;
	}
	if(!mtlFile.is_open())
	{
		std::cout << "Error opening mtl file, using random colors instead." << std::endl;
		randColor = true;
	}
	float ambience[3], diffuse[3], specular[3], shininess;
	std::vector<material> mats;
	material mat;
	std::string s;
	glm::vec3 v;
	glm::vec3 currentColor; 
	int vI[3], uI[3], nI[3];

	// Read in material file
	if(mtlFile.is_open())
	{
		while(true)
		{
			mtlFile >> s;

			if(mtlFile.eof()) break;
		
			if(s == "newmtl")
			{
				mtlFile >> mat.name;
			
			}
			else if(s == "Kd")
			{
				mtlFile >> diffuse[0] >> diffuse[1] >> diffuse[2];
				mat.color = glm::vec3(diffuse[0], diffuse[1], diffuse[2]);
				//std::cout << mat.color.x << std::endl;
				mats.push_back(mat);
			}
		}
		mtlFile.close();
	}
	//Read in obj file
	while(true)
	{
		objFile >> s;
		//std::cout << s << std::endl;
		if(objFile.eof()) break;
		
		if(s == "usemtl")
		{
			objFile >> s;
			for(std::vector<material>::iterator it = mats.begin(); it != mats.end(); ++it)
			{
				if(it->name == s)
				{
					//std::cout << s << std::endl;
					currentColor = it->color;
					break;
				}
			}
		}
		if(s == "v") 
		{
			objFile >> v.x >> v.y >> v.z;
			Vertex a(v,glm::vec3(rand()%100/100.0,rand()%100/100.0,rand()%100/100.0));
			Vertices.push_back(a);
		}
		else if(s == "f")
		{
			//maybe useful for later
			for(int i = 0; i < 3; i++)
			{
				objFile >> vI[i]; //>> uI[i] >> nI[i];
		//std::cout << vI[i] << " ";
				Indices.push_back (vI[i]);
				//Indices.push_back(uI[i]);
				//Indices.push_back(nI[i]);
				if(!randColor)
				{
					Vertices[vI[i]-1].color = currentColor;
				}

			}

		}
	}

	objFile.close();
  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

	return true;
}
