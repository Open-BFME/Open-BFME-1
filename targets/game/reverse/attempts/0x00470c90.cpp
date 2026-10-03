// ?draw@Rva00470C90@@QAEXPAVText00470C90@@PBUICoord2D@@I@Z
// partial score=1.0 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/INI.h"
#include "Common/SubsystemInterface.h"
#include "GameClient/Anim2D.h"




class Text00470C90 {
public:
 virtual void slot00();
 virtual void slot04();
 virtual UnicodeString getText();
 virtual void slot0c();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1c();
 virtual void slot20();
 virtual void slot24();
 virtual void colors(unsigned, unsigned);
 virtual void slot2c();
 virtual void slot30();
 virtual void slot34();
 virtual void draw(int,int,int,int);
 virtual void size(int*,int*);
};
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short>*)this)->releaseBuffer(); }
template<> inline unsigned short StringBase<unsigned short>::getCharAt(int index) const {
 if (m_data) return m_data->data[index];
 return 0;
}
class Rva005BA9E0Anim2D {public: void draw(int,int,int,int);};

class Image;
class Display;
class Rva0040D900 {public: void method(const Image*,float,float,float,float,int,int);};

extern Display *TheDisplay;
class Rva00470C90 {public:
 void draw(Text00470C90*,const ICoord2D*,unsigned);
 char field00[8];int field08,field0c,field10,field14;unsigned field18;
 std::vector<const Image*> field1c;
 std::vector<Anim2D*> field28;
 Anim2D *field34;
 char field38[8];unsigned field40;char field44[8];
 unsigned field4c[5],field60[5];int field74,field78;
};
// BANK ONLY: complete972B five-phase fade render, actual3arg/RET12 ABI.
// Raw retail code470C90..471045, three-byte LEA alignment471045..1048,
// five-entry absolute switch table471048..105C; CC begins47105C.
// Native STLport vector access and split alpha/integer conversion locals made
// the complete parent exact modulo34 relocations. Full binding/EH gate pending.
// Uses canonical Anim2D and ICoord2D plus existing BFME StringBase Unicode shim.
// Direct setter168E7->5BA1D0 RET4 reads16-bit frame; draw30DB9->5BAAB0.
// Image wrapper0000A114->0040D900 has beginB0, seven-word drawD4, endDC,
// RET1C. Caller explicitly converts four integer coordinates to float. Pending
// lead decision: add pin for Rva0040D900::method as opaque ABI view; existing
// float Display pin and seven-int Bfme5Host body are not canonical declarations.
// The callback interface remains address-qualified: slots8 getText/sret,
// 28 two words,38 four words,3C two out pointers; no DisplayString identity claim.
// EA filename evidence FadeInTextRender.cpp; full owner/slot name not claimed.
// Experiments: initial976B/485dif; separate image+alpha locals972B/74dif;
// native vectors14dif; split converted values exact972B. Reusing width output
// local996B/692dif; bit-casting to old seven-int wrapper1008B/405dif. ZH
// UnicodeString's four-byte data prefix is wrong here; BFME reads data+8.
void Rva00470C90::draw(Text00470C90* text,const ICoord2D* pos,unsigned frame) {
 int w,h;
 text->size(&w,&h);
 UnicodeString s=text->getText();
 unsigned imageIndex=(unsigned short)s.getCharAt(0) % field1c.size();
 int y=pos->y-(field78-h)/2;
 int x=pos->x-field74/2;
 int width=field74*2;
 int right=x+width;
 int bottom=y+field78;
 if(field08>x)field08=x;
 if(field10<right)field10=right;
 if(field0c>y)field0c=y;
 if(field14<bottom)field14=bottom;
 for(int i=0;i<5;++i) {
  unsigned start=field4c[i],end=field60[i];
  if(frame>=start && frame<=end) {
   float progress=float(frame-start)/float(end-start);
   switch(i) {
   case 0: {
    unsigned frames=field34->getAnimTemplate()->getNumFrames();
    if(frames) {
     ((Anim2D*)field34)->setCurrentFrame(((frame-start)/4)%frames);
     unsigned color=field18;
     field34->setAlpha(float(color>>24)/255.0f);
     ((Rva005BA9E0Anim2D*)field34)->draw(x-width/2,y,width*2,field78);
     ((Rva005BA9E0Anim2D*)field34)->draw(x-width/2,y,width*2,field78);
    }
    break;
   }
   case 1: {
    int alpha=(int)((1.0f<progress ? 1.0f:progress)*255.0f);
    text->colors(field40|(alpha<<24),alpha);
    text->draw(pos->x,pos->y,1,1);
    const Image* image=field1c[imageIndex];
    alpha=255-alpha;
    unsigned imageColor=alpha<<24;
    imageColor |= 0xffffff;
    ((Rva0040D900*)TheDisplay)->method(image,float(x),float(y),float(right),float(y+field78),imageColor,2);
    break;
   }
   case 2:
    text->colors(field40|field18,field18);
    text->draw(pos->x,pos->y,1,1);break;
   case 3: {
    const Image* image=field1c[imageIndex];
    unsigned alpha=(unsigned)(int)((1.0f<progress?1.0f:progress)*255.0f)<<24;
    ((Rva0040D900*)TheDisplay)->method(image,float(x),float(y),float(right),float(y+field78),alpha|0xffffff,2);
    break;
   }
   case 4: {
    Anim2D* anim=field28[imageIndex];
    unsigned frames=anim->getAnimTemplate()->getNumFrames();
    if(frames) {
     float selected=float(frames)*progress;
     float last=float(frames-1);
     int selectedFrame=(int)(selected<last?selected:last);
     ((Anim2D*)anim)->setCurrentFrame(selectedFrame);
     anim->setAlpha(1.0f);
     ((Rva005BA9E0Anim2D*)anim)->draw(x,y,width,field78);
    }
    break;
   }
   }
  }
 }
}
