// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x005868D0, 642 bytes: countdown-driven APT popup update.
// Address-derived identity: selector zero in table VA 0x0110B9DC reaches this
// body through ILT 0x000162E3; the body consumes one stack pointer and ret 4.
// The pointed record and Command005868D0 are offset-only retail views, not
// assertions about the owning class or the semantic meaning of its fields.
//
// Private helper RVA 0x005867D0 is defined here because the caller supplies
// its output in ESI plus three stack arguments. MSVC 7.1 reproduces that ABI
// from the static C++ definition. Both the 185-byte helper and this caller
// were independently byte-compared. The helper's existing dump row remains
// owned by its separate lane; its typed pin is this caller's dependency.
#include "ascii_string.h"
#include "unicode_string.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length==0; }
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length==0; }
template<> inline void StringBase<unsigned short>::swap(StringBase<unsigned short>& other) { Header* p=m_data; m_data=other.m_data; other.m_data=p; }
inline UnicodeString::UnicodeString() { m_text=0; }
inline UnicodeString::UnicodeString(const wchar_t* s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
class GameTextInterface { public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual UnicodeString fetchByValue(AsciiString key,bool* found=0);
};
extern GameTextInterface* TheGameText;
static __declspec(noinline) void appendText005867D0(UnicodeString& out,const AsciiString& key,int count,const UnicodeString& sep) {
 if(count>0) {
  UnicodeString text;
  text.format(TheGameText->fetchByValue(key),count);
  if(out.isEmpty()) ((StringBase<unsigned short>*)&out)->swap(*(StringBase<unsigned short>*)&text);
  else { out+=sep; out+=text; }
 }
}
class Image;
class CommandButton { public: const Image* getButtonImage() const; };
struct Command005868D0 { char at00[0x10]; AsciiString at10; char at14[0x64]; int at78; int at7c; int at80; bool at84; char at85[0x13]; AsciiString at98; int valueAt78() const { return at78; } int valueAt7c() const { return at7c; } int valueAt80() const { return at80; } };
struct Popup005868D0 { char at00[0x10]; int at10; CommandButton* at14; char at18[0x18]; int at30; int at34; char at38[0x10]; int at48; int at4c; };
class BfmeThingBIF { public: void bfmeGoBIF(void*,void*); };
class WindowManager;
// The retail global at 0x012F19E8 (EA's WindowManager*) has one linked
// identity: ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A. Spelling it
// anything else is a second symbol nothing defines, so it can never link.
extern WindowManager* g_rva012F19E8WindowManager;
extern AsciiString key012F4B80,key012F4B84,key012F4B88;
void bfmeGo1074B(int,int,int);
void _bfme_setLivingWorldRegionName(int,const UnicodeString&);
void _bfme_setLivingWorldRegionBonus(int,const UnicodeString&);
void __stdcall updateCountdown005868D0(Popup005868D0* popup) {
 int index=popup->at10;
 if(--popup->at34==0) {
  bfmeGo1074B(index,popup->at48,popup->at4c);
  AsciiString name;
  name.format("Popup%d/ButtonClip/Portrait",index);
  const Image* image=popup->at14->getButtonImage();
  ((BfmeThingBIF*)g_rva012F19E8WindowManager)->bfmeGoBIF(&name,(void*)image);
  _bfme_setLivingWorldRegionName(index,TheGameText->fetchByValue(((Command005868D0*)popup->at14)->at10));
  UnicodeString bonus;
  if(!((Command005868D0*)popup->at14)->at98.isEmpty()) bonus=TheGameText->fetchByValue(((Command005868D0*)popup->at14)->at98);
  if(((Command005868D0*)popup->at14)->at84) { AsciiString last("LW:LastMissionText"); appendText005867D0(bonus,last,1,UnicodeString(L"\n")); }
  else {
   appendText005867D0(bonus,key012F4B80,((Command005868D0*)popup->at14)->valueAt78(),UnicodeString(L"\n"));
   appendText005867D0(bonus,key012F4B84,((Command005868D0*)popup->at14)->valueAt7c(),UnicodeString(L"\n"));
   appendText005867D0(bonus,key012F4B88,((Command005868D0*)popup->at14)->valueAt80(),UnicodeString(L"\n"));
  }
  _bfme_setLivingWorldRegionBonus(index,bonus);
  popup->at30=1;
 }
}
