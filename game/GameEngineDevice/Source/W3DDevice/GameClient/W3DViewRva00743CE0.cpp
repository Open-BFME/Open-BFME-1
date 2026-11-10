// cl:  /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00743CE0, 530 bytes (ret 0x10 at +0x1F5 and +0x20F): BFME W3DView
// virtual, vtable 0x011217A0 slot 115 (VA 0x0112196C -> ILT 0x00027F84).
// Locks the camera on an object: saves the current view into the globals at
// 0x012F9DC0..0x012F9DF8 the first time, takes the object's template camera
// offset and pitch, and faces it along the object's orientation. Native method
// name and argument meaning are unproven, so the name keeps the address.
// Evidence: targets/game/reverse/identity_evidence/00743ce0-w3dview-object-camera-mode.md
typedef int Int;
typedef bool Bool;
typedef float Real;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7FFFFFFF
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

// Retail 0x0073A680 copies the template's +0x4B8 vector into the out
// parameter and returns it.
struct Vec3
{
	Real x;
	Real y;
	Real z;
};

class Rva0073A680
{
public:
	Vec3 *getPosition(Vec3 *out) const;

	char m_pad00[0x4C4];
	Real m_cameraPitch;					// +0x4C4
};

class Object
{
public:
	Rva0073A680 *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (Rva0073A680 *)m_template->getFinalOverride();
	}

	void *m_vptr;
	Overridable *m_template;				// +0x04
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;						// +0x38
	Real m_orientation;					// +0x44
	char m_pad48[0x74 - 0x48];
	ObjectID m_id;						// +0x74
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

// Retail 0x005A4570 is called on TheMouse but reads only globals.
class Mouse
{
public:
	void rva005A4570();
	void _bfme_setEngineVisibility(Bool visible);

	char m_pad0000[0x4E0D];
	Bool m_4e0d;						// +0x4E0D
};

class Rva003FD060TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const;	// +0x18
};
// The global at 0x012EF4CC is EA's TerrainLogic *TheTerrainLogic
// (?TheTerrainLogic@@3PAVTerrainLogic@@A), defined in
// game/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp. The struct above is
// this TU's local ABI view of the slots it calls, cast to at the use; the cast
// is a no-op, so the bytes are unchanged.
class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeDirectionWeight1285;		// VA 0x01075C74, 10.0f
extern Mouse *TheMouse;

void __fastcall normAngle(Real &angle);
extern const Real g_bfmeDefaultEG;			// VA 0x01097114, pi/2

// The view saved on entering the mode; read back by the W3DView body at
// 0x0073D4C0. Only the two vectors are extern here: file-static scalars give
// retail's load/store schedule (the scalar stores do not block later loads).
extern Coord3D g_Va012F9DE4;
static Real g_Va012F9DD8;
static Real g_Va012F9DD4;
static Real g_Va012F9DD0;
extern Coord3D g_Va012F9DF0;
static Real g_Va012F9DCC;
static Real g_Va012F9DC8;
static Real g_Va012F9DC4;
static Real g_Va012F9DC0;

