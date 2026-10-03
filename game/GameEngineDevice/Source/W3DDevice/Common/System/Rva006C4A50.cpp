// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims/player
// stlport
#include "Common/Player.h"
#include "Common/Radar.h"
// Retail RVA006C4A50, 1486 bytes. See identity_evidence/006c4a50-radar-draw.md.
// BFME adds a fifth packed-color argument to the ZH draw algorithm.
// All address-qualified views below describe witnessed call ABIs only.
typedef ICoord2D Rva006C4A50Pair;
class W3DRadarResetSurface { void *p; public: ~W3DRadarResetSurface(); void clear(unsigned); };
class W3DRadarResetTexture { void *p; public: W3DRadarResetSurface getSurfaceLevel(); };
int Rva006C0890(int,int);

struct Rva006C4A50Players { char p[12]; Player *local; };
class PlayerList; extern PlayerList *ThePlayerList;

struct Rva006C4A50GlobalRadar { char p[13]; bool forced; };

class Rva006C4A50Display { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual void slot7C();
virtual void slot80();
virtual void slot84();
virtual void slot88(void*);
virtual void slot8C();
virtual void slot90(int);
virtual void slot94();
virtual void slot98();
virtual void slot9C();
virtual void slotA0();
virtual void slotA4();
virtual void slotA8();
virtual void slotAC();
virtual void begin();
virtual void slotB4();
virtual void slotB8();
virtual void slotBC();
virtual void slotC0();
virtual void slotC4();
virtual void slotC8();
virtual void slotCC();
virtual void slotD0();
virtual void image(void*,float,float,float,float,int,int);
virtual void slotD8();
virtual void end();
void fill(float,float,float,float,int); // retail4336F0 float-stack call view
void line(float,float,float,float,float,int); // retail479E00 float-stack call view
__forceinline void draw(void *im,float x,float y,float xx,float yy,int color) {begin(); image(im,x,y,xx,yy,color,2);end();}
};
class Rva006C4A50Client { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual unsigned frame();
};
class Rva006C4A50View { public:
virtual void slot00();
virtual void slot04();
virtual void slot08();
virtual void slot0C();
virtual void slot10();
virtual void slot14();
virtual void slot18();
virtual void slot1C();
virtual void slot20();
virtual void slot24();
virtual void slot28();
virtual void slot2C();
virtual void slot30();
virtual void slot34();
virtual void slot38();
virtual void slot3C();
virtual void slot40();
virtual void slot44();
virtual void slot48();
virtual void slot4C();
virtual void slot50();
virtual void slot54();
virtual void slot58();
virtual void slot5C();
virtual void slot60();
virtual void slot64();
virtual void slot68();
virtual void slot6C();
virtual void slot70();
virtual void slot74();
virtual void slot78();
virtual void slot7C();
virtual void slot80();
virtual void slot84();
virtual void slot88();
virtual void slot8C();
virtual void slot90();
virtual void slot94();
virtual void slot98();
virtual void slot9C();
virtual void slotA0();
virtual void slotA4();
virtual void slotA8();
virtual void slotAC();
virtual void slotB0();
virtual void slotB4();
virtual void slotB8();
virtual void slotBC();
virtual void slotC0();
virtual void slotC4();
virtual void slotC8();
virtual void slotCC();
virtual void slotD0();
virtual void slotD4();
virtual void slotD8();
virtual void slotDC();
virtual void slotE0();
virtual void slotE4();
virtual void slotE8();
virtual void slotEC();
virtual void slotF0();
virtual void slotF4();
virtual void slotF8();
virtual float angle();
virtual void slot100();
virtual void slot104();
virtual void slot108();
virtual void slot10C();
virtual void slot110();
virtual void slot114();
virtual void slot118();
virtual void slot11C();
virtual float zoom();
};
class Display; extern Display *TheDisplay;
class GameClient; extern GameClient *TheGameClient;
class View; extern View *TheTacticalView;
class Rva006C0FA0W3DRadar { public: void method(int,int,int,int,int); };
class Rva006C0C00W3DRadar { public: void reconstructViewBox(); };
class Rva006C4A50Owner {
public:
 void method(int x,int y,int w,int h,int color);
 void renderObjectList(void*,W3DRadarResetTexture*,int); //6C43F0
 void drawEvents(int,int,int,int,int); //6C3170


