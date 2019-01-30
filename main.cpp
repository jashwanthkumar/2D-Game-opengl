#include "magnet.h"
#include "mag.h"
#include "bullets.h"
#include "boomerang.h"
#include "ground.h"
#include "viserion.h"
#include "projectile.h"
#include "fireline.h"
#include "firebeam.h"
#include "main.h"
#include "timer.h"
#include "ball.h"
#include "coin.h"
#include "circle.h"
#include <stdlib.h>
#define GLM_ENABLE_EXPERIMENTAL
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Viserion viserion;
long long number_coins = 84;
int Lives = 3;
int number_fireline = 11;
int number_firebeam = 2;
int number_boom = 20;
int number_magnets = 4;
int number_proj = 2;
double score;
int level = 1;
long long coins;
Ball ball1;
Circle circle;
Boomerang boomerang[100];
Mag mag[100];
Mag mag1;
Magnet magnet[100];
Ground gr;
// Projectile projectile;
Projectile projectile[100];
Fireline fireline[100];
Firebeam firebeam[100];
Coin coin[10000];
Bullets bullets[100000];
Bullets viser_bullets[100000];
bool coin_coll[100] = { 0 };
bool fireline_coll[100] = { 0 };
bool firebeam_coll[100] = { 0 };
bool projectile_coll[100] = { 0 };
bool bullets_coll[100000] = { 0 };
bool viser_bull_coll[100000] = { 0 };
bool boom_coll[100] = { 0 };
bool proj_coll[100] = { 0 };
bool isViser = 0;
int point = 0;
long long vis = 0;
int count = 0;
bool isCircle = 0;
double radius = 0.0;
double boom_pos[100];
double proj_pos[100];
int collide = 0;

double ang = 0.0;

float camera_rotation_angle = 90;
glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
glm::vec3 target (0, 0, 0);
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

bool detect_collision_circles(Viserion* viserion,Bullets* bullets)
{
	if((sqrt(((viserion->position.x-bullets->position.x)*(viserion->position.x-bullets->position.x))+((viserion->position.x-bullets->position.x)*(viserion->position.x-bullets->position.x)))<=0.8))
    {
        return 1;
    }
    return 0;
}

void shoot()
{
    vis++;
    viser_bullets[vis].set_position(viserion.position.x,viserion.position.y);
}

void bull()
{
        point++;
        bullets[point].set_position(ball1.position.x+0.5,ball1.position.y);
}

void gameover()
{
    if(Lives==0)
    {
        std::cout << "GAME OVER" << "\n" << "SCORE : " << score << "\n" << "COINS :" << coins << "\n" ;
        quit(window);  
    }
    else Lives--;
}

