// cl: /O2 /MD /EHsc-

class Rva000879C0PointerGetter
{
public:
	void *get() const;

private:
	void *m_value;
};

void *Rva000879C0PointerGetter::get() const
{
	return m_value;
}
