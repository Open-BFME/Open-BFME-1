// cl: /O2 /DNDEBUG /MD

// The BfmeVecEVE element constructor is passed to the generic vector
// constructor at 0x008A2CF0 with an element stride of 0x20.  Its matched
// destructor is at 0x008A20B0; the storage-only split below preserves the
// proven head/count/buffer offsets without inventing any additional ABI.
extern void* (__cdecl* Rva008C5D70Alloc)(unsigned int bytes);
class BfmeItemEVE;

struct BfmeVecEVEHead
{
	BfmeVecEVEHead()
		: m_value00(0),
		  m_value04(0),
		  m_value08(0),
		  m_value0C(0),
		  m_value10(0)
	{
	}

	int m_value00;
	int m_value04;
	int m_value08;
	int m_value0C;
	int m_value10;
};

struct BfmeVecEVETail
{
	BfmeVecEVETail()
		: m_count(0),
		  m_capacity(6),
		  m_values((BfmeItemEVE **)Rva008C5D70Alloc(0x18))
	{
	}

	int m_count;
	int m_capacity;
	BfmeItemEVE **m_values;
};

class BfmeVecEVE
{
public:
	BfmeVecEVE();

private:
	BfmeVecEVEHead m_head;
	BfmeVecEVETail m_tail;
};

BfmeVecEVE::BfmeVecEVE()
	: m_head(),
	  m_tail()
{
}
