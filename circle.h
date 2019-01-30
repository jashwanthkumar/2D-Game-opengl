#include "main.h"

#ifndef CIRCLE_H
#define CIRCLE_H
// #define pi 3.14159265359


class Circle {
public:
    Circle() {}
    Circle(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // CIRCLE_H
