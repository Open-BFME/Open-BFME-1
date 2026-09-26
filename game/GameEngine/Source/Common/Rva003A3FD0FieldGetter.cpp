// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva003A3FD0FieldGetter
{
public:
	void *get(void) const;

private:
	void *m_field;
};

void *Rva003A3FD0FieldGetter::get(void) const
{
	return m_field;
}
