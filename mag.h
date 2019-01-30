#include "main.h"

#ifndef MAG_H
#define MAG_H


class Mag {
public:
    Mag() {}
    Mag(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    // void rand_position();
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAG_H
