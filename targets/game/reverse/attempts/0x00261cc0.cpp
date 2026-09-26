// Rva00261F40Owner::buildPairsAt00261CC0
// partial score=0.15 date=2026-09-15
// Scratch reconstruction of retail RVA 0x00261CC0 (298 bytes).
// The original owner is unresolved; this same-file address-labelled owner is
// used only to preserve the verified incoming-ECX member chain.
// Retail's comparator body at RVA 0x00260650 is strict float less-than.
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <algorithm>
#include <vector>

struct Rva00261CC0Subject
{
    unsigned char m_unmodelled000[0x38];
    float m_positionX;
    float m_positionY;
};

typedef _STL::vector<Rva00261CC0Subject *> Rva00261CC0SubjectVector;

struct Rva00261CC0InputEntry
{
    Rva00261CC0Subject *m_subject;
    Rva00261CC0SubjectVector m_destination;
};

typedef _STL::vector<Rva00261CC0InputEntry> Rva00261CC0InputCollection;
typedef _STL::pair<float, Rva00261CC0SubjectVector *> Rva00261CC0DistancePair;
typedef _STL::vector<Rva00261CC0DistancePair> Rva00261CC0DistancePairs;

extern bool __cdecl Rva00260650Compare(
    const Rva00261CC0DistancePair &left,
    const Rva00261CC0DistancePair &right);

typedef bool (__cdecl *Rva00261CC0CompareFunction)(
    const Rva00261CC0DistancePair &, const Rva00261CC0DistancePair &);

struct Rva00261CC0Compare
{
    Rva00261CC0CompareFunction m_compare;

    bool operator()(const Rva00261CC0DistancePair &left,
        const Rva00261CC0DistancePair &right) const
    {
        return m_compare(left, right);
    }
};

class Rva00261F40Owner
{
public:
    void buildPairsAt00261CC0(Rva00261CC0InputCollection *input,
        Rva00261CC0Subject *subject, Rva00261CC0DistancePairs *out);
};

void Rva00261F40Owner::buildPairsAt00261CC0(
    Rva00261CC0InputCollection *input,
    Rva00261CC0Subject *subject,
    Rva00261CC0DistancePairs *out)
{
    const float subjectX = subject->m_positionX;
    const float subjectY = subject->m_positionY;

    for (Rva00261CC0InputEntry *it = input->begin(); it != input->end(); ++it)
    {
        Rva00261CC0Subject *candidate = it->m_subject;
        const float deltaY = candidate->m_positionY - subjectY;
        const float deltaX = candidate->m_positionX - subjectX;
        const float distance = deltaY * deltaY + deltaX * deltaX;
        out->push_back(Rva00261CC0DistancePair(distance, &it->m_destination));
    }

    Rva00261CC0Compare compare = { Rva00260650Compare };
    _STL::sort(out->begin(), out->end(), compare);
}
