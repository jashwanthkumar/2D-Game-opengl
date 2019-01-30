#include "mag.h"
#include "main.h"

Mag::Mag(float x, float y, color_t color) {
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
		g_vertex_buffer_data[9*i+3]=0.50f;	
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

    this->object = create3DObject(GL_TRIANGLES, 20*3, g_vertex_buffer_data, color, GL_FILL);
}

void Mag::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Mag::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}


void Mag::tick() {
    this->position.x -= speed.x;
    this->position.y -= speed.y;
}

bounding_box_t Mag::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 1, 1 };
    return bbox;
}
