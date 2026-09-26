// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
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

// FILE: W3DSnow.h /////////////////////////////////////////////////////////

#include "W3DDevice/GameClient/W3DSnow.h"
#include "W3DDevice/GameClient/heightmap.h"
#include "GameClient/View.h"
#include "WW3D2/dx8wrapper.h"
#include "WW3D2/rinfo.h"
#include "WW3D2/camera.h"
#include "WW3D2/assetmgr.h"


#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define D3DFVF_POINTVERTEX (D3DFVF_XYZ)
#define SNOW_BUFFER_SIZE 4096	//size of vertex buffer holding particles.
#define SNOW_BATCH_SIZE	2048	//we render at most this many particles per drawprimitive call.  This number * 6 must be less than 65536 to fit into index buffer.

struct POINTVERTEX
{
    Vector3 v;	//center of particle.
};

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride(void) const;

	void *m_vtable;
	const BfmeOverridable *m_nextOverride;
};

class BfmeSnowOverride : public BfmeOverridable
{
public:
	unsigned char m_pad08[4];
	const char *m_snowTextureData;
	unsigned char m_pad10[0x38 - 0x10];
	unsigned char m_usePointSprites;
	unsigned char m_snowEnabled;

	const char *snowTextureName(void) const
	{
		return m_snowTextureData ? m_snowTextureData + 8 :
			(const char *)0x0107388B;
	}
};

extern BfmeSnowOverride *g_bfmeGlo012F15F8;

static const BfmeSnowOverride *walkSnowOverride(const BfmeSnowOverride *setting)
{
	if (setting == 0)
		return 0;
	if (setting->m_nextOverride)
		return (const BfmeSnowOverride *)setting->m_nextOverride->getFinalOverride();
	return setting;
}

void W3DRadarResetLock(void);
void W3DRadarResetUnlock(void);

class BfmeSnowResetLock
{
public:
	BfmeSnowResetLock(void) { W3DRadarResetLock(); }
	~BfmeSnowResetLock(void) { W3DRadarResetUnlock(); }
};

class BfmeSnowDeviceCaps
{
	unsigned char m_pad[0x273];

public:
	unsigned char m_supportPointSprites;
};

extern BfmeSnowDeviceCaps *g_bfmeCaps1340578;

class BfmeSnowDevice
{
public:
	virtual void slot00(void); virtual void slot04(void);
	virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void);
	virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void);
	virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void);
	virtual void slot38(void); virtual void slot3c(void);
	virtual void slot40(void); virtual void slot44(void);
	virtual void slot48(void); virtual void slot4c(void);
	virtual void slot50(void); virtual void slot54(void);
	virtual void slot58(void); virtual void slot5c(void);
	virtual void slot60(void); virtual void slot64(void);
	virtual int __stdcall CreateVertexBuffer(unsigned length, unsigned usage,
		unsigned fvf, unsigned pool, void **vertexBuffer, void *sharedHandle);
};

extern BfmeSnowDevice *g_bfmeDevice1340534;

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	char *name, int mipCount, int format);

