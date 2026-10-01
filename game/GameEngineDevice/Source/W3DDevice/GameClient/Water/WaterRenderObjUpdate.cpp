// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// BFME WaterRenderObjClass::update, retail 0x007A7D70 (1342 bytes).
// Identity: the matched caller BfmeThingQE::bfmeGoQE (BfmeConv907.cpp) reaches
// this body through ILT 0x0001117B where the Zero Hour W3DTerrainVisual::update
// calls m_waterRenderObject->update(); the body keeps the twin's river offset
// scroll (8.25e-5 / 1.65e-4 = 0.0125*33/5000), the NUM_BUMP_FRAMES (32) bump
// counter and the vertex-animated grid pass (0.93 dampening, gravity*3).
//
// BFME differences from the twin, all witnessed by the retail bytes:
//  - m_riverVOrigin is gone; instead a wall-clock delta (timeGetTime through
//    a function-local static, or MSEC_PER_LOGICFRAME_REAL when GlobalData+0xdcd
//    is set) advances +0x5c by +0x4c on every element of the STLport list of
//    pointers at this+0x2ac (the matched constructor builds that list);
//  - when bit 0 of the flag word at 0x012EF418 is raised, the list is rebuilt
//    through ILT 0x000151D6 (retail 0x007A50A0: thiscall, ret 4, fills this+0x2ac
//    with 0x80-byte objects built from polygon triggers) and the bit is cleared.
// Layout: offsets from the matched constructor (WaterRenderObjConstructor.cpp)
// and the matched W3DWater.cpp grid methods (addVelocity, changeGridHeight).
#include <math.h>
#include <list>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#define NUM_BUMP_FRAMES 32

// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
// A namespace-scope const Real has internal linkage, so each TU keeps its own
// copy in .rdata and MSVC loads it from there: retail reads this TU's copy at
// 0x011281DC rather than the pooled __real@42055555 literal.
enum
{
	MSEC_PER_SECOND = 1000,
	LOGICFRAMES_PER_SECOND = 30
};
const Real MSEC_PER_LOGICFRAME_REAL = (((Real)MSEC_PER_SECOND) / ((Real)LOGICFRAMES_PER_SECOND));

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

// Flag word whose bit 0 asks the water object to rebuild its polygon list.
extern UnsignedInt g_Rva00EEF418;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	char m_before1ac[0x1ac];
	Real m_gravity;							// +0x1ac
	char m_beforeDcd[0xdcd - 0x1b0];
	UnsignedByte m_fixedWaterStep0dcd;		// +0xdcd, BFME-only; not witnessed by name
};
extern GlobalData *TheWritableGlobalData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame(void) { return m_frame; }

private:
	char m_beforeFrame[0x3c];
	UnsignedInt m_frame;					// +0x3c
};
extern GameLogic *TheGameLogic;

// Element of the this+0x2ac list; built by retail 0x007A50A0 from a polygon
// trigger. Only the two floats update() touches are modelled.
struct PolygonListItem007A50A0
{
	char m_before4c[0x4c];
	Real m_rate04c;							// +0x4c
	char m_before5c[0x5c - 0x50];
	Real m_value05c;						// +0x5c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DWater.h
class WaterRenderObjClass
{
public:
	enum WaterMeshStatus
	{
		AT_REST = 0x00,
		IN_MOTION = 0x01
	};
	struct WaterMeshData
	{
		Real height;
		Real velocity;
		UnsignedByte status;
		UnsignedByte preferredHeight;
	};

	void update(void);
	void rebuildPolygonList007A50A0(Int unused);

protected:
	char m_before244[0x244];
	Int m_iBumpFrame;										// +0x244
	char m_before258[0x258 - 0x248];
	WaterMeshData *m_meshData;								// +0x258
	UnsignedInt m_meshDataSize;								// +0x25c
	Bool m_meshInMotion;									// +0x260
	Bool m_doWaterGrid;										// +0x261
	char m_before2a0[0x2a0 - 0x262];
	Int m_gridCellsX;										// +0x2a0
	Int m_gridCellsY;										// +0x2a4
	void *m_handle2a8;										// +0x2a8
	_STL::list<PolygonListItem007A50A0 *> m_polygonList;	// +0x2ac
	char m_before2bc[0x2bc - 0x2b0];
	Real m_riverXOffset;									// +0x2bc
	Real m_riverYOffset;									// +0x2c0
};

void WaterRenderObjClass::update(void)
{
	static UnsignedInt lastLogicFrame = 0;
	UnsignedInt currLogicFrame = 0;

	static UnsignedInt lastUpdateTime = timeGetTime();
	UnsignedInt now = timeGetTime();
	Real elapsedMs = (Real)(now - lastUpdateTime);
	if (TheWritableGlobalData->m_fixedWaterStep0dcd)
		elapsedMs = MSEC_PER_LOGICFRAME_REAL;
	Real elapsed = elapsedMs * 0.001f;
	lastUpdateTime = now;

	if (g_Rva00EEF418 & 1)
	{
		rebuildPolygonList007A50A0(0);
		g_Rva00EEF418 &= ~1;
	}

	if (TheGameLogic)
		currLogicFrame = TheGameLogic->getFrame();

	for (_STL::list<PolygonListItem007A50A0 *>::iterator it = m_polygonList.begin();
			it != m_polygonList.end(); ++it)
	{
		(*it)->m_value05c += elapsed * (*it)->m_rate04c;
	}

	m_riverXOffset += (Real)(0.0125*33/5000);
	m_riverYOffset += (Real)(2*0.0125*33/5000);
	if (m_riverXOffset > 1) m_riverXOffset -= 1;
	if (m_riverYOffset > 1) m_riverYOffset -= 1;
	if (m_riverXOffset < -1) m_riverXOffset += 1;
	if (m_riverYOffset < -1) m_riverYOffset += 1;
	m_iBumpFrame++;
	if (m_iBumpFrame >= NUM_BUMP_FRAMES) {
		m_iBumpFrame = 0;
	}

	// we only process some things if the logic frame has changed
	if( lastLogicFrame != currLogicFrame )
	{
		// for vertex animated water we need to update the vector field
		if( m_doWaterGrid && m_meshInMotion == true )
		{
			const Real PREFERRED_HEIGHT_FUDGE = 1.0f;
			const Real AT_REST_VELOCITY_FUDGE = 1.0f;
			const Real WATER_DAMPENING = 0.93f;
			Int i, j;
			Int	mx = m_gridCellsX+1;
			Int my = m_gridCellsY+1;
			WaterMeshData *pData;

			m_meshInMotion = false;

			for( j = 0, pData = m_meshData; j < (my + 2); j++ )
			{
				for( i = 0; i < (mx + 2); i++ )
				{
					if( pData->status & WaterRenderObjClass::IN_MOTION )
					{
						pData->velocity *= WATER_DAMPENING;

						if( pData->height < pData->preferredHeight )
							pData->velocity -= TheWritableGlobalData->m_gravity * 3.0f;
						else
							pData->velocity += TheWritableGlobalData->m_gravity * 3.0f;

						pData->height = pData->height + pData->velocity;

						if( fabs( pData->height - pData->preferredHeight ) < PREFERRED_HEIGHT_FUDGE &&
								fabs( pData->velocity ) < AT_REST_VELOCITY_FUDGE )
						{
							pData->status &= ~WaterRenderObjClass::IN_MOTION;
							pData->height = pData->preferredHeight;
							pData->velocity = 0.0f;
						}
						else
						{
							m_meshInMotion = true;
						}
					}

					pData++;
				}
			}
		}

		lastLogicFrame = currLogicFrame;
	}
}
