// ?method@Rva007AA820@@QAEXPAPAVCameraClass@@@Z
// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/water /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../../../Libraries/Source/WWVegas/WW3D2/texture.h"
#include "dx8wrapper.h"
#include "dx8caps.h"
#include "dx8indexbuffer.h"
#include "Common/GlobalData.h"
#include "W3DDevice/GameClient/W3DShaderManager.h"
#define MAP_XY_FACTOR 10.0f
#define BUMP_SIZE 50.0f

void __cdecl BoxSetTexture(unsigned int, TextureBaseClass *&);

// BFME's device interface differs from the reference SDK declaration.
// The decoded call sites use SetTexture at +104 and SetPixelShader at +1AC.
struct ID3DXBuffer {
    struct Table {
        void *before104[0x104/4];
        HRESULT (__stdcall *setTexture)(ID3DXBuffer *, DWORD, IDirect3DBaseTexture8 *);
        void *before1AC[(0x1ac-0x108)/4];
        HRESULT (__stdcall *setPixelShader)(ID3DXBuffer *, DWORD);
    } *table;
    HRESULT SetTexture(DWORD stage, IDirect3DBaseTexture8 *texture) {
        return table->setTexture(this,stage,texture);
    }
    HRESULT SetPixelShader(DWORD shader) { return table->setPixelShader(this,shader); }
};
static inline ID3DXBuffer *Rva007A8FF0GetDevice() {
    return reinterpret_cast<ID3DXBuffer *>(DX8Wrapper::_Get_D3D_Device8());
}

// 007AA820 supplies a record from the water list plus four Vector3 points.
// 007A92B0 reads its RGB; 007A96CD reads +5C. No semantic type is yet proved.
class Rva007A8FF0Data {
public:
    float getAt5C() const { return m_at5C; }
    char m_before3C[0x3c];
    bool m_additiveAt3C;
    char m_before40[3];
    RGBColor m_colorAt40;
    char m_before5C[0x10];
    float m_at5C;
};

class TextureHandle {
public:
    TextureClass *value;
    TextureHandle() : value(0) {}
    TextureHandle(const TextureHandle &other) : value(other.value) { if(value) value->Add_Ref(); }
    ~TextureHandle() { if(value) value->Release_Ref(); }
    TextureHandle &operator=(const TextureHandle &other) {
        if(other.value) other.value->Add_Ref();
        if(value) value->Release_Ref();
        value=other.value;
        return *this;
    }
};
class W3DShroud { public: TextureHandle getShroudTexture(); };
class WaterShader007A6AA0 { public: void setup(char *settings); };
class WaterShader007A7240 { public: void setup(char *settings); };
struct Rva007A8FF0Terrain {
    float getAt3018() const { return m_depthAt3018; }
    W3DShroud *getShroud() const { return m_shroudAt30B8; }
    char m_before3018[0x3018];
    float m_depthAt3018;
    char m_before30B8[0x9c];
    W3DShroud *m_shroudAt30B8;
};
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern int Rva00903060Get();
class BfmeHandleCX;
extern BfmeHandleCX g_bfmeTableDU[8];
static inline void Rva007A8FF0SetTexture(int stage, const TextureHandle &texture) {
    reinterpret_cast<TextureHandle *>(g_bfmeTableDU)[stage]=texture;
}

class WaterRenderObjClass {
    struct Setting {
        TextureBaseClass *skyTexture;
        TextureBaseClass *waterTexture;
        int waterRepeatCount;
        float skyTexelsPerUnit;
        unsigned int vertex00Diffuse, vertex10Diffuse, vertex11Diffuse, vertex01Diffuse;
        unsigned int waterDiffuse, transparentWaterDiffuse;
        float uScrollPerMs,vScrollPerMs;
    };
    char m_before2A8[0x2a8];
    TextureBaseClass *m_textureAt2A8;
    char m_before2B8[0xc];
    unsigned int m_at2B8;
    char m_before2E0[0x24];
    Setting m_settings[6];
    int m_tod;
public:
    unsigned int getAt2B8() const { return m_at2B8; }
friend class Rva007AA820;
protected:
    inline __declspec(noinline) void drawTrapezoidWater(Rva007A8FF0Data *, Vector3 points[4]);
};

class FVFInfoClass;
class VertexBufferClass;
struct VertexFormatXYZNDUV2;

class BoxDynamicVBAccessClass
{
	const FVFInfoClass &m_fvfInfo;
	unsigned int m_type;
	unsigned int m_fvf;
	unsigned int m_start;
	unsigned short m_vertexCount;
	unsigned short m_vertexBufferOffset;
	VertexBufferClass *m_vertexBuffer;

public:
	BoxDynamicVBAccessClass(unsigned int type, unsigned int fvf,
		unsigned short vertexCount, unsigned int start);
	~BoxDynamicVBAccessClass();

