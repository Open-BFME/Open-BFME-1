// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// W3DPoliceCarDraw::doDrawModule, retail 0x00758EF0, 663 bytes. Identity: slot 9
// of the W3DPoliceCarDraw vtable 0x01122EA8 (thunk 0x0002E956), the class the
// "W3DPoliceCarDraw" literal names. The body is the Zero Hour one
// (W3DPoliceCarDraw.cpp:101) statement for statement.
//
// BFME differences: getRenderObject is virtual (slot 46), and the light layout
// is the one the matched createDynamicLight (W3DPoliceCarDrawCreateDynamicLight.cpp)
// proves. RenderObjClass is 0x34 bytes larger, so Ambient/Diffuse sit at
// +0xD8/+0xE4, the far attenuation range at +0x104/+0x108, and Set_Position is
// slot 22. The base call reaches W3DTruckDraw::doDrawModule, slot 9 of the
// vtable 0x011265B0 that the matched W3DTruckDraw constructor installs.

typedef float Real;
#define NULL 0

class Matrix3D;

extern void j_0001a041();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
// Copied member by member: retail keeps pos.x and pos.y on the x87 stack across
// the light setters and bit-copies pos.z. A POD struct copy gives a block copy
// instead (the Coord3D copy lever, docs/shape_levers.md).
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	Real x, y, z;
};

// Vector3 verbatim from WWMath/vector3.h, as the createDynamicLight sibling
// restates it.
class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) { }
	Vector3(const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/hanim.h
class HAnimClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual int Get_Num_Frames(void);						// slot 4
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21();
	virtual void Set_Position(const Vector3 &p);			// slot 22
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41(); virtual void slot42();
	virtual void slot43();
	virtual void Set_Animation(HAnimClass *motion, float frame, int anim_mode = 0);	// slot 44
	virtual void slot45();
	virtual HAnimClass *Peek_Animation(void);				// slot 46
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDynamicLight.h
class W3DDynamicLight : public RenderObjClass
{
public:
	void Set_Ambient(const Vector3 &color) { Ambient = color; }
	void Set_Diffuse(const Vector3 &color) { Diffuse = color; }
	void Set_Far_Attenuation_Range(double fStart, double fEnd) { FarAttenStart = fStart; FarAttenEnd = fEnd; }

	char			m_renderObjSlice[0xD4];		// LightClass head through +0xD7
	Vector3			Ambient;					// +0xD8
	Vector3			Diffuse;					// +0xE4
	char			m_specularAndNearSlice[0x14];	// Specular +0xF0, Near attenuation +0xFC/+0x100
	float			FarAttenStart;				// +0x104
	float			FarAttenEnd;				// +0x108
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	const Coord3D *getPosition(void) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTruckDraw.h
class W3DTruckDraw
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08();
	virtual void doDrawModule(const Matrix3D *transformMtx);	// slot 9
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25();
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual RenderObjClass *getRenderObject(void);			// slot 46

	Drawable *getDrawable(void) const { return m_drawable; }

	void *m_moduleData;							// +0x04
	Drawable *m_drawable;						// +0x08
	char m_truckTail[0x3EC - 0x0C];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DPoliceCarDraw.h
class W3DPoliceCarDraw : public W3DTruckDraw
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);

protected:
	W3DDynamicLight *createDynamicLight(void);

	W3DDynamicLight *m_light;					// +0x3EC
	Real m_curFrame;							// +0x3F0
};

void W3DPoliceCarDraw::doDrawModule(const Matrix3D *transformMtx)
{
	const Real floatAmt = 8.0f;
	const Real animAmt = 0.25;

	// get pointers to our render objects that we'll need
	RenderObjClass *policeCarRenderObj = getRenderObject();
	if( policeCarRenderObj == NULL )
		return;

	HAnimClass *anim = policeCarRenderObj->Peek_Animation();
	if (anim)
	{
		Real frames = anim->Get_Num_Frames();
		m_curFrame += animAmt;
		if (m_curFrame > frames-1) {
			m_curFrame = 0;
		}
		policeCarRenderObj->Set_Animation(anim, m_curFrame);
	}
	Real red = 0;
	Real green = 0;
	Real blue = 0;
	if (m_curFrame < 3) {
		red = 1; green = 0.5;
	} else if (m_curFrame < 6) {
		red = 1;
	} else if (m_curFrame < 7) {
		red = 1; green = 0.5;
	} else if (m_curFrame < 9) {
		red = 0.5+(9-m_curFrame)/4;
		blue = (m_curFrame-5)/6;
	} else if (m_curFrame < 12) {
		blue=1;
	} else if (m_curFrame <= 14) {
		green = (m_curFrame-11)/3;
		blue = (14-m_curFrame)/2;
		red =		(m_curFrame-11)/3;
	}

	// make us a light if we don't already have one
	if( m_light == NULL )
		m_light = createDynamicLight();

	// if we have a search light, position it
	if( m_light )
	{
		Coord3D pos = *getDrawable()->getPosition();
		m_light->Set_Diffuse( Vector3( red, green, blue) );
		m_light->Set_Ambient( Vector3( red/2, green/2, blue/2) );
		m_light->Set_Far_Attenuation_Range( 3, 20 );
		m_light->Set_Position( Vector3( pos.x,pos.y,pos.z+floatAmt ) );
	}
	// Retail's qualified base call lands on the 5-byte ILT thunk 0x0001A041
	// (?j_0001a041@@YAXXZ) that jumps to W3DTruckDraw::doDrawModule 0x00781660.
	union BaseDrawRoute
	{
		void (*raw)();
		void (W3DTruckDraw::*member)(const Matrix3D *);
	} route;
	route.raw = j_0001a041;
	(this->*route.member)(transformMtx);
}
