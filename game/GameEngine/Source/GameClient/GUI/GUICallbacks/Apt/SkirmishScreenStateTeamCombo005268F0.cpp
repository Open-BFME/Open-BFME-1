// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

#include "unicode_string.h"

// Retail keeps the one-handle StringBase forwarders visible at this call site.
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString(const UnicodeString &src)
{
    ((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&src);
}
inline UnicodeString::~UnicodeString()
{
    ((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &src)
{
    ((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&src);
    return *this;
}

class GameWindow;
void GadgetComboBoxGetSelectedPos(GameWindow *window, int *selected);
void *GadgetComboBoxGetItemData(GameWindow *window, int index);
void GadgetComboBoxReset(GameWindow *window);
int GadgetComboBoxAddEntry(GameWindow *window, UnicodeString text, int color);
void GadgetComboBoxSetItemData(GameWindow *window, int index, void *data);
void GadgetComboBoxSetSelectedPos(GameWindow *window, int index, bool dontHide);

class MultiplayerColorDefinition
{
public:
    int getColor() const { return *(const int *)((const char *)this + 0x10); }
};
class MultiplayerSettings
{
public:
    MultiplayerColorDefinition *getColor(int index);
};
extern MultiplayerSettings *TheMultiplayerSettings;

class GameTextInterface
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

struct StartPositionInfo
{
    int m_unmodelled00;
    int m_04;
    unsigned char m_unmodelled08[12];
};
class MpGameSetup
{
public:
    const StartPositionInfo *getStartPositionInfo(int index);
};

class SkirmishScreenState
{
public:
    void rebuildTeamCombo005268F0(int index, bool isObserver);
private:
    unsigned char m_unmodelled00[0xA8];
    GameWindow *m_teamCombos[8];
};

// The Team:0 and Team:%d entries use the slot's team combo at +0xA8.
// ?rebuildTeamCombo005268F0@SkirmishScreenState@@QAEXH_N@Z
void SkirmishScreenState::rebuildTeamCombo005268F0(int index, bool isObserver)
{
    UnicodeString teamName;
    int fixedTeam = -1;
    const StartPositionInfo *position = ((MpGameSetup *)this)->getStartPositionInfo(index);
    if (position)
        fixedTeam = position->m_04;
    int selectedData = -1;
    int entry;
    GadgetComboBoxGetSelectedPos(m_teamCombos[index], &entry);
    if (entry >= 0)
        selectedData = (int)GadgetComboBoxGetItemData(m_teamCombos[index], entry);
    GadgetComboBoxReset(m_teamCombos[index]);
    MultiplayerColorDefinition *def = TheMultiplayerSettings->getColor(-1);
    if (isObserver || fixedTeam < 0)
    {
        entry = GadgetComboBoxAddEntry(m_teamCombos[index], TheGameText->fetch("Team:0"), def->getColor());
        GadgetComboBoxSetItemData(m_teamCombos[index], entry, (void *)-1);
        if (isObserver)
        {
            GadgetComboBoxSetSelectedPos(m_teamCombos[index], 0, false);
            return;
        }
    }
    int selectedEntry = 0;
    for (int team = 0; team < 4; ++team)
    {
        if (fixedTeam >= 0 && fixedTeam != team)
            continue;
        AsciiString teamLabel;
        teamLabel.format("Team:%d", team + 1);
        teamName = TheGameText->fetch(teamLabel.str());
        entry = GadgetComboBoxAddEntry(m_teamCombos[index], teamName, def->getColor());
        GadgetComboBoxSetItemData(m_teamCombos[index], entry, (void *)team);
        if (team == selectedData)
            selectedEntry = entry;
    }
    GadgetComboBoxSetSelectedPos(m_teamCombos[index], selectedEntry, false);
}
