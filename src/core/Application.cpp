// #include "Application.h"

// Application::Application()
// {
//     m_Texture1 = Texture::Create("C:/Users/86166/Desktop/cs32/Game32/src/Asset/yan.jpg");
// }

// void Application::run(int argc, char** argv)
// {
//     glutInit(&argc, argv);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("Game32");

//     glEnable(GL_DEPTH_TEST);

//     glutDisplayFunc(BIND_FUNCTION(Application::GlutDisplayFunc));
//     glutReshapeFunc(BIND_FUNCTION(Application::WindowResizeFunc));

//     glutMainLoop();
// }

// void Application::GlutDisplayFunc()
// {
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//     gluLookAt(0.0, 0.0, -1.0,  // Camera position
//               0.0, 0.0, 0.0,   // Look at the origin
//               0.0, 1.0, 0.0);   // Up vector

//     Renderer::Init();
//     glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//     // Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, { 0.2, 0.3, 0.4 });
//     Renderer::DrawQuad({ 0.0, 0.0 }, 0.1, m_Texture1);
//     Renderer::Flush();
// }

// void Application::WindowResizeFunc(int width, int height) {
//     glViewport(0, 0, width, height);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     if (width <= height) {
//         glOrtho(-1.0, 1.0, -1.0 * (GLfloat)height / width, 1.0 * (GLfloat)height / width, -1.0, 1.0);
//     } else {
//         glOrtho(-1.0 * (GLfloat)width / height, 1.0 * (GLfloat)width / height, -1.0, 1.0, -1.0, 1.0);
//     }

//     glMatrixMode(GL_MODELVIEW);
// }
