// ?step006E0080@Rva006E0080Owner@@QAEXPAUCoord3D@@0PAURva006E0080Context@@@Z
// partial score=0.7525 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// Retail 0x006E0080 (986 bytes): an anonymous camera-transition step.
//
// IDENTITY IS NOT RECOVERED.  The only caller is the still-unconverted body at
// 0x006E0580 (through ILT), which calls it thiscall with two Coord3D out
// pointers and a context record.  No vtable slot, string or Zero Hour twin
// names the owner, so every name here carries the address.
// Caller evidence: 0x006E0580 (Rva006E0580State::build, reached from
// W3DView::buildCameraTransform) passes its own this and its context argument,
// so the owner is that state object and the context is the 0xD8 Gen_006DFC60.
//
// What the bytes show: a five-state machine on this+0x2C.
//   - It compares a module AsciiString (0x012F8044) against "Target" and
//     "Zoom" to pick the requested state (2 or 3, else -1).
//   - It looks the context's object (+0xA4) up through
//     GameLogic::findObjectByID and seeds two tracks (+0x30 and +0x3C) from
//     the out pointers unless the context's +0x9C flag is set.
//   - It eases two blend factors, whose steps and limits are .data floats
//     0.4/0.03 and 0.5/0.05, to interpolate the tracks toward the object's
//     position (Thing::m_cachedPos, +0x38).
//   - In state 3 it projects the context's half screen size through
//     TheTacticalView->screenToTerrain (vtable +0x164, witnessed in
//     InGameUIBodies.cpp) into a point that is never read.

typedef int Int;
typedef float Real;
typedef bool Bool;

#define TRUE true
#define FALSE false

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	~StringBase();

public:
	int compare( const T *text ) const;

private:
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	~AsciiString() {}

	Int compare( const char *text ) const { return StringBase<char>::compare( text ); }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D &operator=( const Coord3D &other ) { x = other.x; y = other.y; z = other.z; return *this; }

	Real x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x, y;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_cachedPos; }

private:
	char m_unmodelled_00[0x38];
	Coord3D m_cachedPos;								///< Thing+0x38
};

class GameLogic
{
public:
	Object *findObjectByID( Int id );
};

extern GameLogic *TheGameLogic;

