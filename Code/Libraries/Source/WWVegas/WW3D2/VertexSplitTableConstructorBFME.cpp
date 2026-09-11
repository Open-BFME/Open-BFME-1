// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /Ireference/shims/sweep
// Open-BFME5: BFME's out-of-line Vertex_Split_Table constructor.
// Retail identity: ??0Vertex_Split_Table@@QAE@PAVMeshModelClass@@@Z at 0x00946FE0.
// The BFME mesh layout keeps polygon count at +0x24 and the polygon buffer at
// +0x2c, while the caps object keeps Support_NPatches at +0x13b.

#include <new.h>

extern "C" void *memcpy(void *, const void *, unsigned int);
extern "C" void *__cdecl bfmeArrayNew(unsigned int size);

typedef unsigned short TriIndex[3];

class MeshModelClass
{
    unsigned char m_padding[0x24];
    unsigned m_polygon_count;
    unsigned char m_padding_after_count[4];
    class PolygonBuffer
    {
        unsigned char m_padding[0xc];

    public:
        const TriIndex *Get_Array(void) const
        {
            return *(const TriIndex **)((const char *)this + 0xc);
        }
    } *m_polygon_array;

public:
    bool Needs_Vertex_Normals(void);
    unsigned Get_Polygon_Count(void) const
    {
        return *(const unsigned *)((const char *)this + 0x24);
    }

    const TriIndex *Get_Polygon_Array(void) const
    {
        return m_polygon_array->Get_Array();
    }
};

class BfmeCaps
{
    unsigned char m_padding[0x13b];
    unsigned char m_support_npatches;

public:
    bool Support_NPatches(void) const
    {
        return m_support_npatches != 0;
    }
};

extern BfmeCaps *BfmeCurrentCaps;

class DX8Wrapper
{
public:
    static const BfmeCaps *Get_Current_Caps(void)
    {
        return BfmeCurrentCaps;
    }
};

class Vertex_Split_Table
{
    MeshModelClass *mmc;
    bool npatch_enable;
    unsigned polygon_count;
    TriIndex *polygon_array;
    bool allocated_polygon_array;

public:
    __declspec(noinline) Vertex_Split_Table(MeshModelClass *mmc_)
        :
        mmc(mmc_),
        npatch_enable(false),
        allocated_polygon_array(false)
    {
        if (DX8Wrapper::Get_Current_Caps()->Support_NPatches() && mmc->Needs_Vertex_Normals()) {
            if (*(const unsigned *)((const char *)mmc + 0x18) & 0x10000) {
                npatch_enable=true;
            }
        }

        polygon_count=mmc->Get_Polygon_Count();
        allocated_polygon_array=true;
        polygon_array=(TriIndex *)bfmeArrayNew(polygon_count*sizeof(TriIndex));
        memcpy(
            polygon_array,
            mmc->Get_Polygon_Array(),
            mmc->Get_Polygon_Count()*sizeof(TriIndex));
    }
};

// Emission anchor for the out-of-line constructor. This helper has no retail
// claim; the constructor body above is the only retail function here.
__declspec(noinline) void force_vertex_split_table_constructor(MeshModelClass *mmc)
{
    Vertex_Split_Table table(mmc);
}
