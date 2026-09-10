// ?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.95 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include

// Module-constructor family shape: an out-of-line ObjectModule base call
// (pinned at 0x000170E4), then UpdateModule's constructor inlined -- its two
// vtables at 0x0c and 0x10 then its three members -- then this class's own
// three vtables.
//
// Here the derived member follows the vtable stores because its value comes
// from the module data, not from a constant. UpdateModule's own members still
// group by value ahead of them.
//
// update() (retail 0x002950D0) reuses this exact layout: the interface
// vtable at 0x10 is the "this" the retail body operates on, so m_flag20
// (the real header's m_enabled) reads at this+0x10, and getObject() reads
// m_08 at this-8. TheTerrainLogic and Object are BFME-vtable-drifted
// against the vendored headers (isUnderwater sits at retail slot 19/0x4c,
// getDrawable at slot 10/0x28) so both get minimal TU-local views sized to
// the verified slot instead of the real classes.

typedef float Real;
typedef int Bool;
#define TRUE 1

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

#include "WWMath/matrix3d.h"
#include <math.h>

// Minimal Drawable view: the instance matrix sits at +0x198 and is read as
// twelve plain floats (getInstanceMatrix() is inlined in retail); setting it
// back is an out-of-line call (?setInstanceMatrix@Drawable@@QAEXPBVMatrix3D@@@Z,
// unpinned -- retail RVA 0x00811840 via ILT 0x0003AAD0).
class DrawableView
{
public:
	unsigned char m_pad000[0x198];
	Matrix3D m_instance;					///< +0x198

	const Matrix3D *getInstanceMatrix() const { return &m_instance; }
	void setInstanceMatrix( const Matrix3D *instance, int extra );
};

// Minimal TerrainLogic view: only isUnderwater's slot (retail 19, offset
// 0x4c) needs to be correct; the other 19 slots are unused padding.
class TerrainLogicView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	virtual Bool isUnderwater( Real x, Real y, Real *waterZ, Real *terrainZ );
};

extern void *TheTerrainLogic;			// ?TheTerrainLogic@@3PAXA

// Minimal GameLogic view: only the frame counter at +0x3c is read.
class GameLogicView
{
public:
	unsigned char m_pad000[0x3c];
	unsigned int m_frame;					///< +0x3c
};

extern GameLogicView *TheGameLogic;	// ?TheGameLogic@@3PAVGameLogicView@@A

// Minimal Object view: slot 10 (offset 0x28) is the verified retail slot
// for getDrawable(); m_position sits at +0x38 (plain field, not virtual).
class ObjectView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual DrawableView *getDrawable();

	unsigned char m_pad018[0x38 - 0x04];
	Coord3D m_position;						///< +0x38

	const Coord3D *getPosition() const { return &m_position; }
	void setPosition( const Coord3D *pos );	///< ?setPosition@Thing@@QAEXPBUCoord3D@@@Z
};

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();		///< vptr at 0x00

	void *m_04;
	void *m_08;								///< ends at 0x0c

	ObjectView *getObject() const { return (ObjectView *)m_08; }
};

class BehaviorInterface
{
public:
	virtual void behaviorAnchor() = 0;		///< vptr at 0x0c
};

class UpdateInterface
{
public:
	virtual UpdateSleepTime update() = 0;	///< vptr at 0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public ObjectModule,
	public BehaviorInterface, public UpdateInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData)
		: ObjectModule(thing, moduleData)
	{
		m_nextCallFrameAndPhase = 0;
		m_indexInLogic = -1;
		m_updateState = -1;
	}

	virtual void behaviorAnchor();
	virtual UpdateSleepTime update();

	int m_nextCallFrameAndPhase;			///< 0x14
	int m_indexInLogic;						///< 0x18
	int m_updateState;						///< 0x1c
};

// The trailing member is read from the module data at +8 rather than zeroed,
// which is why the vtable stores land before it and no register residual
// arises: only one zero is live, so 0x14 is written as an immediate.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h
class FloatUpdateModuleData
{
public:
	unsigned char m_head[8];
	bool m_enabled;							///< +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h
class FloatUpdate : public UpdateModule
{
public:
	FloatUpdate(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();
	virtual void behaviorAnchor();
	virtual UpdateSleepTime update();

	bool m_flag20;							///< 0x20
};

// ??0FloatUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
FloatUpdate::FloatUpdate( Thing *thing, const ModuleData *moduleData )
	: UpdateModule( thing, moduleData )
{
	m_flag20 = ((const FloatUpdateModuleData *)moduleData)->m_enabled;
}

// ?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ at retail RVA 0x002950D0
// Zero Hour reference source: GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdate.cpp
UpdateSleepTime FloatUpdate::update( void )
{
	if( m_flag20 == TRUE )
	{
		const Coord3D *pos = getObject()->getPosition();

		Real waterZ;
		((TerrainLogicView *)TheTerrainLogic)->isUnderwater( pos->x, pos->y, &waterZ, 0 );

		Coord3D newPos;
		newPos.x = pos->x;
		newPos.y = pos->y;
		newPos.z = waterZ;
		getObject()->setPosition( &newPos );
	}

	DrawableView *draw = getObject()->getDrawable();
	if (draw)
	{
		Real angle = (Real)(TheGameLogic->m_frame);
		Real yaw = sinf(angle * 0.0291f) * 0.05f;
		Real pitch = sinf(angle * 0.0515f) * 0.05f;

		Matrix3D mx = *draw->getInstanceMatrix();

		Real zRot = mx.Get_Z_Rotation();
		mx.Make_Identity();
		mx.Rotate_Z(zRot);
		mx.Rotate_Y(yaw);
		mx.Rotate_X(pitch);

		draw->setInstanceMatrix(&mx, 0);
	}

	return UPDATE_SLEEP_NONE;
}
