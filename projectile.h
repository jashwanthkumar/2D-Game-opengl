#include "main.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H
// #define pi 3.14159265359


class Projectile {
public:
    Projectile() {}
    Projectile(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    double speedy;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // PROJECTILE_H
