// ?rva00736b60@W3DTreeBuffer@@QAEXIURva00736B60Coord@@MPBVMatrix3D@@MPBURva00736B60Data@@HABVAsciiString@@3@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/stringinline
// BFME RVA 0x00736B60. Matched BaseHeightMap wrapper 0x006C8950 and
// the retained tree insertion control flow establish W3DTreeBuffer ownership.
// Retail consumes eleven argument words: position by value, scale, matrix
// pointer, random-scale amount, module data, shadow kind and two strings.
// The E8-byte tree record and 5C-byte type record offsets below are witnessed
// by this complete body; address-qualified fields retain unknown identities.
// translateBounds preserves the retail x87 operand order while evaluating
// the selected array elements once.
#include "StringInline.h"
#include "vector3.h"
#include "matrix3d.h"
#include "sphere.h"
struct Rva00736B60Coord { float x,y,z; };
struct Rva00736B60Data {
 unsigned char prefix[8]; AsciiString modelName, nameC;
 unsigned char gap10[0x38]; AsciiString name48;
 unsigned char gap4c[8]; bool flag54;
};
struct Rva00736B60Type {
 void *mesh; Vector3 offset; SphereClass bounds; const void *data;
 unsigned char gap24[0x20]; unsigned char shadow; unsigned char alignment[3];
 AsciiString textureName,modelName,nameC,nameD; int field58;
};
struct Rva00736B60Tree {
 Vector3 location; float scale; Matrix3D transform;
 int treeType; bool visible; unsigned char alignment45[3]; SphereClass bounds;
 unsigned int drawableID; float pushAside; int swayType, firstIndex, bufferIndex;
 unsigned int pushAsideSource; float pushAsideDelta; Vector3 vector74;
 unsigned int lastFrame; int field84; bool flag88; unsigned char gap89[3]; int field8c;
 Matrix3D matrix90; int fieldc0; bool flagc4; unsigned char gapc5[3];
 int fieldc8,typecc,fieldd0,fieldd4,fieldd8,fielddc,fielde0,fielde4;
};
extern float GetGameClientRandomValueReal(float,float,char*,int);
extern int GetGameClientRandomValue(int,int,char*,int);
static inline void translateBounds(Vector3 &center, const Vector3 &position)
{
 center.X=position.X+center.X;
 center.Y=position.Y+center.Y;
 center.Z=position.Z+center.Z;
}
class W3DTreeBuffer {
public:
 int addTreeType(const AsciiString&, const AsciiString&, const void*,int,const AsciiString&,const AsciiString&);
 int rva00736940(const AsciiString&, int,const AsciiString&);
 void rva00736b60(unsigned int,Rva00736B60Coord,float,const Matrix3D*,float,const Rva00736B60Data*,int,const AsciiString&,const AsciiString&);
 unsigned char prefix[0x1b0]; Rva00736B60Tree trees[12000];
 int numTrees; unsigned char gapb4[2]; bool changed,initialized; unsigned char gapb8;
 bool needUpdate; unsigned char gapba[2]; Rva00736B60Type types[64]; int numTypes;
};
void W3DTreeBuffer::rva00736b60(unsigned int id,Rva00736B60Coord location,float scale,
 const Matrix3D *transform,float randomScaleAmount,const Rva00736B60Data *data,
 int shadowKind,const AsciiString &textureName,const AsciiString &nameD)
{
 if(numTrees>=12000) return;
 if(!initialized) return;
 int type=-2;
 for(int i=0;i<numTypes;++i) {
  if(types[i].modelName.compareNoCase(data->modelName)==0 && types[i].nameC.compareNoCase(data->nameC)==0) {type=i;break;}
 }
 if(type<0) {
  type=addTreeType(data->modelName,data->nameC,data,shadowKind,textureName,nameD);
  if(type<0) return;
  needUpdate=true;
 }
 types[type].field58=rva00736940(data->name48,shadowKind,textureName);
 float randomScale=GetGameClientRandomValueReal(1.0f-randomScaleAmount,1.0f+randomScaleAmount,
  "F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x4a9);
 trees[numTrees].transform=*transform;
 if(randomScaleAmount>0.0f) trees[numTrees].scale=scale*randomScale;
 else trees[numTrees].scale=scale;
 trees[numTrees].location=Vector3(location.x,location.y,location.z);
 trees[numTrees].treeType=type;
 trees[numTrees].typecc=type;
 trees[numTrees].fieldd0=types[type].field58;
 trees[numTrees].bounds=types[type].bounds;
 trees[numTrees].bounds.Center*=trees[numTrees].scale;
 trees[numTrees].bounds.Radius*=trees[numTrees].scale;
 translateBounds(trees[numTrees].bounds.Center,trees[numTrees].location);
 trees[numTrees].visible=false;
 trees[numTrees].drawableID=id;
 trees[numTrees].firstIndex=0;
 trees[numTrees].bufferIndex=-1;
 trees[numTrees].swayType=data->flag54?0:GetGameClientRandomValue(1,9,
  "F:\\bfme\\Code\\gameenginedevice\\Source\\W3DDevice\\GameClient\\W3DTreeBuffer.cpp",0x4c5);
 trees[numTrees].pushAside=0;
 trees[numTrees].lastFrame=0;
 trees[numTrees].fieldc8=0;
 trees[numTrees].fielde0=255;
 trees[numTrees].fielde4=255;
 trees[numTrees].flagc4=false;
 trees[numTrees].fieldd8=0;
 trees[numTrees].fielddc=0;
 trees[numTrees].fieldd4=0;
 trees[numTrees].pushAsideSource=0;
 trees[numTrees].pushAsideDelta=0;
 trees[numTrees].vector74.Set(0,0,0);
 trees[numTrees].field84=0;
 trees[numTrees].flag88=false;
 trees[numTrees].field8c=0;
 trees[numTrees].matrix90.Make_Identity();
 trees[numTrees].fieldc0=0;
 ++numTrees;
 changed=true;
}