static inline void BFMEAssignSnowTexture(
	TextureClass *&destination, const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

class BfmeW3DSnowManagerLayout
{
public:
	unsigned char m_pad00[0x3d];
	unsigned char m_visible;
	unsigned char m_pad3e[0x68 - 0x3e];
	DX8IndexBufferClass *m_indexBuffer;
	TextureClass *m_snowTexture;
	void *m_vertexBufferD3D;
	int m_dwBase;
	int m_dwFlush;
	int m_dwDiscard;
};

class Gen0045A970_00723FB0
{
public:
	void releaseResources(void);
};

// ??0W3DSnowManager@@ present-unmatched
W3DSnowManager::W3DSnowManager(void)
{
	m_indexBuffer=NULL;
	m_snowTexture=NULL;
	m_VertexBufferD3D=NULL;
}

// ??1W3DSnowManager@@ present-unmatched
W3DSnowManager::~W3DSnowManager()
{
	ReleaseResources();
}

// ?init@W3DSnowManager@@ present-unmatched
void W3DSnowManager::init( void )
{
	SnowManager::init();
	ReAcquireResources();
}

/** Releases all W3D/D3D assets before a reset.. */
// ?ReleaseResources@W3DSnowManager@@ present-unmatched
void W3DSnowManager::ReleaseResources(void)
{
	REF_PTR_RELEASE(m_snowTexture);

	if (m_VertexBufferD3D)
		m_VertexBufferD3D->Release();

	m_VertexBufferD3D=NULL;

	REF_PTR_RELEASE(m_indexBuffer);
}

// ?ReAcquireResources@W3DSnowManager@@QAE_NXZ
Bool W3DSnowManager::ReAcquireResources(void)
{
	BfmeSnowResetLock lock;
	((Gen0045A970_00723FB0 *)this)->releaseResources();

	BfmeW3DSnowManagerLayout *layout = (BfmeW3DSnowManagerLayout *)this;
	register const BfmeSnowOverride *base = g_bfmeGlo012F15F8;
	register const BfmeSnowOverride *setting = walkSnowOverride(base);
	if (setting->m_snowEnabled == 0 || layout->m_visible == 0)
		return true;

	setting = walkSnowOverride(base);
	register const BfmeSnowOverride *current = base;
	if (setting->m_usePointSprites != 0 &&
		g_bfmeCaps1340578->m_supportPointSprites != 0)
	{
		BfmeSnowDevice *device = g_bfmeDevice1340534;
		if (layout->m_vertexBufferD3D == 0)
		{
			if (device->CreateVertexBuffer(
				0x10000, 0x248, 0x42, 0, &layout->m_vertexBufferD3D, 0) < 0)
				return false;
			current = g_bfmeGlo012F15F8;
		}
	}
	else
	{
		layout->m_indexBuffer = ::new DX8IndexBufferClass(
			0x3000, DX8IndexBufferClass::USAGE_DEFAULT);

		{
			IndexBufferClass::WriteLockClass lockIndex(
				(IndexBufferClass *)layout->m_indexBuffer, 0);
			unsigned short *ib = lockIndex.Get_Index_Array();
			int vbCount = 0;
			for (int i = 0; i < 0x800; ++i)
			{
				ib[0] = (unsigned short)(vbCount + 3);
				ib[1] = (unsigned short)vbCount;
				ib[2] = (unsigned short)(vbCount + 2);
				ib[3] = (unsigned short)(vbCount + 2);
				ib[4] = (unsigned short)vbCount;
				ib[5] = (unsigned short)(vbCount + 1);
				vbCount += 4;
				ib += 6;
			}
		}
		current = g_bfmeGlo012F15F8;
	}

	register const BfmeSnowOverride *finalSetting = walkSnowOverride(current);
	BFMEAssignSnowTexture(
		layout->m_snowTexture,
		BFMEGetWaterTrackTexture((char *)finalSetting->snowTextureName(), 0, 0));
	layout->m_dwBase = 0x1000;
	layout->m_dwDiscard = 0x1000;
	layout->m_dwFlush = 0x800;
	return true;
}

// ?updateIniSettings@W3DSnowManager@@ present-unmatched
void W3DSnowManager::updateIniSettings(void)
{
	//Call base class
	SnowManager::updateIniSettings();

	if (m_snowTexture && stricmp(m_snowTexture->Get_Texture_Name(),TheWeatherSetting->m_snowTexture.str()) != 0)
	{	
		REF_PTR_RELEASE(m_snowTexture);
		m_snowTexture = WW3DAssetManager::Get_Instance()->Get_Texture(TheWeatherSetting->m_snowTexture.str());
	}
}

// ?reset@W3DSnowManager@@ present-unmatched
void W3DSnowManager::reset( void )
{
	SnowManager::reset();
}

// byte-exact reconstruction: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnowManagerUpdate.cpp
// ?update@W3DSnowManager@@ present-unmatched
void W3DSnowManager::update(void)
{

	m_time += WW3D::Get_Frame_Time() / 1000.0f;

	//find current time offset, adjusting for overflow
	m_time=fmod(m_time,m_fullTimePeriod);
}

#define MAXIMUM_CAMERA_DISTANCE 100000	//maximum distance of camera position from world origin.
#define ISPOW2(x)  (x && (x & (x-1)) == 0)	//is a number a power of 2?
#define MODPOW2(x,y) ((x) & (y-1))		//mod '%' operator for powers of 2.

// Helper function to stuff a FLOAT into a DWORD argument
inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }

