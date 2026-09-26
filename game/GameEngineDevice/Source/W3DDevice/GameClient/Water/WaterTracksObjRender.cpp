// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
// WaterTracksObj::render at retail 0x007ABAA0 (2200 B, ends at ret 0xc +0x895).
// Identity: the matched WaterTracksRenderSystem::flush (0x007AD620) calls this
// body through ILT 0x000371DC in the Zero Hour twin's mod->render() position,
// passing (m_vertexBuffer, m_batchStart, rinfo); retail pops 12 argument bytes
// and reads rinfo.Camera (+0) for the cull, so BFME added the RenderInfoClass&.
// Body: Zero Hour W3DWaterTracks.cpp render() plus the BFME frustum cull of the
// four wave corners and the local-player shroud test.
#include "Lib/BaseType.h"
#include "vector2.h"
#include "vector3.h"
#include "aabox.h"
#include "rinfo.h"
#include "dx8fvf.h"

// BFME DX8VertexBufferClass keeps fvf_info at +0x14 (ZH layout hint) but its
// D3D buffer sits at +0x1c, four bytes past ZH's; this body reads only those.
class DX8VertexBufferClass
{
public:
	const FVFInfoClass& FVF_Info() const { return *fvf_info; }
	IDirect3DVertexBuffer8* Get_DX8_Vertex_Buffer() { return VertexBuffer; }
private:
	char m_unmodelled00[0x14];
	FVFInfoClass *fvf_info;
	char m_unmodelled18[0x4];
	IDirect3DVertexBuffer8 *VertexBuffer;
};

class IndexBufferClass {};
class DX8IndexBufferClass : public IndexBufferClass {};

class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass* ib,unsigned short index_base_offset);
	static void Draw_Strip(unsigned short start_index, unsigned short polygon_count, unsigned short min_vertex_index, unsigned short vertex_count);
};

enum waveType
{
	WaveTypeFirst,
	WaveTypePond=WaveTypeFirst,
	WaveTypeOcean,
	WaveTypeCloseOcean,
	WaveTypeCloseOceanDouble,
	WaveTypeRadial,
	WaveTypeLast = WaveTypeRadial,
	WaveTypeStationary,
	WaveTypeMax,
};

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED,
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(Int playerIndex, const Coord3D *loc) const;
};
extern PartitionManager *TheShroudManager;

// Player +0x24 m_playerIndex and PlayerList +0xc m_local: name_oracle layout witness.
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	char m_unmodelled00[0x24];
	Int m_playerIndex;
};

class PlayerList
{
public:
	Player *getLocalPlayer() { return m_local; }
private:
	char m_unmodelled00[0xc];
	Player *m_local;
};
extern PlayerList *ThePlayerList;

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual Bool isUnderwater( Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL ); // 19, +0x4c
};
extern TerrainLogic *TheTerrainLogic;

// Pin target for BFME's 183B CameraClass::Cull_Box at 0x9330C0 (see W3DTerrainBackground.cpp).
struct BFMECameraCullBox
{
	bool Cull_Box(const AABoxClass & box) const;
};

// Members this body reads, at the Zero Hour twin's offsets (the twin's render()
// reads the same fields in the same expressions; BFME kept these offsets).
class WaterTracksObj
{
public:
	Int render(DX8VertexBufferClass *vertexBuffer, Int batchStart, RenderInfoClass &rinfo);

protected:
	char m_unmodelled00[0x30];
	waveType	m_type;					// +0x30
	Int			m_x;					// +0x34
	Int			m_y;					// +0x38
	char m_unmodelled3c[0x4];
	Vector2		m_startPos;				// +0x40
	Vector2		m_waveDir;				// +0x48
	Vector2		m_perpDir;				// +0x50
	char m_unmodelled58[0x14];
	Int		m_fadeMs;					// +0x6c
	Int		m_totalMs;					// +0x70
	Int			m_elapsedMs;			// +0x74
	Real	m_waveInitialWidth;			// +0x78
	Real	m_waveInitialHeight;		// +0x7c
	Real	m_waveFinalWidth;			// +0x80
	char m_unmodelled84[0x4];
	Real	m_waveFinalHeight;			// +0x88
	Real m_initialVelocity;				// +0x8c
	char m_unmodelled90[0x4];
	Real m_timeToReachBeach;			// +0x94
	Real m_frontSlowDownAcc;			// +0x98
	Real m_timeToStop;					// +0x9c
	Real m_timeToRetreat;				// +0xa0
	Real m_backSlowDownAcc;				// +0xa4
	Real m_timeToCompress;				// +0xa8
	Real m_flipU;						// +0xac
};

class WaterTracksRenderSystem
{
public:
	DX8VertexBufferClass		*m_vertexBuffer;
	DX8IndexBufferClass			*m_indexBuffer;
};
extern WaterTracksRenderSystem *TheWaterTracksRenderSystem;

