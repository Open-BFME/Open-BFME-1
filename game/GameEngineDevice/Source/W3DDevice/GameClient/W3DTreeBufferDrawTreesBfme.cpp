// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DTreeBuffer::drawTrees, retail 0x00737B70..0x007390C1 (5457 bytes).
// The matched terrain caller and tree constructor prove the owner and ABI.
// See targets/game/reverse/identity_evidence/00737b70.md for layout and
// dependencies.

// stlport
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include "matrix3d.h"
#include "vector3.h"
#include "vector4.h"
#include "wwstring.h"
#include <math.h>
#include <string.h>
#include <vector>

class CameraClass;
class RenderObjClass;
template <class T> class RefMultiListIterator;
struct BreezeInfo {
  float direction, x, y, intensity, lean, randomness;
  short period, version;
};
class ScriptEngine {
public:
  bool isTimeFrozenDebug();
  bool _bfme_isClientFrameFrozen();
  bool isDebugFrozen() {
    return isTimeFrozenDebug() || _bfme_isClientFrameFrozen();
  }
  const BreezeInfo &getBreezeInfo() const {
    return *(const BreezeInfo *)((char *)this + 0x17604);
  }
};
class BfmeScriptEngineFreezeExtra {
public:
  unsigned char get() const;
};
extern ScriptEngine *TheScriptEngine;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00367E30Logic;
class BfmeGameLogicPause {
public:
  bool isGamePaused();
};
struct Rva006C9270GlobalData {
  char head[0x18];
  bool flag18;
  char gap19[0xdbc - 0x19];
  bool useOverbright;
};
// Retail's one writable GlobalData global (0x012ED5C8) is declared with EA's
// own type; the field view above is TU-local and cast at each use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
static inline Rva006C9270GlobalData *localGlobalData() {
  return (Rva006C9270GlobalData *)TheWritableGlobalData;
}
struct Rva002EE330Player {
  char head[0x24];
  int field24;
};
struct Rva002EE330PlayerList {
  char head[0xc];
  Rva002EE330Player *field0c;
};
// Retail's global at 0x012ED748 is EA's PlayerList *ThePlayerList, defined in
// game/GameEngine/Source/Common/RTS/PlayerList.cpp; only that TU may define it.
// The field view above is TU-local and cast at each use.
class PlayerList;
extern PlayerList *ThePlayerList;
struct Rva002EEDA0ShroudManager;
class PartitionManager;
extern PartitionManager *ThePartitionManager;
class ShroudManager;
extern ShroudManager *TheShroudManager;

struct Coord3D;
enum ObjectShroudStatus { RvaShroud0, RvaShroud1, RvaShroud2, RvaShroud3 };
class PartitionManager {
public:
  ObjectShroudStatus getPropShroudStatusForPlayer(int, const Coord3D *) const;
};
class GameEngine {
public:
  char head[0x30];
  int field30;
};
extern GameEngine *TheGameEngine;
struct Rva00737B70Shroud {
  char head[0x10];
  float width, height;
  char gap18[8];
  int textureWidth, textureHeight;
  char gap28[4];
  float originX, originY;
};
struct Rva00737B70Map {
  char head[8];
  int field8;
};
class BfmeA1087 {
public:
  char head[0x2ff4];
  Rva00737B70Map *map;
  char gap2ff8[0x30b8 - 0x2ff8];
  Rva00737B70Shroud *shroud;
};
extern BfmeA1087 *g_bfmeA1087;
struct Rva00737B70Coord {
  float x, y, z;
  void set(float px, float py, float pz) {
    x = px;
    y = py;
    z = pz;
  }
};
class BfmeGlobCC0 {
public:
  virtual void v00();
  virtual void v04();
  virtual void v08();
  virtual void v0c();
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual bool v28();
  char gap4[0x2c - 4];
  Rva00737B70Coord field2c;
  char gap38[0xa8 - 0x38];
  int fielda8;
  const Rva00737B70Coord &getField2c() const { return field2c; }
};
extern BfmeGlobCC0 *g_bfmeGlobCC0;
struct Rva00737B70Matrix {
  float m[4][4];
};
extern "C" Rva00737B70Matrix *__stdcall
D3DXMatrixMultiply(Rva00737B70Matrix *, const Rva00737B70Matrix *,
                   const Rva00737B70Matrix *);