class View
{
public:
#define BFME_VIEW_SLOT( n ) virtual void slot##n() = 0;
	BFME_VIEW_SLOT( 00 ) BFME_VIEW_SLOT( 01 ) BFME_VIEW_SLOT( 02 ) BFME_VIEW_SLOT( 03 )
	BFME_VIEW_SLOT( 04 ) BFME_VIEW_SLOT( 05 ) BFME_VIEW_SLOT( 06 ) BFME_VIEW_SLOT( 07 )
	BFME_VIEW_SLOT( 08 ) BFME_VIEW_SLOT( 09 ) BFME_VIEW_SLOT( 10 ) BFME_VIEW_SLOT( 11 )
	BFME_VIEW_SLOT( 12 ) BFME_VIEW_SLOT( 13 ) BFME_VIEW_SLOT( 14 ) BFME_VIEW_SLOT( 15 )
	BFME_VIEW_SLOT( 16 ) BFME_VIEW_SLOT( 17 ) BFME_VIEW_SLOT( 18 ) BFME_VIEW_SLOT( 19 )
	BFME_VIEW_SLOT( 20 ) BFME_VIEW_SLOT( 21 ) BFME_VIEW_SLOT( 22 ) BFME_VIEW_SLOT( 23 )
	BFME_VIEW_SLOT( 24 ) BFME_VIEW_SLOT( 25 ) BFME_VIEW_SLOT( 26 ) BFME_VIEW_SLOT( 27 )
	BFME_VIEW_SLOT( 28 ) BFME_VIEW_SLOT( 29 ) BFME_VIEW_SLOT( 30 ) BFME_VIEW_SLOT( 31 )
	BFME_VIEW_SLOT( 32 ) BFME_VIEW_SLOT( 33 ) BFME_VIEW_SLOT( 34 ) BFME_VIEW_SLOT( 35 )
	BFME_VIEW_SLOT( 36 ) BFME_VIEW_SLOT( 37 ) BFME_VIEW_SLOT( 38 ) BFME_VIEW_SLOT( 39 )
	BFME_VIEW_SLOT( 40 ) BFME_VIEW_SLOT( 41 ) BFME_VIEW_SLOT( 42 ) BFME_VIEW_SLOT( 43 )
	BFME_VIEW_SLOT( 44 ) BFME_VIEW_SLOT( 45 ) BFME_VIEW_SLOT( 46 ) BFME_VIEW_SLOT( 47 )
	BFME_VIEW_SLOT( 48 ) BFME_VIEW_SLOT( 49 ) BFME_VIEW_SLOT( 50 ) BFME_VIEW_SLOT( 51 )
	BFME_VIEW_SLOT( 52 ) BFME_VIEW_SLOT( 53 ) BFME_VIEW_SLOT( 54 ) BFME_VIEW_SLOT( 55 )
	BFME_VIEW_SLOT( 56 ) BFME_VIEW_SLOT( 57 ) BFME_VIEW_SLOT( 58 ) BFME_VIEW_SLOT( 59 )
	BFME_VIEW_SLOT( 60 ) BFME_VIEW_SLOT( 61 ) BFME_VIEW_SLOT( 62 ) BFME_VIEW_SLOT( 63 )
	BFME_VIEW_SLOT( 64 ) BFME_VIEW_SLOT( 65 ) BFME_VIEW_SLOT( 66 ) BFME_VIEW_SLOT( 67 )
	BFME_VIEW_SLOT( 68 ) BFME_VIEW_SLOT( 69 ) BFME_VIEW_SLOT( 70 ) BFME_VIEW_SLOT( 71 )
	BFME_VIEW_SLOT( 72 ) BFME_VIEW_SLOT( 73 ) BFME_VIEW_SLOT( 74 ) BFME_VIEW_SLOT( 75 )
	BFME_VIEW_SLOT( 76 ) BFME_VIEW_SLOT( 77 ) BFME_VIEW_SLOT( 78 ) BFME_VIEW_SLOT( 79 )
	BFME_VIEW_SLOT( 80 ) BFME_VIEW_SLOT( 81 ) BFME_VIEW_SLOT( 82 ) BFME_VIEW_SLOT( 83 )
	BFME_VIEW_SLOT( 84 ) BFME_VIEW_SLOT( 85 ) BFME_VIEW_SLOT( 86 ) BFME_VIEW_SLOT( 87 )
	BFME_VIEW_SLOT( 88 )
#undef BFME_VIEW_SLOT
	virtual void screenToTerrain( const ICoord2D *pixel, Coord3D *world, Bool clamp ) = 0;	///< +0x164
};

extern View *TheTacticalView;

// The context record the caller passes; only the fields read here are modelled.
struct Rva006E0080Context
{
	char m_unmodelled_00[0x9C];
	Bool m_flag9C;										///< +0x9C
	char m_unmodelled_9D[0x07];
	Int m_objectIDA4;									///< +0xA4
	char m_unmodelled_A8[0x0C];
	Int m_fieldB4;										///< +0xB4
	Int m_fieldB8;										///< +0xB8
	Int m_widthBC;										///< +0xBC
	Int m_heightC0;										///< +0xC0
};

class Rva006E0080Owner
{
public:
	void step006E0080( Coord3D *pos, Coord3D *target, Rva006E0080Context *context );

private:
	char m_unmodelled_00[0x2C];
	Int m_state2C;										///< +0x2C
	Coord3D m_target30;									///< +0x30
	Coord3D m_pos3C;									///< +0x3C
};

static AsciiString s_mode012F8044;						///< retail [0x012F8044]
static Real s_blend012F8030;							///< retail [0x012F8030]
static Real s_blend012F8034;							///< retail [0x012F8034]
static Real s_blend012F8038;							///< retail [0x012F8038]
static Real s_blend012F803C;							///< retail [0x012F803C]
static Real s_limit012BA8B0 = 0.5f;						///< retail [0x012BA8B0]
static Real s_step012BA8B4 = 0.05f;						///< retail [0x012BA8B4]
static Real s_limit012BA8B8 = 0.4f;						///< retail [0x012BA8B8]
static Real s_step012BA8BC = 0.03f;						///< retail [0x012BA8BC]

