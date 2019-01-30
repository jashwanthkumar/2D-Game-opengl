#include "ball.h"
#include "main.h"
Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 1;
    speedy = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        0.5f, 0.5f,0.0f,
        0.5f, -0.5f,0.0f, // triangle 2 : begin
        -0.5f, -0.5f,0.0f, // triangle 2 : begin
        -0.5f, 0.5f,0.0f,
        0.5f, 0.5f,0.0f, // triangle 2 : begin
        -0.5f, -0.5f,0.0f,
    };
    static const GLfloat vertex_buffer_data[] = {
        0.5f, -0.3f,0.0f,
        -0.5f, -0.3f,0.0f, // triangle 2 : begin
        0.0f, 0.1f,0.0f, // triangle 2 : begin
        -0.5f, 0.5f,0.0f,
        0.5f, 0.5f,0.0f, // triangle 2 : begin
        0.0f, 0.1f,0.0f,
        0.5f, -0.3f,0.0f,
        -0.5f, -0.3f,0.0f,
        -0.5f, -0.5f,0.0f,
        0.5f, -0.3f,0.0f,
        -0.5f, -0.3f,0.0f,
        0.5f, -0.5f, 0.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_BLUE, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {
    // this->rotation += speed;
    this->position.y += speedy;
    // else
    // this->position.y = 5.0;
}

void Ball::moveleft() {
    if(this->position.x < -3.75) 
	{
		// this->position.x = 3.75;
		
	}
	this->position.x -= 0.1;
}

void Ball::moveright() {
    // if(this->position.x > 3.75) this->position.x = -3.75;
    this->position.x += 0.1;
}

void Ball::jump() {
    // if(this->position.y < 5.0)
    speedy += 0.01;
    // else speedy = 0;
}

bounding_box_t Ball::bounding_box()
{
    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.width = 1.0f;
    temp.height = 1.0f;
    return temp;
}
