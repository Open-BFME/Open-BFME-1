// ?get@Rva003A3D20Owner@@QBEPAXXZ
// cl: /O2 /MD /EHsc-
//
// Retail 0x003A3D20 loads the pointer at this+0x28 and returns it.
// The carved boundary and the generated thunk prove the body and its extent,
// but they do not prove a semantic owner, so this address-derived name keeps
// the identity claim limited to the observed field access.

class Rva003A3D20Owner
{
public:
	void *get() const;

	unsigned char m_padding[0x28];
	void *m_value;
};

void *Rva003A3D20Owner::get() const
{
	return m_value;
}
