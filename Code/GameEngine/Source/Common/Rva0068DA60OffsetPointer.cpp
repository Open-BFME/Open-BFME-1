// cl: /O2 /Ob1 /EHsc

class Rva0068DA60OffsetPointer
{
public:
	char *get(void) const;

private:
	char *m_base;
};

// ?get@Rva0068DA60OffsetPointer@@QBEPADXZ
char *Rva0068DA60OffsetPointer::get(void) const
{
	return m_base + 0x10;
}