extern "C" Rva00737B70Matrix *__stdcall
D3DXMatrixTranspose(Rva00737B70Matrix *, const Rva00737B70Matrix *);
struct Rva012F8048State {
  char head[0x94];
  Rva00737B70Matrix matrix;
  Rva00737B70Coord fieldd4;
  float fielde0;
};
extern Rva012F8048State *Rva012F8048StateInstance;
#define TreeRenderState Rva012F8048StateInstance

struct IDirect3DDevice8;
struct Rva00737B70DeviceVtable {
  char p0[0xb4];
  long(__stdcall *GetTransform)(IDirect3DDevice8 *, unsigned,
                                Rva00737B70Matrix *);
  char p1[0x10c - 0xb8];
  long(__stdcall *SetTextureStageState)(IDirect3DDevice8 *, unsigned, unsigned,
                                        unsigned);
  char p2[0x15c - 0x110];
  long(__stdcall *SetVertexDeclaration)(IDirect3DDevice8 *, unsigned);
  char p3[4];
  long(__stdcall *SetFVF)(IDirect3DDevice8 *, unsigned);
  char p4[8];
  long(__stdcall *SetVertexShader)(IDirect3DDevice8 *, unsigned);
  char p5[4];
  long(__stdcall *SetVertexShaderConstant)(IDirect3DDevice8 *, unsigned,
                                           const void *, unsigned);
  char p6[0x1ac - 0x17c];
  long(__stdcall *SetPixelShader)(IDirect3DDevice8 *, unsigned);
  char p7[4];
  long(__stdcall *SetPixelShaderConstant)(IDirect3DDevice8 *, unsigned,
                                          const void *, unsigned);
};
struct IDirect3DDevice8 {
  Rva00737B70DeviceVtable *v;
};
class TextureBaseClass;
class VertexBufferClass;
class IndexBufferClass;
class ShaderClass {
public:
  unsigned bits;
};
class W3DShaderManager {
public:
  static int setShroudTex(int);
};
extern unsigned number_of_DX8_calls;
extern unsigned BaseHeightMapScorchStageChanges;
extern bool Rva0133F451Snapshot;
extern unsigned Rva01340EC0Shader, Rva0133F49CChanged;
extern ShaderClass Rva012BB14CShader, Rva012BB150Shader;
extern bool g_rva007A2330Flag;
class DX8Wrapper {
  friend class W3DTreeBuffer;
  static IDirect3DDevice8 *D3DDevice;
  static Vector4 Vertex_Shader_Constants[256], Pixel_Shader_Constants[8];
  static unsigned TextureStageStates[8][32];

public:
  static void Set_Shader(const ShaderClass &shader) {
    if (!g_rva007A2330Flag && shader.bits == Rva01340EC0Shader)
      return;
    Rva01340EC0Shader = shader.bits;
    Rva0133F49CChanged |= 0x8000;
    StringClass str;
  }
  static void Get_DX8_Texture_Stage_State_Value_Name(StringClass &,
                                                     unsigned long, unsigned);
  static __forceinline void Set_DX8_Texture_Stage_State(unsigned stage,
                                                        unsigned long state,
                                                        unsigned value) {
    unsigned &current = TextureStageStates[stage][state];
    if (current == value)
      return;
    if (Rva0133F451Snapshot) {
      StringClass name(0, true);
      Get_DX8_Texture_Stage_State_Value_Name(name, state, value);
    }
    current = value;
    D3DDevice->v->SetTextureStageState(D3DDevice, stage, state, value);
    ++number_of_DX8_calls;
    ++BaseHeightMapScorchStageChanges;
  }
  static void Apply_Render_State_Changes();
  static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned);
  static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
  static void Draw_Triangles(unsigned short, unsigned short, unsigned short,
                             unsigned short);
  static void GetTransform(unsigned which, Rva00737B70Matrix &matrix) {
    D3DDevice->v->GetTransform(D3DDevice, which, &matrix);
    ++number_of_DX8_calls;
  }
  static __forceinline void VertexConstant(int reg, const void *data,
                                           int count) {
    void *dst = &Vertex_Shader_Constants[reg];
    if (memcmp(data, dst, count * 16) == 0)
      return;
    memcpy(dst, data, count * 16);
    D3DDevice->v->SetVertexShaderConstant(D3DDevice, reg, data, count);
    ++number_of_DX8_calls;
  }
  static void PixelConstant(int reg, const void *data, int count) {
    void *dst = &Pixel_Shader_Constants[reg];
    if (memcmp(data, dst, count * 16) == 0)
      return;
    memcpy(dst, data, count * 16);
    D3DDevice->v->SetPixelShaderConstant(D3DDevice, reg, data, count);
    ++number_of_DX8_calls;
  }
  static void SetFVF(unsigned shader) {
    D3DDevice->v->SetFVF(D3DDevice, shader);
    ++number_of_DX8_calls;
  }
  static void SetDeclaration(unsigned declaration) {
    D3DDevice->v->SetVertexDeclaration(D3DDevice, declaration);
    ++number_of_DX8_calls;
  }
  static void SetPixelShader(unsigned shader) {
    D3DDevice->v->SetPixelShader(D3DDevice, shader);
    ++number_of_DX8_calls;
  }
};
void BoxSetTexture(unsigned, TextureBaseClass *&);
struct Rva00737B70Data {
  char head[0x40];
  unsigned sinkFrames;
  float sinkDistance;
  char gap48[0x5c - 0x48];
  int field5c;
  int field60;
};
struct Rva00737B70Type {
  char head[0x20];
  const Rva00737B70Data *data;
  char tail[0x5c - 0x24];
};
struct Rva00733580Record {
  Vector3 location;
  char gap0c[0x40 - 0x0c];
  int treeType;
  bool visible;
  char gap45[0x80 - 0x45];
  int toppleState;
  char gap84[0x90 - 0x84];
  Matrix3D matrix;
  int sinkFramesLeft;
  bool sinking;
  char gapc5[3];
  int fieldc8;
  char gapcc[0xe4 - 0xcc];
  int fielde4;
};
class Rva00733580Owner {
public:
  void update(Rva00733580Record *);
};
class W3DTreeBuffer {
public:
  void drawTrees(CameraClass *, RefMultiListIterator<RenderObjClass> *);
  void updateTexture();

protected:
  void updateSway(const BreezeInfo &);

public:
  void rva00734180(const CameraClass *);
  void rva00734790(int);
  void rva00734CB0(void *);
  void rva00734270();
  void *vtable;
  VertexBufferClass *vertex[20];
  IndexBufferClass *index[20];
  unsigned pixelShader, vertexShader, shaderAC, shaderB0, declaration;
  TextureBaseClass *texture1450, *texture1454;
  char gapc0[0x110 - 0xc0];
  int numVertices[20], numIndices[20];
  Rva00733580Record trees[12000];
  int numTrees;
  bool anythingChanged, anyPushChanged, updateAllKeys, initialized,
      isTerrainPass, needTexture;
  char gap2a7cba[2];
  Rva00737B70Type types[64];
  int numTypes;
  char gap2a93c0[12];
  Vector3 swayOffsets[100];
  int swayVersion;
  float swayOffset[10], swayStep[10], swayFactor[10], swayPeriod;
  bool flag391c;
  char gap2a98fd[3];
  int indexStep;
  TextureBaseClass *texture3914;
  int numBuffers;
  bool field2a990c, useSmallBuffers;
};
class Object;
class PartitionFilter {
public:
  PartitionFilter() : m_next(0) {}
  virtual ~PartitionFilter() {}
  virtual bool allow(Object *) = 0;
  virtual int getPlayerMask();
  PartitionFilter *m_next;
};
class Rva00265150RJFilter : public PartitionFilter {
public:
  Rva00265150RJFilter(void *p, void *e, bool m)
      : m_subobject(p), m_extra(e), m_match(m) {}
  virtual ~Rva00265150RJFilter() {}
  virtual bool allow(Object *);
  void *m_subobject, *m_extra;
  bool m_match;
};
struct Rva00737B70Entry {
  Object *object;
  unsigned field4;
};
struct Rva00737B70Result {
  std::vector<Rva00737B70Entry> entries;
  Rva00737B70Entry *current;
  int references;
};
struct BfmeWideResult {
  Rva00737B70Result *value;
  BfmeWideResult();
  BfmeWideResult(const BfmeWideResult &);
  ~BfmeWideResult() {
    if (--value->references == 0)
      delete value;
  }
  Object *next() {
    if (value->current == value->entries.end())
      return 0;
    return (value->current++)->object;
  }
};
class BfmeWideForwardC {
public:
  BfmeWideResult bfmeForwardWideC(int, int, int, int, int);
};

