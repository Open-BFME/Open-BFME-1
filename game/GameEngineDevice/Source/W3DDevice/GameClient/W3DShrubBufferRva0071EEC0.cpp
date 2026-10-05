// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// Full retail body 0x0071EEC0..0x0071FEE3, including the final RET 8.
// The original dump ended 19 bytes before the return. The constructor layout,
// terrain caller and directly matched shrub methods prove the owner; the BFME
// public method spelling remains unknown. See targets/game/reverse/identity_evidence/0071eec0.md.
// Native WWMath types and POD address-derived coordinate views preserve the
// observed copies. Shader cache methods mirror dx8wrapper.h.

#include "matrix3d.h"
#include "vector3.h"
#include "vector4.h"
#include <math.h>
#include <string.h>

class CameraClass;
class RenderObjClass;
template <class T> class RefMultiListIterator;
struct BreezeInfo
{
	float direction, x, y, intensity, lean, randomness;
	short period, version;
};
class ScriptEngine
{
  public:
	bool isTimeFrozenDebug();
	bool _bfme_isClientFrameFrozen();
	bool isDebugFrozen()
	{
		return isTimeFrozenDebug() || _bfme_isClientFrameFrozen();
	}
	const BreezeInfo &getBreezeInfo() const
	{
		return *(const BreezeInfo *)((char *)this + 0x17604);
	}
};
class BfmeScriptEngineFreezeExtra
{
  public:
	unsigned char get() const;
};
extern ScriptEngine *TheScriptEngine;
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00367E30Logic;
class BfmeGameLogicPause
{
  public:
	bool isGamePaused();
};
struct Rva006C9270GlobalData
{
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
struct Rva002EE330Player
{
	char head[0x24];
	int field24;
};
struct Rva002EE330PlayerList
{
	char head[0xc];
	Rva002EE330Player *field0c;
};
// Retail's global at 0x012ED748 is EA's PlayerList *ThePlayerList, defined in
// game/GameEngine/Source/Common/RTS/PlayerList.cpp; only that TU may define it.
// The field view above is TU-local and cast at each use.
class PlayerList;
extern PlayerList *ThePlayerList;
struct Rva002EEDA0ShroudManager;
class ShroudManager;
extern ShroudManager *TheShroudManager;

struct Coord3D;
enum ObjectShroudStatus
{
	RvaShroud0,
	RvaShroud1,
	RvaShroud2,
	RvaShroud3
};
class PartitionManager
{
  public:
	ObjectShroudStatus getPropShroudStatusForPlayer(int, const Coord3D *) const;
};
class GameEngine
{
  public:
	char head[0x30];
	int field30;
};
extern GameEngine *TheGameEngine;
struct Rva0071EEC0Shroud
{
	char head[0x10];
	float width, height;
	char gap18[8];
	int textureWidth, textureHeight;
	char gap28[4];
	float originX, originY;
};
struct Rva0071EEC0Map
{
	char head[8];
	int field8;
};
class BfmeA1087
{
  public:
	char head[0x2ff4];
	Rva0071EEC0Map *map;
	char gap2ff8[0x30b8 - 0x2ff8];
	Rva0071EEC0Shroud *shroud;
};
extern BfmeA1087 *g_bfmeA1087;
struct Rva0071EEC0Coord
{
	float x, y, z;
};
class BfmeGlobCC0
{
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
	Rva0071EEC0Coord field2c;
	char gap38[0xa8 - 0x38];
	int fielda8;
	const Rva0071EEC0Coord &getField2c() const
	{
		return field2c;
	}
};
extern BfmeGlobCC0 *g_bfmeGlobCC0;
struct Rva0071EEC0Matrix
{
	float m[4][4];
};
extern "C" Rva0071EEC0Matrix *__stdcall D3DXMatrixMultiply(Rva0071EEC0Matrix *, const Rva0071EEC0Matrix *,
														   const Rva0071EEC0Matrix *);
extern "C" Rva0071EEC0Matrix *__stdcall D3DXMatrixTranspose(Rva0071EEC0Matrix *, const Rva0071EEC0Matrix *);
struct Rva012F8048State
{
	char head[0x94];
	Rva0071EEC0Matrix matrix;
	Rva0071EEC0Coord fieldd4;
	float fielde0;
};
extern Rva012F8048State *Rva012F8048StateInstance;
#define Eec0State Rva012F8048StateInstance

struct IDirect3DDevice8;
struct Rva0071EEC0DeviceVtable
{
	char p0[0xb4];
	long(__stdcall *GetTransform)(IDirect3DDevice8 *, unsigned, Rva0071EEC0Matrix *);
	char p1[0x10c - 0xb8];
	long(__stdcall *SetTextureStageState)(IDirect3DDevice8 *, unsigned, unsigned, unsigned);
	char p2[0x15c - 0x110];
	long(__stdcall *SetVertexDeclaration)(IDirect3DDevice8 *, unsigned);
	char p3[4];
	long(__stdcall *SetFVF)(IDirect3DDevice8 *, unsigned);
	char p4[8];
	long(__stdcall *SetVertexShader)(IDirect3DDevice8 *, unsigned);
	char p5[4];
	long(__stdcall *SetVertexShaderConstant)(IDirect3DDevice8 *, unsigned, const void *, unsigned);
	char p6[0x1ac - 0x17c];
	long(__stdcall *SetPixelShader)(IDirect3DDevice8 *, unsigned);
	char p7[4];
	long(__stdcall *SetPixelShaderConstant)(IDirect3DDevice8 *, unsigned, const void *, unsigned);
};
struct IDirect3DDevice8
{
	Rva0071EEC0DeviceVtable *v;
};
class TextureBaseClass;
class VertexBufferClass;
class IndexBufferClass;
class ShaderClass
{
  public:
	unsigned bits;
};
class W3DShaderManager
{
  public:
	static int setShroudTex(int);
};
// Retail 0x012BAF40: the fixed-function fog ShaderClass handed to
// DX8Wrapper::Set_Shader. Not recorded in dir32_addresses.csv, so it keeps an
// address-derived name.
extern const ShaderClass g_012BAF40;
extern unsigned number_of_DX8_calls;
class DX8Wrapper
{
	friend class W3DShrubBuffer;
	static IDirect3DDevice8 *D3DDevice;
	static Vector4 Vertex_Shader_Constants[256], Pixel_Shader_Constants[8];

