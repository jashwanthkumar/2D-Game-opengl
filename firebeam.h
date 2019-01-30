#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H
// #define pi 3.14159265359


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, float theta, float length, color_t color);
    glm::vec3 position;
    float leng;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // Firebeam_H
