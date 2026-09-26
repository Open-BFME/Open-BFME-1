// cl: /DNDEBUG /MD /EHsc
// Shell::reset, retail 0x0057F8E0.

typedef bool Bool;
typedef int Int;

class BfmeImeManager
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void slot18() = 0;
    virtual void slot1C() = 0;
    virtual void slot20() = 0;
    virtual void slot24() = 0;
    virtual void bfmeDetach() = 0;
};

extern BfmeImeManager *TheBfmeImeManager;
extern void *TheGameSpyInfo;
void GameSpyCloseAllOverlays();

class WindowLayout
{
public:
    virtual void slot00(void *) = 0;
    virtual void slot04(void *) = 0;
    virtual void slot08(void *) = 0;
    virtual void runShutdown(void *) = 0;
};

class AnimateWindowManager
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0C() = 0;
    virtual void reset() = 0;
};

class SubsystemInterface
{
public:
    virtual ~SubsystemInterface();
    virtual void init() = 0;
    virtual Bool loadIniFilesFromLegend();
    virtual void slot03();
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual Bool slot06(Int);
    virtual void slot07();
    virtual void slot08(Int);

protected:
    void *m_name;
};

class Shell : public SubsystemInterface
{
public:
    virtual void reset();

private:
    void pop()
    {
        WindowLayout *screen;
        if (!m_screenCount)
            screen = 0;
        else
            screen = m_screenStack[m_screenCount - 1];

        if (TheGameSpyInfo)
            GameSpyCloseAllOverlays();

        if (!screen)
            return;

        m_pendingPop = true;
        Bool immediatePop = false;
        screen->runShutdown(&immediatePop);

        if (TheBfmeImeManager)
            TheBfmeImeManager->bfmeDetach();
    }

    WindowLayout *m_screenStack[16];
    Int m_screenCount;
    Bool m_pendingPush;
    Bool m_pendingPop;
    char m_padding[0x0e];
    AnimateWindowManager *m_animateWindowManager;
};

void Shell::reset()
{
    if (TheBfmeImeManager)
        TheBfmeImeManager->bfmeDetach();

    while (m_screenCount)
        pop();

    m_animateWindowManager->reset();
}
