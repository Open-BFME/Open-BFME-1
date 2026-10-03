// ?classify@Rva005329Classify@@QAEXPAVRva005329C0Obj@@H@Z
// Native selection helper visibility preserves the retail loop-entry reload.
// See targets/game/reverse/identity_evidence/00532280-selection-visibility.md.
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_copyctor_outofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// The matched wrappers at 0x005329C0 and 0x005329E0 call ILT 0x00047807.
// That thunk routes to this 460-byte body at 0x00532280. Both wrappers
// declare the target as Rva005329Classify::classify(Rva005329C0Obj *, int).
#define _STLP_USE_STATIC_LIB 1
#include <vector>
#include "Common/AsciiString.h"
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
class GameWindow;
class Rva005329C0Obj;
void *GadgetListBoxGetItemData(GameWindow*,int,int);
// The caller supplies ECX, which this helper does not consume. Keep the native
// body visible: its vector effects determine the caller's empty-path reload.
class Rva00531DE0Receiver
{
public:
    int Rva00531DE0RefreshSelectedIndices(GameWindow *, std::vector<int> *);
};
class BfmeStateXC { public: void bfmeNotifyXC(int); };
class GameSpyInfo;
class GameSpyConfigInterface;
extern GameSpyInfo *TheGameSpyInfo;
extern GameSpyConfigInterface *TheGameSpyConfig;
struct PlayerRecord00532280 { char pad00[4]; AsciiString text04; char pad08[12]; int field14; unsigned int flags18; };
class PlayerSlots00532280 {
public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
 S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
 virtual PlayerRecord00532280 *slot20(int);
 S(21) S(22) S(23) S(24) S(25) S(26) S(27)
 virtual int slot28();
 S(29) S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
 S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
 S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
 S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69) S(70)
 virtual void slot71(int);
 virtual void slot72(int);
 virtual void slot73(int,AsciiString);
 virtual void slot74(int);
#undef S
};
class ConfigSlots00532280 {
public:
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10)
#undef S
 virtual bool slot11(int);
};
class Rva005329Classify { public: void classify(Rva005329C0Obj*, int); };
void Rva005329Classify::classify(Rva005329C0Obj *obj, int action)
{
 GameWindow *window = reinterpret_cast<GameWindow *>(obj);
 std::vector<int> selected;
 int count=((Rva00531DE0Receiver*)this)->Rva00531DE0RefreshSelectedIndices(window,&selected); if (count>0) {
  if(!selected.empty()) { int *it=selected.begin(); do {
   UnicodeString text;
   int row=*it;
   int id=(int)GadgetListBoxGetItemData(window,row,0);
   switch(action) {
   case 0:
    if(id!=((PlayerSlots00532280*)TheGameSpyInfo)->slot28()) ((PlayerSlots00532280*)TheGameSpyInfo)->slot71(id);
    break;
   case 1: {
    PlayerRecord00532280 *player=((PlayerSlots00532280*)TheGameSpyInfo)->slot20(id);
    if(player) {
     int peer=player->field14;
     if(peer!=((PlayerSlots00532280*)TheGameSpyInfo)->slot28() && !(player->flags18&0x20) && (!TheGameSpyConfig || !((ConfigSlots00532280*)TheGameSpyConfig)->slot11(peer)))
      ((PlayerSlots00532280*)TheGameSpyInfo)->slot73(id,player->text04);
    }
    break;
   }
   case 2: ((PlayerSlots00532280*)TheGameSpyInfo)->slot72(id); break;
   case 3: ((PlayerSlots00532280*)TheGameSpyInfo)->slot74(id); break;
   }
   } while(++it!=selected.end()); }
 } else ((BfmeStateXC*)this)->bfmeNotifyXC(action);
}

extern int GadgetListBoxGetNumEntries( GameWindow *listbox );
extern void GadgetListBoxGetSelected( GameWindow *listbox, int *selectList );

__declspec(noinline) int Rva00531DE0Receiver::Rva00531DE0RefreshSelectedIndices( GameWindow *listbox, std::vector<int> *vecptr )
{
	std::vector<int> &vec = *vecptr;
	int count = GadgetListBoxGetNumEntries( listbox );
	vec.erase(vec.begin(), vec.end());

	if ( count != 0 )
	{
		int *selected = 0;
		GadgetListBoxGetSelected( listbox, (int *)&selected );

		for ( int i = 0; i < count; ++i )
		{
			if ( selected[ i ] < 0 )
				break;

			vec.push_back( selected[ i ] );
		}
	}

	return (int)vec.size();
}