	class WriteLockClass
	{
		BoxDynamicVBAccessClass *m_access;
		VertexFormatXYZNDUV2 *m_vertices;
	public:
		WriteLockClass(BoxDynamicVBAccessClass *access);
		~WriteLockClass();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return m_vertices; }
	};
};

struct Rva007A8FF0GlobalData {
    char before8C[0x8c];
    bool m_showSoftWaterEdge;
    char before98[11];
    int m_featherWater;
    char before9BC[0x9bc-0x9c];
    RGBColor m_terrainAmbient[3];
    RGBColor m_terrainDiffuse[3];
    Coord3D m_terrainLightPos[3];
    char beforeA58[0xa58-0xa28];
    int m_numGlobalLights;
};
static inline Rva007A8FF0GlobalData *Rva007A8FF0Globals() {
    return reinterpret_cast<Rva007A8FF0GlobalData *>(TheWritableGlobalData);
}
static inline float Rva007A8FF0Length(const Vector3 &v) { return WWMath::Sqrt(v.Y*v.Y + v.Z*v.Z + v.X*v.X); }
//-------------------------------------------------------------------------------------------------
//Draw a 4 sided flat water area.
//-------------------------------------------------------------------------------------------------
inline __declspec(noinline) void WaterRenderObjClass::drawTrapezoidWater(Rva007A8FF0Data *water, Vector3 points[4])
{
	Vector3 origin(points[0]);
	Vector3 uVec1(points[1]);
	Vector3 vVec1(points[3]);
	Vector3 uVec2(points[2]);
	Vector3 vVec2(points[2]);
	uVec2 -= vVec1;
	vVec2 -= uVec1;
	uVec1 -= origin;
	vVec1 -= origin;
	Real uLen1 = Rva007A8FF0Length(uVec1);
	Real uLen2 = Rva007A8FF0Length(uVec2);
	Int uCount = (uLen1+uLen2) / (32*MAP_XY_FACTOR);
	if (uCount<1) uCount = 1;
	Int vCount = (Rva007A8FF0Length(vVec1)+Rva007A8FF0Length(vVec2)) / (32*MAP_XY_FACTOR);
	if (vCount<1) vCount = 1;	

	if (uCount>50) uCount = 50;
	if (vCount>50) vCount = 50;

	static Bool doWobble = true;

	Int rectangleCount = uCount*vCount;

	uCount++;
	vCount++;

	Int i, j;
	//allocate 2 triangles per side with 3 indices per triangle
	DynamicIBAccessClass ib_access(BUFFER_TYPE_DYNAMIC_DX8,(rectangleCount+1)*2*3);
	{
		DynamicIBAccessClass::WriteLockClass lockib(&ib_access);
 		UnsignedShort *curIb = lockib.Get_Index_Array();
		for (j=0; j<vCount-1; j++)
		{	for (i=0; i<uCount-1; i++)
			{
				//triangle 1
				curIb[0] = (j)*uCount + i;
				curIb[1] = (j+1)*uCount + i+1;
				curIb[2] = (j+1)*uCount + i;

				//triangle 2
				curIb[3] = (j)*uCount + i;
				curIb[4] = (j)*uCount + i+1;
				curIb[5] = (j+1)*uCount + i+1;

				curIb += 6;	//skip the 6 indices we just added.
			}
		}
	}

	Real	waterFactor=150;
	Real shadeR=water->m_colorAt40.red;
	Real shadeG=water->m_colorAt40.green;
	Real shadeB=water->m_colorAt40.blue;

	//If the water color is not overridden, use legacy lighting code.
	if ( shadeR==1.0f && shadeG==1.0f && shadeB==1.0f)
	{
		shadeR = Rva007A8FF0Globals()->m_terrainAmbient[0].red;
		shadeG = Rva007A8FF0Globals()->m_terrainAmbient[0].green;
		shadeB = Rva007A8FF0Globals()->m_terrainAmbient[0].blue;

		//Add in diffuse lighting from each terrain light
		for (Int lightIndex=0; lightIndex < Rva007A8FF0Globals()->m_numGlobalLights; lightIndex++)
		{
			if (-Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z > 0)
			{	shadeR += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].red;
				shadeG += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].green;
				shadeB += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].blue;
			}
		}

		//Get water material colors
		Real waterShadeR = (m_settings[m_tod].waterDiffuse & 0xff) / 255.0f;
		Real waterShadeG = ((m_settings[m_tod].waterDiffuse >> 8) & 0xff) / 255.0f;
		Real waterShadeB = ((m_settings[m_tod].waterDiffuse >> 16) & 0xff) / 255.0f;

		shadeR=shadeR*waterShadeR*255.0f;
		shadeG=shadeG*waterShadeG*255.0f;
		shadeB=shadeB*waterShadeB*255.0f;
	}
	else
	{
		shadeR=shadeR*255.0f;
		shadeG=shadeG*255.0f;
		shadeB=shadeB*255.0f;

		if (shadeR == 0 && shadeG == 0 && shadeB == 0)
		{	//special case where we disable lighting
			shadeR=255;
			shadeG=255;
			shadeB=255;
		}
	}

	Int diffuse=Int(shadeB) | (Int(shadeG) << 8) | (Int(shadeR) << 16);

	//Keep diffuse from lighting calculations but substitute custom alpha
	diffuse |= m_settings[m_tod].waterDiffuse & 0xff000000;	//copy alpha/opacity from ini setting

	BoxDynamicVBAccessClass vb_access(2, 5, (rectangleCount+1)*2, 0);


