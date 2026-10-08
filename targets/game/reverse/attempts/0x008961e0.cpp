// ?helper@Gen_00896320@@QAEXPAX00@Z
// partial score=0.3259 date=2026-10-08
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
class BfmeDropObjectA;
class BfmeRefVGO
{
public:
    BfmeRefVGO &bfmeAssignVGO(const BfmeRefVGO &o);
    unsigned *m_bfmeP;
};

class Rva00894D90Accessor
{
public:
    static unsigned int decrement(unsigned int *value);
};
__declspec(noinline) void bfmeDropA(void *value);

class Rva00896100Item : public BfmeRefVGO
{
public:
    // ??0Rva00896100Item@@QAE@XZ absent-from-retail
    Rva00896100Item() { m_bfmeP = 0; }
    // ??1Rva00896100Item@@QAE@XZ present-unmatched
    ~Rva00896100Item()
    {
        if (m_bfmeP && Rva00894D90Accessor::decrement(m_bfmeP) == 0)
            bfmeDropA(m_bfmeP);
    }
};
typedef Rva00896100Item Gen00896320Item;

BfmeDropObjectA **Rva00895430Copy(BfmeDropObjectA **first, BfmeDropObjectA **last, BfmeDropObjectA **result);
BfmeDropObjectA **bfmeCopyBackVPD(BfmeDropObjectA **first, BfmeDropObjectA **last, BfmeDropObjectA **result);

class Gen_00896320
{
public:
    void append(void **source);
    void helper(void *first, void *last, void *result);
    void rva00896100(int capacity);
private:
    unsigned m_count;
    int m_capacity;
    Gen00896320Item *m_begin;
    Gen00896320Item m_inline[1];
};

// ?helper@Gen_00896320@@QAEXPAX00@Z present-unmatched
void Gen_00896320::helper(void *first, void *last, void *result)
{
    Gen00896320Item **firstReference = (Gen00896320Item **)first;
    Gen00896320Item **lastReference = (Gen00896320Item **)last;
    Gen00896320Item *rangeLast = *lastReference;
    Gen00896320Item *rangeFirst = *firstReference;
    int count = rangeLast - rangeFirst;
    if (count == 0)
        return;
    int newCount = m_count + count;
    int shape_frame_capacity_55[2];
    shape_frame_capacity_55[1] = m_capacity;
    if (newCount < shape_frame_capacity_55[1])
    {
        Gen00896320Item *end = m_begin + m_count;
        if (*(Gen00896320Item **)result == end)
        {
            Rva00895430Copy((BfmeDropObjectA **)rangeFirst, (BfmeDropObjectA **)rangeLast, (BfmeDropObjectA **)end);
            const Gen00896320Item empty;
            m_begin[newCount].bfmeAssignVGO(empty);
            m_count = newCount;
            __assume(empty.m_bfmeP == 0);
        }
        else
        {
            int destinationIndex = *(Gen00896320Item **)result - m_begin + count;
            bfmeCopyBackVPD((BfmeDropObjectA **)*(Gen00896320Item **)result, (BfmeDropObjectA **)end, (BfmeDropObjectA **)(m_begin + destinationIndex));
            Rva00895430Copy((BfmeDropObjectA **)*(Gen00896320Item **)first, (BfmeDropObjectA **)*(Gen00896320Item **)last, (BfmeDropObjectA **)*(Gen00896320Item **)result);
            const Gen00896320Item empty;
            m_begin[newCount].bfmeAssignVGO(empty);
            m_count = newCount;
            __assume(empty.m_bfmeP == 0);
        }
    }
    else
    {
        int newCapacity = (int)(shape_frame_capacity_55[1] * 2.0);
        if (newCapacity < newCount)
            newCapacity = newCount;
        int index = *(Gen00896320Item **)result - m_begin;
        rva00896100(newCapacity);
        Gen00896320Item *position = m_begin + index;
        helper(firstReference, lastReference, &position);
    }
}