void winner()
{
        std::cout << "Congratulations! U have completed the game" << "\n" << "SCORE : " << score << "\n" << "COINS :" << coins << "\n" << "LIVES :" << Lives << "\n";
        quit(window);  
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i = 0; i < number_magnets; i++)
    {
        magnet[i].draw(VP);
        mag[i].draw(VP);
    }
    
    for(int i=0;i<number_boom;i++)
    {
    if(ball1.position.x > boom_pos[i] && !boom_coll[i])
    boomerang[i].draw(VP);
    }
    for(int i = 0;i<point;i++)
    {
        if(!bullets_coll[i])
        bullets[i].draw(VP);
    }
    for(int i=1;i<vis;i++)
    {
        viser_bullets[i].draw(VP);
    }
    for(int i = 0; i < number_proj; i++)
    {
    if(ball1.position.x > proj_pos[i] && !proj_coll[i])
    projectile[i].draw(VP);    
    }
    
    gr.draw(VP);    
    for(int i = 0; i < number_coins; i++)
    {
        if(coin_coll[i] == 0)
        coin[i].draw(VP);
    }
    for(int i = 0; i < number_fireline; i++)
    {
        if(fireline_coll[i] == 0)
        fireline[i].draw(VP);
    }
    for(int i = 0; i < number_firebeam; i++)
    {
        if(firebeam_coll[i] == 0)
        {
            firebeam[i].draw(VP);
        }
    }
    viserion.draw(VP);
     circle.draw(VP);
    // // mag1.draw(VP);
    ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int space = glfwGetKey(window,GLFW_KEY_SPACE);
    if(space)
    {
        // count = (count + 1)%10;
        // if(count == 1) point++;
        // bullets[point].set_position(ball1.position.x+0.5,ball1.position.y);
        // bull();
    }
    if (!isViser && left && ball1.position.x > -3 + target.x && !isCircle) {
        // if(ball1.position.x <= -3 + target.x)
        {
            ball1.moveleft();
            eye.x -= 0.1;
            target.x -= 0.1;
            gr.position.x -=0.1;
        }
    }
    if (!isViser && left && ball1.position.x > -3 + target.x && isCircle && ball1.position.x > circle.position.x -2.0) {
        // if(ball1.position.x <= -3 + target.x)
        // {
        //     eye.x -= 0.1;
        //     target.x -= 0.1;
        //     gr.position.x -=0.1;
        // }
        ang -= 1;
        ball1.position.x = circle.position.x -2.0 + 2.0*(1-cos(M_PI*ang/180));
        ball1.position.y = circle.position.y + 2.0*(sin(M_PI*ang/180));
        eye.x = ball1.position.x;
        target.x = ball1.position.x;
        gr.position.x = ball1.position.x;
    }
    if(!isViser && right && !isCircle){
        // if(ball1.position.x >= 2 + target.x )
        {
            ball1.moveright();
            score += 0.1;
            eye.x += 0.1;
            target.x += 0.1;
            gr.position.x +=0.1;
        }
    }
    if(right && isCircle){
        ang += 1;
        if(ang > 180) ang = 180;
        if(ang == 180) isCircle = 0;
        ball1.position.x = circle.position.x -2.0 + 2.0*(1-cos(M_PI*ang/180));
        ball1.position.y = circle.position.y + 2.0*(sin(M_PI*ang/180));
        eye.x = ball1.position.x;
        target.x = ball1.position.x;
        gr.position.x = ball1.position.x;        
        // if(ball1.position.x >= 2 + target.x)
        // {
        //     eye.x += 0.1;
        //     target.x += 0.1;
        //     gr.position.x +=0.1;
        // }
    }
    if(up && !isCircle) {
        ball1.jump();
    }
}

