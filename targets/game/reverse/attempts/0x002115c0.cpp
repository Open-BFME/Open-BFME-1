// ?applyAt@Rva00211890Owner@@QAEXMPBURva00211890Coord@@@Z
// partial score=0.98 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// The matched Rva00211890ForwardSourcePosition caller proves applyAt(float,
// Coord3D const*). m_data+8 is copied as a whole Matrix3D local (retail keeps
// its +0x1C/+0x2C floats in a 0x30-byte stack copy); the four side projections
// are sorted descending by index and the amount is spread over m_values.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include <algorithm>
#include "WWMath/matrix3d.h"

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
    const Matrix3D *getTransform() const { return reinterpret_cast<const Matrix3D *>(&m_axis0x); }
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
    Matrix3D mtx(*data->getTransform());
    Vector3 dir(mtx.Get_X_Translation() - point->x, mtx.Get_Y_Translation() - point->y, mtx.Get_Z_Translation() - point->z);
    float projections[4];
    projections[0] = Vector3::Dot_Product(-mtx.Get_X_Vector(), dir);
    projections[1] = Vector3::Dot_Product(mtx.Get_Y_Vector(), dir);
    projections[2] = -projections[0];
    projections[3] = -projections[1];
    std::vector<int> sorted;
    for (int i = 0; i < 4; ++i) {
        bool inserted = false;
        for (std::vector<int>::iterator where = sorted.begin(); where != sorted.end(); ++where) {
            if (projections[i] > projections[*where]) {
                sorted.insert(where, i);
                inserted = true;
                break;
            }
        }
        if (!inserted)
            sorted.push_back(i);
    }
    float limit = m_resource.slot18() * 0.25f;
    limit *= 0.75f;
    float remaining = amount;
    for (int j = 0; remaining > 0.0f && j < 4; ++j) {
        float *current = &m_values[sorted[j]];
        float available = limit - *current;
        float applied = std::min(remaining, available);
        if (applied > 0.0f) {
            *current += applied;
            remaining -= applied;
        }
    }
}
