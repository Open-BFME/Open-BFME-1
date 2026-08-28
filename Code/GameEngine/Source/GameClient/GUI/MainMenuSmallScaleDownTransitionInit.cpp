// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@MainMenuSmallScaleDownTransition@@UAEXPAVGameWindow@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
    int x;
    int y;
};

class Image;
extern const char g_smallText;
extern const char g_emptyText;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
    AsciiString() : m_data(0) {}
    ~AsciiString();
    AsciiString &operator=(const AsciiString &other);
    void concat(const char *text, int length);

    const char *str() const
    {
        return m_data ? static_cast<const char *>(m_data) + 8 : &g_emptyText;
    }

private:
    void *m_data;
};

struct GameWindowInstanceData
{
    unsigned char m_pad00[0x18c];
    AsciiString m_decoratedNameString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
    void winGetSize(int *width, int *height);
    void winGetScreenPosition(int *x, int *y);
    GameWindowInstanceData *winGetInstanceData();
    void winSetEnabledImage(int index, const Image *image);

    const Image *winGetEnabledImage() const { return m_enabledImage; }

private:
    unsigned char m_pad00[0x48];
    const Image *m_enabledImage;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
    int nameToKey(const char *name);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00c();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01c();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02c();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03c();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04c();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05c();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06c();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07c();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08c();
    virtual void slot090();
    virtual void slot094();
    virtual void slot098();
    virtual void slot09c();
    virtual void slot0a0();
    virtual void slot0a4();
    virtual void slot0a8();
    virtual void slot0ac();
    virtual void slot0b0();
    virtual void slot0b4();
    virtual void slot0b8();
    virtual void slot0bc();
    virtual void slot0c0();
    virtual void slot0c4();
    virtual void slot0c8();
    virtual void slot0cc();
    virtual void slot0d0();
    virtual void slot0d4();
    virtual void slot0d8();
    virtual GameWindow *winGetWindowFromId(GameWindow *parent, int id);
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class Transition
{
public:
    virtual ~Transition();
    virtual void init(GameWindow *window);
    virtual void update(int frame);
    virtual void reverse();
    virtual void draw();
    virtual void skip();

protected:
    int m_frameLength;
    bool m_isFinished;
    bool m_isForward;
    unsigned char m_pad0a[2];
    GameWindow *m_window;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class MainMenuSmallScaleDownTransition : public Transition
{
public:
    virtual void init(GameWindow *window);

protected:
    ICoord2D m_position;
    ICoord2D m_size;
    int m_drawState;
    ICoord2D m_growPosition;
    ICoord2D m_growSize;
    ICoord2D m_incrementSize;
    GameWindow *m_growWindow;
};

// ?init@MainMenuSmallScaleDownTransition@@UAEXPAVGameWindow@@@Z
void MainMenuSmallScaleDownTransition::init(GameWindow *window)
{
    if (window)
    {
        m_window = window;
        m_window->winGetSize(&m_size.x, &m_size.y);
        m_window->winGetScreenPosition(&m_position.x, &m_position.y);
    }

    AsciiString growWindowName;
    growWindowName = m_window->winGetInstanceData()->m_decoratedNameString;
    growWindowName.concat(&g_smallText, 5);
    m_growWindow = TheWindowManager->winGetWindowFromId(
        0, TheNameKeyGenerator->nameToKey(growWindowName.str()));
    if (!m_growWindow)
        return;

    m_growWindow->winGetSize(&m_growSize.x, &m_growSize.y);
    m_growWindow->winGetScreenPosition(&m_growPosition.x, &m_growPosition.y);

    m_isForward = false;
    update(0);
    m_isFinished = false;
    m_isForward = true;

    m_incrementSize.x = (m_growSize.x - m_size.x) / 6;
    m_incrementSize.y = (m_growSize.y - m_size.y) / 6;
    m_growWindow->winSetEnabledImage(0, m_window->winGetEnabledImage());
}
