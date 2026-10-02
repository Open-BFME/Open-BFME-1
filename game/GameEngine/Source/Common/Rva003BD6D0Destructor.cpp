// RVA 0x003BBC20, 145-byte destructor.
// Owner: constructor 0x003BD6D0 installs the same 0x010ED8F8 vtable.
// Evidence: targets/game/reverse/identity_evidence/rva003bbc20.md
// cl: /DNDEBUG /MD /EHsc /O2

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *);

class RefThing003BBC20
{
public:
	virtual ~RefThing003BBC20();
	void release003BBC20() { if (InterlockedDecrement(&m_field4) <= 0) delete this; }

	long m_field4;
};

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ(void) { }
};

struct Rva003BBC20Ref
{
    RefThing003BBC20 *m_ptr;
    ~Rva003BBC20Ref()
    {
        if (m_ptr) m_ptr->release003BBC20();
    }
    void clear()
    {
        if (m_ptr)
        {
            m_ptr->release003BBC20();
            m_ptr = 0;
        }
    }
};

class Rva003BD6D0 : public BfmeBaseVUQ
{
public:
    virtual ~Rva003BD6D0();
    virtual void bfmePure003BBC20() = 0;
private:
    unsigned char m_pad004[8];
    Rva003BBC20Ref m_ref;
};
Rva003BD6D0::~Rva003BD6D0()
{
    m_ref.clear();
}