class Team;
enum Relationship { RvaRelation0, RvaRelation1, RvaRelation2 };
class Player {
public:
  Relationship getRelationship(const Team *) const;
  char head[0x230];
  Team *field230;
};
class Object {
public:
  Player *getControllingPlayer() const;
  char head[0x90];
  unsigned field90;
  char gap94[0x344 - 0x94];
  unsigned field344;
};
// BaseType's fast_float2long_round is the witnessed two-instruction x87 helper:
// the already rounded floor result uses FISTP rather than the compiler's
// __ftol2.
inline int treeRound(float value) {
  int result;
  __asm {
 fld value
 fistp result
  }
  return result;
}
void W3DTreeBuffer::drawTrees(CameraClass *camera,
                              RefMultiListIterator<RenderObjClass> *lights) {
  if (!isTerrainPass)
    return;
  flag391c = false;
  const BreezeInfo &info = TheScriptEngine->getBreezeInfo();
  bool pause = ((BfmeScriptEngineFreezeExtra *)TheScriptEngine)->get() ||
               TheScriptEngine->isDebugFrozen();
  if (TheGameLogic &&
      ((BfmeGameLogicPause *)TheGameLogic)->isGamePaused())
    pause = true;
  static Rva00265150RJFilter filter((char *)TheWritableGlobalData + 0xedc, 0,
                                    true);
  if (!pause && info.version != swayVersion)
    updateSway(info);
  Vector3 sway[10];
  int i;
  for (i = 0; i < 10; ++i) {
    if (!pause) {
      swayOffset[i] += swayStep[i];
      if (swayOffset[i] > 99)
        swayOffset[i] -= 99;
    }
    int minOffset = treeRound((float)floor(swayOffset[i]));
    if (minOffset >= 0 && minOffset + 1 < 100) {
      float f2 = swayOffset[i] - minOffset;
      float f1 = 1.0f - f2;
      sway[i] = f1 * swayOffsets[minOffset] + f2 * swayOffsets[minOffset + 1];
      sway[i] *= swayFactor[i];
    }
  }
  isTerrainPass = false;
  if (needTexture) {
    needTexture = false;
    updateTexture();
  }
  if (!texture1450)
    return;
  if (updateAllKeys)
    rva00734180(camera);
  for (int curTree = 0; curTree < numTrees; curTree += indexStep) {
    if (pause)
      break;
    int type = trees[curTree].treeType;
    if (type < 0)
      continue;
    if (trees[curTree].fieldc8) {
      if (TheGameEngine->field30 == 1)
        rva00734790(curTree);
    } else {
      if (trees[curTree].toppleState == 1 || trees[curTree].toppleState == 2)
        ((Rva00733580Owner *)this)->update(&trees[curTree]);
      else if (trees[curTree].toppleState == 3 && trees[curTree].sinking) {
        if (trees[curTree].sinkFramesLeft == 0) {
          trees[curTree].treeType = -2;
          anythingChanged = true;
        }
        --trees[curTree].sinkFramesLeft;
        float sinkFrames = (float)types[type].data->sinkFrames;
        trees[curTree].location.Z -=
            types[type].data->sinkDistance / sinkFrames;
        trees[curTree].matrix.Set_Translation(trees[curTree].location);
      }
      if (trees[curTree].visible && !useSmallBuffers && (*reinterpret_cast<BfmeWideForwardC **>(&ThePartitionManager)) &&
          TheGameEngine->field30 == 1) {
        Rva00737B70Coord position;
        position.set(trees[curTree].location.X, trees[curTree].location.Y,
                     trees[curTree].location.Z);
        BfmeWideResult result = (*reinterpret_cast<BfmeWideForwardC **>(&ThePartitionManager))->bfmeForwardWideC(
            (int)&position, types[type].data->field60, 1, (int)&filter, 0);
        Object *object;
        while ((object = result.next()) != 0) {
          if (!object->getControllingPlayer() || (object->field344 & 1))
            continue;
          if ((object->field90 & 0x8000) && !(object->field90 & 0x20000)) {
            if (((Player *)((Rva002EE330PlayerList *)ThePlayerList)->field0c)
                    ->getRelationship(
                        object->getControllingPlayer()->field230) != 2)
              continue;
          }
          break;
        }
        if (object) {
          if (trees[curTree].fielde4 != types[type].data->field5c) {
            trees[curTree].fielde4 = types[type].data->field5c;
            field2a990c = true;
          }
        } else if (trees[curTree].fielde4 != 255) {
          trees[curTree].fielde4 = 255;
          field2a990c = true;
        }
      }
    }
  }
  if (anythingChanged) {
    flag391c = true;
    rva00734CB0(lights);
    anythingChanged = false;
  } else if (anyPushChanged || field2a990c) {
    anyPushChanged = false;
    field2a990c = false;
    rva00734270();
  }
  if (!numIndices[0])
    return;
  if (useSmallBuffers)
    DX8Wrapper::Set_Shader(Rva012BB14CShader);
  else
    DX8Wrapper::Set_Shader(Rva012BB150Shader);
  BoxSetTexture(0, texture1450);
  DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0);
  DX8Wrapper::Set_DX8_Texture_Stage_State(1, 11, 1);
  DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 1);
  DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 1);
  DX8Wrapper::Apply_Render_State_Changes();
  if (W3DShaderManager::setShroudTex(1)) {
    DX8Wrapper::Set_DX8_Texture_Stage_State(1, 5, 2);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1, 6, 1);
    DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 4);
  } else
    BoxSetTexture(1, texture3914);
  DX8Wrapper::Apply_Render_State_Changes();
  if (vertexShader) {
    Rva00737B70Matrix matProj, matView, matWorld, mat;
    DX8Wrapper::GetTransform(256, matWorld);
    DX8Wrapper::GetTransform(2, matView);
    DX8Wrapper::GetTransform(3, matProj);
    D3DXMatrixMultiply(&mat, &matView, &matProj);
    D3DXMatrixMultiply(&mat, &matWorld, &mat);
    D3DXMatrixTranspose(&mat, &mat);
    DX8Wrapper::VertexConstant(4, &mat, 4);
    Vector4 noSway(0, 0, 0, 0);
    DX8Wrapper::VertexConstant(8, &noSway, 1);
    for (i = 0; i < 10; ++i) {
      Vector4 sway4(sway[i].X, sway[i].Y, sway[i].Z, 0);
      DX8Wrapper::VertexConstant(9 + i, &sway4, 1);
    }
    Rva00737B70Shroud *shroud = g_bfmeA1087->shroud;
    if (shroud) {
      float width = shroud->width, height = shroud->height;
      Vector4 offset(width - shroud->originX, height - shroud->originY, 0, 0);
      DX8Wrapper::VertexConstant(32, &offset, 1);
      width = 1.0f / (width * shroud->textureWidth);
      height = 1.0f / (height * shroud->textureHeight);
      offset.Set(width, height, 1, 1);
      DX8Wrapper::VertexConstant(33, &offset, 1);
    } else {
      Vector4 offset(0, 0, 0, 0);
      DX8Wrapper::VertexConstant(32, &offset, 1);
      DX8Wrapper::VertexConstant(33, &offset, 1);
    }
    DX8Wrapper::SetDeclaration(declaration);

    float overbright = 0.5f;
    if (TheWritableGlobalData && localGlobalData()->useOverbright)
      overbright = 1;
    DX8Wrapper::PixelConstant(1, &Vector4(overbright, overbright, overbright, overbright), 1);
    if (pixelShader) {
      IDirect3DDevice8 *device = DX8Wrapper::D3DDevice;
      device->v->SetPixelShader(device, pixelShader);
      ++number_of_DX8_calls;
    }
    if (g_bfmeGlobCC0 && g_bfmeGlobCC0->v28()) {
      int kind = g_bfmeGlobCC0->fielda8;
      if ((kind == 1 || kind == 2) && shaderAC) {
        Rva00737B70Matrix matrix = TreeRenderState->matrix;
        D3DXMatrixTranspose(&matrix, &matrix);
        DX8Wrapper::VertexConstant(34, &matrix, 4);
        float v = g_bfmeA1087->map->field8 * 5.0f - 20.0f;
        DX8Wrapper::VertexConstant(38, &Vector4(v, v, v, v), 1);
        Rva00737B70Coord vec = g_bfmeGlobCC0->getField2c();
        Vector4 factor(vec.x, 1.0f - vec.x, 0, 0);
        DX8Wrapper::VertexConstant(39, &factor, 1);
        Vector4 values(20, 1, 1, 0);
        DX8Wrapper::VertexConstant(40, &values, 1);
      } else if ((kind == 3 || kind == 4) && shaderB0) {
        Rva00737B70Coord vec = g_bfmeGlobCC0->getField2c();
        Vector4 factor(vec.x, 1.0f - vec.x, 0, 0);
        DX8Wrapper::VertexConstant(39, &factor, 1);
        Rva00737B70Coord pos = TreeRenderState->fieldd4;
        float value = TreeRenderState->fielde0;
        Vector4 position(pos.x, pos.y, pos.z, 1);
        DX8Wrapper::VertexConstant(34, &position, 1);
        DX8Wrapper::VertexConstant(35, &Vector4(value, 0, 0, 0), 1);
        Vector4 values(20, 1, 1, 0);
        DX8Wrapper::VertexConstant(40, &values, 1);
      }
    }
  } else
    DX8Wrapper::SetFVF(0x152);
  for (int b = 0; b < numBuffers; ++b) {
    if (!numIndices[b])
      break;
    DX8Wrapper::Set_Index_Buffer(index[b], 0);
    DX8Wrapper::Set_Vertex_Buffer(vertex[b], 0);
    DX8Wrapper::Apply_Render_State_Changes();
    if (vertexShader) {
      if (g_bfmeGlobCC0 && g_bfmeGlobCC0->v28()) {
        int kind = g_bfmeGlobCC0->fielda8;
        if ((kind == 1 || kind == 2) && shaderAC)
          DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice,
                                                    shaderAC);
        else if ((kind == 3 || kind == 4) && shaderB0)
          DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice,
                                                    shaderB0);
        else
          DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice,
                                                    vertexShader);
      } else
        DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice,
                                                  vertexShader);
      DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 0,
                                                     11, 0);
      DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 1,
                                                     11, 1);
      DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 1,
                                                     24, 0);
    }
    DX8Wrapper::Draw_Triangles(0, numIndices[b] / 3, 0, numVertices[b]);
  }
  DX8Wrapper::SetFVF(0x152);
  DX8Wrapper::SetPixelShader(0);
}
