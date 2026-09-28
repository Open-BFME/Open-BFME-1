// cl: /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Constructor body at 0x00787710. Matched factory 0x00788290 allocates 0x30
// bytes and calls this body through ILT 0x0003097C. The established factory
// spelling bfmeConstruct00788290 is retained by the ledger object-symbol note.
// Vtable 0x01126AD0 and destructor 0x007859D0 independently establish the owner,
// base, m_name (+4), and m_displayString (+8). Tail fields are address-qualified.
// Rect/size aggregate initialization preserves the native store order. The
// two volatile rectangle stores retain retail's y-before-right write ordering.
// Existing display-string shims put getSize at +0x30; this body calls +0x3C
// and +0x48, so its observed virtual interface is kept local. The text fetch
// by-value ABI at +0x24 also agrees with GameTextFetchAscii.cpp (0x00436F90).
// UnicodeString's canonical four-byte view forwards the native StringBase
// construction directly; placement-new would introduce a spurious null check.

#include <string>
#include <string.h>
#include <new>
#include "string_base.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
template<> inline int StringBase<char>::getLength() const { return m_data ? m_data->length : 0; }
template<> inline char StringBase<char>::getCharAt(int i) const { return m_data ? m_data->data[i] : 0; }
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length==0; }
template<> inline void StringBase<char>::set(const char *s) { set(s,s?strlen(s):0); }
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
template<> inline StringBase<unsigned short>::StringBase() { m_data=0; }
template<> inline StringBase<unsigned short>::~StringBase() { releaseBuffer(); }
#include "ascii_string.h"
inline AsciiString::AsciiString(const char *s,int n):StringBase<char>(s,n) {}
#include "unicode_string.h"
inline UnicodeString::UnicodeString() { new(this) StringBase<unsigned short>(); }
inline UnicodeString::UnicodeString(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s); }
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->~StringBase<unsigned short>(); }
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s) { ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this; }
inline UnicodeString &UnicodeString::operator=(const wchar_t *s) { ((StringBase<unsigned short>*)this)->set((const unsigned short*)s,s?wcslen(s):0); return *this; }
std::wstring MultiByteToWideCharSingleLine(const char*);
class GameFont;
class FontLibrary { public: GameFont *getFont(AsciiString*,float,unsigned char); };
extern FontLibrary *TheFontLibrary;
class DisplayString {
public:
 virtual ~DisplayString();
 virtual void setText(UnicodeString text);
 virtual UnicodeString getText();
 virtual int getTextLength();
 virtual void notifyTextChanged();
 virtual void reset();
 virtual void setFont(GameFont*);
 virtual GameFont *getFont();
 virtual void setWordWrap(int);
 virtual void setWordWrapCentered(bool);
 virtual void slot28();virtual void slot2C();virtual void slot30();virtual void slot34();virtual void slot38();
 virtual void getSize(int*,int*);
 virtual void slot40();virtual void slot44();
 virtual void slot48(int,int);
};
class DisplayStringManager {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();
 virtual DisplayString *newDisplayString();
};
extern DisplayStringManager *TheDisplayStringManager;
class GameTextInterface {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual void slot0C();virtual void slot10();
 virtual void slot14();virtual void slot18();virtual void slot1C();virtual void slot20();
 virtual UnicodeString fetch(AsciiString,bool*);
};
extern GameTextInterface *TheGameText;
class AptTextListener;
class WindowManager { public: void bfme_bindAptText(const AsciiString&,const UnicodeString&,AptTextListener*); };
extern WindowManager *g_theWindowManager;
extern bool Rva012BB864ScaleEnabled;
extern float Rva012BB86CScaleX,Rva012BB870ScaleY;
class Rva00788290Base { public: virtual ~Rva00788290Base() {} };
class Rva00788290Object {
public:
 const char *m_at00;
 float m_at04,m_at08,m_at0c,m_at10;
 int m_at14,m_at18;
 int m_state1c;
 float m_value20;
 int m_at24,m_at28,m_at2c;
 char m_pad30[0x10];
 float m_value40,m_value44;
 float m_at48;
 int m_at4c,m_at50;
 const char *m_at54;
 unsigned m_flags58;
 void *m_source5c;
};
struct Rect00787710 { float a,b,c,d; Rect00787710() : a(0),b(0),c(0),d(0) {} };
struct Size00787710 { float a,b; Size00787710(float x,float y) : a(x),b(y) {} };
class Rva00788290Allocation : public Rva00788290Base {
public:
 Rva00788290Allocation(Rva00788290Object *source);
 void setSize00787710(float w,float h) { m_size00787710.a=w; m_size00787710.b=h; }
 void setRect00787710(float x,float y,float r,float b) {m_rect00787710.a=x;*(volatile float*)&m_rect00787710.b=y;*(volatile float*)&m_rect00787710.c=r;m_rect00787710.d=b;}
 virtual ~Rva00788290Allocation();
 AsciiString m_name;
 DisplayString *m_displayString;
 Rect00787710 m_rect00787710;
 Size00787710 m_size00787710;
 unsigned m_at24,m_at28;
 bool m_at2c,m_dropShadow,m_at2e;
};
Rva00788290Allocation::Rva00788290Allocation(Rva00788290Object *source):
 m_displayString(0),m_rect00787710(),m_size00787710(1,1),
 m_at24(source->m_at2c),m_at28(source->m_at14),m_at2c(Rva012BB864ScaleEnabled),m_dropShadow(false),m_at2e(!source->m_at28 || !source->m_at24)
{
 m_displayString=TheDisplayStringManager->newDisplayString();
 float x=source->m_at04;
 float y=source->m_at08;
 float fontSize=source->m_at48;
 float right=source->m_at0c;
 float bottom=source->m_at10;
 if(m_at2c) {
  fontSize *= Rva012BB86CScaleX < Rva012BB870ScaleY ? Rva012BB86CScaleX : Rva012BB870ScaleY;
  x*=Rva012BB86CScaleX;
  y*=Rva012BB870ScaleY;
  right*=Rva012BB86CScaleX;
  bottom*=Rva012BB870ScaleY;
 }
 setRect00787710(x,y,right,bottom);
 GameFont *font;
 { AsciiString fontName(source->m_at00); font=TheFontLibrary->getFont(&fontName,fontSize,0); }
 m_displayString->setFont(font);
 AsciiString text(source->m_at54);
 for(int i=0;i<text.getLength();++i) {
  if(text.getCharAt(i)=='&' && !_stricmp(text.str()+i+1,"dropShadow")) {
   text=AsciiString(text.str(),i);
   m_dropShadow=true;
   break;
  }
 }
 UnicodeString translated;
 if(text.getCharAt(0)=='$') {
  const char *label=text.str()+1;
  if(strchr(label,':')) m_name.set(label);
  else m_name.format(AsciiString("APT:%s"),label);
  bool exists;
  translated=TheGameText->fetch(m_name,&exists);
 } else {
  translated=MultiByteToWideCharSingleLine(text.str()).c_str();
 }
 if(source->m_at24) {
  m_displayString->setWordWrapCentered(m_at28==2);
  m_displayString->setWordWrap((int)(right-x));
 }
 if(m_name.isEmpty()) {
  m_displayString->slot48(0,0);
  m_displayString->setText(translated);
  int width,height;
  m_displayString->getSize(&width,&height);
  setSize00787710((float)width,(float)height);
 } else g_theWindowManager->bfme_bindAptText(m_name,translated,(AptTextListener*)this);
 source->m_value40=m_size00787710.a;
 source->m_value44=m_size00787710.b;
 source->m_value20=m_size00787710.a;
 source->m_state1c=1;
}
