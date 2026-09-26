// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva004E9DE0PointerGetter
{
public:
	void *get(void) const;

private:
	void *m_base;
};

void *Rva004E9DE0PointerGetter::get(void) const
{
	return static_cast<unsigned char *>(m_base) + 0x10;
}
