// ?d_003c4490@@YAXXZ
// partial score=0.1827 date=2026-10-04
// cl: /DNDEBUG /MD /O2 /Ob0 /EHsc /D_STLP_USE_STATIC_LIB /Igame /Iinputs/reference/shims/stringinline
// stlport
#include "GameEngine/Source/GameLogic/LivingWorld/Load003C4160.cpp"
#include "GameEngine/Source/Common/Bfme5SingletonClear.cpp"
#include "GameEngine/Source/Common/Bfme5TwoVectorClear.cpp"
#include "GameEngine/Source/Common/BfmeOneAQAStopBfmeLayout.cpp"
#include "GameEngine/Source/Common/BfmeOneHundredNinetyTwo.cpp"
extern "C" __declspec(dllimport) void __cdecl free(void *);
extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned);
void postLoadGameFadeSteps();
class Rva003C4490Secondary {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual void transfer(Xfer *); virtual void state(int);
};
class GameLogic;
extern GameLogic *TheGameLogic;
class BfmeLivingWorldCampaignManager;
extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;
extern BfmeOneAQA *g_bfmeOneAQA;
struct Rva003C4490GameMode { char m_00[0x10c]; int mode; };
struct Rva003C4490Sub { int m_00; int active; };
class Rva003C4490 {
public:
 void run(Xfer *);
 char m_00[0x20]; Rva003C4490Sub *m_sub;
 char m_24; bool m_25; char m_26[0x17]; bool m_3D;
 char m_3E[0x8e]; void *m_buffer; unsigned m_size;
};
void Rva003C4490::run(Xfer *xfer) {
 if (xfer->IsLightCRC()) return;
 Xfer::Version version; version.data[0]=1; version.data[1]=3;
 *xfer==version;
 if (version.data[1]>=3) {
  *xfer==m_size;
  if (xfer->IsLoading()) { free(m_buffer); m_buffer=malloc(m_size); }
  xfer->XferRawBytes(m_buffer,m_size);
 }
 Transfer003C3D90 *owner=reinterpret_cast<Transfer003C3D90 *>(reinterpret_cast<char *>(this)-8);
 if (xfer->IsLoading()) {
  *xfer==m_3D;
  g_bfmeOneAQA->bfmeStopAQA();
  if (!m_3D) return;
  owner->load003C4160(xfer);
 } else {
  m_3D=m_sub->active!=0;
  *xfer==m_3D;
  if (!m_3D) return;
  owner->transfer(xfer);
 }
 reinterpret_cast<Rva003C4490Secondary *>(reinterpret_cast<char *>(TheLivingWorldCampaignManager)+8)->transfer(xfer);
 if (version.data[1]>=2) {
  int mode=reinterpret_cast<Rva003C4490GameMode *>(TheGameLogic)->mode;
  bool enabled=mode!=8 && mode!=4;
  *xfer==enabled;
  m_25=!enabled;
  if (xfer->IsLoading()) {
   if (m_25) reinterpret_cast<Gen_003C1190 *>(owner)->bfmeClear();
   else reinterpret_cast<Gen_003C0F70 *>(owner)->bfmeClear();
  }
 }
 reinterpret_cast<Rva003C4490Secondary *>(m_sub)->transfer(xfer);
 reinterpret_cast<BfmeThingEN *>(TheGameLogic)->bfmeGoEN(reinterpret_cast<BfmeItemEN *>(xfer));
 reinterpret_cast<Rva003C4490Secondary *>(reinterpret_cast<char *>(g_bfmeGameCW)+8)->transfer(xfer);
 if (xfer->IsLoading()) {
  int state; *xfer==state;
  if (!state) postLoadGameFadeSteps();
  else { reinterpret_cast<Rva003C4490Secondary *>(g_bfmeOneAQA)->state(0); m_25=false; }
 } else {
  int mode=reinterpret_cast<Rva003C4490GameMode *>(TheGameLogic)->mode;
  int state=version.data[1]>=2 ? (mode!=8 && mode!=4) : mode!=8;
  *xfer==state;
 }
}
