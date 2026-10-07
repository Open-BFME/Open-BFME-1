// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/gamewindow /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
// Retail RVA 0x0055E470, 1806 bytes; Options constructor 0x00563370
// registers ILT 0x00007D0B with the literal "AptOptions::Reset".
// See targets/game/reverse/identity_evidence/0055e470-options-reset.md.
// Unidentified preset fields and virtual operations retain address/slot names.
// The canonical preferences header carries the existing BFME-only member.
#include "../../../Include/Common/UserPreferences.h"
class BfmeAptScreenSetComboFromIndex { public: void setComboFromIndex(int); };
class Rva0007C510 { public: int ge() const; };
void GadgetCheckBoxSetChecked(GameWindow *, bool);
void GadgetComboBoxSetSelectedPos(GameWindow *, int, bool);
struct AudioSettings { char pad[0x80]; float m_defaultSoundVolume,m_defaultVoiceVolume,m_defaultMusicVolume,m_defaultAmbientVolume,m_defaultMovieVolume; };
class Rva0055E470Windows { public:
virtual void slot0() = 0;
virtual void slot1() = 0;
virtual void slot2() = 0;
virtual void slot3() = 0;
virtual void slot4() = 0;
virtual void slot5() = 0;
virtual void slot6() = 0;
virtual void slot7() = 0;
virtual void slot8() = 0;
virtual void slot9() = 0;
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
virtual int slot53(GameWindow *, unsigned, unsigned, unsigned) = 0;
};
class Rva0055E470Audio { public:
virtual void slot0() = 0;
virtual void slot1() = 0;
virtual void slot2() = 0;
virtual void slot3() = 0;
virtual void slot4() = 0;
virtual void slot5() = 0;
virtual void slot6() = 0;
virtual void slot7() = 0;
virtual void slot8() = 0;
virtual void slot9() = 0;
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
virtual void slot48(float) = 0;
virtual void slot49(float) = 0;
virtual void slot50(float) = 0;
virtual void slot51(float) = 0;
virtual void slot52(float) = 0;
virtual void slot53() = 0;
virtual void slot54() = 0;
virtual void slot55() = 0;
virtual void slot56() = 0;
virtual void slot57() = 0;
virtual void slot58() = 0;
virtual void slot59() = 0;
virtual void slot60() = 0;
virtual void slot61() = 0;
virtual void slot62() = 0;
virtual void slot63() = 0;
virtual void slot64() = 0;
virtual void slot65() = 0;
virtual void slot66() = 0;
virtual void slot67() = 0;
virtual void slot68() = 0;
virtual void slot69() = 0;
virtual void slot70() = 0;
virtual void slot71() = 0;
virtual AudioSettings *slot72() = 0;
virtual void slot73() = 0;
virtual void slot74() = 0;
virtual void slot75() = 0;
virtual void slot76() = 0;
virtual void slot77() = 0;
virtual void slot78() = 0;
virtual void slot79() = 0;
virtual void slot80() = 0;
virtual void slot81() = 0;
virtual void slot82() = 0;
virtual void slot83() = 0;
virtual void slot84() = 0;
virtual void slot85() = 0;
virtual void slot86() = 0;
virtual void slot87() = 0;
virtual void slot88() = 0;
virtual void slot89() = 0;
virtual void slot90() = 0;
virtual void slot91(bool) = 0;
};
class Rva0055E470Display { public:
virtual void slot0() = 0;
virtual void slot1() = 0;
virtual void slot2() = 0;
virtual void slot3() = 0;
virtual void slot4() = 0;
virtual void slot5() = 0;
virtual void slot6() = 0;
virtual void slot7() = 0;
virtual void slot8() = 0;
virtual void slot9() = 0;
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
virtual void slot20(float,float,float,float) = 0;
};
class GameWindowManager; extern GameWindowManager *TheWindowManager;
class AudioManager; extern AudioManager *TheAudio;
class Display; extern Display *TheDisplay;
class GameLogic; extern GameLogic *TheGameLogic;
class GlobalData; extern GlobalData *TheWritableGlobalData;
class GameLODManager; extern GameLODManager *TheGameLODManager;
class PalantirUIState; extern PalantirUIState *g_aptPalantirUIState;
extern unsigned char g_optByte12F4AD0;
struct Rva0055E470Logic { char pad[0x10c]; int field10c; };
struct Rva0055E470Global { char pad[0xbc0]; float m_keyboardDefaultScrollFactor; };
struct Rva0055E470State { char pad[8]; bool field08; };
struct StaticGameLODInfo { int m_maxParticleCount; bool m_useShadowVolumes,m_useShadowDecals,m_useAnisotropic; char pad07; bool field08,m_showSoftWaterEdge; char pad0a[14]; bool m_useBuildupScaffolds; char pad19[3]; int m_textureReduction; char pad20; bool field21,m_showProps; char pad23[13]; };
struct Rva0055E470LOD { StaticGameLODInfo presets[6]; char pad120[0x16c4-0x120]; int field16c4; };
#define wm ((Rva0055E470Windows *)TheWindowManager)
#define audio ((Rva0055E470Audio *)TheAudio)
#define display ((Rva0055E470Display *)TheDisplay)
#define logic ((Rva0055E470Logic *)TheGameLogic)
#define global ((Rva0055E470Global *)TheWritableGlobalData)
#define lod ((Rva0055E470LOD *)TheGameLODManager)
#define state ((Rva0055E470State *)g_aptPalantirUIState)
class BfmeAptScreenOptions { public:
 void _bfme_reset(const char *);
 char pad000[0x258]; int m_page; char pad25c[0x284-0x25c];
 GameWindow *w284;
 GameWindow *w288;
 GameWindow *w28c;
 GameWindow *w290;
 GameWindow *w294;
 GameWindow *w298;
 GameWindow *w29c;
 GameWindow *w2a0;
 GameWindow *w2a4;
 GameWindow *w2a8;
 GameWindow *w2ac;
 GameWindow *w2b0;
 GameWindow *w2b4;
 GameWindow *w2b8;
 GameWindow *w2bc;
 GameWindow *w2c0;
 GameWindow *w2c4;
 GameWindow *w2c8;
 GameWindow *w2cc;
 GameWindow *w2d0;
 GameWindow *w2d4;
 GameWindow *w2d8;
 GameWindow *w2dc;
 GameWindow *w2e0;
 GameWindow *w2e4;
 GameWindow *w2e8;
 GameWindow *w2ec;
 GameWindow *w2f0;
 GameWindow *w2f4;
 GameWindow *w2f8;
 GameWindow *w2fc;
 GameWindow *w300;
int field304;
OptionPreferences *prefs() { return (OptionPreferences *)((char*)this+0x260); }
};
typedef char Rva0055E470PresetSize[(sizeof(StaticGameLODInfo)==0x30)?1:-1];

