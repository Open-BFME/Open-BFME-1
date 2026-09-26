// cl: /O2
// Address-derived field address getter at retail 0x0049C970.
// The carved boundary proves only the this-relative address at +0x0C.

class Rva0049C970FieldAddress
{
public:
	void *get() const;

private:
	char m_padding[ 0x0C ];
};

void *Rva0049C970FieldAddress::get() const
{
	return (char *)this + 0x0C;
}