class W3DView
{
public:
    virtual void slot000();
    virtual void slot001();
    virtual void slot002();
    virtual void slot003();
    virtual void slot004();
    virtual void slot005();
    virtual void slot006();
    virtual void slot007();
    virtual void slot008();
    virtual void slot009();
    virtual void slot010();
    virtual void slot011();
    virtual void slot012();
    virtual void slot013();
    virtual void slot014();
    virtual void slot015();
    virtual void slot016();
    virtual void slot017();
    virtual void slot018();
    virtual void slot019();
    virtual void slot020();
    virtual void lookAt(const Coord3D *o);				// slot 21, +0x54
    virtual void slot022();
    virtual void slot023();
    virtual void slot024();
    virtual void slot025();
    virtual void slot026();
    virtual void slot027();
    virtual void slot028();
    virtual void slot029();
    virtual void slot030();
    virtual void slot031();
    virtual void slot032();
    virtual void slot033();
    virtual void slot034();
    virtual void slot035();
    virtual void slot036();
    virtual void slot037();
    virtual void slot038();
    virtual void slot039();
    virtual void slot040();
    virtual void slot041();
    virtual void slot042();
    virtual void slot043();
    virtual void slot044();
    virtual void slot045();
    virtual void slot046();
    virtual void slot047();
    virtual void slot048();
    virtual void slot049();
    virtual void slot050();
    virtual void slot051();
    virtual void slot052();
    virtual void slot053();
    virtual void slot054();
    virtual void slot055();
    virtual void slot056();
    virtual void slot057();
    virtual void slot058();
    virtual void slot059();
    virtual void slot060(Real pitch, Int a, Int b, Int c);	// +0xF0
    virtual void slot061();
    virtual void slot062();
    virtual void slot063();
    virtual void slot064();
    virtual void slot065();
    virtual void slot066();
    virtual void slot067();
    virtual void slot068();
    virtual void slot069();
    virtual void slot070();
    virtual void slot071();
    virtual void slot072();
    virtual void slot073();
    virtual void slot074();
    virtual void slot075();
    virtual void slot076();
    virtual void slot077();
    virtual void slot078();
    virtual void slot079();
    virtual void slot080();
    virtual void slot081();
    virtual void slot082();
    virtual void slot083();
    virtual void slot084();
    virtual void slot085();
    virtual void slot086();
    virtual void slot087();
    virtual void slot088();
    virtual void slot089();
    virtual void slot090();
    virtual void slot091();
    virtual void slot092();
    virtual void slot093();
    virtual void slot094();
    virtual void slot095();
    virtual void slot096();
    virtual void slot097();
    virtual void slot098();
    virtual void slot099();
    virtual void slot100();
    virtual void slot101();
    virtual void slot102();
    virtual void slot103();
    virtual void slot104();
    virtual void slot105();
    virtual void slot106();
    virtual void slot107();
    virtual void slot108();
    virtual void slot109();
    virtual void slot110();
    virtual void slot111();
    virtual void slot112();
    virtual void slot113();
    virtual Bool rva00746080Gate();				// slot 114, +0x1C8
    virtual void rva00743CE0(Int unused, ObjectID id, Bool enable, Bool repitch);	// slot 115, +0x1CC
    virtual ObjectID getCameraLock();				// slot 116, +0x1D0
    virtual void setCameraLock(ObjectID id);			// slot 117, +0x1D4
    virtual void rva0073D4C0();				// slot 118, +0x1D8
    virtual void slot119();
    virtual void slot120();					// +0x1E0
    virtual Bool slot121();					// +0x1E4
    virtual void slot122();
    virtual void slot123();
    virtual void slot124();
    virtual void slot125();
    virtual void slot126();
    virtual void slot127();
    virtual void slot128();
    virtual void slot129();
    virtual void slot130();
    virtual void slot131(Real a, Real b);			// +0x20C
    virtual void slot132();
    virtual void slot133();
    virtual void slot134();
    virtual void slot135();
    virtual void slot136();
    virtual void slot137();
    virtual void slot138();
    virtual void slot139();
    virtual void slot140();
    virtual void slot141();
    virtual void slot142();
    virtual void slot143();
    virtual void slot144();
    virtual void slot145();
    virtual void slot146();
    virtual void slot147();
    virtual void slot148();
    virtual void slot149();
    virtual void slot150();
    virtual void slot151();
    virtual void slot152();
    virtual void slot153(Int a);				// +0x264
    virtual Bool slot154();					// +0x268
    virtual void slot155();
    virtual void slot156(Int a);				// +0x270

private:
	char m_pad0004[0x0C - 0x04];
	Coord3D m_pos;						// +0x0C
	char m_pad0018[0x28 - 0x18];
	Real m_angle;						// +0x28
	Real m_2c;						// +0x2C
	char m_pad0030[0x3C - 0x30];
	Real m_3c;						// +0x3C
	Real m_40;						// +0x40
	char m_pad0044[0x4C - 0x44];
	Real m_4c;						// +0x4C
	Real m_50;						// +0x50
	char m_pad0054[0x6C - 0x54];
	Real m_FXPitch;						// +0x6C
	Real m_pitch;						// +0x70
	char m_pad0074[0xAC - 0x74];
	Real m_ac;						// +0xAC
	Real m_b0;						// +0xB0
	char m_pad00b4[0x23D8 - 0xB4];
	Coord3D m_cameraOffset;					// +0x23D8
	char m_pad23e4[0x23F8 - 0x23E4];
	Real m_groundLevel;						// +0x23F8
	char m_pad23fc[0x240C - 0x23FC];
	Bool m_cameraConstraintValid;						// +0x240C
	char m_pad240d[0x2439 - 0x240D];
	Bool m_objectCameraMode;				// +0x2439
	char m_pad243a[0x2474 - 0x243A];
	Real m_2474;						// +0x2474
	Real m_2478;						// +0x2478
	char m_pad247c[0x2481 - 0x247C];
	Bool m_2481;						// +0x2481
	Bool m_2482;						// +0x2482
	Bool m_2483;						// +0x2483
};

