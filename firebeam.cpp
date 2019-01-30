#include "firebeam.h"
#include "main.h"
Firebeam::Firebeam(float x, float y, float theta, float length, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
	this->leng = length;
    speed = 0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[1870];

	for(int i = 0;i < 100; i += 1)
	{
		if(i==0)
		{

		g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=0.20f;	
		g_vertex_buffer_data[9*i+4]=0.0f;	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/100) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/100) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+8]=0.0f;	
		}
		else{
			g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=g_vertex_buffer_data[9*(i-1)+6];	
		g_vertex_buffer_data[9*i+4]=g_vertex_buffer_data[9*(i-1)+7];	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/100) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/100) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+8]=0.0f;
		}
	}

	for(int i =100;i < 200; i += 1)
	{
		if(i==100)
		{

		g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=0.20f;	
		g_vertex_buffer_data[9*i+4]=0.0f;	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/100) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/100) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+8]=0.0f;	
		}
		else{
		g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=g_vertex_buffer_data[9*(i-1)+6];	
		g_vertex_buffer_data[9*i+4]=g_vertex_buffer_data[9*(i-1)+7];	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/100) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/100) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/100);	
		g_vertex_buffer_data[9*i+8]=0.0f;
		}
	}

	for(int i =100;i < 200; i += 1)
	{
		g_vertex_buffer_data[9*i]+=length*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+1]+=length*sin((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+3]+=length*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+4]+=length*sin((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+6]+=length*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+7]+=length*sin((3.14159265359/180)*theta);	
	}
	g_vertex_buffer_data[1800] = 0.0f;
	g_vertex_buffer_data[1801] = 0.0f;
	g_vertex_buffer_data[1802] = 0.0f;
	g_vertex_buffer_data[1803] = length*cos((3.14159265359/180)*theta);
	g_vertex_buffer_data[1804] = length*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1805] = 0.0f;
	g_vertex_buffer_data[1806] = -0.1*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1807] = 0.1*cos((3.14159265359/180)*theta);
	g_vertex_buffer_data[1808] = 0.0f;
	g_vertex_buffer_data[1809] = length*cos((3.14159265359/180)*theta);
	g_vertex_buffer_data[1810] = length*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1811] = 0.0f;
	g_vertex_buffer_data[1812] = -0.1*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1813] = 0.1*cos((3.14159265359/180)*theta);
	g_vertex_buffer_data[1814] = 0.0f;
	g_vertex_buffer_data[1815] = length*cos((3.14159265359/180)*theta)-0.1*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1816] =  0.1*cos((3.14159265359/180)*theta)+length*sin((3.14159265359/180)*theta);
	g_vertex_buffer_data[1817] = 0.0f;
    this->object = create3DObject(GL_TRIANGLES,202*3, g_vertex_buffer_data, color, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    this->position.y -= speed;
	if(this->position.y <= -1.75) speed = -speed;
	if(this->position.y >= 3.0) speed = -speed;
}

bounding_box_t Firebeam::bounding_box()
{
    bounding_box_t temp;
    temp.x = this->position.x + this->leng/2;
    temp.y = this->position.y;
    temp.width = this->leng;
    temp.height = 0.4f;
    return temp;
}
