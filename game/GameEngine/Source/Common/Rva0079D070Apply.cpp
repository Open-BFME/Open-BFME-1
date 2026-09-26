// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0079D070Apply
{
public:
	Rva0079D070Apply *apply(int *ptr, int value);

	int *m_ptr;
	int m_saved;
};

Rva0079D070Apply *Rva0079D070Apply::apply(int *ptr, int value)
{
	m_ptr = ptr;
	m_saved = *ptr;
	*ptr = value;
	return this;
}
