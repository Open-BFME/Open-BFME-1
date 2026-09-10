// ?updateSpecialPowerShortcut@ControlBar@@IAEXXZ
// partial score=0.89 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Clean reconstruction of ?updateSpecialPowerShortcut@ControlBar@@IAEXXZ.
// The bounded body is tied to the named populateSpecialPowerShortcut caller at
// 0x0049E3C9 and to the retail fields/callees below; it is not a dump lift.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { FALSE = 0, TRUE = 1 };

class Object;

class GameWindow
{
public:
    Bool winIsHidden(void);
    Int winHide(Bool hide);
    Int winEnable(Bool enable);
    UnsignedInt winSetStatus(UnsignedInt status);
    UnsignedInt winClearStatus(UnsignedInt status);
};

class CommandButton
{
public:
    UnsignedInt getOptions(void) const
    {
        return *(const UnsignedInt *)((const unsigned char *)this + 0x18);
    }
};

class Player
{
public:
    Object *findNaturalCommandCenter(void);
    Bool isPlayerActive(void) const;
};

class PlayerList
{
public:
    Player *getLocalPlayer(void) { return m_localPlayer; }

private:
    unsigned char m_unreconstructed_00[0x0c];
    Player *m_localPlayer;
};

extern PlayerList *ThePlayerList;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeScaleBC;

void *GadgetButtonGetData(GameWindow *window);
void GadgetButtonDrawInverseClock(GameWindow *window, Int percent, Int color);

class BfmeAnimateWindowManager
{
public:
    Bool isFinished(void) const
    {
        return *(const Bool *)((const unsigned char *)this + 0x10);
    }
};

enum CommandAvailability
{
    COMMAND_RESTRICTED = 0,
    COMMAND_AVAILABLE = 1,
    COMMAND_ACTIVE = 2,
    COMMAND_HIDDEN = 3,
    COMMAND_NOT_READY = 4,
    COMMAND_CANT_AFFORD = 5,
    COMMAND_NOT_READY_SPECIAL = 6,
    COMMAND_RESTRICTED_SPECIAL = 7
};

class ControlBar
{
public:
    void showSpecialPowerShortcut(void);
    void animateSpecialPowerShortcut(Bool isOn);
    void hideSpecialPowerShortcut(void);

protected:
    CommandAvailability getCommandAvailability(const CommandButton *command,
                                               GameWindow *window,
                                               Object *object,
                                               Real *percent,
                                               Bool forceDisabledEvaluation) const;
    void updateSpecialPowerShortcut(void);

private:
    unsigned char m_unreconstructed_00[0x10];
    BfmeAnimateWindowManager *m_animateWindowManagerForGenShortcuts;
    unsigned char m_unreconstructed_14[0x20];
    GameWindow *m_contextParent[1];
    unsigned char m_unreconstructed_38[0x94];
    GameWindow *m_specialPowerShortcutButtons[10];
    Int m_currentlyUsedSpecialPowersButtons;
    unsigned char m_unreconstructed_f8[4];
    GameWindow *m_specialPowerShortcutParent;
    unsigned char m_unreconstructed_100[0x16c];
    UnsignedInt m_buildUpClockColor;
};

void ControlBar::updateSpecialPowerShortcut(void)
{
    if(!m_specialPowerShortcutParent || !m_specialPowerShortcutButtons
       || !ThePlayerList || !ThePlayerList->getLocalPlayer())
        return;

    if(ThePlayerList->getLocalPlayer()->findNaturalCommandCenter()
       && m_specialPowerShortcutParent->winIsHidden()
       && m_contextParent[0] && !m_contextParent[0]->winIsHidden())
    {
        showSpecialPowerShortcut();
        animateSpecialPowerShortcut(TRUE);
    }
    else if(!ThePlayerList->getLocalPlayer()->findNaturalCommandCenter()
            && !m_specialPowerShortcutParent->winIsHidden()
            && !m_animateWindowManagerForGenShortcuts->isFinished())
    {
        animateSpecialPowerShortcut(FALSE);
    }

    if(m_specialPowerShortcutParent->winIsHidden())
        return;

    if(!ThePlayerList->getLocalPlayer()->isPlayerActive())
    {
        hideSpecialPowerShortcut();
        return;
    }

    if(m_contextParent[0] && !m_contextParent[0]->winIsHidden()
       && m_specialPowerShortcutParent->winIsHidden())
        showSpecialPowerShortcut();

    for(Int i = 0; i < m_currentlyUsedSpecialPowersButtons; i++)
    {
        GameWindow *win = m_specialPowerShortcutButtons[i];
        if(win->winIsHidden() == TRUE)
            continue;

        const CommandButton *command = (const CommandButton *)GadgetButtonGetData(win);
        if(command == 0)
            continue;

        win->winClearStatus(0x00400000);
        win->winClearStatus(0x01000000);
        win->winClearStatus(0x40000000);
        win->winClearStatus(0x80000000);

        CommandAvailability availability = COMMAND_RESTRICTED;
        Real percent = 0.0f;
        if(ThePlayerList->getLocalPlayer()->findNaturalCommandCenter())
        {
            availability = getCommandAvailability(
                command, win, ThePlayerList->getLocalPlayer()->findNaturalCommandCenter(),
                &percent, FALSE);
        }

        if(availability == COMMAND_RESTRICTED || availability == COMMAND_NOT_READY_SPECIAL)
        {
            if(command->getOptions() & 0x00400000)
                availability = COMMAND_HIDDEN;
        }

        Int color = 0;
        switch(availability)
        {
        case COMMAND_HIDDEN:
            win->winHide(TRUE);
            break;
        case COMMAND_RESTRICTED:
        case COMMAND_RESTRICTED_SPECIAL:
            win->winEnable(FALSE);
            win->winSetStatus(0x80000000);
            if(availability == COMMAND_RESTRICTED_SPECIAL)
                win->winSetStatus(0x01000000);
            break;
        case COMMAND_NOT_READY:
            color = m_buildUpClockColor;
            win->winEnable(FALSE);
            win->winSetStatus(0x00400000);
            break;
        case COMMAND_CANT_AFFORD:
        case COMMAND_NOT_READY_SPECIAL:
            win->winEnable(FALSE);
            win->winSetStatus(0x01000000);
            break;
        case COMMAND_AVAILABLE:
        case COMMAND_ACTIVE:
        default:
            win->winEnable(TRUE);
            break;
        }

        if(percent < g_bfmeDefaultBU)
            GadgetButtonDrawInverseClock(win, (Int)(g_bfmeScaleBC * percent), color);
    }
}
