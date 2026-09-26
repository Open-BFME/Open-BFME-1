// ?d_002115c0@@YAXXZ
// partial score=0.52 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// The matched Rva00211890ForwardSourcePosition caller proves applyAt(float,
// Coord3D const*) and its owner. This version models the four signed planar
// projections, stable descending insertion, and limited weight distribution.
// Retail uses a wider 0x54-byte EH frame and a distinct FP scheduling pattern.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>

struct Rva00211890Coord { float x, y, z; };
struct Rva002115C0Data {
    char m_prefix[8];
    float m_axis0x, m_axis1x;
    char m_padding10[4];
    float m_basex, m_axis0y, m_axis1y;
    char m_padding20[4];
    float m_basey, m_axis0z, m_axis1z;
    char m_padding30[4];
    float m_basez;
};
class Rva002115C0Resource {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual float slot18();
};
class Rva00211890Owner {
public:
    void applyAt(float amount, const Rva00211890Coord *point);
    void *m_vptr;
    void *m_extra04;
    Rva002115C0Data *m_data;
    void *m_object;
    Rva002115C0Resource m_resource;
    char m_toAc[0x98];
    float m_values[4];
};
void Rva00211890Owner::applyAt(float amount, const Rva00211890Coord *point)
{
    const Rva002115C0Data *data = m_data;
    float dx = data->m_basex - point->x;
    float dy = data->m_basey - point->y;
    float dz = data->m_basez - point->z;
    float projections[4];
    projections[0] = -(data->m_axis0x * dx + data->m_axis0y * dy + data->m_axis0z * dz);
    projections[1] = data->m_axis1x * dx + data->m_axis1y * dy + data->m_axis1z * dz;
    projections[2] = -projections[0];
    projections[3] = -projections[1];
    std::vector<int> sorted;
    for (int i = 0; i < 4; ++i) {
        std::vector<int>::iterator where = sorted.begin();
        for (; where != sorted.end(); ++where)
            if (projections[i] > projections[*where])
                break;
        if (where == sorted.end())
            sorted.push_back(i);
        else
            sorted.insert(where, i);
    }
    float remaining = amount;
    float value = m_resource.slot18() * *(const float *)0x01083B6C * *(const float *)0x0109F748;
    for (int j = 0; remaining > *(const float *)0x01075350 && j < 4; ++j) {
        float *current = &m_values[sorted[j]];
        float available = value - *current;
        float applied = available < remaining ? available : remaining;
        if (applied > *(const float *)0x01075350) {
            *current += applied;
            remaining -= applied;
        }
    }
}
