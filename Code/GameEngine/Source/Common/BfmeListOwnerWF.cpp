// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the list-owning constructor at retail 0x0014C7A0, 137 bytes.
//
// The name arrives by value.  The table store is the compiler's own vfptr
// initialisation, not an assignment: a real virtual destructor is what puts
// the receiver ahead of the pushed argument, the same shape as the landed
// constructor at 0x0014ADC0.

namespace _STL {

class __new_alloc
{
public:
	static void *allocate(unsigned int n);
};

}

class AsciiStringWF
{
public:
	AsciiStringWF(const AsciiStringWF &other);
	~AsciiStringWF(void);
};

class BfmeStrWF : private AsciiStringWF
{
public:
	BfmeStrWF(const AsciiStringWF &other) : AsciiStringWF(other) {}
	~BfmeStrWF(void) {}
};

struct BfmeNodeWF
{
	BfmeNodeWF *m_bfmeNext;					// +0x00
	BfmeNodeWF *m_bfmePrev;					// +0x04
	int m_bfmeSlot[2];					// +0x08
};

class BfmeListWF
{
public:
	__forceinline BfmeListWF(void)
	{
		m_bfmeNode = 0;

		BfmeNodeWF *node = (BfmeNodeWF *)_STL::__new_alloc::allocate(0x10);

		node->m_bfmeNext = node;
		node->m_bfmePrev = node;

		m_bfmeNode = node;
	}

	BfmeNodeWF *m_bfmeNode;					// +0x00
};

class Gen_0014C7A0
{
public:
	Gen_0014C7A0(AsciiStringWF name);

	virtual ~Gen_0014C7A0(void);

private:
	BfmeStrWF m_bfmeName;					// +0x04
	int m_bfmeCount;					// +0x08
	BfmeListWF m_bfmeList;					// +0x0C
	int m_bfmeSize;						// +0x10
};

// ??0Gen_0014C7A0@@QAE@VAsciiStringWF@@@Z
Gen_0014C7A0::Gen_0014C7A0(AsciiStringWF name)
	: m_bfmeName(name),
	  m_bfmeCount(1),
	  m_bfmeSize(0)
{
}