  public:
	static void Set_Shader(const ShaderClass &);
	static void Set_DX8_Texture_Stage_State(unsigned, unsigned long, unsigned);
	static void Apply_Render_State_Changes();
	static void Set_Vertex_Buffer(const VertexBufferClass *, unsigned);
	static void Set_Index_Buffer(const IndexBufferClass *, unsigned short);
	static void Draw_Triangles(unsigned short, unsigned short, unsigned short, unsigned short);
	static void GetTransform(unsigned which, Rva0071EEC0Matrix &matrix)
	{
		D3DDevice->v->GetTransform(D3DDevice, which, &matrix);
		++number_of_DX8_calls;
	}
	static void VertexConstant(int reg, const void *data, int count)
	{
		void *dst = &Vertex_Shader_Constants[reg];
		if (memcmp(data, dst, count * 16) == 0)
			return;
		memcpy(dst, data, count * 16);
		D3DDevice->v->SetVertexShaderConstant(D3DDevice, reg, data, count);
		++number_of_DX8_calls;
	}
	static void PixelConstant(int reg, const void *data, int count)
	{
		void *dst = &Pixel_Shader_Constants[reg];
		if (memcmp(data, dst, count * 16) == 0)
			return;
		memcpy(dst, data, count * 16);
		D3DDevice->v->SetPixelShaderConstant(D3DDevice, reg, data, count);
		++number_of_DX8_calls;
	}
	static void SetFVF(unsigned shader)
	{
		D3DDevice->v->SetFVF(D3DDevice, shader);
		++number_of_DX8_calls;
	}
	static void SetDeclaration(unsigned declaration)
	{
		D3DDevice->v->SetVertexDeclaration(D3DDevice, declaration);
		++number_of_DX8_calls;
	}
	static void SetPixelShader(unsigned shader)
	{
		D3DDevice->v->SetPixelShader(D3DDevice, shader);
		++number_of_DX8_calls;
	}
};
void BoxSetTexture(unsigned, TextureBaseClass *&);
struct Rva0071EEC0Data
{
	char head[0x14];
	unsigned framesInward;
};
struct Rva0071EEC0Type
{
	char head[0x20];
	const Rva0071EEC0Data *data;
	char tail[0x5c - 0x24];
};
struct Rva0071EEC0Tree
{
	Vector3 location;
	float scale;
	Matrix3D transform;
	int treeType;
	bool visible;
	char gap45[0x60 - 0x45];
	float pushAside, pushAsideDelta, pushAsideSin, pushAsideCos;
	char gap70[0x88 - 0x70];
	int toppleState;
	char gap8c[0xa0 - 0x8c];
	int fielda0;
};
class W3DShrubBuffer
{
  public:
	void rva0071EEC0(CameraClass *, RefMultiListIterator<RenderObjClass> *);
	void rva0071DAF0();

