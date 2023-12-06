#include <GL/glut.h>
#include <cmath>

#include "Renderer.h"
#include "Scene/Entity.h"
#include <iostream>
#include <string.h>

#include <GL/freeglut.h>

const float PI = 3.14159265359;

void Renderer::Init()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Flush()
{
    glFlush();
    glutSwapBuffers();
}

void Renderer::DrawQuad(std::shared_ptr<Entity> entity)
{
    if (entity->m_EntityType== EntityType::LEADER)
    {
        std::string Message = std::to_string(entity->Rank) + ":   ";
        Message += std::to_string(entity->time);
        DrawLeaderBoard(entity->m_Position,Message);
        return;
    }

    if (!entity->m_Texture)
    {
        DrawQuad(entity->m_Position, entity->m_Size, entity->m_Color, entity->m_Alpha, entity->m_Depth);
    }
    else 
    {
        DrawQuad(entity->m_Position, entity->m_Size, entity->m_Texture, entity->m_Depth);
    }
}

void Renderer::DrawQuad(vec2 position, vec2 scale, vec3 color, double alpha, double depth)
{
    // d c
    // a b
    vec2 a(-0.5, -0.5);
    vec2 b(0.5, -0.5);
    vec2 c(0.5, 0.5);
    vec2 d(-0.5, 0.5);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glBegin(GL_QUADS);
    glColor4f(color.x, color.y, color.z, alpha);
    glVertex3f(a.x, a.y, depth);
    glVertex3f(b.x, b.y, depth);
    glVertex3f(c.x, c.y, depth);
    glVertex3f(d.x, d.y, depth);

    glEnd();
}


void Renderer::DrawQuad(vec2 position, vec2 scale, std::shared_ptr<Texture> texture, double depth)
{
    
    // d c
    // a b
    vec2 a(-0.5, -0.5);
    vec2 b(0.5, -0.5);
    vec2 c(0.5, 0.5);
    vec2 d(-0.5, 0.5);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture->m_RendererID);
    

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(a.x, a.y, depth);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(b.x, b.y, depth);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(c.x, c.y, depth);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(d.x, d.y, depth);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

void Renderer::DrawRing(vec2 position, vec2 scale, vec3 color, double alpha, double depth, double angle)
{
    glColor4f(color.x, color.y, color.z, alpha);

    const float radius = scale.x;
    const float startAngle = angle;
    const float endAngle = 270;

    glBegin(GL_TRIANGLE_STRIP);

    for (float angle = startAngle; angle <= endAngle; angle += 1.0) {
        float radians = angle * (PI / 180.0);
        float x = radius * cos(radians);
        float y = radius * sin(radians);

        glVertex3f(position.x + x, position.y + y, depth);
        glVertex3f(position.x, position.y, depth);
    }

    glEnd();
}


void Renderer::DrawLeaderBoard( vec2 position ,std::string Message)
{
   DrawQuad(vec2(3,3), vec2(0.01,0.01), vec3(1.0, 1.0, 1.0), 1.0 , 0);
   std::cout << position.x << " " << position.y <<std::endl;
   glRasterPos2i(position.x,position.y);
   glColor3f(0.2f, 0.7f, 0.0f);
   glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)Message.c_str());
}