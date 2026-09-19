// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva004AFD20FieldGetter
{
public:
	void *get(void) const;

private:
	char m_padding[4];
	void *m_field;
};

void *Rva004AFD20FieldGetter::get(void) const
{
	return m_field;
}
