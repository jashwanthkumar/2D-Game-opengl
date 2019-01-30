#include "fireline.h"
#include "main.h"
#include "math.h"
#include "stdlib.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>

Fireline::Fireline(float x, float y, float theta, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
	this->theta = theta;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[2200];
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
		g_vertex_buffer_data[9*i]+=2.5*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+1]+=2.5*sin((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+3]+=2.5f*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+4]+=2.5f*sin((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+6]+=2.5f*cos((3.14159265359/180)*theta);	
		g_vertex_buffer_data[9*i+7]+=2.5f*sin((3.14159265359/180)*theta);	
	}
	// g_vertex_buffer_data[1800] = 0.0f;
	// g_vertex_buffer_data[1801] = 0.0f;
	// g_vertex_buffer_data[1802] = 0.0f;
	// g_vertex_buffer_data[1803] = 2.5*cos((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1804] = 2.5*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1805] = 0.0f;
	// g_vertex_buffer_data[1806] = -0.1*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1807] = 0.1*cos((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1808] = 0.0f;
	// g_vertex_buffer_data[1809] = 2.5*cos((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1810] = 2.5*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1811] = 0.0f;
	// g_vertex_buffer_data[1812] = -0.1*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1813] = 0.1*cos((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1814] = 0.0f;
	// g_vertex_buffer_data[1815] = 2.5*cos((3.14159265359/180)*theta)-0.1*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1816] =  0.1*cos((3.14159265359/180)*theta)+2.5*sin((3.14159265359/180)*theta);
	// g_vertex_buffer_data[1817] = 0.0f;
	for(int i = 0;i < 20;i++)
	{
		if(i==0)
		{
		g_vertex_buffer_data[1800 + 18*i] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+1] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+2] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+3] = 0.125f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+4] = 0.125f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+5] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+6] = 0.125f*cos(M_PI*theta/180) - 0.15f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+7] = 0.125f*sin(M_PI*theta/180) + 0.15f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+8] = 0.0f + i*0.01;
		g_vertex_buffer_data[1800 + 18*i+9] = g_vertex_buffer_data[1800 + 18*i];
		g_vertex_buffer_data[1800 + 18*i+10] = g_vertex_buffer_data[1800 + 18*i+1];
		g_vertex_buffer_data[1800 + 18*i+11] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+12] = g_vertex_buffer_data[1800 + 18*i+3];
		g_vertex_buffer_data[1800 + 18*i+13] = g_vertex_buffer_data[1800 + 18*i+4];
		g_vertex_buffer_data[1800 + 18*i+14] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+15] = g_vertex_buffer_data[1800 + 18*i] + 0.15f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+16] = g_vertex_buffer_data[1800 + 18*i+1] - 0.15f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+17] = 0.0f - i*0.01;
		}
		else
		{
		g_vertex_buffer_data[1800 + 18*i] = g_vertex_buffer_data[1800 + 18*(i-1)+3];
		g_vertex_buffer_data[1800 + 18*i+1] = g_vertex_buffer_data[1800 + 18*(i-1)+4];
		g_vertex_buffer_data[1800 + 18*i+2] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+3] = g_vertex_buffer_data[1800 + 18*i] + 0.125f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+4] = g_vertex_buffer_data[1800 + 18*i + 1] + 0.125f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+5] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+6] = g_vertex_buffer_data[1800 + 18*i+3] - 0.15f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+7] = g_vertex_buffer_data[1800 + 18*i+4] + 0.15f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+8] = 0.0f + i*0.01;
		g_vertex_buffer_data[1800 + 18*i+9] = g_vertex_buffer_data[1800 + 18*i];
		g_vertex_buffer_data[1800 + 18*i+10] = g_vertex_buffer_data[1800 + 18*i + 1];
		g_vertex_buffer_data[1800 + 18*i+11] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+12] = g_vertex_buffer_data[1800 + 18*i+3];
		g_vertex_buffer_data[1800 + 18*i+13] = g_vertex_buffer_data[1800 + 18*i+4];
		g_vertex_buffer_data[1800 + 18*i+14] = 0.0f;
		g_vertex_buffer_data[1800 + 18*i+15] = g_vertex_buffer_data[1800 + 18*i] + 0.15f*sin(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+16] = g_vertex_buffer_data[1800 + 18*i+1] - 0.15f*cos(M_PI*theta/180);
		g_vertex_buffer_data[1800 + 18*i+17] = 0.0f - i*0.01;
			
		}
		
	}
    this->object = create3DObject(GL_TRIANGLES,720, g_vertex_buffer_data, color, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(cos(theta*M_PI/180), sin(theta*M_PI/180), 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bool Fireline::detect_collision(double x,double y)
{
	for(double in = 0;in <= 10; in++)
	{
		double i = in*0.25;
		if((sqrt((x-this->position.x-i*cos((M_PI/180)*this->theta))*(x-this->position.x-i*cos((M_PI/180)*this->theta))+((y-this->position.y-i*sin((M_PI/180)*this->theta))*(y-this->position.y-i*sin((M_PI/180)*this->theta))))<=0.75))
		{
			// std::cout << this->theta <<"\n";
			// std::cout << sqrt((x-this->position.x-i*cos((M_PI/180)*this->theta))*(x-this->position.x-i*cos((M_PI/180)*this->theta))+((y-this->position.y-i*sin((M_PI/180)*this->theta))*(y-this->position.y-i*sin((M_PI/180)*this->theta)))) << "\n";
			// std::cout << i << "\n";
			// std::cout << 11;
			return 1;
		}
	}
	return 0;
}