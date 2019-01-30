#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    // void rand_position();
    void tick();
    bool magnetcheck(double x,double y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAGNET_H
