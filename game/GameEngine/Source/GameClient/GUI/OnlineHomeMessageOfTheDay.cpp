// Retail 0x00546920 (993 bytes). Matched OnlineHomeInitMessageGadget calls
// bfmeRefreshMessageOfTheDay through ILT 0x0003FFDF. Field +0x3C is its gadget.
// MOTD colour parsing follows the ZH WOLWelcomeMenu.cpp grabUByte/update helper.
// stlport
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#define _STLP_USE_STATIC_LIB 1
#include <string>
#include <stdlib.h>
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#pragma intrinsic(strlen)

template <typename T> inline void StringBase<T>::set(const T *s) { set(s, s ? strlen((const char*)s) : 0); }
template <typename T> inline void StringBase<T>::concat(const StringBase<T>& s) {
    concat(s.m_data ? s.m_data->data : (const T*)"", s.m_data ? s.m_data->length : 0);
}
inline UnicodeString::UnicodeString() : m_text(0) {}
inline UnicodeString::UnicodeString(const UnicodeString& s) {
    ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&s);
}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::~StringBase(); }

template<class T> inline T StringBase<T>::getCharAt(int i) const {return m_data?m_data->data[i]:0;}
template<class T> inline bool StringBase<T>::isEmpty() const {return !m_data || m_data->length==0;}
template<> inline bool StringBase<char>::startsWith(const char *s) const {return startsWith(s,strlen(s));}
inline AsciiString &AsciiString::operator=(const char *s) {StringBase<char>::set(s); return *this;}
inline UnicodeString::UnicodeString(const wchar_t* s) {
 ((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase((const unsigned short*)s);
}
inline UnicodeString& UnicodeString::operator=(const UnicodeString& s) {
 ((StringBase<unsigned short>*)this)->set(*(const StringBase<unsigned short>*)&s); return *this;
}
class GameSpyInfo { public:
virtual void slot000();
virtual void slot004();
virtual void slot008();
virtual void slot00C();
virtual void slot010();
virtual void slot014();
virtual void slot018();
virtual void slot01C();
virtual void slot020();
virtual void slot024();
virtual void slot028();
virtual void slot02C();
virtual void slot030();
virtual void slot034();
virtual void slot038();
virtual void slot03C();
virtual void slot040();
virtual void slot044();
virtual void slot048();
virtual void slot04C();
virtual void slot050();
virtual void slot054();
virtual void slot058();
virtual void slot05C();
virtual void slot060();
virtual void slot064();
virtual void slot068();
virtual void slot06C();
virtual void slot070();
virtual void slot074();
virtual void slot078();
virtual void slot07C();
virtual void slot080();
virtual void slot084();
virtual void slot088();
virtual void slot08C();
virtual void slot090();
virtual void slot094();
virtual void slot098();
virtual void slot09C();
virtual void slot0A0();
virtual void slot0A4();
virtual void slot0A8();
virtual void slot0AC();
virtual void slot0B0();
virtual void slot0B4();
virtual void slot0B8();
virtual void slot0BC();
virtual void slot0C0();
virtual void slot0C4();
virtual void slot0C8();
virtual void slot0CC();
virtual void slot0D0();
virtual void slot0D4();
virtual void slot0D8();
virtual void slot0DC();
virtual void slot0E0();
virtual void slot0E4();
virtual void slot0E8();
virtual void slot0EC();
virtual void slot0F0();
virtual void slot0F4();
virtual void slot0F8();
virtual void slot0FC();
virtual void slot100();
virtual const AsciiString &getMOTD();
};
class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;
class GameWindow;
extern int GameSpyColor[];
void GadgetListBoxReset(GameWindow*);
int GadgetListBoxAddEntryText(GameWindow*,UnicodeString,int,int,int,bool=true);
void GadgetListBoxSetTopVisibleEntry(GameWindow*,int);
std::wstring MultiByteToWideCharSingleLine(const char*);
static unsigned char grabUByte(const char *s) {
 char tmp[5] = "0xff";
 tmp[2]=s[0]; tmp[3]=s[1];
 unsigned char b = strtol(tmp,0,16);
 return b;
}
inline int GameMakeColor(unsigned char r,unsigned char g,unsigned char b,unsigned char a) {return (a<<24)|(r<<16)|(g<<8)|b;}
class BfmeAptScreenOnlineHome { public:
 void bfmeRefreshMessageOfTheDay();
 unsigned char m_unmodelled[0x3c];
 GameWindow *m_messageOfTheDay;
};
void BfmeAptScreenOnlineHome::bfmeRefreshMessageOfTheDay() {
 if(m_messageOfTheDay && TheGameSpyInfo) {
  GadgetListBoxReset(m_messageOfTheDay);
  AsciiString aLine;
  UnicodeString line;
  AsciiString aMotd = reinterpret_cast<GameSpyInfo *>(TheGameSpyInfo)->getMOTD();
  while(aMotd.nextToken(&aLine,"\n")) {
   if(aLine.getCharAt(aLine.getLength()-1)=='\r') aLine.removeLastChar();
   aLine.trim();
   if(aLine.isEmpty()) aLine=" ";
   int c=GameSpyColor[27];
   if(aLine.startsWith("\\\\")) aLine=aLine.str()+1;
   else if(aLine.startsWith("\\") && aLine.getLength()>9) {
    unsigned char a,r,g,b;
    a=grabUByte(aLine.str()+1); r=grabUByte(aLine.str()+3);
    g=grabUByte(aLine.str()+5); b=grabUByte(aLine.str()+7);
    c=GameMakeColor(r,g,b,a);
    aLine=aLine.str()+9;
   }
   line=UnicodeString(MultiByteToWideCharSingleLine(aLine.str()).c_str());
   GadgetListBoxAddEntryText(m_messageOfTheDay,line,c,-1,-1);
   GadgetListBoxSetTopVisibleEntry(m_messageOfTheDay,0);
  }
 }
}

