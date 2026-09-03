// cl: /DNDEBUG /MD
//
// Retail 0x003E5820: the per-cell examine step of a BFME pathfind walk.
//
// __thiscall on a pathfind-walk payload (ret 0x10 -> four stack arguments):
// the cell the walk came from (may be NULL), the cell being examined, and the
// cell's x/y.  Returns 1 to keep walking, 0 to stop.
//
// Struct layout recovered from the accesses: pathfinder 0x00, obj 0x04, a bool
// at 0x08, the current cell position 0x0C/0x10, the cell's zone 0x14, a status
// int at 0x3C, the previous cell position 0x40/0x44, a sub-object at 0x48 and
// two bools at 0x54/0x55.
//
// PathfindCell's bit word at 0x0C carries a 3-bit type at bit 0, a 6-bit zone
// at bit 6, a blocked flag at bit 18 and an open flag at bit 24.
//
// Codegen note: bit 18 has to be read as `(unsigned char)(m_word >> 18) & 1`.
// Reading it as the plain `m_blocked` bitfield lets MSVC 7.1 fold the whole
// test into `test dword ptr [ebx+0Ch], 40000h`; retail keeps the load, the
// `shr 18` and a byte-wide `test dl, 1`, which only the char-narrowed form
// reproduces.  Bit 24 is the opposite case: it must stay a :1 bitfield so the
// test collapses to `test byte ptr [ebx+0Fh], 1`.
//
// No /EHsc: retail registers no handler for the body.

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	int m_field00;
	int m_field04;
	int m_field08;

	union
	{
		unsigned int m_word;			// 0x0C
		struct
		{
			unsigned int m_type : 3;	// bits 0-2
			unsigned int m_pad03 : 3;	// bits 3-5
			unsigned int m_zone : 6;	// bits 6-11
			unsigned int m_pad12 : 6;	// bits 12-17
			unsigned int m_blocked : 1;	// bit 18
			unsigned int m_pad19 : 5;	// bits 19-23
			unsigned int m_open : 1;	// bit 24
			unsigned int m_pad25 : 7;	// bits 25-31
		};
	};
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	bool bfmeStepE0930( Object *obj, ICoord2D *pos, ICoord2D *prev );
	bool bfmeStepE05B0( Object *obj, ICoord2D *pos );
	bool bfmeStepD4F90( void *state, PathfindCell *cell );
};

class Rva003E5820Info
{
public:
	int examine( PathfindCell *from, PathfindCell *cell, int x, int y );

	Pathfinder *m_pathfinder;		// 0x00
	Object *m_obj;					// 0x04
	bool m_field08;					// 0x08
	ICoord2D m_pos;					// 0x0C
	int m_zone;						// 0x14
	char m_pad18[0x3c - 0x18];
	int m_field3C;					// 0x3C
	ICoord2D m_prev;				// 0x40
	int m_field48;					// 0x48
	char m_pad4C[0x54 - 0x4c];
	bool m_field54;					// 0x54
	bool m_field55;					// 0x55
};

int Rva003E5820Info::examine( PathfindCell *from, PathfindCell *cell, int x, int y )
{
	if (m_field54)
	{
		if (cell->m_open)
			m_field55 = true;
		else if (m_field55)
			return 1;
	}

	m_pos.x = x;
	m_pos.y = y;
	m_zone = cell->m_zone;

	if (from != 0)
	{
		if (!m_pathfinder->bfmeStepE0930( m_obj, &m_pos, &m_prev ))
			return 1;
	}
	else
	{
		if (!m_pathfinder->bfmeStepE05B0( m_obj, &m_pos ))
			return 1;
	}

	if (m_field3C != 0)
		return 1;

	m_prev.x = x;
	m_prev.y = y;

	if (!m_field08 && ((unsigned char)(cell->m_word >> 18) & 1))
		return 1;

	if (from != 0)
	{
		int zone = cell->m_zone;

		if (zone >= 2 && zone <= 15 &&
			(int)from->m_zone == zone &&
			cell->m_type == 0)
			return 0;
	}

	return !m_pathfinder->bfmeStepD4F90( &m_field48, cell );
}
