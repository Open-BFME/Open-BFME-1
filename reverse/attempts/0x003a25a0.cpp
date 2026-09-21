// ??0Rva003A35A0Element@@QAE@PBVWaypoint@@@Z
// partial score=0.14 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
//
// A second constructor for the 184-byte Rva003A35A0Element already pinned
// by RvaVectorInsertOverflowOutOfLineCopy.cpp's vector<T>::_M_insert_overflow
// instantiation, and whose full field layout (int key; int prefix[10];
// Coord3D points[10] CONTIGUOUS; int wordA/B/C; AsciiString name; int tail)
// was recovered independently from the default constructor at 0x003A18D0.
// This body instead COPY-CONSTRUCTS an element from a Waypoint * source:
// name via the pinned Waypoint::getName() (0x0001026C), a 12-byte location
// copied verbatim from source+0xC into wordA/B/C, and source+4 (the
// WaypointID) into the trailing tail word -- confirming those three
// trailing words really are a Coord3D location, not independent scalars.
// No named caller or owning method proves the class; identity stays
// address-derived per docs/naming_evidence.md.

#include "ascii_string.h"
#include "coord3d.h"

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class Gen003A25A0StringData
{
public:
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_length;
	unsigned short m_pad;
};

class Waypoint
{
public:
	AsciiString getName() const;

	void *m_vptr;   // +0x00
	int m_id;       // +0x04
	void *m_namePad; // +0x08 (AsciiString m_name, read only via getName())
	int m_locX;     // +0x0c
	int m_locY;     // +0x10
	int m_locZ;     // +0x14
};

class Rva003A35A0Element
{
public:
	Rva003A35A0Element(const Waypoint *source);

private:
	int m_key;
	int m_prefix[10];
	Coord3D m_points[10];
	int m_wordA;
	int m_wordB;
	int m_wordC;
	AsciiString m_name;
	int m_tail;
};

// ??0Rva003A35A0Element@@QAE@PBVWaypoint@@@Z
Rva003A35A0Element::Rva003A35A0Element(const Waypoint *source)
{
	m_name.set(source->getName());

	m_wordA = source->m_locX;
	m_wordB = source->m_locY;
	m_wordC = source->m_locZ;
	m_tail = source->m_id;

	m_key = 0;

	m_prefix[0] = 0;
	m_points[0].x = 0.0f;
	m_points[0].y = 0.0f;
	m_points[0].z = 0.0f;

	m_prefix[1] = 0;
	m_points[1].x = 0.0f;
	m_points[1].y = 0.0f;
	m_points[1].z = 0.0f;

	m_prefix[2] = 0;
	m_points[2].x = 0.0f;
	m_points[2].y = 0.0f;
	m_points[2].z = 0.0f;

	m_prefix[3] = 0;
	m_points[3].x = 0.0f;
	m_points[3].y = 0.0f;
	m_points[3].z = 0.0f;

	m_prefix[4] = 0;
	m_points[4].x = 0.0f;
	m_points[4].y = 0.0f;
	m_points[4].z = 0.0f;

	m_prefix[5] = 0;
	m_points[5].x = 0.0f;
	m_points[5].y = 0.0f;
	m_points[5].z = 0.0f;

	m_prefix[6] = 0;
	m_points[6].x = 0.0f;
	m_points[6].y = 0.0f;
	m_points[6].z = 0.0f;

	m_prefix[7] = 0;
	m_points[7].x = 0.0f;
	m_points[7].y = 0.0f;
	m_points[7].z = 0.0f;

	m_prefix[8] = 0;
	m_points[8].x = 0.0f;
	m_points[8].y = 0.0f;
	m_points[8].z = 0.0f;

	m_prefix[9] = 0;
	m_points[9].x = 0.0f;
	m_points[9].y = 0.0f;
	m_points[9].z = 0.0f;
}
