// ?field@Rva003AC320Opaque@@QAEPADXZ
// cl: /DNDEBUG /MD /EHs-c-

class Rva003AC320Opaque
{
public:
	char *field(void);

private:
	int m_prefix;
	char m_field[4];
};

char *Rva003AC320Opaque::field(void)
{
	return m_field;
}
