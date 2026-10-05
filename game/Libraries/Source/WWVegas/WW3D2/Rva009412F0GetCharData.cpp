// ?Get_Char_Data@Rva00941400Font@@QAEPBURva00941400CharRecord@@G@Z
// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// The retail body spans 0x009412F0 through 0x009413F3 and returns with RET 4.
// Two INT3 bytes follow it in the retail image.
// FontCharsClass_Get_Char_Metric.cpp calls this method on Rva00941400Font.
// FontCharsClass::Get_Char_Data at 0x00941290 handles the separate map lookup.
// The friend declaration lets this class call FontCharsClass::Get_Char_Data and Grow_Unicode_Array.
// The member offsets below describe this BFME font's character arrays.
// The strict add_match check verified all 260 bytes and all four DIR32 references.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "game/Libraries/Source/WWVegas/WW3D2/render2dsentence.h"

extern "C" __declspec(dllimport) DWORD WINAPI GetGlyphIndicesW(HDC,LPCWSTR,int,LPWORD,DWORD);
class FontCharsClassGdiState;extern FontCharsClassGdiState *g_fontCharsGdiState0134AEAC;
struct Rva009412F0GdiView {char m00[16];HDC m10;};
struct Rva00941400CharRecord;
// The generated loader target uses thiscall, takes one stack argument, and returns with RET 4.
void d_0093f440();
class Rva00941400Font {
public:
 const Rva00941400CharRecord *Get_Char_Data(unsigned short ch);
 char m00[8];Rva00941400Font*m08;char m0C[0x48-12];HFONT m48;
 const Rva00941400CharRecord*m4C[256];const Rva00941400CharRecord**m44C;
 char m450[12];unsigned short m45C;
 const Rva00941400CharRecord *load(unsigned short ch) {
  union {void(*p)();const Rva00941400CharRecord*(Rva00941400Font::*m)(unsigned short);}u;
  typedef char MemberWidth[sizeof(u)==4?1:-1];
  u.p=d_0093f440;return (this->*u.m)(ch);
 }
};
const Rva00941400CharRecord *Rva00941400Font::Get_Char_Data(unsigned short ch) {
 if((ch>=0xe01 && ch<=0xe3a)||(ch>=0xe3f && ch<=0xe5b)) {
  unsigned glyph=0xffff;
  HGDIOBJ font=m48;
  HDC dc=((Rva009412F0GdiView*)g_fontCharsGdiState0134AEAC)->m10;
  HGDIOBJ old=SelectObject(dc,font);
  GetGlyphIndicesW(((Rva009412F0GdiView*)g_fontCharsGdiState0134AEAC)->m10,&ch,1,(WORD*)&glyph,1);
  SelectObject(dc,old);
  if((unsigned short)glyph!=0xffff) return (const Rva00941400CharRecord*)(reinterpret_cast<FontCharsClass*>(this)->Get_Char_Data((unsigned short)glyph));
  if(m08) return m08->Get_Char_Data(ch);
 }
 const Rva00941400CharRecord *data;
 if(ch<256)data=m4C[ch];
 else {reinterpret_cast<FontCharsClass*>(this)->Grow_Unicode_Array(ch);data=m44C[(unsigned)ch-(unsigned)m45C];}
 if(!data)data=load(ch);
 if(data==(const Rva00941400CharRecord*)-1) {
  if(m08 && this!=m08)return m08->Get_Char_Data(ch);
  return 0;
 }
 return data;
}
