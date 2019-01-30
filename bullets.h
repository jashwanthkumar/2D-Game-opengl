#include "main.h"

#ifndef BULLETS_H
#define BULLETS_H
// #define pi 3.14159265359


class Bullets {
public:
    Bullets() {}
    Bullets(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int sign);
    double speed;
    bounding_box_t bounding_box();
    double speedy;
private:
    VAO *object;
};

#endif // BULLETS_H
