#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H
// #define pi 3.14159265359


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, float theta, color_t color);
    glm::vec3 position;
    float theta;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    bool detect_collision(double x,double y);
private:
    VAO *object;
};

#endif // FIRELINE_H
