// ?drawTrapezoidWater@WaterRenderObjClass@@IAEXPAVRva007A8FF0Data@@QAVVector3@@@Z
// partial score=0.997981021603 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/water /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// RVA 007A8FF0: continuous Capstone decode of 4953 bytes, RET 8 at 007AA346,
// end 007AA349 followed by INT3. The old one-argument signature is wrong.
// Caller 007AA820 supplies a water-list payload and four Vector3 points.
// Identity of drawTrapezoidWater follows the original W3DWater algorithm;
// the additional record's semantic type is unproved and retains its RVA.
// The two typed helper calls below still need pins if this body lands:
//   rva007A6AA0 -> ILT 00025EC3 -> physical 007A6AA0 (RET 4)
//   rva007A7240 -> ILT 00024A14 -> physical 007A7240 (RET 4).
// Both independently decoded helpers accept this plus the record pointer;
// 007A6AA0 selects record textures +34/+38; 007A7240 selects +24 and reads +3C.
// Shroud getter uses existing Gen_006D2630::bfmeGet returning BfmeHandleCX;
// its body copies the owning texture at +1C and increments the WORD refcount.
// Layout: WaterRenderObjSky.cpp proves settings +2E0 and TOD +400. Retail
// proves record color +40, phase input +5C, texture +2A8 and shader +2B8.
// GlobalData lighting +9BC/+9E0/+A04 and count +A58 agree with retail;
// the reference header still describes an older layout.
// Probe: 4953/4953, 10 non-reloc differences, score 1-10/4953=0.997981021603.
// Residue: vVec2 length operand order +1AA..+1C0; reload order +2BA/+2BE.
// Getter-based ABI views closed the frame and tail. Native/dot/scalar length,
// independent declaration/operand orders, named temporaries and /Op did not
// close the residue. No assembly, volatile shaping or shared header changes.
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
#include "../../Code/Libraries/Source/WWVegas/WW3D2/texture.h"
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

