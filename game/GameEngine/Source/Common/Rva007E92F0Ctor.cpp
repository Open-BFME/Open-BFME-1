// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x007E92F0: two base vptrs and a payload at +8.
//
// The class is Rva007E9B40Object, the class whose allocate-and-construct
// factory 0x007E9B40 is matched in Q3MakeDerivedFamily.cpp: this constructor
// installs the second base's vftable 0x01129744 (dir32 ??_7Q3MakeBaseB@@6B@),
// then the derived pair 0x01129810/0x01129808, which the dir32 record owns as
// ??_7Rva007E9B40Object@@6BQ3MakeBaseA@@@ and ...@@6BQ3MakeBaseB@@@.  Same
// reconciliation as Rva007F3850Constructor.cpp (Rva007F40F0Object).  The
// factory inlines the constructor; this is its out-of-line copy.
class Q3MakeBaseA
{
public:
    virtual void primary();
};

class Q3MakeBaseB
{
public:
    virtual void secondary();
    void *m_payload;
    Q3MakeBaseB(void *payload) : m_payload(payload) {}
};

class Rva007E9B40Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
    Rva007E9B40Object(void *payload);
    virtual void primary();
    virtual void secondary();
};

Rva007E9B40Object::Rva007E9B40Object(void *payload) : Q3MakeBaseB(payload) {}
