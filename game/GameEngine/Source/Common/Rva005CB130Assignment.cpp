// cl: /DNDEBUG /MD /EHsc
// Copy assignment of the class whose copy constructor is 0x005CB130
// (Y3ChainCopyCtors.cpp): a cloned ChainVictim at +0 and Sub005C92F0 at +4.
// Retail 0x005CB1D0 clones the other side (slot 1), deletes the old one
// (slot 0 with push 1: scalar deleting destructor), stores, then calls
// Sub005C92F0::operator= (0x005C93C0 via ILT 0x0000FF29) on the +4 subobject.
//
// It forms the parameter's subobject with `lea eax,[ebx+4] / push eax`, the
// same outlier its copy constructor shows, and for the same measured reason:
// Sub005C92F0 is reached through the empty intermediate Mid005CB130.  A
// direct member or direct base gives `add ebx,4 / push ebx` (the four
// U1CloneAssignOperators.cpp rows).  Identity past the address is unknown.
class ChainVictim
{
public:
	virtual ~ChainVictim();
	virtual ChainVictim *clone() const;
};

class ChainCloneHold
{
public:
	ChainVictim *m_p;
};

class Sub005C92F0
{
public:
	Sub005C92F0 &operator=( const Sub005C92F0 &other );
};

class Mid005CB130 : public Sub005C92F0 {};

class Rva005CB130 : public ChainCloneHold, public Mid005CB130
{
public:
	Rva005CB130 &operator=( const Rva005CB130 &other );
};

Rva005CB130 &Rva005CB130::operator=( const Rva005CB130 &other )
{
	ChainVictim *p = other.m_p;
	ChainVictim *copy = p ? p->clone() : 0;
	delete m_p;
	m_p = copy;
	Mid005CB130::operator=( other );
	return *this;
}
