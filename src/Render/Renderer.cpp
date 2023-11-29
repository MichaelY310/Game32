#include <GL/glut.h>

#include "Renderer.h"

void Renderer::Init()
{   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Flush()
{   
    glFlush();
}

void Renderer::DrawQuad(vec2 position, double scale, vec3 color)
{
    // d c
    // a b
    vec2 a(0, 0);
    vec2 b(1, 0);
    vec2 c(1, 1);
    vec2 d(0, 1);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glBegin(GL_QUADS);
    glColor3f(color.x, color.y, color.z); // Red
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);

    glEnd();
}


void Renderer::DrawQuad(vec2 position, double scale, std::shared_ptr<Texture> texture)
{
    // d c
    // a b
    vec2 a(0, 0);
    vec2 b(1, 0);
    vec2 c(1, 1);
    vec2 d(0, 1);

    a = a * scale;
    b = b * scale;
    c = c * scale;
    d = d * scale;

    a = a + position;
    b = b + position;
    c = c + position;
    d = d + position;

    glBegin(GL_QUADS);
    glBindTexture(GL_TEXTURE_2D, texture->m_RendererID);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);

    glEnd();
}