// ?get@Rva001A42A0Owner@@QBEPAXXZ
// cl: /O2 /MD /EHsc-
//
// Retail loads the first dword from this and returns it.
// The adjacent STLport list iterator bodies place this helper in the Audio TU,
// but the binary does not prove a semantic owner.

class Rva001A42A0Owner
{
public:
	void *get() const;

	void *m_value;
};

void *Rva001A42A0Owner::get() const
{
	return m_value;
}
