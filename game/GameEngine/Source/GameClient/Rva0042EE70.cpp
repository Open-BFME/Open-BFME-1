// ?Rva0042EE70@@YAHH_N@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
void setFPMode();
#define SLOT(n) virtual void slot##n();
class GameEngine { public: SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) virtual void serviceWindowsOS(); };
class GameWindowManager { public: SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) virtual void update(); };
class Display { public: SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) virtual void update(); unsigned char pad04[0x10c]; bool field110; void bfmeStopMovie(); };
class BfmeThingVMZ {public: void bfmeGo2VMZ(int,int,int,int,int,int);};
class BfmeThingE170 {public: void bfmeGo3E170(int,int,int,int,int,int,int);};
class Image;
class ImageCollection {public: const Image *findImageByName(const AsciiString &);};
class GameWindowTransitionsHandler { public: SLOT(0) SLOT(1) SLOT(2) SLOT(3) virtual void reset(); void reverse(AsciiString); void setGroup(AsciiString,bool); };
class Rva0048B0E0TransitionHandler {public: void update();};
#undef SLOT
extern GameEngine *TheGameEngine;
extern GameWindowManager *TheWindowManager;
extern Display *TheDisplay;
extern ImageCollection *TheMappedImageCollection;
// Retail's singleton at 0x012F3330 is defined once, as
// `GameWindowTransitionsHandler *TheTransitionHandler`, by
// game/GameEngine/Source/GameClient/GUI/GameWindowTransitions.cpp:66, so this
// TU must spell the global with that class name; the second view of the same
// pointer (Rva0048B0E0TransitionHandler) is cast at each use.
extern GameWindowTransitionsHandler *TheTransitionHandler;
// Retail's global at 0x012ED5C8 is EA's `GlobalData *TheWritableGlobalData`,
// defined once in Common/GlobalData.cpp.  Rva0042EE70Flags below is this TU's
// view of the pointee, so the canonical global is forward declared and the cast
// at each use is the whole translation.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva0042EE70Flags {unsigned char pad000[0xbb4]; bool fieldbb4; unsigned char padbb5[3]; bool fieldbb8; unsigned char padbb9[0x206]; bool fielddbf;};
int Rva0042EE70(int, bool start) {
 TheGameEngine->serviceWindowsOS();
 if (start) {
 ((Rva0042EE70Flags *)TheWritableGlobalData)->fielddbf=false;
 ((Rva0042EE70Flags *)TheWritableGlobalData)->fieldbb8=true;
 ((Rva0042EE70Flags *)TheWritableGlobalData)->fielddbf=false;
 AsciiString imageName("TitleScreenLogo");
 const Image *image=TheMappedImageCollection->findImageByName(imageName);
 if (image) {
  ((BfmeThingVMZ *)TheDisplay)->bfmeGo2VMZ((int)image,2,0,0,0x3f800000,0x3f800000);
  ((GameWindowTransitionsHandler *)TheTransitionHandler)->reverse(AsciiString("FadeInGameMovie"));
  ((Rva0048B0E0TransitionHandler *)TheTransitionHandler)->update();
  unsigned long (__stdcall *const clock)()=timeGetTime;
  unsigned long startTime=clock();
 unsigned long end=startTime+5000;
  while (end>clock()) {
   TheGameEngine->serviceWindowsOS();
   TheWindowManager->update();
   TheDisplay->update();
   Sleep(100);
  }
  setFPMode();
  TheDisplay->field110=true;
  ((GameWindowTransitionsHandler *)TheTransitionHandler)->reset();
  if (((Rva0042EE70Flags *)TheWritableGlobalData)->fieldbb4) {
   TheDisplay->bfmeStopMovie();
   ((BfmeThingE170 *)TheDisplay)->bfmeGo3E170((int)image,0,0,0x3f800000,0x3f800000,10,45);
  } else {
   ((GameWindowTransitionsHandler *)TheTransitionHandler)->setGroup(AsciiString("FadeInGameMovie"),false);
   ((Rva0048B0E0TransitionHandler *)TheTransitionHandler)->update();
   TheDisplay->bfmeStopMovie();
  }
 }
 ((Rva0042EE70Flags *)TheWritableGlobalData)->fielddbf=false;
 return 1;
 }
 return 6;
}