//#define WAVY_WATER
//#define FEATHER_LAYER_COUNT (3) //LORENZEN
//#define FEATHER_LAYER_THICKNESS (2.5f)
//#define FEATHER_WATER

//#ifdef WAVY_WATER // the NEW WATER a'la LORENZEN
	if ( Rva007A8FF0Globals()->m_featherWater )
	{

		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

		Real phase = 0;
		Real mapCoeff = PI/(4*MAP_XY_FACTOR);
		Real wave = 0;
		Real amplitude = 0.5f;



		//The first (high order) byte is the Alpha value for this patch
		// It needs to be set proportional to the number of feather layers
		// this comes from TheGlobalData->m_featherWater, which is a count of layers
		Int Alpha = 0;
		if ( Rva007A8FF0Globals()->m_featherWater == 5) Alpha = 80;
		if ( Rva007A8FF0Globals()->m_featherWater == 4) Alpha = 110;
		if ( Rva007A8FF0Globals()->m_featherWater == 3) Alpha = 140;
		if ( Rva007A8FF0Globals()->m_featherWater == 2) Alpha = 200;
		if ( Rva007A8FF0Globals()->m_featherWater == 1) Alpha = 255;

		//Keep diffuse from lighting calculations but substitute custom alpha
		Int customDiffuse = (diffuse & 0x00ffffff) | (Alpha<< 24);//(0x80 << 16)|(0x90 << 8)|0xa0;

		for (j=0; j<vCount; j++)
		{
			Real dv = j;
			dv /= (vCount-1);
			for (i=0; i<uCount; i++)
			{
				Real du = i;
				du /= (uCount-1);
				Vector3 vertex = origin;
				vertex += uVec1*du;
				vertex += vVec1*dv;
				vertex += (dv)*(du)*(vVec2-vVec1);

				vb->x=vertex.X;
				vb->y=vertex.Y;

				// common to all the waving effects
				phase = 25 * water->getAt5C() + vertex.X * mapCoeff;
				wave = (sin(phase) - 1.0f) * amplitude;

				vb->z = (vertex.Z + wave);
				vb->diffuse = customDiffuse;
				vb->u1 = (vertex.X/waterFactor) + 0.02*cos(11*water->getAt5C())*wave;
				vb->v1 = (vertex.Y/waterFactor) + 0.02*cos(5*water->getAt5C())*wave;
				vb->u2 = vertex.X/BUMP_SIZE;
				vb->v2 = vertex.Y/BUMP_SIZE + 0.3f*vertex.X/BUMP_SIZE;
				vb->nx = 0;
				vb->ny = 0;
				vb->nz = 1.0f;
				vb++;
			}
		}
	}
