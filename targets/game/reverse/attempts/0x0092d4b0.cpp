// ?apply@Rva0092D4B0@@QAEXHPBD@Z
// partial score=0.992 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
#include "shader.h"
extern "C" {
__declspec(dllimport) char* __cdecl strchr(const char*,int);
__declspec(dllimport) int __cdecl _strcmpi(const char*,const char*);
__declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
__declspec(dllimport) char* __cdecl _strlwr(char*);
}
class BFMEWaterTrackTexture { public: void Release_Ref(); char field00[8]; int field08; };
struct BfmeHandleUZA {
 BFMEWaterTrackTexture* ptr;
 ~BfmeHandleUZA() { if(ptr) ptr->Release_Ref(); }
};
class BFMEWaterTrackTextureHandle {
public:
 BFMEWaterTrackTexture* ptr;
 ~BFMEWaterTrackTextureHandle() { if(ptr) ptr->Release_Ref(); }
};
class BfmeThingAUZA { public: BfmeHandleUZA bfmeGoAUZA(int,int) const; };
class BfmeTexVGS;
class BfmeMeshVGT { public: void bfmeSetVGT(BfmeTexVGS**,int,int);
 void setTexture(const BFMEWaterTrackTextureHandle& t) { bfmeSetVGT((BfmeTexVGS**)&t.ptr,0,1); } };
class MeshMatDescClass { public: void Set_Single_Shader(ShaderClass,int); char field00[0x94]; unsigned field94; };
struct Rva0092D4B0Model {
 virtual void slot00();
 int refs;
 char field08[0x94];
 MeshMatDescClass* field9C;
};
void* PeekHashMapValue008FF850(int);
void bfmeRegisterCY(const char*,int,int);
bool Render_Obj_Exists(const char*);
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class Rva0092D4B0 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0C(); virtual void slot10(); virtual void slot14();
 virtual const char* slot18();
 char field04[0xc4];
 Rva0092D4B0Model* fieldC8;
 void apply(int,const char*);
};
void Rva0092D4B0::apply(int id,const char* excluded)
{
 const char* name=slot18();
 if(name) {
  const char* suffix=strchr(name,'.');
  if(suffix) {
   ++suffix;
   if(!excluded || _strcmpi(suffix,excluded)) {
    Rva0092D4B0Model* model=fieldC8;
    if(model) ++model->refs;
    model=fieldC8;
    BfmeHandleUZA texture=((BfmeThingAUZA*)model)->bfmeGoAUZA(0,0);
    const char* mapped=(const char*)PeekHashMapValue008FF850(texture.ptr ? texture.ptr->field08 : -1);
    if(mapped) {
     char buffer[256];
     sprintf(buffer,"#%d#%s",id,mapped);
     _strlwr(buffer);
     if(!Render_Obj_Exists(buffer)) bfmeRegisterCY(mapped,(int)buffer,id);
     unsigned bits=model->field9C->field94;
     ((BfmeMeshVGT*)model->field9C)->setTexture(BFMEGetWaterTrackTexture(buffer,0,0));
     bits=(bits&0xffbfffff)|0x1a00000;
     model->field9C->Set_Single_Shader(ShaderClass(bits),0);
    }
    if(model && --model->refs==0) model->slot00();
   }
  }
 }
}
