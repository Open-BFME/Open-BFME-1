// Retail RVA 0x0059A3D0 (523 bytes). No receiver or arguments are read.
// The literal apt_spellstore_%d.%s proves the behavior; no authentic function
// name is known. The extension table at VA 0x0110C5F8 is {dds,tga}.
// Asset-list layout and native pointer-set ABI follow AssetListOperatorInsert.cpp.
// The increment is inside the scope: retail advances it before both RAII cleanups.
// stlport
// cl: /Igame/Libraries/Source/WWVegas/WWLib
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include "ascii_string.h"
static __forceinline const char *textureName0059A3D0(const AsciiString &s) { const char *p=*(const char *const *)&s; return p?p+8:""; }
class FileSystem { public: bool doesFileExist(const char *) const; };
extern FileSystem *TheFileSystem;
class BFMEWaterTrackTexture { public: void Release_Ref(); };
class BFMEWaterTrackTextureHandle {
public:
 BFMEWaterTrackTexture *m_texture;
 ~BFMEWaterTrackTextureHandle() { if(m_texture) m_texture->Release_Ref(); }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *,int,int);
class ShroudFilter { public: char pad[12]; int field_c,field_10; };
class ShroudTexture { public: ShroudFilter *getFilter(); };
class Gen_0090E810 { public: void bfmeSetFlag(unsigned char); };
struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key,_STL::less<Rva001408C0Key>,_STL::allocator<Rva001408C0Key> > AssetSet0059A3D0;
void *bfmeGoEMEb(void *);
class AssetList0059A3D0 {
public:
 AssetList0059A3D0():field_c(0),changed(true) {}
 void insert(const AsciiString &name) {
  if(prototypes.insert((Rva001408C0Target*)bfmeGoEMEb((void*)textureName0059A3D0(name))).second) changed=true;
 }
 AssetSet0059A3D0 prototypes;
 unsigned field_c;
 bool changed;
};
void Rva009EBAC0(int);
extern void *AssetSubsystem0059A3D0;
static const char *TextureExtensions0059A3D0[2] = { "dds", "tga" };
void preloadSpellTextures0059A3D0()
{
 if(!TheFileSystem) return;
 for(int index=1;;) {
  AsciiString name;
  unsigned ext;
  for(ext=0;ext<2;++ext) {
   name.format("apt_spellstore_%d.%s",index,TextureExtensions0059A3D0[ext]);
   if(TheFileSystem->doesFileExist(textureName0059A3D0(AsciiString("art/textures/")+name))) break;
  }
  if(ext>=2) return;
  BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture((char*)textureName0059A3D0(name),1,0);
  ((ShroudTexture*)&texture)->getFilter()->field_10=1;
  ((ShroudTexture*)&texture)->getFilter()->field_c=1;
  ((Gen_0090E810*)&texture)->bfmeSetFlag(1);
  if(AssetSubsystem0059A3D0) {
   AssetList0059A3D0 assets;
   assets.insert(name);
   Rva009EBAC0((int)&assets);
  }
  ++index;
 }
}
