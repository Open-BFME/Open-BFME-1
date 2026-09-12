// ?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ
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
// vtable at 0x10 is the "this" the retail body operates on, so m_enabled
// (the real header's m_enabled) reads at this+0x10, and getObject() reads
// m_object at this-8. TheTerrainLogic and Object are BFME-vtable-drifted
// against the vendored headers (isUnderwater sits at retail slot 19/0x4c,
// getDrawable at slot 10/0x28) so both get minimal TU-local views sized to
// the verified slot instead of the real classes.

#include "PreRTS.h"

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

// BFME matrix at +0x198 is also proved by the matched Drawable setter:
// RVA 0x00411840, reached through ILT 0x0003AAD0, takes (Matrix3D const*, bool).
// Its field remains address-qualified because no member-name witness exists.
class Drawable
{
public:
	unsigned char m_pad000[0x198];
	Matrix3D m_at198;					///< +0x198

	const Matrix3D *getInstanceMatrix() const { return &m_at198; }
	void setInstanceMatrix( const Matrix3D *instance, bool extra );
};

// Minimal TerrainLogic view: only isUnderwater's slot (retail 19, offset
// 0x4c) needs to be correct; the other 19 slots are unused padding.
class TerrainLogic
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

extern TerrainLogic *TheTerrainLogic;		// ?TheTerrainLogic@@3PAVTerrainLogic@@A

// Minimal GameLogic view: only the frame counter at +0x3c is read.
class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	unsigned int m_frame;					///< +0x3c
	unsigned int getFrame() const { return m_frame; }
};

extern GameLogic *TheGameLogic;			// ?TheGameLogic@@3PAVGameLogic@@A

// Minimal Object view: slot 10 (offset 0x28) is the verified retail slot
// for getDrawable(); m_cachedPos sits at +0x38 (plain field, not virtual).
class Thing
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable();

	unsigned char m_pad004[0x38 - 0x04];
	Coord3D m_cachedPos;						///< +0x38

	const Coord3D *getPosition() const { return &m_cachedPos; }	
	void setPosition( const Coord3D *pos );	///< ?setPosition@Thing@@QAEXPBUCoord3D@@@Z
};

class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	ObjectModule(Thing *, const ModuleData *);

	virtual void objectModuleAnchor();		///< vptr at 0x00

	void *m_04;
	void *m_object;								///< ends at 0x0c

	Thing *getObject() const { return (Thing *)m_object; }
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

	bool m_enabled;							///< 0x20
};

// ?update@FloatUpdate@@UAE?AW4UpdateSleepTime@@XZ at retail RVA 0x002950D0
// Zero Hour reference source: GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdate.cpp
UpdateSleepTime FloatUpdate::update( void )
{
	if( m_enabled == TRUE )
	{
		const Coord3D *pos = getObject()->getPosition();

		Real waterZ;
		TheTerrainLogic->isUnderwater( pos->x, pos->y, &waterZ, 0 );

		Coord3D newPos;
		newPos.x = pos->x;
		newPos.y = pos->y;
		newPos.z = waterZ;
		getObject()->setPosition( &newPos );
	}

	Drawable *draw = getObject()->getDrawable();
	if (draw)
	{
		Real angle = INT_TO_REAL(TheGameLogic->getFrame());
		Real yaw = sin(angle * 0.0291f) * 0.05f;
		Real pitch = sin(angle * 0.0515f) * 0.05f;

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
