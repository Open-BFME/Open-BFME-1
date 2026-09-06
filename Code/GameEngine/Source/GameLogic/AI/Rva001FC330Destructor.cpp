// Address-derived ABI slice for the multi-vtable destructor at 0x002D6B80.
// Open-BFME7: retail 0x001FC330 (56 bytes) is the twin of Rva002D6B80Destructor.cpp whose
// leading trivial base is only a vtable pointer (no 4-byte member), so every store lands
// four bytes earlier; names re-tagged for this address.
// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs-

class Rva1FC330TrivialHead
{
public:
	virtual void headAnchor();

};

class Rva00047C53MultiBase
{
public:
	virtual ~Rva00047C53MultiBase();

private:
	unsigned int m_04;
	unsigned int m_08;
};

class Rva1FC330IfaceA
{
public:
	virtual void ifaceAAnchor();
};

class Rva1FC330IfaceB
{
public:
	virtual void ifaceBAnchor();
};

class Rva1FC330DeepBase : public Rva00047C53MultiBase, public Rva1FC330IfaceA
{
public:
	virtual ~Rva1FC330DeepBase() {}
};

class Rva1FC330Middle : public Rva1FC330DeepBase, public Rva1FC330IfaceB
{
public:
	virtual ~Rva1FC330Middle() {}
};

class Rva001FC330MultiTailDtor : public Rva1FC330TrivialHead, public Rva1FC330Middle
{
public:
	virtual ~Rva001FC330MultiTailDtor();
};

Rva001FC330MultiTailDtor::~Rva001FC330MultiTailDtor()
{
}
