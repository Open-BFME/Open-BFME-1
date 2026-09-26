// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// The original 147-byte dump contains two distinct 31-byte predicates
// separated by 0xCC padding, followed by an unrelated comparison helper.
class Rva008ABFE0Flags
{
public:
	int rva008ABFE0() const;
	int rva008AC000() const;

private:
	int m_unused;
	unsigned int m_flags;
};

int Rva008ABFE0Flags::rva008ABFE0() const
{
	if ((m_flags & 63) == 7 && ((unsigned char)~(unsigned char)(m_flags >> 15) & 1) == 0)
		return 1;
	return 0;
}

int Rva008ABFE0Flags::rva008AC000() const
{
	if ((m_flags & 63) == 36 && ((unsigned char)~(unsigned char)(m_flags >> 15) & 1) == 0)
		return 1;
	return 0;
}
