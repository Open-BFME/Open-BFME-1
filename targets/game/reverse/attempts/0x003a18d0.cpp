// ??0Rva003A35A0Element@@QAE@XZ
// partial score=0.77 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// stlport
//
// ??0Rva003A35A0Element@@QAE@XZ -- default constructor for the 184-byte
// vector element already pinned as Rva003A35A0Element (see
// RvaVectorInsertOverflowOutOfLineCopy.cpp, which names it opaquely for its
// vector<T>::_M_insert_overflow instantiation) and already laid out for real
// by the sibling _Construct body at 0x003A2360 (Rva003A2360PairCopy.cpp):
// one leading int key, ten prefix ints, ten Coord3D points (CONTIGUOUS, not
// interleaved with the prefix ints -- Coord3D has a user default ctor/dtor,
// so the array goes through the compiler's own eh-vector-ctor-iterator
// helper at 0x0DF6EE4, matching this body's ctor/dtor callback pair 0x16C93
// /0x1364C), three trailing words, an AsciiString, and a final word.
//
// The owning type is still not identified; keep the layout TU-local under
// the address label until a named caller proves it.

#include "ascii_string.h"
#include "coord3d.h"

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}

class Rva003A35A0Element
{
public:
	Rva003A35A0Element();

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

Rva003A35A0Element::Rva003A35A0Element()
{
	m_wordA = 0;
	m_wordB = 0;
	m_wordC = 0;
	m_tail = 0;
	m_name.clear();

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