/*Recursively subdivide the large snow box enclosing the camera until we reach some predefined leaf size.  This
method is used so that very few off-screen particles end up getting rendered.  Culling them individually would
be too expensive since we're dealing with 1000's for this effect.*/
// ?renderSubBox@W3DSnowManager@@ present-unmatched
void W3DSnowManager::renderSubBox(RenderInfoClass &rinfo, Int originX, Int originY, Int cubeDimX, Int cubeDimY )
{
	//check if this box is too large and needs subdivision
	Int boxDimX=cubeDimX - originX;
	Int boxDimY=cubeDimY - originY;
	Int halfX=REAL_TO_INT_CEIL(boxDimX*0.5f);
	Int halfY=REAL_TO_INT_CEIL(boxDimY*0.5f);

	CameraClass &camera=rinfo.Camera;
	MinMaxAABoxClass mmbox;

	if (boxDimX > m_leafDim)
	{	//subdivide the box
		if (boxDimY > m_leafDim)
		{	//subdivide in both directions
			//Upper left
			mmbox.MinCorner.Set(originX*m_emitterSpacing-m_cullOverscan, (originY + halfY)*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set((originX + halfX)*m_emitterSpacing+m_cullOverscan, cubeDimY*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX, originY + halfY, originX + halfX, cubeDimY);
			//Upper right
			mmbox.MinCorner.Set((originX + halfX)*m_emitterSpacing-m_cullOverscan, (originY + halfY)*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set(cubeDimX*m_emitterSpacing+m_cullOverscan, cubeDimY*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX + halfX, originY + halfY,cubeDimX, cubeDimY);
			//Lower left
			mmbox.MinCorner.Set(originX*m_emitterSpacing-m_cullOverscan, originY*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set((originX + halfX)*m_emitterSpacing+m_cullOverscan, (originY + halfY)*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX,originY,originX + halfX, originY + halfY);
			//Lower right
			mmbox.MinCorner.Set((originX + halfX)*m_emitterSpacing-m_cullOverscan, originY*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set(cubeDimX*m_emitterSpacing+m_cullOverscan, (originY + halfY)*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX + halfX, originY, cubeDimX, originY + halfY);
			return;
		}
		else
		{	//only subdivide in x direction.
			//Left
			mmbox.MinCorner.Set(originX*m_emitterSpacing-m_cullOverscan, originY*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set((originX + halfX)*m_emitterSpacing+m_cullOverscan, cubeDimY*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX, originY, originX + halfX, cubeDimY);
			//Right
			mmbox.MinCorner.Set((originX + halfX)*m_emitterSpacing-m_cullOverscan, originY*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
			mmbox.MaxCorner.Set(cubeDimX*m_emitterSpacing+m_cullOverscan, cubeDimY*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
			if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
				renderSubBox(rinfo, originX + halfX, originY, cubeDimX, cubeDimY);
			return;
		}
	}
	else
	if (boxDimY > m_leafDim)
	{	//only subdivide in y direction
		//Top
		mmbox.MinCorner.Set(originX*m_emitterSpacing-m_cullOverscan, (originY+halfY)*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
		mmbox.MaxCorner.Set(cubeDimX*m_emitterSpacing+m_cullOverscan, cubeDimY*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
		if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
			renderSubBox(rinfo, originX, originY+halfY,cubeDimX, cubeDimY);
		//Bottom
		mmbox.MinCorner.Set(originX*m_emitterSpacing-m_cullOverscan, originY*m_emitterSpacing-m_cullOverscan, m_snowCeiling-m_boxDimensions);
		mmbox.MaxCorner.Set(cubeDimX*m_emitterSpacing+m_cullOverscan, (originY + halfY)*m_emitterSpacing+m_cullOverscan, m_snowCeiling);
		if (CollisionMath::Overlap_Test(camera.Get_Frustum(),mmbox) != CollisionMath::OUTSIDE)
			renderSubBox(rinfo, originX, originY, cubeDimX, originY + halfY);
		return;
	}

	//Box too small to subdivide so render it.

	//Find total number of particles that need rendering.
	Int totalPart=(cubeDimY-originY)*(cubeDimX-originX);

	if (!totalPart)
		return;	//nothing to render.

	Int y=originY;	//loop counter.
	Int cubeOriginXRemainder = originX;	//loop counter - adjusted when not all particles fit into render buffer.
	Vector3 snowCenter;

	m_totalRendered += totalPart;

	while (totalPart)
	{
		Int batchSize=totalPart;

		if (batchSize > m_dwFlush)
			batchSize = m_dwFlush;

		if((m_dwBase + batchSize) > m_dwDiscard)
			m_dwBase = 0;

		POINTVERTEX* verts;

		if(m_VertexBufferD3D->Lock(m_dwBase * sizeof(POINTVERTEX), batchSize * sizeof(POINTVERTEX),
			(unsigned char **) &verts, m_dwBase ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD) != D3D_OK )
			return;	//couldn't lock buffer.

		Int numberInBatch=0;

		for (;y<cubeDimY; y++)
		{
			for (Int x=cubeOriginXRemainder; x<cubeDimX; x++)
			{
				if (numberInBatch >= batchSize)
				{	cubeOriginXRemainder = x;
					goto flush_particles;
				}

				//Get initial height from noise table.  We add a large value to make sure it's positive.  Then
				//modulate by table dimensions to find a value.
				Int noiseOffset=MODPOW2(x+MAXIMUM_CAMERA_DISTANCE,SNOW_NOISE_X)+MODPOW2(y+MAXIMUM_CAMERA_DISTANCE,SNOW_NOISE_Y)*SNOW_NOISE_X;
				if (noiseOffset > (SNOW_NOISE_X * SNOW_NOISE_Y))
					noiseOffset = 0;	//this should never happen but check to prevent buffer over/under flow.

				//find current height
				Real h0=m_snowCeiling-fmod(m_heightTraveled+m_startingHeights[noiseOffset],m_boxDimensions);

				//find world-space position of snow flake
				snowCenter.Set(x*m_emitterSpacing,y*m_emitterSpacing,h0);

				//Adjust position so snow flakes don't fall straight down.
				snowCenter.X += m_amplitude * WWMath::Fast_Sin( h0 * m_frequencyScaleX + (Real)x); 
				snowCenter.Y += m_amplitude * WWMath::Fast_Sin( h0 * m_frequencyScaleY + (Real)y); 

				*(Vector3 *)verts=snowCenter;
				verts++;

				numberInBatch++;
			}
			//getting here means we did not overflow the render buffer, so reset x origin to normal.
			cubeOriginXRemainder = originX;	//reset to normal amount
		}

flush_particles:
		m_VertexBufferD3D->Unlock();
		//Render any particles that may be queued up.
		if (numberInBatch)
		{
			Debug_Statistics::Record_DX8_Polys_And_Vertices(numberInBatch*2,numberInBatch*4,ShaderClass::_PresetOpaqueShader);
			DX8Wrapper::_Get_D3D_Device8()->DrawPrimitive( D3DPT_POINTLIST, m_dwBase, numberInBatch);
			totalPart -= numberInBatch;
			m_dwBase += numberInBatch;
		}
	}
}

// ?render@W3DSnowManager@@ present-unmatched
void W3DSnowManager::render(RenderInfoClass &rinfo)
{
	if (!TheWeatherSetting->m_snowEnabled || !m_isVisible)
		return;

	Int usePointSprites = DX8Wrapper::Get_Current_Caps()->Support_PointSprites() && TheWeatherSetting->m_usePointSprites;

	//make sure the noise table is powers of 2 in dimensions.
	WWASSERT(ISPOW2(SNOW_NOISE_X) && ISPOW2(SNOW_NOISE_Y));

	//CameraClass &camera=rinfo.Camera;

	const Coord3D &cPos=TheTacticalView->get3DCameraPosition();
	Vector3 camPos(cPos.x,cPos.y,cPos.z);

	//Number of emitters from cube center to edge of visible extent.
	Int mumEmittersInHalf=(Int)floor(m_boxDimensions / m_emitterSpacing * 0.5f);

	//Find origin of visible cube surrounding camera.
	Int cubeCenterX=(Int)floor(camPos.X/m_emitterSpacing);
	Int cubeCenterY=(Int)floor(camPos.Y/m_emitterSpacing);

	//Find extents of visible cube surrounding camera.
	Int cubeOriginX=cubeCenterX - mumEmittersInHalf;	//top/left extents.
	Int cubeOriginY=cubeCenterY - mumEmittersInHalf;
	Int cubeDimX=cubeCenterX + mumEmittersInHalf;		//bottom/right extents.
	Int cubeDimY=cubeCenterY + mumEmittersInHalf;

 	const FrustumClass & frustum = rinfo.Camera.Get_Frustum();
	AABoxClass bbox;

	//Get a bounding box around our visible universe.  Bounded by terrain and the sky
	//so much tighter fitting volume than what's actually visible.  This will cull
	//particles falling under the ground.

 	TheTerrainRenderObject->getMaximumVisibleBox(frustum, &bbox, TRUE);

	//Particles move outside the visible box as a result of local sine movement
	//so adjust bounding box to include them.
	bbox.Extent.X += m_amplitude+m_quadSize;
	bbox.Extent.Y += m_amplitude+m_quadSize;

	//Clip our visible snow rendering box
	if ((cubeOriginX * m_emitterSpacing ) < (bbox.Center.X - bbox.Extent.X))
		cubeOriginX = (Int)floor ((bbox.Center.X - bbox.Extent.X)/m_emitterSpacing);

	if ((cubeOriginY * m_emitterSpacing ) < (bbox.Center.Y - bbox.Extent.Y))
		cubeOriginY = (Int)floor ((bbox.Center.Y - bbox.Extent.Y)/m_emitterSpacing);

	if ((cubeDimX * m_emitterSpacing ) > (bbox.Center.X + bbox.Extent.X))
		cubeDimX = (Int)floor ((bbox.Center.X + bbox.Extent.X)/m_emitterSpacing);

	if ((cubeDimY * m_emitterSpacing ) > (bbox.Center.Y + bbox.Extent.Y))
		cubeDimY = (Int)floor ((bbox.Center.Y + bbox.Extent.Y)/m_emitterSpacing);

	if ((cubeDimY - cubeOriginY) < 0 || (cubeDimX-cubeOriginX) < 0)
		return;	//entire snow box is culled by either x or y screen boundary.

	//Find total number of particles that need rendering.
	Int totalPart=(cubeDimY-cubeOriginY)*(cubeDimX-cubeOriginX);

	if (totalPart <= 0)
		return;	//nothing to render.

	//Height at the top of the cube with camera at center.
	m_snowCeiling = camPos.Z + m_boxDimensions/2.0f;

	//Offset to allow cube extents to move with camera.
	Real cameraOffset = fmod (camPos.Z,m_boxDimensions);
	m_heightTraveled=m_time*m_velocity+cameraOffset;	//height that snow flake traveled this frame.

	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);	

	DX8Wrapper::Set_Shader(ShaderClass::_PresetAlphaShader);

	VertexMaterialClass *vmat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vmat);
	REF_PTR_RELEASE(vmat);

	//make sure we have all the resources we need
	if (usePointSprites && !m_VertexBufferD3D)
		ReAcquireResources();

	if (!usePointSprites && !m_indexBuffer)
		ReAcquireResources();

	DX8Wrapper::Set_Texture(0,m_snowTexture);

	if (!usePointSprites)
	{	
		renderAsQuads(rinfo,cubeOriginX,cubeOriginY,cubeDimX,cubeDimY);
		return;
	}

	Vector3 snowCenter;

	DX8Wrapper::Apply_Render_State_Changes();

    // Set the render states for using point sprites
	DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSPRITEENABLE, TRUE );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSCALEENABLE,  TRUE );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSIZE,     FtoDW(m_pointSize) );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSIZE_MIN, FtoDW(m_minPointSize) );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSIZE_MAX, FtoDW(m_maxPointSize) );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );

	DX8Wrapper::_Get_D3D_Device8()->SetStreamSource( 0, m_VertexBufferD3D, sizeof(POINTVERTEX) );
    DX8Wrapper::_Get_D3D_Device8()->SetVertexShader( D3DFVF_POINTVERTEX );
	m_dwBase = SNOW_BUFFER_SIZE;	//start with a new vertex buffer each frame.

	m_leafDim = 45;	//cull boxes that are 20x20 emitters in size. Making them much smaller will result in too many draw calls.
	m_totalRendered = 0;	//keep track of how many particles were rendered.

	//Particle centers can deviate from center by by amplitude of sine offset.  They also have radius m_quadSize.
	//Enlarge culling bounds to compensate.
	m_cullOverscan = m_amplitude+m_quadSize;
	renderSubBox(rinfo,cubeOriginX,cubeOriginY,cubeDimX,cubeDimY);

	// Reset render states
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSPRITEENABLE, FALSE );
    DX8Wrapper::Set_DX8_Render_State( D3DRS_POINTSCALEENABLE,  FALSE );

}

