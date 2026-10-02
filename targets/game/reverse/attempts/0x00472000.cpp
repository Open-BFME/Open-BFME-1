// ?m@Rva00472000@@QAEXXZ
// partial score=1.0 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/AsciiString.h"
#include "GameClient/Display.h"
class FontLibraryBFMERetail {public: GameFont *getFont(AsciiString*,float,unsigned char); };
#include "GameClient/Anim2D.h"
#include <new>
// The canonical Anim2D prefix omits the two cached Int tail fields which
// the independently matched native constructor writes at +0x2c/+0x30.
// Retail allocates 0x34 bytes. Keep its native constructor ABI and reserve
// that full storage, including delete-on-construction-failure semantics.
inline void *operator new(size_t, unsigned extent) {return ::operator new(extent);}
__forceinline void operator delete(void *p, unsigned) throw() {::operator delete(p);}
extern "C" const float g_Rva00CF7608;
// Retail 0x00472000/387B: vtable 0x010F760C slot1, installed by
// matched constructor 0x00471EC0. Source owner remains address-derived.
// Its 0x004721F0 sibling independently witnesses the cache and phase fields.
class Rva00472000 {public:
 void m();
 void *vptr; GameFont *font04; char p08[0x14]; Anim2D *animation1c;
 float scale20; AsciiString name24; unsigned p28,p2c,size30;
 int start34,start38,start3c,end40,end44,end48,width4c,height50;
};
void Rva00472000::m()
{
 float width=(float)TheDisplay->getWidth();
 float scale=width/800.0f;
 scale*=g_Rva00CF7608;
 if(scale!=scale20) {font04=0;scale20=scale;}
 if(!font04) font04=((FontLibraryBFMERetail*)TheFontLibrary)->getFont(&name24,(float)size30*scale,0);
 if(!animation1c) {
  animation1c=::new (0x34u) Anim2D(TheAnim2DCollection->findTemplate(AsciiString("TextElvenClouds")),TheAnim2DCollection);
  end48=-1;end40=-1;start38=0;end44=30;start3c=31;start34=46;
 }
 width4c=(int)width;
 height50=(int)((float)animation1c->getCurrentFrameHeight()*scale);
}