class BfmeHandleCX {
public:
    TextureClass *value;
    BfmeHandleCX() : value(0) {}
    BfmeHandleCX(const BfmeHandleCX &other) : value(other.value) { if(value) value->Add_Ref(); }
    ~BfmeHandleCX() { if(value) value->Release_Ref(); }
    BfmeHandleCX &operator=(const BfmeHandleCX &other) {
        if(other.value) other.value->Add_Ref();
        if(value) value->Release_Ref();
        value=other.value;
        return *this;
    }
};
class Gen_006D2630 { public: BfmeHandleCX bfmeGet() const; };
struct Rva007A8FF0Terrain {
    float getAt3018() const { return m_depthAt3018; }
    Gen_006D2630 *getShroud() const { return m_shroudAt30B8; }
    char m_before3018[0x3018];
    float m_depthAt3018;
    char m_before30B8[0x9c];
    Gen_006D2630 *m_shroudAt30B8;
};
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern BfmeHandleCX Rva012F9D28Textures[8];
static inline void Rva007A8FF0SetTexture(int stage, const BfmeHandleCX &texture) {
    Rva012F9D28Textures[stage]=texture;
}
extern ShaderClass zFillAlphaShader;

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
protected:
    void drawTrapezoidWater(Rva007A8FF0Data *, Vector3 points[4]);
    void rva007A6AA0(Rva007A8FF0Data *);
    void rva007A7240(Rva007A8FF0Data *);
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
void WaterRenderObjClass::drawTrapezoidWater(Rva007A8FF0Data *water, Vector3 points[4])
{
	Vector3 origin(points[0]);
	Vector3 uVec1(points[1]);
	Vector3 vVec1(points[3]);
	Vector3 uVec2(points[2]);
	Vector3 vVec2(points[2]);
	uVec2 -= vVec1;
	vVec2	-= uVec1;
	uVec1 -= origin;
	vVec1 -= origin;
	Int uCount = (Rva007A8FF0Length(uVec1)+Rva007A8FF0Length(uVec2)) / (8*MAP_XY_FACTOR);
	if (uCount<1) uCount = 1;
	Int vCount = (Rva007A8FF0Length(vVec1)+Rva007A8FF0Length(vVec2)) / (8*MAP_XY_FACTOR);
	if (vCount<1) vCount = 1;	

	if (uCount>50) uCount = 50;
	if (vCount>50) vCount = 50;

	static Bool doWobble = true;

	Int rectangleCount = uCount*vCount;

	uCount++;
	vCount++;

	Int i, j;
	DynamicIBAccessClass ib_access(BUFFER_TYPE_DYNAMIC_DX8,(rectangleCount+1)*2*3);
	{
		DynamicIBAccessClass::WriteLockClass lockib(&ib_access);
 		UnsignedShort *curIb = lockib.Get_Index_Array();
		for (j=0; j<vCount-1; j++)
		{	for (i=0; i<uCount-1; i++)
			{
				curIb[0] = (j)*uCount + i;
				curIb[1] = (j+1)*uCount + i+1;
				curIb[2] = (j+1)*uCount + i;

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

	if ( shadeR==1.0f && shadeG==1.0f && shadeB==1.0f)
	{
		shadeR = Rva007A8FF0Globals()->m_terrainAmbient[0].red;
		shadeG = Rva007A8FF0Globals()->m_terrainAmbient[0].green;
		shadeB = Rva007A8FF0Globals()->m_terrainAmbient[0].blue;

		for (Int lightIndex=0; lightIndex < Rva007A8FF0Globals()->m_numGlobalLights; lightIndex++)
		{
			if (-Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z > 0)
			{	shadeR += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].red;
				shadeG += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].green;
				shadeB += -Rva007A8FF0Globals()->m_terrainLightPos[lightIndex].z * Rva007A8FF0Globals()->m_terrainDiffuse[lightIndex].blue;
			}
		}

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

	diffuse |= m_settings[m_tod].waterDiffuse & 0xff000000;	//copy alpha/opacity from ini setting

	BoxDynamicVBAccessClass vb_access(2, 5, (rectangleCount+1)*2, 0);


	if ( Rva007A8FF0Globals()->m_featherWater )
	{

		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

		Real phase = 0;
		Real mapCoeff = PI/(4*MAP_XY_FACTOR);
		Real wave = 0;
		Real amplitude = 0.5f;



		Int Alpha = 0;
		if ( Rva007A8FF0Globals()->m_featherWater == 5) Alpha = 80;
		if ( Rva007A8FF0Globals()->m_featherWater == 4) Alpha = 110;
		if ( Rva007A8FF0Globals()->m_featherWater == 3) Alpha = 140;
		if ( Rva007A8FF0Globals()->m_featherWater == 2) Alpha = 200;
		if ( Rva007A8FF0Globals()->m_featherWater == 1) Alpha = 255;

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
	else

	{
		BoxDynamicVBAccessClass::WriteLockClass lock(&vb_access);
		VertexFormatXYZNDUV2* vb=lock.Get_Formatted_Vertex_Array();

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
				vb->u1=vertex.X*ooWaterFactor + constA*WWMath::Fast_Sin(constC+vertex.X*constD);
				vb->v1=vertex.Y*ooWaterFactor + constB*WWMath::Fast_Sin(constC+vertex.Y*constD);
				vb->u2 = vertex.X/BUMP_SIZE;
				vb->v2 = (vertex.Y+0.3f*vertex.X)/BUMP_SIZE;
				vb->nx = 0;
				vb->ny = 0;
				vb->nz = 1.0f;
				vb++;
			}
		}
	}




	Matrix3D tm(1);

	DX8Wrapper::Set_Transform(D3DTS_WORLD,tm);	//position the water surface
	DX8Wrapper::Set_Index_Buffer(ib_access,0);
	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&vb_access));

	Bool wireframe = false;
    if (DX8Wrapper::Get_DX8_Render_State(D3DRS_FILLMODE) == D3DFILL_WIREFRAME)
        wireframe = true;
    Bool useAt98 = (DX8Wrapper::Get_Current_Caps()->Get_DX8_Caps().TextureOpCaps & 0x00200000) != 0;
    if (useAt98 && !wireframe) rva007A6AA0(water);
    else rva007A7240(water);// lorenzen sez use the alpha shader

	if (int(DX8Wrapper::getBackBufferFormat()) == D3DFMT_A8R8G8B8 && Rva007A8FF0Globals()->m_showSoftWaterEdge && reinterpret_cast<Rva007A8FF0Terrain *>(TheTerrainRenderObject)->getAt3018() !=0)
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

		DX8Wrapper::Draw_Triangles(	0,rectangleCount*2, 0,	(rectangleCount+1)*2);//lorenzen thinks this is where to itereate the soft shoreline effect
	}




	if (m_at2B8) Rva007A8FF0GetDevice()->SetPixelShader(NULL);
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
		if (m_at2B8 && !useAt98)
		{	//shroud was applied in stage3 of main pass so just need to restore state here.
			W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
			Rva007A8FF0GetDevice()->SetTexture(3,NULL);	//free possible reference to shroud texture
		}
		else
		{	//do second pass to apply the shroud on water plane for cards that can't do it in main pass.
			DX8Wrapper::Invalidate_Cached_Render_States();
            Rva007A8FF0SetTexture(0, reinterpret_cast<Rva007A8FF0Terrain *>(TheTerrainRenderObject)->getShroud()->bfmeGet());
			W3DShaderManager::setShader(W3DShaderManager::ST_SHROUD_TEXTURE, 0);
            DX8Wrapper::Set_Shader(zFillAlphaShader);
            DX8Wrapper::Apply_Render_State_Changes();
			DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			DX8Wrapper::Draw_Triangles(	0,rectangleCount*2, 0,	(rectangleCount+1)*2);
			W3DShaderManager::resetShader(W3DShaderManager::ST_SHROUD_TEXTURE);
		}
	}
	DX8Wrapper::_Get_D3D_Device8()->SetRenderState(D3DRS_CULLMODE, cull);
}
