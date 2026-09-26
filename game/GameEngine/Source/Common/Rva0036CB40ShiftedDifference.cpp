// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB

class Rva0036CB40Owner
{
public:
	int shiftedDifference() const;

private:
	unsigned char m_padding[0xe8];
	int m_begin;
	int m_end;
};

int Rva0036CB40Owner::shiftedDifference() const
{
	return (m_end - m_begin) >> 2;
}
