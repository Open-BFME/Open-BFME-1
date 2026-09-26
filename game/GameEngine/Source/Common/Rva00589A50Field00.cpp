// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved body reads the first dword from this and returns it. The caller
// and nearby bodies do not prove the field's semantic type, so the source
// keeps the address-derived owner and names the operation by its offset.

class Rva00589A50Owner
{
public:
	void *getField00(void) const;

private:
	void *m_field00;
};

// ?getField00@Rva00589A50Owner@@QBEPAXXZ
void *Rva00589A50Owner::getField00(void) const
{
	return m_field00;
}
