// cl: /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#define _STLP_NO_EXCEPTIONS 1
#include <slist>
#include "rendobj.h"
#include "multilist.h"

// Retail element stride28, intrusive multi-list sentinel at+8.
struct Rva009441D0Element
{
    unsigned int m_00;
    MultiListClass<RenderObjClass> m_objects;
};

class Rva009441D0
{
public:
    void method(void *object, void *nodes, int node_count, int min_x, int min_y,
        int max_x, int max_y, int unused_x, int unused_y, int count);
};

void Rva009441D0::method(void *object, void *nodes, int node_count,
    int min_x, int min_y, int max_x, int max_y, int unused_x, int unused_y, int count)
{
    {
        if (!((Rva009441D0Element *)nodes)->m_objects.Is_Empty())
        {
            MultiListIterator<RenderObjClass> it(&((Rva009441D0Element *)nodes)->m_objects);
            for (; !it.Is_Done(); it.Next())
                ((std::slist<RenderObjClass *> *)object)->push_front(it.Peek_Obj());
        }
        if (((Rva009441D0Element *)nodes)->m_00 == 0)
            return;
        count /= 2;
        nodes = (Rva009441D0Element *)nodes + 1;
        if (min_y < unused_y + count)
        {
            if (min_x < unused_x + count)
                method(object, nodes, (unsigned)node_count >> 2,
                    min_x, min_y, max_x, max_y, unused_x, unused_y, count);
            if (max_x >= unused_x + count)
                method(object, ((Rva009441D0Element *)nodes) + node_count, (unsigned)node_count >> 2,
                    min_x, min_y, max_x, max_y, unused_x + count, unused_y, count);
        }
        if (max_y >= unused_y + count)
        {
            if (min_x < unused_x + count)
                method(object, ((Rva009441D0Element *)nodes) + 2 * node_count, (unsigned)node_count >> 2,
                    min_x, min_y, max_x, max_y, unused_x, unused_y + count, count);
            if (max_x >= unused_x + count)
            {
                return method(object, ((Rva009441D0Element *)nodes) + 3 * node_count, (unsigned)node_count >> 2,
                    min_x, min_y, max_x, max_y, unused_x + count, unused_y + count, count);
            }
        }
        return;
    }
}