#define WATER_VB_PAGES	1000
#define WATER_STRIP_X	2
#define WATER_STRIP_Y	2

Int WaterTracksObj::render(DX8VertexBufferClass	*vertexBuffer, Int batchStart, RenderInfoClass &rinfo)
{
	VertexFormatXYZDUV1 *vb;
	Vector2	waveTailOrigin,waveFrontOrigin;
	Real	ooWaveDirLen=1.0f/m_waveDir.Length();	//one over length
	Real	waterHeight;
	Real	waveAlpha;
	Real	widthFrac;
	Real	heightFrac;

	if (batchStart < (WATER_VB_PAGES*WATER_STRIP_X*WATER_STRIP_Y-m_x*m_y))
	{	//we have room in current VB, append new verts
		if(vertexBuffer->Get_DX8_Vertex_Buffer()->Lock(batchStart*vertexBuffer->FVF_Info().Get_FVF_Size(),m_x*m_y*vertexBuffer->FVF_Info().Get_FVF_Size(),(unsigned char**)&vb,D3DLOCK_NOOVERWRITE) != D3D_OK)
			return batchStart;
	}
	else
	{	//ran out of room in last VB, request a substitute VB.
		if(vertexBuffer->Get_DX8_Vertex_Buffer()->Lock(0,m_x*m_y*vertexBuffer->FVF_Info().Get_FVF_Size(),(unsigned char**)&vb,D3DLOCK_DISCARD) != D3D_OK)
			return batchStart;
		batchStart=0;	//reset start of page to first vertex
	}

	heightFrac=1.0f;
	widthFrac = 1.0f;

	if (m_type == WaveTypeStationary)
	{	//stationary wave
		waveFrontOrigin = m_startPos;
		waveFrontOrigin -= m_perpDir*m_waveFinalWidth*0.5f;	//offset to left edge of wave
		waveTailOrigin = waveFrontOrigin - m_waveFinalHeight * ooWaveDirLen*m_waveDir;
		waveAlpha = 0.0f;

		if (m_elapsedMs >= m_totalMs)
			m_elapsedMs = 0;	//done with effect*/
		if (m_elapsedMs > (m_timeToReachBeach + m_timeToStop -1000 + m_fadeMs))
		{	//fading out
			waveAlpha = m_elapsedMs-(m_timeToReachBeach + m_timeToStop - 1000 +m_fadeMs);
			waveAlpha = waveAlpha / m_timeToRetreat;
			waveAlpha = 1.0f - waveAlpha;
			if (waveAlpha < 0.0f)
				waveAlpha = 0.0f;
		}
		else
		if (m_elapsedMs > (m_timeToReachBeach + m_timeToStop - 1000))
		{	//start fading up
			waveAlpha = m_elapsedMs-(m_timeToReachBeach + m_timeToStop - 1000);
			waveAlpha = waveAlpha / m_fadeMs;
			if (waveAlpha > 1.0f)
				waveAlpha = 1.0f;
		}
	}
	else
	{	//moving wave
		if (m_elapsedMs < m_timeToReachBeach)
		{
			waveAlpha = m_elapsedMs / m_timeToReachBeach;
			widthFrac = waveAlpha;
			widthFrac=(m_waveInitialWidth + widthFrac* (m_waveFinalWidth-m_waveInitialWidth))/m_waveFinalWidth;

			waveFrontOrigin = m_startPos + m_initialVelocity*m_elapsedMs*ooWaveDirLen*m_waveDir;
			waveFrontOrigin -= m_perpDir*m_waveFinalWidth*0.5f*widthFrac;
			waveTailOrigin = waveFrontOrigin - m_waveInitialHeight * ooWaveDirLen*m_waveDir;
		}
		else
		if (m_elapsedMs < m_totalMs)
		{	waveAlpha = 1.0f;
			widthFrac = 1.0f;
			waveFrontOrigin = m_startPos + m_initialVelocity*m_timeToReachBeach*ooWaveDirLen*m_waveDir;
			waveTailOrigin = waveFrontOrigin;
			Real elapsedMs=m_elapsedMs - m_timeToReachBeach;
			waveFrontOrigin += (m_initialVelocity*elapsedMs+0.5f*m_frontSlowDownAcc*elapsedMs*elapsedMs)*ooWaveDirLen*m_waveDir;
			waveFrontOrigin -= m_perpDir*m_waveFinalWidth*0.5f*widthFrac;

			Real timeSinceBacktrack = m_elapsedMs - m_timeToReachBeach - m_timeToStop;
			if (timeSinceBacktrack < 0)
				timeSinceBacktrack = 0;
			waveAlpha = timeSinceBacktrack/m_fadeMs;
			if (waveAlpha > 1.0f)
				waveAlpha = 1.0f;

			waveAlpha = 1.0f - waveAlpha;

			waveTailOrigin -= m_waveInitialHeight * ooWaveDirLen*m_waveDir;

			if (m_elapsedMs > (m_timeToReachBeach+m_timeToStop+m_timeToCompress))
			{	elapsedMs=elapsedMs;
				waveTailOrigin += (0.5f*m_backSlowDownAcc*(m_timeToStop+m_timeToCompress)*(m_timeToStop+m_timeToCompress))*ooWaveDirLen*m_waveDir;
				Real newElapsed = m_elapsedMs - (m_timeToReachBeach+m_timeToStop+m_timeToCompress);
				waveTailOrigin += (0.5f*m_frontSlowDownAcc*newElapsed*newElapsed)*ooWaveDirLen*m_waveDir;
			}
			else
			waveTailOrigin += (0.5f*m_backSlowDownAcc*elapsedMs*elapsedMs)*ooWaveDirLen*m_waveDir;

			waveTailOrigin -= m_perpDir*m_waveFinalWidth*0.5f*widthFrac;
		}
		else
		{	m_elapsedMs = 0;
			waveAlpha = m_elapsedMs / m_timeToReachBeach;
			widthFrac = waveAlpha;
			widthFrac=(m_waveInitialWidth + widthFrac* (m_waveFinalWidth-m_waveInitialWidth))/m_waveFinalWidth;

			waveFrontOrigin = m_startPos + m_initialVelocity*m_elapsedMs*ooWaveDirLen*m_waveDir;
			waveFrontOrigin -= m_perpDir*m_waveFinalWidth*0.5f*widthFrac;
			waveTailOrigin = waveFrontOrigin - m_waveInitialHeight * ooWaveDirLen*m_waveDir;
		}
	}

	Vector2 tailRight = waveTailOrigin + m_perpDir*m_waveFinalWidth*widthFrac;
	Vector2 frontRight = waveFrontOrigin + m_perpDir*m_waveFinalWidth*widthFrac;
	TheTerrainLogic->isUnderwater(waveTailOrigin.X,waveTailOrigin.Y,&waterHeight);

	Vector3 points[4];
	points[0].Set(waveTailOrigin.X, waveTailOrigin.Y, waterHeight+1.5f);
	points[1].Set(tailRight.X, tailRight.Y, waterHeight+1.5f);
	points[2].Set(waveFrontOrigin.X, waveFrontOrigin.Y, waterHeight+1.5f);
	points[3].Set(frontRight.X, frontRight.Y, waterHeight+1.5f);
	AABoxClass box(points, 4);
	if (((const BFMECameraCullBox *)&rinfo.Camera)->Cull_Box(box))
		return batchStart;

	if (TheShroudManager)
	{
		Int playerIndex = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;
		Bool shrouded = true;
		for (Int i = 0; i < 4; i++)
		{
			Coord3D pos;
			pos.x = points[i].X;
			pos.y = points[i].Y;
			pos.z = waterHeight+1.5f;
			if (TheShroudManager->getShroudStatusForPlayer(playerIndex, &pos) != CELLSHROUD_SHROUDED)
			{
				shrouded = false;
				break;
			}
		}
		if (shrouded)
			return batchStart;
	}

	vb->x=	waveTailOrigin.X;
	vb->y=	waveTailOrigin.Y;
	vb->z=waterHeight+1.5f;
	vb->diffuse=((Int)(waveAlpha*255.0f)<<24) |0xffffff;
	if (m_flipU)
		vb->u1=1;
	else
		vb->u1=0;
	vb->v1=0;
	vb++;
	vb->x=	tailRight.X;
	vb->y=	tailRight.Y;
	vb->z=waterHeight+1.5f;
	vb->diffuse=((Int)(waveAlpha*255.0f)<<24) |0xffffff;
	if (m_flipU)
		vb->u1=0.0f;
	else
		vb->u1=1.0f;
	vb->v1=0;
	vb++;
	vb->x=	waveFrontOrigin.X;
	vb->y=	waveFrontOrigin.Y;
	vb->z=waterHeight+1.5f;
	vb->diffuse=((Int)(waveAlpha*255.0f)<<24) |0xffffff;
	if (m_flipU)
		vb->u1=1;
	else
		vb->u1=0;
	vb->v1=1.0f;
	vb++;
	vb->x=	frontRight.X;
	vb->y=	frontRight.Y;
	vb->z=waterHeight+1.5f;
	vb->diffuse=((Int)(waveAlpha*255.0f)<<24) |0xffffff;
	if (m_flipU)
		vb->u1=0;
	else
		vb->u1=1.0f;
	vb->v1=1.0f;
	vb++;

	vertexBuffer->Get_DX8_Vertex_Buffer()->Unlock();

	Int idxCount=(m_y-1)*(m_x*2+2) - 2;	//index count

	DX8Wrapper::Set_Index_Buffer(TheWaterTracksRenderSystem->m_indexBuffer,batchStart);
	DX8Wrapper::Draw_Strip(0,idxCount-2,0,m_x*m_y);

	return batchStart+m_x*m_y;
}
