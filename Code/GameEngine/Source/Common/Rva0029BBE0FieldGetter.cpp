// cl: /O2 /Ob2 /GR- /EHsc- /MD /DNDEBUG

class Rva0029BBE0FieldGetter
{
public:
	void *get(void) const;

private:
	char m_padding[12];
	void *m_field;
};

void *Rva0029BBE0FieldGetter::get(void) const
{
	return m_field;
}
