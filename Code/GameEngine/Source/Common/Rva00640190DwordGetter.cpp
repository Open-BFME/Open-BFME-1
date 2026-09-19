// cl: /DNDEBUG /MD /EHsc
// The carved body at retail RVA 0x00640190 loads the first dword and returns.
// The address-derived owner records that field access without claiming a
// semantic class name.

class Rva00640190Owner
{
public:
	int get() const;

	int m_value;
};

int Rva00640190Owner::get() const
{
	return m_value;
}

class Rva006401B0DwordGetter
{
public:
	int get() const;

	int m_value;
};

int Rva006401B0DwordGetter::get() const
{
	return m_value;
}
