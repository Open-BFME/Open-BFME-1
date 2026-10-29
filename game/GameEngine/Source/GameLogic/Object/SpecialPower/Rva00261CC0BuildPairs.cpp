// Retail [0x00261CC0,0x00261DEA): 298 bytes, thiscall with three stack
// arguments (RET 12). The owner's identity is unresolved; the matched caller
// Rva00261F40Owner::selectAt00261E40 (0x00261E40, ILT 0x0002A036) passes the
// context collection, the subject and a local result vector.
// Retail reads only the subject's X/Y at +0x38/+0x3C (address formed with
// add eax,0x38), ranks the 16-byte input entries by squared XY distance and
// sorts float/pointer records with the comparator at 0x00260650. The
// overflow provider at 0x00261750 copies records as POD, so the record is a
// plain aggregate, not _STL::pair.
// The 305-byte overflow body at 0x00261750 is this record vector's own
// instantiation (retail calls it through ILT 0x00024537).
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include <algorithm>
#include <vector>

class Rva00261F40Subject
{
public:
    struct Position { float x, y, z; };
    const Position *getPosition() const { return &m_position; }

private:
    unsigned char m_unmodelled000[0x38];
    Position m_position;
};

typedef _STL::vector<Rva00261F40Subject *> Rva00261F40Vector;

struct Rva00261CC0InputEntry
{
    Rva00261F40Subject *m_subject;
    Rva00261F40Vector m_destination;
};

typedef _STL::vector<Rva00261CC0InputEntry> Rva00261CC0InputCollection;

struct Rva00261CC0DistancePair
{
    float first;
    Rva00261F40Vector *second;
};

typedef _STL::vector<Rva00261CC0DistancePair> Rva00261CC0DistancePairs;

// The comparator's matched row (Rva00261F40Distribution.cpp) is typed on
// _STL::pair<float, vector *>; it reads only the leading float key, which has
// the same offset in this record.
typedef _STL::pair<float, Rva00261F40Vector *> Rva00261E40Pair;
bool __cdecl compareDistanceAt00260650(const Rva00261E40Pair &a, const Rva00261E40Pair &b);
typedef bool (__cdecl *Rva00261CC0Compare)(const Rva00261CC0DistancePair &, const Rva00261CC0DistancePair &);

class Rva00261F40Owner
{
public:
    void buildPairsAt00261CC0(Rva00261CC0InputCollection *input,
        Rva00261F40Subject *subject, Rva00261CC0DistancePairs *out);
};

void Rva00261F40Owner::buildPairsAt00261CC0(
    Rva00261CC0InputCollection *input,
    Rva00261F40Subject *subject,
    Rva00261CC0DistancePairs *out)
{
    const Vector3 position(subject->getPosition()->x, subject->getPosition()->y, subject->getPosition()->z);
    for (Rva00261CC0InputEntry *entry = input->begin(); entry != input->end(); ++entry)
    {
        const Rva00261F40Subject::Position *p = entry->m_subject->getPosition();
        Vector3 delta = Vector3(p->x, p->y, p->z) - position;
        Rva00261CC0DistancePair value;
        value.first = delta.X * delta.X + delta.Y * delta.Y;
        value.second = &entry->m_destination;
        out->push_back(value);
    }
    _STL::sort(out->begin(), out->end(),
        reinterpret_cast<Rva00261CC0Compare>(&compareDistanceAt00260650));
}
