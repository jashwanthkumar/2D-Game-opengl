#include "projectile.h"
#include "main.h"
Projectile::Projectile(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.07;
    speedy = -0.01;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat g_vertex_buffer_data[9*100];

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

    this->object = create3DObject(GL_TRIANGLES,100*3, g_vertex_buffer_data, color, GL_FILL);
}

void Projectile::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Projectile::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Projectile::tick() {
    // this->rotation += 5.0;
    this->position.x += speed;
    this->position.y += speedy;
}

bounding_box_t Projectile::bounding_box()
{
    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.width = 0.4f;
    temp.height = 0.4f;
    return temp;
}