 template<class T> __forceinline T &at(int n) {return *(T*)((char*)this+n);}
};
void Rva006C4A50Owner::method(int x,int y,int w,int h,int color)
{
 if(!((Rva006C4A50Players*)ThePlayerList)->local->hasRadar() && !((Rva006C4A50GlobalRadar*)TheRadar)->forced) return;
 if(at<bool>(0x1464)) ((Rva006C4A50Display*)TheDisplay)->slot88((char*)this+0x1454);
 Rva006C4A50Pair ul,lr;
 ((Radar*)this)->findDrawPositions(x,y,w,h,&ul,&lr);
 int sw=lr.x-ul.x, sh=lr.y-ul.y;
 if(!at<bool>(0x14dd) && !at<bool>(0x14de)) {
  int fillColor=Rva006C0890(0xff000000,color);
  int lineColor=Rva006C0890(0xff323232,color);
  if((at<float>(0x1448)-at<float>(0x143c))/w >= (at<float>(0x144c)-at<float>(0x1440))/h) {
   ((Rva006C4A50Display*)TheDisplay)->fill(x,y,w,ul.y-y-1,fillColor);
   ((Rva006C4A50Display*)TheDisplay)->fill(x,lr.y+1,w,y+h-lr.y-1,fillColor);
   ((Rva006C4A50Display*)TheDisplay)->line(x,ul.y,x+w,ul.y,1,lineColor);
   ((Rva006C4A50Display*)TheDisplay)->line(x,lr.y+1,x+w,lr.y+1,1,lineColor);
  } else {
   ((Rva006C4A50Display*)TheDisplay)->fill(x,y,ul.x-x-1,h,fillColor);
   ((Rva006C4A50Display*)TheDisplay)->fill(lr.x+1,y,w-(lr.x-x)-1,h,fillColor);
   ((Rva006C4A50Display*)TheDisplay)->line(ul.x,y,ul.x,y+h,1,lineColor);
   ((Rva006C4A50Display*)TheDisplay)->line(lr.x+1,y,lr.x+1,y+h,1,lineColor);
  }
 }
 ((Rva006C4A50Display*)TheDisplay)->draw(at<void*>(0x1474),ul.x,ul.y,lr.x,lr.y,color);
 if(at<bool>(0x146c) || ((Rva006C4A50Client*)TheGameClient)->frame()%6==0) {
  at<W3DRadarResetTexture>(0x1488).getSurfaceLevel().clear(0);
  renderObjectList(at<void*>(0x10),&at<W3DRadarResetTexture>(0x1488),color);
  renderObjectList(at<void*>(0x14),&at<W3DRadarResetTexture>(0x1488),color);
 }
 ((Rva006C4A50Display*)TheDisplay)->draw(at<void*>(0x149c),ul.x,ul.y,lr.x,lr.y,color);
 ((Rva006C4A50Display*)TheDisplay)->draw(at<void*>(0x1484),ul.x,ul.y,lr.x,lr.y,color);
 ((Rva006C4A50Display*)TheDisplay)->draw(at<void*>(0x1490),x,y,x+w,y+h,color);
 drawEvents(ul.x,ul.y,sw,sh,color);
 if(((Rva006C4A50View*)TheTacticalView)->zoom()!=at<float>(0x14e4)) at<bool>(0x14dc)=true;
 if(((Rva006C4A50View*)TheTacticalView)->angle()!=at<float>(0x14e0)) at<bool>(0x14dc)=true;
 if(at<bool>(0x14dc)==true) ((Rva006C0C00W3DRadar*)this)->reconstructViewBox();
 ((Rva006C0FA0W3DRadar*)this)->method(ul.x,ul.y,sw,sh,color);
 if(at<bool>(0x1464)) ((Rva006C4A50Display*)TheDisplay)->slot90(0);
 at<bool>(0x146c)=false;
}
