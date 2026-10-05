// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
// Complete 585B InGameUI slot-19 body and its 233B private helper.
// Canonical string headers; address-qualified BFME ABI views, never instantiated
// as substitute native owners. Evidence: 00441d30-coupled-subtitle-recovery.md.
#include <stddef.h>
#include "unicode_string.h"
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }
template<> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const { return m_data ? m_data->data[index] : 0; }
inline UnicodeString::UnicodeString() {m_text=0;}
inline UnicodeString::UnicodeString(const UnicodeString &o) {((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&o);}
inline UnicodeString::UnicodeString(const UnicodeString &o,int start,int len) {((StringBase<unsigned short>*)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short>*)&o,start,len);}
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
class GameFont;class DisplayString;class DisplayStringManager;
extern DisplayStringManager *TheDisplayStringManager;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern void j_0001d0a2();extern void j_00004e67();extern void j_0000abc3();
class GlobalLanguageData;class FontLibrary;
class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;extern FontLibrary *TheFontLibrary;
class Rva00441D30Calls {};
typedef int (Rva00441D30Calls::*Adjust)(int);
typedef GameFont *(Rva00441D30Calls::*Font)(const AsciiString&,float,bool);
__forceinline Adjust adjustCall(){union{void(*raw)();Adjust m;}p;p.raw=j_00004e67;return p.m;}
__forceinline Font fontCall(){union{void(*raw)();Font m;}p;p.raw=j_0000abc3;return p.m;}
// Address-qualified ABI view for the native display's BFME slots, including
// native UnicodeString transport and its canonical substring constructor.
class Rva0043E5C0Display {
public:
 virtual void s0()=0;
 virtual void s4(UnicodeString)=0;
 virtual UnicodeString s8()=0;
 virtual void sc()=0;virtual void s10()=0;virtual void s14()=0;virtual void s18(GameFont*)=0;virtual void s1c()=0;
 virtual void s20()=0;virtual void s24()=0;virtual void s28()=0;virtual void s2c()=0;
 virtual void s30()=0;virtual void s34()=0;virtual void s38()=0;
 virtual void s3c(int*,int*)=0;
};
static int rva0043e5c0(Rva0043E5C0Display *display,const UnicodeString&text,int index)
{
 int end=index;
 while(end<text.getLength() && text.getCharAt(end)!=10) ++end;
 if(end>index) {
  UnicodeString old=display->s8();
  display->s4(UnicodeString(text,index,end-index));
  int width,height;display->s3c(&width,&height);
  display->s4(old);
  return width;
 }
 return 0;
}
// Absent-from-retail caller preserves the real helper's nonconstant index domain.
int forceRva0043E5C0(Rva0043E5C0Display *d,const UnicodeString &s,int i) {return rva0043e5c0(d,s,i);}
class Rva00441D30Manager {public:
virtual void s0()=0;virtual void s4()=0;virtual void s8()=0;virtual void sc()=0;virtual void s10()=0;
virtual void s14()=0;virtual void s18()=0;virtual void s1c()=0;virtual void s20()=0;virtual Rva0043E5C0Display *s24()=0;
};
struct Rva00441D30Record {
 UnicodeString f00;int f04;Rva0043E5C0Display *f08[4];int f18[4];Rva0043E5C0Display *f28;
 int f2c,f30,f34,f38;unsigned f3c,f40;bool f44;
};
class Rva00441D30 {
public:
 void method(UnicodeString text,int duration);
 __forceinline Rva00441D30Record *&record(){return *(Rva00441D30Record**)((char*)this+0x818);}
};
class Rva00441D30OwnerSlots { public:
 virtual void s00()=0;virtual void s04()=0;virtual void s08()=0;virtual void s0c()=0;
 virtual void s10()=0;virtual void s14()=0;virtual void s18(GameFont*)=0;virtual void s1c()=0;
 virtual void s20()=0;virtual void s24()=0;virtual void s28()=0;virtual void s2c()=0;
 virtual void s30()=0;virtual void s34()=0;virtual void s38()=0;virtual void s3c()=0;
 virtual void s40()=0;virtual void s44()=0;virtual void s48()=0;virtual void s4c()=0;
 virtual void s50()=0;virtual void s54()=0;
};
void Rva00441D30::method(UnicodeString text,int duration)
{
 ((Rva00441D30OwnerSlots*)this)->s54();
 ((void(*)(const UnicodeString&,bool))j_0001d0a2)(text,false);
 StringBase<unsigned short> &base=*(StringBase<unsigned short>*)&text;
 if(base.isEmpty() || duration<=0) return;
 int keepDuration=duration; duration=32;base.concat((unsigned short*)&duration,1);
 record()=new Rva00441D30Record;
 ((StringBase<unsigned short>*)&record()->f00)->set(base);
 record()->f30=keepDuration;record()->f38=0;record()->f34=0;
 record()->f3c=timeGetTime();record()->f04=0;record()->f44=false;
 for(int i=1;i<4;++i){record()->f08[i]=0;record()->f18[i]=0;}
 GameFont *font=(((Rva00441D30Calls*)TheFontLibrary)->*fontCall())(*(AsciiString*)((char*)this+0x878),
 (float)(((Rva00441D30Calls*)TheGlobalLanguageData)->*adjustCall())(*(int*)((char*)this+0x87c)),*(bool*)((char*)this+0x880));
 record()->f2c=0;
 record()->f08[0]=((Rva00441D30Manager*)TheDisplayStringManager)->s24();
 record()->f08[0]->s14();record()->f08[0]->s18(font);
 if(*(bool*)((char*)this+0x874)) record()->f18[0]=-rva0043e5c0((Rva0043E5C0Display*)record()->f08[0],record()->f00,0)/2;
 record()->f28=((Rva00441D30Manager*)TheDisplayStringManager)->s24();record()->f28->s14();record()->f28->s18(font);
 record()->f40=(((unsigned char)*(int*)((char*)this+0x868)<<24)|((unsigned char)*(int*)((char*)this+0x85c)<<16)|((unsigned char)*(int*)((char*)this+0x860)<<8)|(unsigned char)*(int*)((char*)this+0x864));
 if(float(*(int*)((char*)this+0x890))<1.0f) *(int*)((char*)this+0x890)=1;
}

typedef char Rva00441D30RecordSize[(sizeof(Rva00441D30Record)==0x48)?1:-1];
typedef char Rva00441D30MemberWidth[(sizeof(Adjust)==4 && sizeof(Font)==4)?1:-1];