void tick_elements() {
    // eye.x += 0.01;
    // target.x += 0.01;
    // gr.position.x +=0.01;
    // if(ball1.position.x > 20) system("aplay ")
    for(int i = 0; i < point; i++)
    {
    // std::cout << (sqrt(((viserion.position.x-bullets[i].position.x)*(viserion.position.x-bullets[i].position.x))+((viserion.position.x-bullets[i].position.x)*(viserion.position.x-bullets[i].position.x)))) << "\n";
    if(isViser && !bullets_coll[i] && ((sqrt(((viserion.position.x-bullets[i].position.x)*(viserion.position.x-bullets[i].position.x))+((viserion.position.x-bullets[i].position.x)*(viserion.position.x-bullets[i].position.x)))) < 0.8))
    {
        bullets_coll[i] = 1;
        collide++;
        if(collide >= 1)
        {
            isViser = 0;
            score+=10000;
            Lives += 3;
        }
    }
    }
    for(int i=0;i<vis;i++)
    {
        if(!viser_bull_coll[i] && detect_collision(viser_bullets[i].bounding_box(),ball1.bounding_box()))
        {
            viser_bull_coll[i] = 1;
            Lives--;
        }
    }

    if(ball1.position.x > 20) level = 2;
    if(ball1.position.x > 72) level = 3;
    if(ball1.position.x > 90) level = 4;
    if(ball1.position.x > 102) winner();

    if(ball1.position.x - viserion.position.x > -2.0 && collide < 1) isViser = 1;
    if(isViser)
    {
        ball1.position.x  = target.x-3.5;
        viserion.position.x = target.x +3.5;
        int kl = rand()%100;
        if(kl==95) shoot();
    }
    if(ball1.position.x <= -3 + target.x)
    {
        ball1.position.x += 0.01;
        // eye.x -= 0.1;
        // target.x -= 0.1;
        // gr.position.x -=0.1;
    }
    for(int i = 1; i < vis; i++)
    {
        viser_bullets[i].tick(-10);
    }
    
    for (int i = 0;i<point;i++)
    {
        if(!bullets_coll[i])
        bullets[i].tick(10);
    }
    for(int i = 0; i < number_fireline; i++)
    {
        if(!fireline_coll[i])
        fireline[i].tick();
    }
    
    for(int i = 0; i < number_fireline; i++)
    {
        if(!isCircle && !fireline_coll[i] && fireline[i].detect_collision(ball1.position.x,ball1.position.y))
        {
            // score -= 1000;
            // quit(window);
            gameover();
            fireline_coll[i] = 1;
        }
        for(int j = 0; j < point; j++)
        {
        if(!isCircle && !fireline_coll[i] && fireline[i].detect_collision(bullets[j].position.x,bullets[j].position.y))
        {
            score += 100;
            fireline_coll[i] = 1;
            bullets_coll[j] = 1;
        }
        }
    }
    
    if(!isCircle && ball1.position.x > circle.position.x-2.0 && ball1.position.y+0.5>=circle.position.y && ball1.position.x < circle.position.x + 2.0)
    {
        isCircle = 1;
        ball1.position.x = circle.position.x - 2.0;
        ball1.position.y = circle.position.y;
        ball1.speedy = 0;
        ang = 0;
        // radius = sqrt((ball1.position.x - circle.position.x)*(ball1.position.x - circle.position.x)+(ball1.position.y - circle.position.y)*(ball1.position.y - circle.position.y));
        // ball1.position.x
    }
    else if(!ball1.position.x == circle.position.x-2.0 && !ball1.position.x == circle.position.x+2.0)isCircle = 0;
    for(int i = 0; i < number_boom ; i++)
    if(ball1.position.x > boom_pos[i])
    {  
        boomerang[i].tick();
        if(!isCircle && !boom_coll[i] && detect_collision(boomerang[i].bounding_box(),ball1.bounding_box()))
        {
            boom_coll[i] = 1;
            gameover();
            // quit(window);
            // score -= 1000;
        }
        for(int j = 0; j < point; j++)
        {
        if(!isCircle && !boom_coll[i] && detect_collision(boomerang[i].bounding_box(),bullets[j].bounding_box()))
        {
            score += 100;
            boom_coll[i] = 1;
            bullets_coll[j] = 1;
        }
        }
    }

    ball1.tick();
    char title[100];
    for(int i = 0; i < number_coins; i++)
    {
        coin[i].tick();
        if(!coin_coll[i] && detect_collision(coin[i].bounding_box(),ball1.bounding_box()))
        {
            system("aplay ../src/smw_coin.wav &");
            score += 1000;
            coins += 1;
            coin_coll[i] = 1;
        }
    }
    for(int i = 0; i < number_firebeam; i++)
    {
        firebeam[i].tick();
        if(!isCircle && !firebeam_coll[i] && detect_collision(firebeam[i].bounding_box(),ball1.bounding_box()))
        {
            gameover();
            // quit(window);
            // score -= 1000;
            firebeam_coll[i] = 1;
        }
        for(int j = 0; j < point; j++)
        {
        if(!isCircle && !firebeam_coll[i] && detect_collision(firebeam[i].bounding_box(),bullets[j].bounding_box()))
        {
            score += 100;
            firebeam_coll[i] = 1;
            bullets_coll[j] = 1;
        }
        }
        
    }
    for(int i = 0; i < number_magnets; i++)
    {
    if(magnet[i].magnetcheck(ball1.position.x,ball1.position.y))
    {
        if(ball1.position.y + 0.5 > magnet[i].position.y - 1.0)
        {
            ball1.position.y = magnet[i].position.y - 1.5;
            ball1.speedy = 0;
        }
        else
        ball1.speedy += 0.01;
    }

    }
    
    sprintf(title,"JETPACK JOYRIDE, SCORE : %d, LIVES : %d ,COINS : %lld, LEVEL: %d",(int)score,Lives,coins,level);
    if(ball1.position.x > proj_pos[0])
    {
    projectile[0].tick();
    if(!proj_coll[0] && detect_collision(projectile[0].bounding_box(),ball1.bounding_box()))
    {
        proj_coll[0] = 1;
        score += 1000000;
    }
    }
    
    if(ball1.position.x > proj_pos[1])
    {
    projectile[1].tick();
    if(!proj_coll[1] && detect_collision(projectile[1].bounding_box(),ball1.bounding_box()))
    {
        proj_coll[1] = 1;
        Lives += 3;
    }
    }

    glfwSetWindowTitle(window, title);
    camera_rotation_angle = 90;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1           =   Ball(0, -1.5, COLOR_RED);
    gr              =   Ground(0, -1, COLOR_GREEN);
    mag1            =   Mag(88,0.5,COLOR_RED);
    for(int i = 0; i < 7; i++)
    {
        coin[i]     =   Coin(i+2,-1.5,COLOR_YELLOW);
    }

    for(int i = 7; i < 14; i++)
    {
        coin[i]     =   Coin(2+(i%7),-0.5,COLOR_YELLOW);
    }
    
    for(int i = 14; i < 21; i++)
    {
        coin[i]     =   Coin(2+(i%7),0.5,COLOR_YELLOW);
    }
    
    for(int i = 21; i < 28; i++)
    {
        coin[i]     =   Coin(2+(i%7),1.5,COLOR_YELLOW);
    }

    for(int i = 28; i < 35; i++)
    {
        coin[i]     =   Coin(2+(i%7),2.5,COLOR_YELLOW);
    }
    for(int i = 35; i < 42; i++)
    {
        coin[i]     =   Coin(20+(i%7),-1.5,COLOR_YELLOW);
    }
    for(int i = 42; i < 49; i++)
    {
        coin[i]     =   Coin(20+(i%7),3.0,COLOR_YELLOW);
    }
    for(int i = 49; i < 56; i++)
    {
        coin[i]     =   Coin(20+(i%7),1.0,COLOR_YELLOW);
    }
    for(int i = 56; i < 63; i++)
    {
        coin[i]     =   Coin(65+(i%7),-1.5,COLOR_YELLOW);
    }
    for(int i = 63; i < 70; i++)
    {
        coin[i]     =   Coin(65+(i%7),-1.0,COLOR_YELLOW);
    }
    for(int i = 70; i < 77; i++)
    {
        coin[i]     =   Coin(65+(i%7),-0.5,COLOR_YELLOW);
    }
    for(int i = 77; i < 84; i++)
    {
        coin[i]     =   Coin(65+(i%7),0.0,COLOR_YELLOW);
    }
    fireline[0]     =   Fireline(11,-1.5,90.0,COLOR_BLUE);
    fireline[1]     =   Fireline(14,1.0,90.0,COLOR_DARKRED);
    fireline[2]     =   Fireline(17,0.25,90.0,COLOR_BLACK);
    fireline[3]     =   Fireline(36,3.5,-30,COLOR_PURPLE);    
    fireline[4]     =   Fireline(36,-1.5,30,COLOR_PURPLE);  
    fireline[5]     =   Fireline(45,-1.75,90,COLOR_PURPLE);  
    fireline[6]     =   Fireline(48,-1.75,90,COLOR_PURPLE);  
    fireline[7]     =   Fireline(51,-1.75,90,COLOR_PURPLE);  
    fireline[8]     =   Fireline(56,3.5,-90,COLOR_PURPLE); 
    fireline[9]     =   Fireline(59,3.5,-90,COLOR_PURPLE); 
    fireline[10]    =   Fireline(62,-1.75,90,COLOR_PURPLE); 

    firebeam[0]     =   Firebeam(19,0,0.0,7.5,COLOR_LIGHTRED);
    firebeam[1]     =   Firebeam(65,0,0.0,7.5,COLOR_LIGHTRED);
    
    projectile[0]      =   Projectile(-3,3,COLOR_PURPLE);
    proj_pos[0]     = -1.0;
    projectile[1]      =   Projectile(10,4,COLOR_BLACK);
    proj_pos[1]     = 15.0;

        mag[0]             =   Mag(6,4,COLOR_BACKGROUND);
        magnet[0]          =   Magnet(6,4,COLOR_BROWN);
        mag[1]             =   Mag(65,4,COLOR_BACKGROUND);
        magnet[1]          =   Magnet(65,4,COLOR_BROWN);
        mag[2]             =   Mag(67,4,COLOR_BACKGROUND);
        magnet[2]          =   Magnet(67,4,COLOR_BROWN);
        mag[3]             =   Mag(69,4,COLOR_BACKGROUND);
        magnet[3]          =   Magnet(69,4,COLOR_BROWN);
    boomerang[0]       =   Boomerang(10,3,COLOR_GREEN);
    boom_pos[0] = 5.0f;
    boomerang[1]       =   Boomerang(65,3,COLOR_GREEN);
    boom_pos[1] = 60.0f;
    boomerang[2]       =   Boomerang(67,3,COLOR_GREEN);
    boom_pos[2] = 62.0f;
    boomerang[3]       =   Boomerang(69,3,COLOR_GREEN);
    boom_pos[3] = 64.0f;
    boomerang[4]       =   Boomerang(71,3,COLOR_GREEN);
    boom_pos[4] = 66.0f;
    boomerang[5]       =   Boomerang(85,3,COLOR_GREEN);
    boom_pos[5] = 5.0f;
    boomerang[6]       =   Boomerang(87,3,COLOR_GREEN);
    boom_pos[6] = 82.0f;
    boomerang[7]       =   Boomerang(88,3,COLOR_GREEN);
    boom_pos[7] = 82.0f;
    boomerang[8]       =   Boomerang(89,3,COLOR_GREEN);
    boom_pos[8] = 82.0f;
    boomerang[9]       =   Boomerang(90,3,COLOR_GREEN);
    boom_pos[9] = 82.0f;
    boomerang[10]       =   Boomerang(91,3,COLOR_GREEN);
    boom_pos[10] = 82.0f;
    boomerang[11]       =   Boomerang(92,3,COLOR_GREEN);
    boom_pos[11] = 82.0f;
    boomerang[12]       =   Boomerang(93,3,COLOR_GREEN);
    boom_pos[12] = 82.0f;
    boomerang[13]       =   Boomerang(94,3,COLOR_GREEN);
    boom_pos[13] = 82.0f;
    boomerang[14]       =   Boomerang(95,3,COLOR_GREEN);
    boom_pos[14] = 82.0f;
    boomerang[15]       =   Boomerang(96,3,COLOR_GREEN);
    boom_pos[15] = 82.0f;
    boomerang[16]       =   Boomerang(97,3,COLOR_GREEN);
    boom_pos[16] = 82.0f;
    boomerang[17]       =   Boomerang(98,3,COLOR_GREEN);
    boom_pos[17] = 82.0f;
    boomerang[18]       =   Boomerang(99,3,COLOR_GREEN);
    boom_pos[18] = 82.0f;
    boomerang[19]       =   Boomerang(100,3,COLOR_GREEN);
    boom_pos[19] = 82.0f;
    circle          =   Circle(88,0.5,COLOR_BLACK);
    viserion        =   Viserion(100,-1.5,COLOR_DARKRED);

    for(int i =0 ;i < 10000;i++) bullets[i] = Bullets(0,0,COLOR_BLUE);
    for(int i =0 ;i < 10000;i++) viser_bullets[i] = Bullets(0,0,COLOR_RED);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void jumpcheck()
{
    if(!isCircle && ball1.position.y > -1.5)
    ball1.speedy -= 0.003;
    if(ball1.position.y <= -1.5 && ball1.speedy < 0) 
    {
        ball1.speedy = 0;
        ball1.position.y = -1.5;
    }
    if(ball1.position.y > 3.5) 
    {
        ball1.speedy = 0;
        ball1.position.y = 3.5;
    }
}

void bulletcheck()
{
    for(int i =0;i<point;i++)
    {
        if(!bullets_coll[i])
        {
            // bullets[i].speedy-=0.003;
            if(bullets[i].position.x >= target.x+4.0) bullets_coll[i] = 1;
        }
    }
}

void boomerangcheck()
{
    for(int i = 0; i < number_boom; i++)
    {
    if(ball1.position.x > boom_pos[i])
    boomerang[i].speed -=0.003;   
    }
    
}


void projectilecheck()
{
        if(ball1.position.x > proj_pos[0])
        projectile[0].speedy -= 0.003;
        if(projectile[0].position.y <=-2.0) projectile[0].speedy = -projectile[0].speedy;
        if(ball1.position.x > proj_pos[1])
        {
            if(projectile[1].position.y > 0)
            projectile[1].speedy -= 0.009;
            else projectile[1].speedy += 0.009;
        }
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 800;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            jumpcheck();
            projectilecheck();
            boomerangcheck();
            viserion.position.y = ball1.position.y;
            viser_bullets[vis].set_position(viserion.position.x,viserion.position.y);
            bullets[point].set_position(ball1.position.x+0.5,ball1.position.y);
            bulletcheck();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}


void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
