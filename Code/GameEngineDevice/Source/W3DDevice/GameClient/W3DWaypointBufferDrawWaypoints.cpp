// cl: /DNDEBUG /MD /EHsc
// stlport
//
// W3DWaypointBuffer::drawWaypoints at retail 0x00746A30 (687 bytes).
// Identity: Zero Hour twin W3dWaypointBuffer.cpp drawWaypoints (waypoint-mode
// gate, ambient-only LightEnvironmentClass, RenderInfoClass copy, 513-entry
// Vector3 point array, WW3D::Render per node, Set_Points + line Render), and
// its only caller HeightMapRenderObjClass::Render at 0x006D3480 calls it
// through ILT 0x000377EA as `if (m_waypointBuffer) m_waypointBuffer->drawWaypoints(rinfo)`.
// BFME dropped the Zero Hour rally-point else-branch.

#include <list>
#include <bitset>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

#define MAX_DISPLAY_NODES 512

enum KindOfType
{
	KINDOF_IGNORED_IN_GUI = 47
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Vector3
{
public:
	Vector3(void) {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Set(const Vector3 &that) { X = that.X; Y = that.Y; Z = that.Z; }

	float X;
	float Y;
	float Z;
};

class Matrix3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void Render(class RenderInfoClass &rinfo);
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform(void) const;
	virtual void slot21();
	virtual void Set_Position(const Vector3 &v);

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)m_transform;
	}

	unsigned char m_unreconstructed_04[0x18 - 4];
	unsigned char m_transform[0x30];
};

class CameraClass : public RenderObjClass {};

class SegmentedLineClass : public RenderObjClass
{
public:
	void Set_Points(unsigned int num_points, Vector3 *locs);
};

class Gen_uw_0094a880
{
public:
	~Gen_uw_0094a880();
};

// Size 0x228 from LightEnvironmentClassConstructor.cpp (retail 0x0094AAF0).
class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void) { reinterpret_cast<Gen_uw_0094a880 *>(this)->~Gen_uw_0094a880(); }
	void Reset(const Vector3 &object_center, const Vector3 &scene_ambient);
	void Pre_Render_Update(const Matrix3D &camera_tm);

private:
	unsigned char m_unreconstructed_000[0x228];
};

struct Rva00923880Owner
{
	void releaseStacks(void);
};

// layout: RenderInfoClassConstructorBfme.cpp (retail 0x00923690), 0x1b8 bytes.
class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass &cam);
	~RenderInfoClass(void) { reinterpret_cast<Rva00923880Owner *>(this)->releaseStacks(); }

	CameraClass &Camera;
	float fog_scale;
	float fog_start;
	float fog_end;
	float alphaOverride;
	float materialPassAlphaOverride;
	float materialPassEmissiveOverride;
	LightEnvironmentClass *light_environment;
	void *Texture_Projector;
	unsigned char m_unreconstructed_24[0x1b8 - 0x24];
};

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
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

// m_kindof: KindOfMaskType; the STLport bitset test is what gives retail's
// dword load + `test ch,ch; js` for bit 47 (a plain mask narrows to a byte).
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType t) const { return m_kindof.test(t); }

	unsigned char m_unreconstructed_008[0xC8 - 0x08];
	_STL::bitset<96> m_kindof;
};

// Rva0016F770Path is the ledger's address-derived name for the goal-path
// lookup at 0x0016F770 reached through AIUpdateInterface+0x30 (ZH:
// getStateMachine()->getGoalPathPosition(index)).
struct Rva0016F770Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0016F770Path
{
public:
	Rva0016F770Coord3D *getPoint(int index);
};

class AIUpdateInterface
{
public:
	// retail 0x00271AE0 via ILT 0x0000BD84: ZH AIUpdate.cpp body (state id vs
	// AI_FOLLOW_PATH=6 with INVALID_STATE_ID 999999, then goal-path size / 12).
	Int friend_getWaypointGoalPathSize() const;
	Int friend_getCurrentGoalPathIndex() const { return m_nextGoalPathIndex; }
	const Rva0016F770Coord3D *friend_getGoalPathPosition(Int index) const { return m_stateMachine->getPoint(index); }

	unsigned char m_unreconstructed_000[0x30];
	Rva0016F770Path *m_stateMachine;
	unsigned char m_unreconstructed_034[0x194 - 0x34];
	Int m_nextGoalPathIndex;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const
	{
		if (!m_template)
			return 0;
		return (const ThingTemplate *)m_template->getFinalOverride();
	}
	Bool isKindOf(KindOfType t) const { return getTemplate()->isKindOf(t); }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	AIUpdateInterface *getAI() { return m_ai; }

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_cachedPos;
	unsigned char m_unreconstructed_044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class Drawable
{
public:
	Object *getObject() { return m_object; }

	unsigned char m_unreconstructed_000[0xFC];
	Object *m_object;
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;
#undef BFME_UI_SLOT

	Bool isInWaypointMode() const { return m_waypointMode; }

	unsigned char m_pad004[0x12AC];
	Bool m_waypointMode;
};

extern InGameUI *TheInGameUI;

class W3DWaypointBuffer
{
public:
	void drawWaypoints(RenderInfoClass &rinfo);

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
};

void W3DWaypointBuffer::drawWaypoints(RenderInfoClass &rinfo)
{
	if( TheInGameUI && TheInGameUI->isInWaypointMode() )
	{
		LightEnvironmentClass lightEnv;
		lightEnv.Reset(Vector3(0,0,0), Vector3(1.0f,1.0f,1.0f));
		lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		RenderInfoClass localRinfo(rinfo.Camera);
		localRinfo.light_environment=&lightEnv;
		Vector3 points[ MAX_DISPLAY_NODES + 1 ];

		const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
		Drawable *draw;
		for( DrawableListCIt it = selected->begin(); it != selected->end(); ++it )
		{
			draw = *it;
			Object *obj = draw->getObject();
			Int numPoints = 1;
			if( obj && ! obj->isKindOf( KINDOF_IGNORED_IN_GUI ))
			{
				AIUpdateInterface *ai = obj->getAI();
				Int goalSize = ai ? ai->friend_getWaypointGoalPathSize() : 0;
				Int gpIdx = ai ? ai->friend_getCurrentGoalPathIndex() : 0;
				if( ai && gpIdx >= 0 && gpIdx < goalSize )
				{
					const Coord3D *pos = obj->getPosition();
					points[ 0 ].Set( Vector3( pos->x, pos->y, pos->z ) );

					for( int i = gpIdx; i < goalSize; i++ )
					{
						const Rva0016F770Coord3D *waypoint = ai->friend_getGoalPathPosition( i );
						if( waypoint )
						{
							if( numPoints < MAX_DISPLAY_NODES + 1 )
							{
								points[ numPoints ].Set( Vector3( waypoint->x, waypoint->y, waypoint->z ) );
								numPoints++;
							}

							m_waypointNodeRobj->Set_Position(Vector3(waypoint->x,waypoint->y,waypoint->z));
							WW3D::Render(*m_waypointNodeRobj,localRinfo);
						}
					}
					m_line->Set_Points( numPoints, points );
					m_line->Render( localRinfo );
				}
			}
		}
	}
}
