// cl: /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <slist>
#include "rendobj.h"
#include "multilist.h"

// Retail element stride28, intrusive multi-list sentinel at+8.
struct BfmeSceneVectorElement
{
    unsigned int m_00;
    MultiListClass<RenderObjClass> m_objects;
};


struct Gen_uw_0002e866 { void *m_00; };
class BfmeSceneVector;
class Gen_00943CF0
{
    friend class BfmeSceneVector;
    void unlink(void *value);
};
class BfmeSceneVector
{
    void clear(Gen_uw_0002e866 *objects);
    char unused[0x18];
    BfmeSceneVectorElement *vector;
    int vector_max;
    float scale;
    unsigned int level_mask;
};
void BfmeSceneVector::clear(Gen_uw_0002e866 *objects)
{
    BfmeSceneVectorElement *element = vector;
    for (int index = 0; index < vector_max; ++index, ++element)
    {
        RenderObjClass *object;
        while ((object = element->m_objects.Peek_Head()) != 0)
        {
            ((std::slist<RenderObjClass *> *)objects)->push_front(object);
            ((Gen_00943CF0 *)this)->unlink(object);
        }
    }
}
