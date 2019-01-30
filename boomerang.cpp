#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.2;
    speedy = -0.035;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	static const GLfloat g_vertex_buffer_data[] = {
        0.0f, 0.35f, 0.5f,
        0.0f, 0.2f,0.5f, // triangle 2 : begin
        -0.5f, 0.0f,0.0f, // triangle 2 : begin
        0.0f, 0.35f,0.5f,
        0.0f, 0.2f,0.5f, // triangle 2 : begin
        0.5f, 0.0f,0.0f,
    };

    this->object = create3DObject(GL_TRIANGLES,2*3, g_vertex_buffer_data, color, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->rotation += 5.0;
    this->position.x -= speed;
    this->position.y += speedy;
}

bounding_box_t Boomerang::bounding_box()
{
    bounding_box_t temp;
    temp.x = this->position.x;
    temp.y = this->position.y;
    temp.width = 1.0f;
    temp.height = 0.35f;
    return temp;
}
