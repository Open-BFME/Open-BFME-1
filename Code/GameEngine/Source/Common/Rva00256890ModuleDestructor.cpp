// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Open-BFME5: near-twin of ??1BfmeA1137Term (0x00723F30, BfmeConv1137Term.cpp);
// module-chain destructor that resets three base-subobject vtables (own + two
// interfaces introduced at this level), destructs an int-keyed list member,
// then chains to the primary base's destructor (0x0002514E, already pinned as
// ??1Gen_dtor_001c0e70@@UAE@XZ).

#include <list>

class Rva00256890PrimaryBase
{
public:
	virtual ~Rva00256890PrimaryBase();

private:
	unsigned char m_pad[8];
};

class Rva00256890Interface1 { public: virtual void slot(); };
class Rva00256890Interface2 { public: virtual void slot(); };

class Rva00256890Module : public Rva00256890PrimaryBase,
	public Rva00256890Interface1,
	public Rva00256890Interface2
{
public:
	virtual ~Rva00256890Module();

private:
	unsigned char m_pad2[0x24 - 0x14];
	_STL::list<int> m_list;
};

// ?d_00256890@@YAXXZ
Rva00256890Module::~Rva00256890Module()
{
}
