// cl: /O2 /MD

// Retail 0x004CB210 reads one dword from this+0x04 and returns it. The only
// caller reaches it through ILT 0x00028402, and the available evidence proves
// the field access but not the owning class, so the class keeps the address.

class Rva004CB210Owner
{
public:
	int getValue() const;

private:
	void *m_vptr;
	int m_value;
};

int Rva004CB210Owner::getValue() const
{
	return m_value;
}
