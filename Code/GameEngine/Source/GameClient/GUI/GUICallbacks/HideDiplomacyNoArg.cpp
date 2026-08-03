// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class DiplomacyWindow
{
public:
    char m_pad[0x254];
    unsigned char m_visible;
};

class ControlBar
{
public:
    char m_pad[0x50];
    unsigned char m_field50;
};

class WindowManager
{
public:
    void hideQuitMenu();
};

extern DiplomacyWindow *g_diplomacyWindow;
extern ControlBar *g_controlBar;
extern WindowManager *g_theWindowManager;

// ?HideDiplomacy@@YAXXZ
void HideDiplomacy()
{
    DiplomacyWindow *window = g_diplomacyWindow;
    if (window)
    {
        unsigned char visible = window->m_visible;
        if (!visible)
        {
            visible = 1;
            window->m_visible = visible;
            g_controlBar->m_field50 = visible;
            g_theWindowManager->hideQuitMenu();
        }
    }
}