// ?rva00743CE0@W3DView@@UAEXHW4ObjectID@@_N1@Z
void W3DView::rva00743CE0(Int unused, ObjectID id, Bool enable, Bool repitch)
{
	if (enable)
	{
	if (rva00746080Gate())
		return;

	Object *obj = TheGameLogic->findObjectByID(id);
	if (obj)
	{
	getCameraLock();
	ObjectID objId = obj->m_id;
	if (objId != getCameraLock())
	{
		if (!m_objectCameraMode)
		{
			g_Va012F9DD8 = m_FXPitch;
			g_Va012F9DE4 = m_pos;
			g_Va012F9DD4 = m_3c;
			g_Va012F9DD0 = m_50;
			g_Va012F9DF0 = m_cameraOffset;
			g_Va012F9DCC = m_angle;
			g_Va012F9DC8 = m_pitch;
			g_Va012F9DC4 = m_ac;
			g_Va012F9DC0 = m_b0;
		}
		m_objectCameraMode = true;
		setCameraLock(obj->m_id);
		slot131(-0.0872664675f, 1.55334306f);
		lookAt(&obj->m_pos);
		Vec3 offset;
		m_cameraOffset = *(const Coord3D *)obj->getTemplate()->getPosition(&offset);
		if (!m_objectCameraMode || repitch)
		{
			Real pitch = obj->getTemplate()->m_cameraPitch * (3.14159265359f / 180.0f);
			m_pitch = pitch;
			slot060(pitch, 1, 0, 0);
			if (m_2483)
				m_angle = obj->m_orientation - g_bfmeDefaultEG;
			else if (m_2481)
				m_angle = 0.0f;
			else
				m_angle = obj->m_orientation;
			normAngle(m_angle);
			m_FXPitch = 0.87266463041305542f;
		}
		m_2482 = true;
	}
	}
	}
	else
		rva0073D4C0();
	TheMouse->rva005A4570();
}

// v6c,pos,3c,50,off,ang,pit,ac,b0

// ext pos,off,ang


// Retail 0x0073D4C0, 423 bytes: slot 118 leaves the object camera mode and
// restores the view the call above saved.
// ?rva0073D4C0@W3DView@@UAEXXZ
void W3DView::rva0073D4C0()
{
	rva00746080Gate();
	if (!rva00746080Gate())
		return;

	getCameraLock();
	setCameraLock(INVALID_ID);
	m_FXPitch = g_Va012F9DD8;
	if (m_2483)
	{
		Coord3D pos;
		pos.x = m_2474;
		pos.y = m_2478;
		pos.z = 0.0f;
		m_pos = pos;
	}
	m_pos.z = g_Va012F9DE4.z;
	m_3c = g_Va012F9DD4;
	m_50 = m_40 = g_Va012F9DD0;
	m_cameraOffset = g_Va012F9DF0;
	m_angle = g_Va012F9DCC;
	m_2c = m_4c;
	m_pitch = g_Va012F9DC8;
	m_ac = g_Va012F9DC4;
	m_b0 = g_Va012F9DC0;

	Real height;
	if (TheTerrainLogic)
	{
		height = ((Rva003FD060TerrainLogic *)TheTerrainLogic)->getGroundHeight(m_pos.x, m_pos.y, 0);
		if (height > 700.0f)
			height = 700.0f;
	}
	else
		height = g_bfmeDirectionWeight1285;
	if (height != m_groundLevel)
	{
		m_groundLevel = height;
		m_cameraConstraintValid = false;
	}
	m_objectCameraMode = false;
	TheMouse->rva005A4570();
	if (slot121())
		slot120();
	slot156(0);
	if (slot154())
		slot153(0);
	TheMouse->_bfme_setEngineVisibility(true);
	TheMouse->m_4e0d = false;
}