//#else // STILL THE OLD FLAT WATER
	else

	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

		//Pulling some constants out of the inner loops to improve performance -MW
		Real constA=0.02*cos(11*water->getAt5C());
		Real constB=0.02*cos(5*water->getAt5C());
		Real constC=25*water->getAt5C();
		Real ooWaterFactor = 1.0f/waterFactor;
		const Real constD=PI/(4*MAP_XY_FACTOR);
		Real constE=1.0f/(Real)(vCount-1);
		Real constF=1.0f/(Real)(uCount-1);

		for (j=0; j<vCount; j++)
		{
			Real dv = (Real)j * constE;

			for (i=0; i<uCount; i++)
			{
				Real du = (Real)i * constF;
				Vector3 vertex = origin;
				vertex += uVec1*du;
				vertex += vVec1*dv;
				vertex += (dv)*(du)*(vVec2-vVec1);

				vb->x=vertex.X;
				vb->y=vertex.Y;
				vb->z=vertex.Z;

				vb->diffuse= diffuse;
				//Old slower version
 				//vb->u1=(vertex.X/waterFactor) + 0.02*cos(11*m_riverVOrigin)*sin(25*m_riverVOrigin+vertex.X*PI/(4*MAP_XY_FACTOR));
 				//vb->v1=(vertex.Y/waterFactor) + 0.02*cos(5*m_riverVOrigin)*sin(25*m_riverVOrigin+vertex.Y*PI/(4*MAP_XY_FACTOR));
				vb->u1=vertex.X*ooWaterFactor + constA*WWMath::Fast_Sin(constC+vertex.X*constD);
				vb->v1=vertex.Y*ooWaterFactor + constB*WWMath::Fast_Sin(constC+vertex.Y*constD);
				vb->u2 = vertex.X/BUMP_SIZE;
				//Old slower version
 				//vb->v2 = vertex.Y/BUMP_SIZE + 0.3f*vertex.X/BUMP_SIZE;
				vb->v2 = (vertex.Y+0.3f*vertex.X)/BUMP_SIZE;
				vb->nx = 0;
				vb->ny = 0;
				vb->nz = 1.0f;
				vb++;
			}
		}
	}




//#endif // OLD VS NEW WATER
	Matrix3D tm(1);

	DX8Wrapper::Set_Transform(D3DTS_WORLD,tm);	//position the water surface
	DX8Wrapper::Set_Index_Buffer(ib_access,0);
	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb_access));

	Bool wireframe = false;
    if (DX8Wrapper::Get_DX8_Render_State(D3DRS_FILLMODE) == D3DFILL_WIREFRAME)
        wireframe = true;
    Bool useAt98 = (DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().TextureOpCaps & 0x00200000) != 0;
    if (useAt98 && !wireframe) reinterpret_cast<WaterShader007A6AA0 *>(this)->setup(reinterpret_cast<char *>(water));
    else reinterpret_cast<WaterShader007A7240 *>(this)->setup(reinterpret_cast<char *>(water));// lorenzen sez use the alpha shader

	//If video card supports it and it's enabled, feather the water edge using destination alpha
	if (Rva00903060Get() == D3DFMT_A8R8G8B8 && Rva007A8FF0Globals()->m_showSoftWaterEdge && reinterpret_cast<Rva007A8FF0Terrain *>(TheTerrainRenderObject)->getAt3018() !=0)
	{		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_DESTALPHA );
			if (!water->m_additiveAt3C)
				DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA );
	}


    if (wireframe) {
        BoxSetTexture(0, m_textureAt2A8);
        BoxSetTexture(1, m_textureAt2A8);
        DX8Wrapper::Set_DX8_Render_State(D3DRS_ZFUNC, D3DCMP_ALWAYS);
        DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, false);
    }
    DWORD cull;
	DX8Wrapper::_Get_D3D_Device8()->GetRenderState(D3DRS_CULLMODE, &cull);
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);




	{

//#ifdef FEATHER_WATER // the NEW WATER a'la LORENZEN
//	int layer = 0;//LORENZEN
//	for (layer = 0; layer < FEATHER_LAYER_COUNT; ++layer)//LORENZEN
//#endif // FEATHER_WATER
//#ifdef WAVY_WATER // the NEW WATER a'la LORENZEN
		//increment the depth of the water's surface for every vert in the buffer
//#ifdef  FEATHER_WATER
//		VertexFormatXYZNDUV2 *vertBuf = vertexBufferStart;
//		while (vertBuf < vertexBufferStart + vCount * uCount)
//		{
//			vertBuf->z *= FEATHER_LAYER_THICKNESS;
//			++vertBuf;
//		}
//#endif // FEATHER_WATER
//#endif //WAVY_WATER
		DX8Wrapper::Draw_Triangles(	0,rectangleCount*2, 0,	(rectangleCount+1)*2);//lorenzen thinks this is where to itereate the soft shoreline effect
	}




	if (getAt2B8()) Rva007A8FF0GetDevice()->SetPixelShader(NULL);
	//Restore alpha blend to default values since we may have changed them to feather edges.
	if (!water->m_additiveAt3C)
	{	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	}
	else
	{
		DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_ONE );
		DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_ONE );
	}

	if (reinterpret_cast<Rva007A8FF0Terrain *>(TheTerrainRenderObject)->getShroud())
	{
		if (getAt2B8() && !useAt98)
		{	//shroud was applied in stage3 of main pass so just need to restore state here.
			W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
			Rva007A8FF0GetDevice()->SetTexture(3,NULL);	//free possible reference to shroud texture
		}
		else
		{	//do second pass to apply the shroud on water plane for cards that can't do it in main pass.
			DX8Wrapper::Invalidate_Cached_Render_States();
            Rva007A8FF0SetTexture(0, reinterpret_cast<Rva007A8FF0Terrain *>(TheTerrainRenderObject)->getShroud()->getShroudTexture());
			W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
            DX8Wrapper::Set_Shader(ShaderClass::_PresetMultiplicativeSpriteShader);
            DX8Wrapper::Apply_Render_State_Changes();
			DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			//Shroud shader uses z-compare of EQUAL which wouldn't work on water because it doesn't
			//write to the zbuffer.  Change to LESSEQUAL.
			DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			DX8Wrapper::Draw_Triangles(	0,rectangleCount*2, 0,	(rectangleCount+1)*2);
			W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
		}
	}
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, cull);
}

