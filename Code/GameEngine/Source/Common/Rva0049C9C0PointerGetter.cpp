// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva0049C9C0PointerGetter
{
public:
	void *get(void) const;

private:
	char m_padding[0x144];
	void *m_value;
};

void *Rva0049C9C0PointerGetter::get(void) const
{
	return m_value;
}
