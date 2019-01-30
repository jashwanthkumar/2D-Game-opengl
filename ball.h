#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void moveleft();
    void jump();
    void moveright();
    double speed;
    double speedy;
    double acc;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *object1;
};

#endif // BALL_H
