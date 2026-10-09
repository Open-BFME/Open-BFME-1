// ?method@Rva001F9180@@QAE_NPAVCoord3D@@@Z
// partial score=0.9912 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include <string.h>
#include <coord3d.h>
#include <ascii_string.h>

inline Coord3D::Coord3D() {}
inline Coord3D::~Coord3D() {}
inline Coord3D::Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
inline Coord3D &Coord3D::operator=(const Coord3D &v) { memcpy(this, &v, 12); return *this; }

class Matrix3D;
class Object {
public:
    int getMultiLogicalBonePosition(const char *, int, Coord3D *, Matrix3D *, bool, int) const;
    // ?getPosition@Object@@QBEPBVCoord3D@@XZ absent-from-retail
    const Coord3D *getPosition() const { return &m_position; }
    unsigned char m_unmodelled_000[0x38];
    Coord3D m_position;
};
class Pathfinder {
public:
    bool bfmeGroundCellThreshold(const Coord3D *, bool);
};
class AI {
public:
    Pathfinder *pathfinder() { return m_pathfinder; }
    unsigned char m_unmodelled_000[0x0c];
    Pathfinder *m_pathfinder;
};
extern AI *TheAI;

struct Rva001F9180Record {
    int m_field00;
    unsigned char m_unmodelled_004[4];
};
struct Rva001F9180Data {
    unsigned char m_unmodelled_000[0x70];
    int m_field70;
    unsigned char m_unmodelled_074[0x30];
    AsciiString m_fieldA4;
    Rva001F9180Record *m_fieldA8;
    Rva001F9180Record *m_fieldAC;
    unsigned char m_unmodelled_0B0[0x18];
    int m_fieldC8;
};
class Rva001F9180 {
public:
    bool method(Coord3D *);
    // ?getObject@Rva001F9180@@QBEPAVObject@@XZ absent-from-retail
    Object *getObject() const { return m_object; }
    // ?getModuleData@Rva001F9180@@QBEPBURva001F9180Data@@XZ absent-from-retail
    const Rva001F9180Data *getModuleData() const { return m_data; }
    void *m_vtable;
    Rva001F9180Data *m_data;
    Object *m_object;
};

// ?method@Rva001F9180@@QAE_NPAVCoord3D@@@Z present-unmatched
bool Rva001F9180::method(Coord3D *position)
{
    const Rva001F9180Data *data = getModuleData();
    int index = data->m_fieldC8;
    if (index < 0) {
        if (position)
            *position = *getObject()->getPosition();
        return true;
    }
    if (index >= data->m_fieldAC - data->m_fieldA8) {
        if (position)
            *position = *getObject()->getPosition();
        return true;
    }
    Coord3D positions[16];
    Object *object = getObject();
    object->getMultiLogicalBonePosition(data->m_fieldA4.str(), data->m_field70, positions, 0, true, 0);
    int recordIndex = data->m_fieldC8;
    const Rva001F9180Record &record = data->m_fieldA8[recordIndex];
    Coord3D selected = positions[record.m_field00];
    if (position)
        *position = selected;
    return TheAI->pathfinder()->bfmeGroundCellThreshold(&selected, false);
}
