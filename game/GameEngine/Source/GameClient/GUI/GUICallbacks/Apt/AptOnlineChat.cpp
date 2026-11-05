// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /I.
// The column-0 arm repeats the tooltip call in both branches; VC7.1 cross-jumps
// the two copies into one tail, which is what yields retail's `mov ecx,esp`
// before the EH saved-esp store at +0x1A6 (handoff targets/game/reverse/attempt_support/20261105-005369a0-onlinechat-cross-jump.md).
// OnlineChat vtable 0x01106F58 slot 4 -> ILT 0x000423ED -> 0x005369A0.
// Constructor 0x00536DC0 and destructor 0x0052D7C0 prove the owner.
// The original virtual spelling is unproven; retain the RVA.
// Gadget members +0x40..+0x50 follow BfmeAptScreenOnlineChatInitGadgets.cpp.
// +0xAC/+0xB0/+0xB4 and +0xB8 retain OnlineChatConstructor.cpp names.
// Direct helpers, called by their matched ledger names: ILT 0x00002E1E reaches
// 0x005307B0, matched as AptOnlineCustomMatch::MpOwnerUpdatePlayerTooltip (one
// AsciiString by value); ILT 0x000436E9 reaches 0x00536870, matched as
// BfmeAptScreenOnlineChat::Rva00536870 (receiver in ECX, no stack arguments).
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
class AptOnlineCustomMatch { public: void MpOwnerUpdatePlayerTooltip(AsciiString name); };
class BfmeAptScreenOnlineChat {
public:
 virtual int rva005369A0(GameWindow *window, unsigned message, unsigned data1, unsigned data2);
 void Rva00536870();
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
    if(GadgetListBoxGetItemData(list,row,1) == (void *)1) {
     label = "TOOLTIP:FellowshipIcon";
     TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
    } else {
     label = "APT:NULL";
     TheMouse->setCursorTooltip(TheGameText->fetch(label),-1,0,1.0f);
    }
    m_unusedName = label;
   }
   if(column == 1) {
    AsciiString name;
    name.translate(GadgetListBoxGetText(list,row,2));
    reinterpret_cast<AptOnlineCustomMatch *>(this)->MpOwnerUpdatePlayerTooltip(name);
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
 {
  int handled;
  if((GameWindow *)data1 == m_chatEntry) {
   if(!data2) Rva00536870();
   handled=1;
  } else handled=0;
  return handled;
 }
 }
 return result;
}