/**For hardware that doesn't support point sprites*/
// ?renderAsQuads@W3DSnowManager@@ present-unmatched
void W3DSnowManager::renderAsQuads(RenderInfoClass &rinfo, Int cubeOriginX, Int cubeOriginY, Int cubeDimX, Int cubeDimY)
{

	Matrix4x4 proj;
	Matrix3D view;
	Vector3 snowCenter;
	Vector3 snowCenterVS;

	CameraClass &camera=rinfo.Camera;

	camera.Get_View_Matrix(&view);
	camera.Get_Projection_Matrix(&proj);

	Vector3 vertex_offsets[4] = {
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f)
	};

	Vector2 quad_uvs[4] = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f)
	};


	//pre-multiple the offsets by particle size
	for (Int i=0; i<4; i++)
	{
		vertex_offsets[i] *= m_quadSize;
	}

	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);	

	DX8Wrapper::Set_Index_Buffer(m_indexBuffer,0);

	Int y=cubeOriginY;	//loop counter.
	Int cubeOriginXRemainder = cubeOriginX;	//loop counter - adjusted when not all particles fit into render buffer.

	//Find total number of particles that need rendering.
	Int totalPart=(cubeDimY-cubeOriginY)*(cubeDimX-cubeOriginX);

	m_totalRendered += totalPart;

	while (totalPart)
	{
		Int batchSize=totalPart;

		if (batchSize > SNOW_BATCH_SIZE)
			batchSize = SNOW_BATCH_SIZE;

		Int numberInBatch=0;

		DynamicVBAccessClass vb_access(BUFFER_TYPE_DYNAMIC_DX8,dynamic_fvf_type,batchSize*4);	//allocate 4 verts per flake
		{
			DynamicVBAccessClass::WriteLockClass lock(&vb_access);
			VertexFormatXYZNDUV2* verts=lock.Get_Formatted_Vertex_Array();

			for (;y<cubeDimY; y++)
			{
				for (Int x=cubeOriginXRemainder; x<cubeDimX; x++)
				{
					if (numberInBatch >= batchSize)
					{	cubeOriginXRemainder = x;
						goto flush_particles;
					}

					//Get initial height from noise table.  We add a large value to make sure it's positive.  Then
					//modulate by table dimensions to find a value.
					Int noiseOffset=MODPOW2(x+MAXIMUM_CAMERA_DISTANCE,SNOW_NOISE_X)+MODPOW2(y+MAXIMUM_CAMERA_DISTANCE,SNOW_NOISE_Y)*SNOW_NOISE_X;
					if (noiseOffset > (SNOW_NOISE_X * SNOW_NOISE_Y))
						noiseOffset = 0;	//this should never happen but check to prevent buffer over/under flow.

					//find current height
					Real h0=m_snowCeiling-fmod(m_heightTraveled+m_startingHeights[noiseOffset],m_boxDimensions);

					//find world-space position of snow flake
					snowCenter.Set(x*m_emitterSpacing,y*m_emitterSpacing,h0);

					//Get view-space position
					Matrix3D::Transform_Vector(view,snowCenter,&snowCenterVS);

					//Adjust position so snow flakes don't fall straight down.
					snowCenterVS.X += m_amplitude * WWMath::Fast_Sin( h0 * m_frequencyScaleX + (Real)x);
					snowCenterVS.Y += m_amplitude * WWMath::Fast_Sin( h0 * m_frequencyScaleY + (Real)y);

					for (Int i=0; i<4; i++)
					{
						*(Vector3 *)verts=snowCenterVS + vertex_offsets[i];
						verts->nx=0;	//keep AGP write-combining active
						verts->ny=0;
						verts->nz=0;
						verts->diffuse=0xffffffff;	//set to opaque
						verts->u1=quad_uvs[i].X;
						verts->v1=quad_uvs[i].Y;
						verts->u2=0;	//keep AGP write-combining active
						verts->v2=0;
						verts++;
					}

					numberInBatch++;
				}
				//getting here means we did not overflow the render buffer, so reset x origin to normal.
				cubeOriginXRemainder = cubeOriginX;	//reset to normal amount
			}
flush_particles:
			numberInBatch;	//need something at goto destination - stupid c compiler.
		}

		//Render any particles that may be queued up.
		if (numberInBatch)
		{
			DX8Wrapper::Set_Vertex_Buffer(vb_access);
			DX8Wrapper::Draw_Triangles(	0,numberInBatch*2, 0, numberInBatch*4);	
			totalPart -= numberInBatch;
		}
	}
}
