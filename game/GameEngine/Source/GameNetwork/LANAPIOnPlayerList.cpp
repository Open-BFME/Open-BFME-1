// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
// BFME LANAPI::OnPlayerList candidate (retail RVA 0x00689A40,
// complete code extent 238 bytes).  BFME keeps the player-list GameWindow at
// LANAPI+0x60 and preserves its top visible row across the roster rebuild.
#include "StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Color;

class GameWindow;

extern const Color playerColor;

extern Int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text,
                                     Color color, Int row, Int column,
                                     Bool overwrite = 1);
extern void GadgetListBoxGetSelected(GameWindow *listbox, Int *selectList);
extern void *GadgetListBoxGetItemData(GameWindow *listbox, Int row,
                                      Int column = 0);
extern void GadgetListBoxReset(GameWindow *listbox);
extern void GadgetListBoxSetItemData(GameWindow *listbox, void *data,
                                     Int row, Int column = 0);
extern void GadgetListBoxSetSelected(GameWindow *listbox, Int selectIndex);
extern Int GadgetListBoxGetTopVisibleEntry(GameWindow *listbox);
extern void GadgetListBoxSetTopVisibleEntry(GameWindow *listbox, Int newPos);

class LANPlayer
{
public:
    UnicodeString m_name;      // +0x00
    UnicodeString m_login;     // +0x04
    UnicodeString m_host;      // +0x08
    UnsignedInt m_lastHeard;   // +0x0c
    LANPlayer *m_next;         // +0x10
    UnsignedInt m_ip;          // +0x14; only this verified node prefix is used
};

typedef char LanPlayerSizeCheck[(sizeof(LANPlayer) == 0x18) ? 1 : -1];

class LANAPI
{
public:
    virtual void OnPlayerList(LANPlayer *playerList);

protected:
    unsigned char m_bfmeGap04[0x08 - 0x04];
    LANPlayer *m_lobbyPlayers;                         // +0x08
    unsigned char m_bfmeGap0c[0x3d - 0x0c];
    Bool m_inLobby;                                    // +0x3d
    unsigned char m_bfmeGap3e[0x60 - 0x3e];
    GameWindow *m_playerListBox;                       // +0x60
};

// This TU models only the callback's verified instance prefix.
typedef char LanApiSizeCheck[(sizeof(LANAPI) == 0x64) ? 1 : -1];

// ?OnPlayerList@LANAPI@@UAEXPAVLANPlayer@@@Z
void LANAPI::OnPlayerList(LANPlayer *playerList)
{
    if (m_inLobby)
    {
        UnsignedInt selectedIP = 0;
        Int selectedIndex = -1;
        Int indexToSelect = -1;
        GadgetListBoxGetSelected(m_playerListBox, &selectedIndex);
        Int previousTopIndex = GadgetListBoxGetTopVisibleEntry(m_playerListBox);

        if (selectedIndex != -1)
            selectedIP = (UnsignedInt)GadgetListBoxGetItemData(m_playerListBox, selectedIndex, 0);

        GadgetListBoxReset(m_playerListBox);

        LANPlayer *player = m_lobbyPlayers;
        while (player)
        {
            UnsignedInt playerIP = player->m_ip;
            Int addedIndex = GadgetListBoxAddEntryText(m_playerListBox,
                player->m_name, playerColor, -1, -1);
            GadgetListBoxSetItemData(m_playerListBox,
                (void *)playerIP, addedIndex, 0);

            if (selectedIP == playerIP)
                indexToSelect = addedIndex;

            player = player->m_next;
        }

        if (indexToSelect >= 0)
            GadgetListBoxSetSelected(m_playerListBox, indexToSelect);

        GadgetListBoxSetTopVisibleEntry(m_playerListBox, previousTopIndex);
    }
}
