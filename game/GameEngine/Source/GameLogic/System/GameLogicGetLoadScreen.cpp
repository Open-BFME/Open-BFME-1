// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Identity: startNewGame calls this factory with loadingSaveGame and stores EAX
// in GameLogic+118 (m_loadScreen); ZH getLoadScreen has the same mode dispatch.
// BFME mode +10C and resource strings +78..88 agree with the landed constructor.
// The RET ends at +2B1; the in-function aligned eight-entry jump table extends
// through +2D4. The original 689-byte dump omitted its 3-byte alignment and table.
// Constructor declarations below expose only allocation extents seen here.
// 0051B690 installs vtable 01105FCC and returns this after base ctor 00490420.
// 0051BF30 installs vtable 01106070; stores its one stack arg at +14;
// returns this with RET 4. Both identities remain address-derived.
#include "ascii_string.h"
void* __cdecl operator new(unsigned);
void __cdecl operator delete(void*) throw();
class LoadScreen {};
struct Gen_0051b690 { char storage[0x10]; Gen_0051b690(); };
class AsciiStringVX;
class Gen_00491580 {char storage[0x18];public:Gen_00491580(const AsciiStringVX&,const AsciiStringVX&);};
class Gen_00491880 {char storage[0x24];public:Gen_00491880(const AsciiStringVX&,const AsciiStringVX&,const AsciiStringVX&);};
class LoadScreen0051BF30 {char storage[0xa4];public:LoadScreen0051BF30(unsigned);};
class MultiPlayerLoadScreen {char storage[0xb4];public:MultiPlayerLoadScreen();};
class Rva00490A30 {char storage[0x174];public:Rva00490A30();};
// Retail global 0x012F19E8 is EA's WindowManager*. The one linked identity is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A; the local view below only
// describes the one field this body reads, so the cast happens at the use.
class WindowManager;
extern WindowManager* g_rva012F19E8WindowManager;
class Gen000290D2 {public:char pad000[0x1b8];void* at1b8;};
class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;
extern void* R2Glob012F4ACC;
extern const AsciiString Rva01336E50EmptyAscii;
void j_00016473();
inline void still00386190(AsciiString* p) { ((void (__cdecl*)(AsciiString*))j_00016473)(p); }
class GameLogic {
 char pad000[0x78];
 AsciiString at078,at07c,at080,at084,at088;
 char pad08c[0x10c-0x8c];
 unsigned m_gameMode;
 LoadScreen* getLoadScreen(bool);
};
LoadScreen* GameLogic::getLoadScreen(bool loadingSaveGame) {
 switch(m_gameMode) {
 case 4:
  if(((Gen000290D2*)g_rva012F19E8WindowManager)->at1b8) return (LoadScreen*)new Gen_0051b690;
  return (LoadScreen*)new Gen_00491580((const AsciiStringVX&)at078,(const AsciiStringVX&)at07c);
 case 0: case 3: case 6: case 7:
  if(loadingSaveGame || m_gameMode==3) {
   AsciiString image; still00386190(&image);
   return (LoadScreen*)new Gen_00491880((const AsciiStringVX&)image,(const AsciiStringVX&)Rva01336E50EmptyAscii,(const AsciiStringVX&)Rva01336E50EmptyAscii);
  }
  return (LoadScreen*)new Gen_00491880((const AsciiStringVX&)at080,(const AsciiStringVX&)at084,(const AsciiStringVX&)at088);
 case 2:
  return (LoadScreen*)new LoadScreen0051BF30(m_gameMode);
 case 1:
  if(reinterpret_cast<void * &>(g_rva012F4998LanLobby)) return (LoadScreen*)new LoadScreen0051BF30(m_gameMode);
  return (LoadScreen*)new MultiPlayerLoadScreen;
 case 5:
  if(R2Glob012F4ACC) return (LoadScreen*)new LoadScreen0051BF30(m_gameMode);
  return (LoadScreen*)new Rva00490A30;
 default: return 0;
 }
}
