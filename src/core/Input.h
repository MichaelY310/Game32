#include <unordered_set>
#include <iostream>
#include <GL/glut.h>

class Input
{
public:
    static void keyboardDownCallback(unsigned char key, int x, int y) {
        m_PressedKeys.insert(static_cast<int>(key));
    }

    static void keyboardUpCallback(unsigned char key, int x, int y) {
        m_PressedKeys.erase(static_cast<int>(key));
    }

    static void specialKeyCallback(int key, int x, int y) {
        m_PressedKeys.insert(key);
    }

    static void specialKeyUpCallback(int key, int x, int y) {
        m_PressedKeys.erase(key);
    }

    static bool isKeyPressed(unsigned char key) {
        return m_PressedKeys.find(static_cast<int>(key)) != m_PressedKeys.end();
    }

    static std::unordered_set<int> m_PressedKeys;
};