// ?step006E0080@Rva006E0080Owner@@QAEXPAUCoord3D@@0PAURva006E0080Context@@@Z
void Rva006E0080Owner::step006E0080( Coord3D *pos, Coord3D *target, Rva006E0080Context *context )
{
	static Coord3D s_savedPos012F8020;					///< retail [0x012F8020]
	static Coord3D s_unused;

	Int requested = -1;
	if( s_mode012F8044.compare( "Target" ) == 0 )
		requested = 2;
	else if( s_mode012F8044.compare( "Zoom" ) == 0 )
		requested = 3;

	if( TheGameLogic->findObjectByID( context->m_objectIDA4 ) == 0 )
	{
		s_blend012F803C = 0;
		s_blend012F8038 = 0;
		s_blend012F8034 = 0;
		s_blend012F8030 = 0;
		m_state2C = 0;
	}

	if( !context->m_flag9C )
	{
		m_target30 = *target;
		m_pos3C = *pos;
	}

	switch( m_state2C )
	{
		case 0:
			if( !context->m_flag9C )
				break;
			m_state2C = 3;
			if( requested == 3 )
			{
				s_savedPos012F8020 = m_pos3C;
				context->m_fieldB4 = 0x10;
				context->m_fieldB8 = 2;
			}
			break;

		case 1:
			if( context->m_flag9C )
				break;
			m_state2C = 4;
			break;

		case 2:
		{
			s_blend012F803C += s_blend012F8038;
			if( s_blend012F8038 < s_limit012BA8B8 )
				s_blend012F8038 = s_step012BA8BC + s_blend012F8038;

			Object *obj = TheGameLogic->findObjectByID( context->m_objectIDA4 );
			Coord3D objPos;
			objPos.x = obj->getPosition()->x;
			objPos.y = obj->getPosition()->y;
			objPos.z = obj->getPosition()->z;
			target->x = (objPos.x - m_target30.x) * s_blend012F803C + m_target30.x;
			target->y = (objPos.y - m_target30.y) * s_blend012F803C + m_target30.y;
			target->z = (objPos.z - m_target30.z) * s_blend012F803C + m_target30.z;
			*pos = m_pos3C;

			if( s_blend012F803C >= 1.0f )
			{
				m_state2C = 3;
				s_savedPos012F8020 = m_pos3C;
				s_blend012F803C = 0;
				s_blend012F8038 = 0;
				if( requested == m_state2C )
				{
					context->m_fieldB4 = 0x10;
					context->m_fieldB8 = 2;
				}
			}
			break;
		}

		case 3:
		{
			s_blend012F8034 += s_blend012F8030;
			if( s_blend012F8030 < s_limit012BA8B0 )
				s_blend012F8030 = s_step012BA8B4 + s_blend012F8030;
			if( s_blend012F8034 < 0.9f )
			{
				Object *obj = TheGameLogic->findObjectByID( context->m_objectIDA4 );
				Coord3D objPos;
				objPos.x = obj->getPosition()->x;
				objPos.y = obj->getPosition()->y;
				objPos.z = obj->getPosition()->z;
				ICoord2D center;
				center.x = context->m_widthBC / 2;
				center.y = context->m_heightC0 / 2;
				Coord3D world;
				TheTacticalView->screenToTerrain( &center, &world, FALSE );

				target->x = (objPos.x - m_target30.x) * s_blend012F8034 + m_target30.x;
				target->y = (objPos.y - m_target30.y) * s_blend012F8034 + m_target30.y;
				target->z = (objPos.z - m_target30.z) * s_blend012F8034 + m_target30.z;
				pos->x = (m_target30.x - s_savedPos012F8020.x) * s_blend012F8034 + s_savedPos012F8020.x;
				pos->y = (m_target30.y - s_savedPos012F8020.y) * s_blend012F8034 + s_savedPos012F8020.y;
				pos->z = (m_target30.z - s_savedPos012F8020.z) * s_blend012F8034 + s_savedPos012F8020.z;
			}
			else
			{
				m_state2C = 1;
				context->m_fieldB4 = 0;
				context->m_fieldB8 = 0;
				s_blend012F8034 = 0;
				s_blend012F8030 = 0;
			}
			break;
		}

		case 4:
			m_state2C = 0;
			break;
	}
}
