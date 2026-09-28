// ?rva005369A0@BfmeAptScreenOnlineChat@@UAEHPAVGameWindow@@III@Z
// partial score=0.7783191230207065 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.
// OnlineChat vtable 0x01106F58 slot 4 -> ILT 0x000423ED -> 0x005369A0.
// Constructor 0x00536DC0 and destructor 0x0052D7C0 prove the owner.
// The original virtual spelling is unproven; retain the RVA.
// Gadget members +0x40..+0x50 follow BfmeAptScreenOnlineChatInitGadgets.cpp.
// +0xAC/+0xB0/+0xB4 and +0xB8 retain OnlineChatConstructor.cpp names.
// Direct helpers: rva005307B0 = ILT 0x00002E1E (one AsciiString by value);
// rva00536870 = ILT 0x000436E9 (receiver in ECX; no stack arguments).
// These new address-derived member declarations still need verified resolver
// bindings before landing; no speculative symbols.csv pins accompany this attempt.
#include "game/Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "game/Libraries/Source/WWVegas/WWLib/unicode_string.h"
class GameWindow;
struct RGBColor;
class Mouse { public: void setCursorTooltip(UnicodeString text, int delay, const RGBColor *color, float scale); };
#define SLOT(n) virtual void slot##n();
class GameTextInterface {
public:
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8)
 virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};
class GameSpyInfo {
public:
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5)
 virtual void joinGroupRoom(int id);
 virtual void leaveGroupRoom();
 SLOT(8) SLOT(9) SLOT(10)
 virtual int getCurrentGroupRoom();
};
extern Mouse *TheMouse;
extern GameTextInterface *TheGameText;
extern GameSpyInfo *TheGameSpyInfo;
int GadgetListBoxGetEntryBasedOnXY(GameWindow *, int, int, int &, int &);
void *GadgetListBoxGetItemData(GameWindow *, int, int);
UnicodeString GadgetListBoxGetText(GameWindow *, int, int);
void GadgetComboBoxGetSelectedPos(GameWindow *, int *);
void *GadgetComboBoxGetItemData(GameWindow *, int);
class BfmeAptScreenOnlineChat {
public:
 virtual int rva005369A0(GameWindow *window, unsigned message, unsigned data1, unsigned data2);
 void rva005307B0(AsciiString name);
 void rva00536870();
 unsigned char m_prefix[0x3c];
 GameWindow *m_playersList;
 GameWindow *m_friendsList;
 GameWindow *m_ignoreList;
 GameWindow *m_chatLobbies;
 GameWindow *m_chatEntry;
 unsigned char m_gap54[0x58];
 int m_zAC;
 int m_zB0;
 int m_zB4;
 AsciiString m_unusedName;
};
int BfmeAptScreenOnlineChat::rva005369A0(GameWindow *window, unsigned message, unsigned data1, unsigned data2)
{
 int result = 1;
 switch(message) {
 case 0x18:
 {
  GameWindow *list = (GameWindow *)data1;
  if(list != m_playersList && list != m_friendsList && list != m_ignoreList) break;
  int x = data2 & 0xffff;
  int y = data2 >> 16;
  if(x == m_zAC && y == m_zB0) ++m_zB4;
  else m_zB4 = 0;
  int row, column;
  GadgetListBoxGetEntryBasedOnXY(list,x,y,row,column);
  if(m_zB4 >= 7) {
   if(column == -1 || column == 2) {
    AsciiString label("APT:NULL");
    TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
    m_unusedName = label;
   }
   if(column == 0) {
    AsciiString label;
    if(GadgetListBoxGetItemData(list,row,1) == (void *)1) label = "TOOLTIP:FellowshipIcon";
    else label = "APT:NULL";
    TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
    m_unusedName = label;
   }
   if(column == 1) {
    AsciiString name;
    name.translate(GadgetListBoxGetText(list,row,2));
    rva005307B0(name);
   }
  }
  m_zAC = x;
  m_zB0 = y;
  break;
 }
 case 0x4014: return 0;
 case 0x4025:
 {
  int selected = -1;
  GadgetComboBoxGetSelectedPos(m_chatLobbies,&selected);
  if(selected >= 0) {
   int room = (int)GadgetComboBoxGetItemData(m_chatLobbies,selected);
   if(room && room != TheGameSpyInfo->getCurrentGroupRoom()) {
    TheGameSpyInfo->leaveGroupRoom();
    TheGameSpyInfo->joinGroupRoom(room);
    break;
   }
  }
  break;
 }
 case 0x4030:
  if((GameWindow *)data1 != m_chatEntry) return 0;
  if(!data2) rva00536870();
  break;
 }
 return result;
}