  protected:
	void updateSway(const BreezeInfo &);
	void cull(const CameraClass *);
	void updateTopplingTree(int);

  public:
	void rva0071DF10(void *);
	void rva0071D5E0();
	void *vtable;
	VertexBufferClass *vertex[20];
	IndexBufferClass *index[20];
	unsigned pixelShader, vertexShader, shaderAC, shaderB0, declaration;
	char gapb8[0x1450 - 0xb8];
	TextureBaseClass *texture1450, *texture1454;
	char gap1458[0x14a8 - 0x1458];
	int numVertices[20], numIndices[20];
	Rva0071EEC0Tree trees[12000];
	int numTrees;
	bool anythingChanged, anyPushChanged, updateAllKeys, initialized, isTerrainPass, needTexture;
	char gap1e1cd2[2];
	Rva0071EEC0Type types[64];
	int numTypes;
	char gap1e33d8[12];
	Vector3 swayOffsets[100];
	int swayVersion;
	float swayOffset[10], swayStep[10], swayFactor[10];
	float swayPeriod;
	TextureBaseClass *texture3914;
	int numBuffers;
	bool flag391c;
	char gap391d[3];
	int indexStep, updateIndex;
};
// BaseType's fast_float2long_round is the witnessed two-instruction x87 helper:
// the already rounded floor result uses FISTP rather than the compiler's __ftol2.
inline int eec0Round(float value)
{
	int result;
	__asm {
 fld value
 fistp result
	}
	return result;
}
void W3DShrubBuffer::rva0071EEC0(CameraClass *camera, RefMultiListIterator<RenderObjClass> *lights)
{
	if (!isTerrainPass || !localGlobalData()->flag18)
		return;
	const BreezeInfo &info = TheScriptEngine->getBreezeInfo();
	bool pause = ((BfmeScriptEngineFreezeExtra *)TheScriptEngine)->get() || TheScriptEngine->isDebugFrozen();
	if (TheGameLogic && ((BfmeGameLogicPause *)TheGameLogic)->isGamePaused())
		pause = true;
	if (!pause && info.version != swayVersion)
		updateSway(info);
	Vector3 sway[10];
	int i;
	for (i = 0; i < 10; ++i)
	{
		if (!pause)
		{
			swayOffset[i] += swayStep[i];
			if (swayOffset[i] > 99)
				swayOffset[i] -= 99;
		}
		int minOffset = eec0Round((float)floor(swayOffset[i]));
		if (minOffset >= 0 && minOffset + 1 < 100)
		{
			float f2 = swayOffset[i] - minOffset;
			float f1 = 1.0f - f2;
			sway[i] = f1 * swayOffsets[minOffset] + f2 * swayOffsets[minOffset + 1];
			sway[i] *= swayFactor[i];
		}
	}
	isTerrainPass = false;
	if (needTexture)
	{
		needTexture = false;
		rva0071DAF0();
	}
	if (!texture1450)
		return;
	for (i = 0; i < 30; ++i)
	{
		if (updateIndex >= numTrees)
			updateIndex = 0;
		trees[updateIndex].fielda0 = 0;
		++updateIndex;
	}
	if (updateAllKeys)
		cull(camera);
	int localPlayer = ThePlayerList
		? ((Rva002EE330PlayerList *)ThePlayerList)->field0c->field24 : 0;
	for (int curTree = 0; curTree < numTrees; curTree += indexStep)
	{
		if (pause)
			break;
		int type = trees[curTree].treeType;
		if (type < 0)
			continue;
		if (trees[curTree].toppleState)
		{
			if (TheGameEngine->field30 == 1)
				updateTopplingTree(curTree);
		}
		else if (trees[curTree].visible)
		{
			if (!ThePlayerList || !(*reinterpret_cast<Rva002EEDA0ShroudManager **>(&TheShroudManager)))
				trees[curTree].fielda0 = 1;
			if (!trees[curTree].fielda0)
				trees[curTree].fielda0 = ((PartitionManager *)(*reinterpret_cast<Rva002EEDA0ShroudManager **>(&TheShroudManager)))
											 ->getPropShroudStatusForPlayer(
												 localPlayer, (const Coord3D *)&trees[curTree].location);
			if (trees[curTree].fielda0 < 3 && trees[curTree].fielda0 > 0 &&
				trees[curTree].pushAsideDelta != 0)
			{
				trees[curTree].pushAside += trees[curTree].pushAsideDelta;
				if (trees[curTree].pushAside >= 1)
					trees[curTree].pushAsideDelta = -1.0 / (types[type].data->framesInward * swayPeriod);
				else if (trees[curTree].pushAside <= 0)
				{
					trees[curTree].pushAsideDelta = 0;
					trees[curTree].pushAside = 0;
				}
			}
		}
	}
	flag391c = anythingChanged;
	if (anythingChanged)
	{
		rva0071DF10(lights);
		anythingChanged = false;
	}
	else if (anyPushChanged)
	{
		anyPushChanged = false;
		rva0071D5E0();
	}
	if (!numIndices[0])
		return;
	DX8Wrapper::Set_Shader(g_012BAF40);
	BoxSetTexture(0, texture1450);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, 11, 0);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 11, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 1, 1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, 4, 1);
	DX8Wrapper::Apply_Render_State_Changes();
	if (!W3DShaderManager::setShroudTex(1))
		BoxSetTexture(1, texture3914);
	DX8Wrapper::Apply_Render_State_Changes();
	if (vertexShader)
	{
		Rva0071EEC0Matrix matProj, matView, matWorld, mat;
		DX8Wrapper::GetTransform(256, matWorld);
		DX8Wrapper::GetTransform(2, matView);
		DX8Wrapper::GetTransform(3, matProj);
		D3DXMatrixMultiply(&mat, &matView, &matProj);
		D3DXMatrixMultiply(&mat, &matWorld, &mat);
		D3DXMatrixTranspose(&mat, &mat);
		DX8Wrapper::VertexConstant(4, &mat, 4);
		Vector4 noSway(0, 0, 0, 0);
		DX8Wrapper::VertexConstant(8, &noSway, 1);
		for (i = 0; i < 10; ++i)
		{
			Vector4 sway4(sway[i].X, sway[i].Y, sway[i].Z, 0);
			DX8Wrapper::VertexConstant(9 + i, &sway4, 1);
		}
		Rva0071EEC0Shroud *shroud = g_bfmeA1087->shroud;
		if (shroud)
		{
			float width = shroud->width, height = shroud->height;
			Vector4 offset(width - shroud->originX, height - shroud->originY, 0, 0);
			DX8Wrapper::VertexConstant(32, &offset, 1);
			width = 1.0f / (width * shroud->textureWidth);
			height = 1.0f / (height * shroud->textureHeight);
			offset.Set(width, height, 1, 1);
			DX8Wrapper::VertexConstant(33, &offset, 1);
		}
		else
		{
			Vector4 offset(0, 0, 0, 0);
			DX8Wrapper::VertexConstant(32, &offset, 1);
			DX8Wrapper::VertexConstant(33, &offset, 1);
		}
		DX8Wrapper::SetDeclaration(declaration);
		DX8Wrapper::SetPixelShader(pixelShader);
		float overbright = 0.5f;
		if (TheWritableGlobalData && localGlobalData()->useOverbright)
			overbright = 1;
		DX8Wrapper::PixelConstant(1, &Vector4(overbright, overbright, overbright, overbright), 1);
		if (g_bfmeGlobCC0 && g_bfmeGlobCC0->v28())
		{
			int kind = g_bfmeGlobCC0->fielda8;
			if ((kind == 1 || kind == 2) && shaderAC)
			{
				Rva0071EEC0Matrix matrix = Eec0State->matrix;
				D3DXMatrixTranspose(&matrix, &matrix);
				DX8Wrapper::VertexConstant(34, &matrix, 4);
				float v = g_bfmeA1087->map->field8 * 5.0f - 20.0f;
				DX8Wrapper::VertexConstant(38, &Vector4(v, v, v, v), 1);
				Rva0071EEC0Coord vec = g_bfmeGlobCC0->getField2c();
				Vector4 factor(vec.x, 1.0f - vec.x, 0, 0);
				DX8Wrapper::VertexConstant(39, &factor, 1);
				Vector4 values(20, 1, 1, 0);
				DX8Wrapper::VertexConstant(40, &values, 1);
			}
			else if ((kind == 3 || kind == 4) && shaderB0)
			{
				Rva0071EEC0Coord vec = g_bfmeGlobCC0->getField2c();
				Vector4 factor(vec.x, 1.0f - vec.x, 0, 0);
				DX8Wrapper::VertexConstant(39, &factor, 1);
				Rva0071EEC0Coord pos = Eec0State->fieldd4;
				float value = Eec0State->fielde0;
				Vector4 position(pos.x, pos.y, pos.z, 1);
				DX8Wrapper::VertexConstant(34, &position, 1);
				DX8Wrapper::VertexConstant(35, &Vector4(value, 0, 0, 0), 1);
				Vector4 values(20, 1, 1, 0);
				DX8Wrapper::VertexConstant(40, &values, 1);
			}
		}
	}
	else
		DX8Wrapper::SetFVF(0x152);
	for (int b = 0; b < numBuffers; ++b)
	{
		if (!numIndices[b])
			break;
		DX8Wrapper::Set_Index_Buffer(index[b], 0);
		DX8Wrapper::Set_Vertex_Buffer(vertex[b], 0);
		DX8Wrapper::Apply_Render_State_Changes();
		if (vertexShader)
		{
			if (g_bfmeGlobCC0 && g_bfmeGlobCC0->v28())
			{
				int kind = g_bfmeGlobCC0->fielda8;
				if ((kind == 1 || kind == 2) && shaderAC)
					DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice, shaderAC);
				else if ((kind == 3 || kind == 4) && shaderB0)
					DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice, shaderB0);
				else
					DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice, vertexShader);
			}
			else
				DX8Wrapper::D3DDevice->v->SetVertexShader(DX8Wrapper::D3DDevice, vertexShader);
			DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 0, 11, 0);
			DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 1, 11, 1);
			DX8Wrapper::D3DDevice->v->SetTextureStageState(DX8Wrapper::D3DDevice, 1, 24, 0);
		}
		DX8Wrapper::Draw_Triangles(0, numIndices[b] / 3, 0, numVertices[b]);
	}
	DX8Wrapper::SetFVF(0x152);
	DX8Wrapper::SetPixelShader(0);
}
