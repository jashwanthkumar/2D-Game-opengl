#include "magnet.h"
#include "main.h"
#include "stdlib.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    GLfloat g_vertex_buffer_data[1870];
    
    for(int i = 0;i < 20; i += 1)
	{
		if(i==0)
		{

		g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=1.00f;	
		g_vertex_buffer_data[9*i+4]=0.0f;	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/40) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/40);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/40) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/40);	
		g_vertex_buffer_data[9*i+8]=0.0f;	
		}
		else{
			g_vertex_buffer_data[9*i]=0.0f;	
		g_vertex_buffer_data[9*i+1]=0.0f;	
		g_vertex_buffer_data[9*i+2]=0.0f;	
		g_vertex_buffer_data[9*i+3]=g_vertex_buffer_data[9*(i-1)+6];	
		g_vertex_buffer_data[9*i+4]=g_vertex_buffer_data[9*(i-1)+7];	
		g_vertex_buffer_data[9*i+5]=0.0f;	
		g_vertex_buffer_data[9*i+6]= g_vertex_buffer_data[9*i+3]*cos(2*3.14159265359/40) - g_vertex_buffer_data[9*i+4]*sin(2*3.14159265359/40);	
		g_vertex_buffer_data[9*i+7]= g_vertex_buffer_data[9*i+3]*sin(2*3.14159265359/40) + g_vertex_buffer_data[9*i+4]*cos(2*3.14159265359/40);	
		g_vertex_buffer_data[9*i+8]=0.0f;
		}
	}
    g_vertex_buffer_data[180] = 0.5f;
    g_vertex_buffer_data[181] = 0.0f;
    g_vertex_buffer_data[182] = 0.0f;
    g_vertex_buffer_data[183] = 1.0f;
    g_vertex_buffer_data[184] = -0.5f;
    g_vertex_buffer_data[185] = 0.0f;
    g_vertex_buffer_data[186] = 1.0f;
    g_vertex_buffer_data[187] = 0.0f;
    g_vertex_buffer_data[188] = 0.0f;
    g_vertex_buffer_data[189] = 0.5f;
    g_vertex_buffer_data[190] = 0.0f;
    g_vertex_buffer_data[191] = 0.0f;
    g_vertex_buffer_data[192] = 1.0f;
    g_vertex_buffer_data[193] = -0.5f;
    g_vertex_buffer_data[194] = 0.0f;
    g_vertex_buffer_data[195] = 0.5f;
    g_vertex_buffer_data[196] = -0.5f;
    g_vertex_buffer_data[197] = 0.0f;
    g_vertex_buffer_data[198] = -0.5f;
    g_vertex_buffer_data[199] = 0.0f;
    g_vertex_buffer_data[200] = 0.0f;
    g_vertex_buffer_data[201] = -1.0f;
    g_vertex_buffer_data[202] = -0.5f;
    g_vertex_buffer_data[203] = 0.0f;
    g_vertex_buffer_data[204] = -1.0f;
    g_vertex_buffer_data[205] = 0.0f;
    g_vertex_buffer_data[206] = 0.0f;
    g_vertex_buffer_data[207] = -0.5f;
    g_vertex_buffer_data[208] = 0.0f;
    g_vertex_buffer_data[209] = 0.0f;
    g_vertex_buffer_data[210] = -1.0f;
    g_vertex_buffer_data[211] = -0.5f;
    g_vertex_buffer_data[212] = 0.0f;
    g_vertex_buffer_data[213] = -0.5f;
    g_vertex_buffer_data[214] = -0.5f;
    g_vertex_buffer_data[215] = 0.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 24*3, g_vertex_buffer_data, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Magnet::tick() {
    this->position.x -= speed.x;
    this->position.y -= speed.y;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1, 1 };
    return bbox;
}

bool Magnet::magnetcheck(double x,double y) {
    if(x - 0.5 > this->position.x - 1.5 && y + 0.5 < this->position.y - 0.5 && x+0.5 < this->position.x + 1.5) return 1;
    else return 0;
}
