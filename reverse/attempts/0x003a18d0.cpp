// ??0Rva003A35A0Element@@QAE@XZ
// partial score=0.76 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath

#include "ascii_string.h"
#include "coord3d.h"

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

// The retail element's owning type is not identified.  This address-labelled
// view preserves the 184-byte vector element layout used by its siblings.
class Rva003A35A0Element
{
public:
    Rva003A35A0Element();

private:
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
    Coord3D m_coords[10];
    int m_a4;
    int m_a8;
    int m_ac;
    AsciiString m_name;
    int m_b4;
};

Rva003A35A0Element::Rva003A35A0Element()
    : m_a4(0), m_a8(0), m_ac(0)
{
    m_b4 = 0;
    m_name.clear();

    m_00 = 0;
    m_04 = 0;

    m_coords[0].x = 0.0f;
    m_coords[0].y = 0.0f;
    m_coords[0].z = 0.0f;

    m_08 = 0;

    m_coords[1].x = 0.0f;
    m_coords[1].y = 0.0f;
    m_coords[1].z = 0.0f;

    m_0c = 0;

    m_coords[2].x = 0.0f;
    m_coords[2].y = 0.0f;
    m_coords[2].z = 0.0f;

    m_10 = 0;

    m_coords[3].x = 0.0f;
    m_coords[3].y = 0.0f;
    m_coords[3].z = 0.0f;

    m_14 = 0;

    m_coords[4].x = 0.0f;
    m_coords[4].y = 0.0f;
    m_coords[4].z = 0.0f;

    m_18 = 0;

    m_coords[5].x = 0.0f;
    m_coords[5].y = 0.0f;
    m_coords[5].z = 0.0f;

    m_1c = 0;

    m_coords[6].x = 0.0f;
    m_coords[6].y = 0.0f;
    m_coords[6].z = 0.0f;

    m_20 = 0;

    m_coords[7].x = 0.0f;
    m_coords[7].y = 0.0f;
    m_coords[7].z = 0.0f;

    m_24 = 0;

    m_coords[8].x = 0.0f;
    m_coords[8].y = 0.0f;
    m_coords[8].z = 0.0f;

    m_28 = 0;

    m_coords[9].x = 0.0f;
    m_coords[9].y = 0.0f;
    m_coords[9].z = 0.0f;
}
