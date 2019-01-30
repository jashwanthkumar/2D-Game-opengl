#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H
// #define pi 3.14159265359


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bounding_box_t bounding_box();
    double speedy;
private:
    VAO *object;
};

#endif // BOOMERANG_H