#include "PreRTS.h"
#include "Common/GlobalData.h"
#include "vector3.h"
#include "aabox.h"
#include "camera.h"
#include <list>
struct Rva007AA820Node {
 char pad00[4]; unsigned char field04; char pad05[3]; int field08;
 char pad0C[0x48]; Vector3 *field54; int field58;
};
struct Rva007AA820Call {
 const AABoxClass& box();
 bool cull(const AABoxClass&) const;
 void node(Rva007AA820Node*);
 void quad(Rva007AA820Node*,Vector3*);
};
extern void j_0003a8d2(); extern void j_0003cb2d(); extern void j_00015c26();
class BFMECameraCullBox { public: bool Cull_Box(const AABoxClass&) const; };
template<class T> static __forceinline T rva007AA820Member(void(*raw)()) {
 union {void(*p)();T m;} u;u.p=raw;return u.m;
}
static __forceinline int rva007AA820Count() {
 return *(const int*)((const char*)TheWritableGlobalData+0x98);
}
class Rva007A12C0CachedVolume;
class Rva007A12C0CacheOwner { public: Rva007A12C0CachedVolume &getCachedVolume(); };
class Rva007AA820 {
public:
 void method(CameraClass**);
 char pad0[0x2ac]; std::list<Rva007AA820Node*> field2AC;
};
// ?method@Rva007AA820@@QAEXPAPAVCameraClass@@@Z
void Rva007AA820::method(CameraClass **camera)
{
 for(std::list<Rva007AA820Node*>::iterator it=field2AC.begin();it!=field2AC.end();++it) {
  Rva007AA820Node* node=*it;
  typedef const AABoxClass&(Rva007AA820Call::*Box)();
  const AABoxClass& box=(const AABoxClass&)((Rva007A12C0CacheOwner*)node)->getCachedVolume();
  typedef bool(Rva007AA820Call::*Cull)(const AABoxClass&) const;
  if(((const BFMECameraCullBox*)*camera)->Cull_Box(box)) continue;
  if(node->field04) {
   typedef void(Rva007AA820Call::*Node)(Rva007AA820Node*);
   ((Rva007AA820Call*)this->*rva007AA820Member<Node>(j_0003cb2d))(node);
  } else {
   int back=node->field08;
   int count=node->field58;
   int front=back+1;
   if(front>=count)front=0;
   if(back>=count-1)return;
   for(int i=0;i<count/2;++i) {
    const Vector3 *v0=&node->field54[back];
    const Vector3 *v1=&node->field54[front];
    ++front; --back;
    if(back<0)back=count-1;
    if(front>=count)front=0;
    Vector3 vertices[4];
    vertices[0]=*v0; vertices[1]=*v1;
    vertices[2]=node->field54[front];vertices[3]=node->field54[back];
    typedef void(Rva007AA820Call::*Quad)(Rva007AA820Node*,Vector3*);
    int passes=rva007AA820Count();
    if(passes!=0) {
     for(int repeat=0;repeat<passes;++repeat) {
      ((WaterRenderObjClass*)this)->drawTrapezoidWater((Rva007A8FF0Data*)node,vertices);
      passes=rva007AA820Count();
      vertices[0].Z+=4.0f/(float)passes;
     }
    } else {
     ((WaterRenderObjClass*)this)->drawTrapezoidWater((Rva007A8FF0Data*)node,vertices);
    }
    count=node->field58;
   }
  }
 }
}
typedef char MemberSize[(sizeof(void(Rva007AA820Call::*)(Rva007AA820Node*))==4)?1:-1];
