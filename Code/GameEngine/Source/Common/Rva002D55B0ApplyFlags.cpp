// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class BfmeStrF9
{
    char m_pad[4];
};

class BfmeObjF9
{
public:
    void setFlag(const BfmeStrF9 &name, char flag);
};

struct BfmeStrRangeF9
{
    BfmeStrF9 *m_begin;
    BfmeStrF9 *m_end;
};

class Rva002D55B0
{
public:
    void applyFlags(BfmeObjF9 *object, BfmeStrRangeF9 *range, char flag);
};

void Rva002D55B0::applyFlags(BfmeObjF9 *object, BfmeStrRangeF9 *range, char flag)
{
    for (BfmeStrF9 *it = range->m_begin; it != range->m_end; ++it)
        object->setFlag(*it, flag);
}
