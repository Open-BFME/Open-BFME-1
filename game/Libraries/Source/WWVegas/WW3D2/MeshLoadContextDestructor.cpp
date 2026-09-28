// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep /Iinputs/toolchains/dx81/include
// Complete retail MeshLoadContextClass destructor at 0x0096FD30.
// The old 61-byte extent stops inside mov eax,[esi+0xd4]. Its true RET
// is at 0x0096FF4F, directly before the proven deleting-destructor entry.
// BFME vector offsets 94/AC/C4/DC/F4 are independently used by the landed
// Add_Legacy_Material and read_v3_materials bodies. Textures are owning
// BfmeHandleCX values, so their array destructor releases them automatically.
void __cdecl operator delete(void *) throw();
void __cdecl operator delete[](void *) throw();
#include "wwstring.h"
#include "shader.h"
#include "vector.h"
#include "simplevec.h"
#include "vector2.h"
#include "vertmaterial.h"

class BfmeHandleCX
{
public:
 BfmeHandleCX() : p(0) {}
 ~BfmeHandleCX();
 bool operator==(const BfmeHandleCX &other) const { return p == other.p; }
 bool operator!=(const BfmeHandleCX &other) const { return p != other.p; }
 void *p;
};
// Existing complete destructor at 0x0092A3D0; its surrounding member
// occupies 0xf4 bytes in this retail owner (next member starts at +0x200).
class BfmeHolderBY
{
public:
 ~BfmeHolderBY();
 unsigned char m_storage[0xf4];
};
struct Rva0096E1B0Elem : public Vector2 {};

class MeshLoadContextClass
{
 struct LegacyMaterialClass
 {
  StringClass Name;
  int VertexMaterialIdx, ShaderIdx, TextureIdx;
 };
 unsigned char m_prefix[0x74];
 void *TexCoords;
 unsigned char m_gap78[0x1c];
 DynamicVectorClass<LegacyMaterialClass *> LegacyMaterials;
 DynamicVectorClass<ShaderClass> Shaders;
 DynamicVectorClass<VertexMaterialClass *> VertexMaterials;
 DynamicVectorClass<unsigned long> VertexMaterialCrcs;
 DynamicVectorClass<BfmeHandleCX> Textures;
 BfmeHolderBY AlternateMatDesc;
 SimpleVecClass<Rva0096E1B0Elem> TempUVArray;
 bool LoadedDIG;
 ~MeshLoadContextClass();
};

MeshLoadContextClass::~MeshLoadContextClass()
{
 int i;
 if (TexCoords) {
  ::operator delete(TexCoords);
  TexCoords = 0;
 }
 for (i=0; i<VertexMaterials.Count(); ++i)
  VertexMaterials[i]->Release_Ref();
 for (i=0; i<LegacyMaterials.Count(); ++i)
  delete LegacyMaterials[i];
}
