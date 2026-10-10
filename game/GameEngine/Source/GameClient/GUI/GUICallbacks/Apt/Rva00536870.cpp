// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// OnlineChat member at RVA00536870, native240B RET0. Constructor536DC0
// binds OnBttnEnterText to member wrapper536DB0 through ILT1B3DD.
#include "string_base.h"
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(); }
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->~StringBase<unsigned short>(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
static inline void trim(UnicodeString &s) { ((StringBase<unsigned short>*)&s)->trim(); }
class GameWindow;
UnicodeString GadgetTextEntryGetText(GameWindow *);
void GadgetTextEntrySetText(GameWindow *,UnicodeString);
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
class Rva00536870Dispatch {
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
 virtual void slot10() = 0;
 virtual void slot11() = 0;
 virtual void slot12() = 0;
 virtual void slot13() = 0;
 virtual void slot14() = 0;
 virtual void slot15() = 0;
 virtual void slot16() = 0;
 virtual void slot17() = 0;
 virtual void slot18() = 0;
 virtual void slot19() = 0;
 virtual void slot20() = 0;
 virtual void slot21() = 0;
 virtual void slot22() = 0;
 virtual void slot23() = 0;
 virtual void slot24() = 0;
 virtual void slot25() = 0;
 virtual void slot26() = 0;
 virtual void slot27() = 0;
 virtual void slot28() = 0;
 virtual void slot29() = 0;
 virtual void slot30() = 0;
 virtual void slot31() = 0;
 virtual void slot32() = 0;
 virtual void slot33() = 0;
 virtual void slot34() = 0;
 virtual void slot35() = 0;
 virtual void slot36() = 0;
 virtual void slot37() = 0;
 virtual void slot38() = 0;
 virtual void slot39() = 0;
 virtual void slot40() = 0;
 virtual void slot41() = 0;
 virtual void slot42() = 0;
 virtual void slot43() = 0;
 virtual void slot44() = 0;
 virtual void slot45() = 0;
 virtual void slot46() = 0;
 virtual void slot47() = 0;
 virtual void slot48() = 0;
 virtual void slot49() = 0;
 virtual void slot50() = 0;
 virtual void slot51() = 0;
 virtual void slot52() = 0;
 virtual void slot53() = 0;
 virtual void slot54() = 0;
 virtual void slot55() = 0;
 virtual void slot56() = 0;
 virtual void slot57() = 0;
 virtual void slot58() = 0;
 virtual void slot59() = 0;
 virtual void slot60() = 0;
 virtual void slot61() = 0;
 virtual bool sendChat(UnicodeString,bool,GameWindow *) = 0;
};
class BfmeAptScreenOnlineChat {
public:
 void Rva00536870();
 bool Rva00536530HandleSlashCommands(UnicodeString);
private:
 char m_unmodelled000[0x40];
 GameWindow *m_playersList;
 char m_unmodelled044[0x0C];
 GameWindow *m_chatEntry;
};
void BfmeAptScreenOnlineChat::Rva00536870()
{
 UnicodeString text;
 text=GadgetTextEntryGetText(m_chatEntry);
 GadgetTextEntrySetText(m_chatEntry,UnicodeString::TheEmptyString);
 trim(text);
 if(!reinterpret_cast<const StringBase<unsigned short> &>(text).isEmpty()) {
  if(!Rva00536530HandleSlashCommands(text))
   ((Rva00536870Dispatch *)TheGameSpyInfo)->sendChat(text,false,m_playersList);
 }
}
