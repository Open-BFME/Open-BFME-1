// cl: /O2 /MD
// Gate: ButtonFlashTransition vtable 0x0110c604 slot 4; the authored
// GameWindowTransitionsStyles.cpp contains the corresponding state machine.
class GameWindow;
class Image;
class Display
{
public:
    void drawOpenRect(float x, float y, float width, float height, float thickness, int color);
    void drawFillRect(float x, float y, float width, float height, int color);
    void drawImage(const Image *image, float left, float top, float right, float bottom, int color, int mode);
};
extern Display *TheDisplay;
void PushButtonImageDrawThree(GameWindow *, int);

class ButtonFlashTransition
{
public:
    virtual void unused0();
    virtual void unused1();
    virtual void unused2();
    virtual void unused3();
    virtual void draw();
    unsigned char m_pad04[5];
    bool m_isForward;
    unsigned char m_pad0a[2];
    GameWindow *m_win;
    struct Position { int x, y; } m_pos, m_size;
    int m_drawState;
    Image *m_gradient;
};

void ButtonFlashTransition::draw()
{
    switch (m_drawState) {
    case 1:
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0x64ffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x4bffcb2d);
        break;
    case 2:
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0x96ffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x96ffcb2d);
        break;
    case 3:
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0xc8ffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0xc8ffcb2d);
        break;
    case 4:
        PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0xfaffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x96ffcb2d);
        break;
    case 5:
        PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0xfaffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x64ffcb2d);
        break;
    case 6:
        PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0xfaffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x32ffcb2d);
        break;
    case 7:
        PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawOpenRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 1.0f, 0xfaffcb2d);
        TheDisplay->drawFillRect((float)m_pos.x, (float)m_pos.y, (float)m_size.x, (float)m_size.y, 0x0fffcb2d);
        break;
    case 11:
        if (m_isForward) PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0x64ffffff, 2);
        break;
    case 12:
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0xc8ffffff, 2);
        break;
    case 13:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0x96ffffff, 2);
        break;
    case 14:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0x64ffffff, 2);
        break;
    case 15:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0x32ffffff, 2);
        break;
    case 16:
        if (!m_isForward) PushButtonImageDrawThree(m_win, 255);
        TheDisplay->drawImage(m_gradient, (float)m_pos.x, (float)m_pos.y,
                              (float)(m_pos.x + m_size.x), (float)(m_pos.y + m_size.y), 0x11ffffff, 2);
        break;
    case 18:
        PushButtonImageDrawThree(m_win, 255);
        break;
    }
}
