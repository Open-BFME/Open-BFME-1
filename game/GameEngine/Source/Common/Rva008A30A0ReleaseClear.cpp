// Open-BFME5: release the owned pointer at this+8 and clear the field,
// reconstructed from retail RVA 0x008A30A0.

// The retail call is through a global function-pointer slot at 0x0133782C.
// The DIR32 operand is copied from retail by the reconstruction gate.
extern void (*Rva008A30A0ReleasePtr)( void * );

class Rva008A30A0Object
{
public:
	void clear();

	char m_lead[8];
	void *m_owned;
};

void Rva008A30A0Object::clear()
{
	Rva008A30A0ReleasePtr( m_owned );
	m_owned = 0;
}