// Keep volume outside the guarded audio blocks: its lifetime allows the
// compiler to share the first graphics-flag stack slot. Each preset field is
// read through the array expression; a cached record reference changes codegen.
void BfmeAptScreenOptions::_bfme_reset(const char *) {
 int volume;
 if (m_page == 2 || m_page == 3) {
  if (logic->field10c == 8 || logic->field10c == 4) {
   if (w284 && g_optByte12F4AD0) GadgetComboBoxSetSelectedPos(w284,field304,false);
   if (w288 && (logic->field10c == 8 || logic->field10c == 4) && !state->field08)
    ((BfmeAptScreenSetComboFromIndex *)this)->setComboFromIndex(prefs()->rva00090900IdealStaticGameDetail());
   if (w2f8) {
    int *range=(int*)w2f8->winGetUserData();
    wm->slot53(w2f8,0x400d,range[0]+(range[1]-range[0])/2,0);
    range=(int*)w2f8->winGetUserData();
    if (range && range[3]!=-1) {
     int pos=range[3]; float gamma=1.0f;
     if (pos<50) { if (pos<=0) gamma=0.6f; else gamma=1.0f-(50-pos)*0.008f; }
     else if(pos>50) gamma=(pos-50)*0.02f+1.0f;
     display->slot20(gamma,0.0f,1.0f,0.0f);
    }
   }
  }
  if(w2f4) wm->slot53(w2f4,0x400d,(int)(global->m_keyboardDefaultScrollFactor*50.0f),0);
  if(w290) {
   int level=prefs()->rva00090900IdealStaticGameDetail();
   if(level==0 || level==1) { GadgetCheckBoxSetChecked(w290,true); w290->winEnable(false); }
   else { GadgetCheckBoxSetChecked(w290,true); w290->winEnable(true); }
  }
  if(w294) GadgetCheckBoxSetChecked(w294,false);
  if(w29c) {
   int level=prefs()->rva00090900IdealStaticGameDetail();
   if(level==0 || level==1) { GadgetCheckBoxSetChecked(w29c,false); w29c->winEnable(false); }
   else { GadgetCheckBoxSetChecked(w29c,true); w29c->winEnable(true); }
  }
  if(w2a0) GadgetCheckBoxSetChecked(w2a0,false);
  if(w2ac) GadgetCheckBoxSetChecked(w2ac,false);
  if(w2a8) GadgetCheckBoxSetChecked(w2a8,false);
  if(w2b4) { audio->slot91(false); GadgetCheckBoxSetChecked(w2b4,false); }
  if(w2b8) { if(((Rva0007C510*)TheGameLODManager)->ge()==1) GadgetCheckBoxSetChecked(w2b8,true); else GadgetCheckBoxSetChecked(w2b8,false); }
  if(w2e0) { volume=(int)(audio->slot72()->m_defaultMusicVolume*100.0f); wm->slot53(w2e0,0x400d,volume,0); audio->slot50(volume*0.01f); }
  if(w2e4) { volume=(int)(audio->slot72()->m_defaultSoundVolume*100.0f); wm->slot53(w2e4,0x400d,volume,0); audio->slot48(volume*0.01f); }
  if(w2e8) { volume=(int)(audio->slot72()->m_defaultVoiceVolume*100.0f); wm->slot53(w2e8,0x400d,volume,0); audio->slot49(volume*0.01f); }
  if(w2ec) { volume=(int)(audio->slot72()->m_defaultAmbientVolume*100.0f); wm->slot53(w2ec,0x400d,volume,0); audio->slot52(volume*0.01f); }
  if(w2f0) { volume=(int)(audio->slot72()->m_defaultMovieVolume*100.0f); wm->slot53(w2f0,0x400d,volume,0); audio->slot51(volume*0.01f); }
 }
 if(m_page==4) {
  int level=4;
  int particles=3000;
  int reduction=0;
  bool b06=true,b08=true,b04=true,b05=true,b09=true,b22=true,b18=true,b21=true;
  if(lod) {
   level=lod->field16c4;
   if(level<0 || level>=6 || level==5) level=4;
   particles=lod->presets[level].m_maxParticleCount; reduction=lod->presets[level].m_textureReduction;
   b06=lod->presets[level].m_useAnisotropic; b08=lod->presets[level].field08; b04=lod->presets[level].m_useShadowVolumes; b05=lod->presets[level].m_useShadowDecals; b09=lod->presets[level].m_showSoftWaterEdge; b22=lod->presets[level].m_showProps; b18=lod->presets[level].m_useBuildupScaffolds; b21=!lod->presets[level].field21;
  }
  if(w2bc) GadgetCheckBoxSetChecked(w2bc,b06);
  if(w2c0) GadgetCheckBoxSetChecked(w2c0,b08);
  if(w2c4) GadgetCheckBoxSetChecked(w2c4,b04);
  if(w2c8) GadgetCheckBoxSetChecked(w2c8,b05);
  if(w2cc) GadgetCheckBoxSetChecked(w2cc,b09);
  if(w2d0) GadgetCheckBoxSetChecked(w2d0,b22);
  if(w2d4) GadgetCheckBoxSetChecked(w2d4,b18);
  if(w2d8) { if(level==0 || level==1) GadgetCheckBoxSetChecked(w2d8,false); else GadgetCheckBoxSetChecked(w2d8,true); }
  if(w2dc) GadgetCheckBoxSetChecked(w2dc,b21);
  if(w2fc) wm->slot53(w2fc,0x400d,(int)((2-reduction)*50.0f+0.5f),0);
  if(w300) wm->slot53(w300,0x400d,(particles-100)/29,0);
 }
}
