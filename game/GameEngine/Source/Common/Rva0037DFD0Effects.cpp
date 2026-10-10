// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source
// stlport
// Evidence: targets/game/reverse/identity_evidence/0037dfd0-effects.md.
#include <new>
#include <vector>
#define _OPERATOR_NEW_DEFINED_
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "matrix3d.h"
#include "GameLogic/Object/object.h"
#include "GameClient/FXListRetail.h"

// ?isEmpty@?$StringBase@D@@QBE_NXZ absent-from-retail
template <typename T> inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

class ObjectCreationList
{
public:
    void createInternal(const Object *, const Object *, unsigned) const;
};

class Drawable
{
public:
    bool getCurrentWorldspaceClientBonePositions(const char *, Matrix3D &) const;
};

struct FXEntry
{
    FXList *fx;
    AsciiString name;
};

struct Rva0037DFD0Container
{
    char pad[0x34];
    _STL::vector<FXEntry> begin;
    ObjectCreationList *ocl;
};

// ?rva0037dfd0@@YGXPAURva0037DFD0Container@@PAVObject@@@Z
void __stdcall rva0037dfd0(Rva0037DFD0Container *container, Object *primary)
{
    for (unsigned i = 0; i < container->begin.size(); ++i)
    {
        FXEntry *entry = &container->begin[i];
        if (!entry->name.isEmpty() && primary->getDrawable())
        {
            Matrix3D transform(true);
            primary->getDrawable()->getCurrentWorldspaceClientBonePositions(entry->name.str(), transform);
            Coord3D pos;
            pos.x = transform[0][3];
            pos.y = transform[1][3];
            pos.z = transform[2][3];
            FXList *fx = entry->fx;
            if (fx && !fx->bfmeIsBlocked())
                fx->doFXPos(&pos, &transform, 0.0f, 0);
        }
        else
        {
            FXList *fx = entry->fx;
            if (fx && !fx->bfmeIsBlocked())
                fx->doFXObj(primary, 0);
        }
    }
    if (container->ocl)
        container->ocl->createInternal(primary, 0, 0);
}
