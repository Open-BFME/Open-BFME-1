// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB

class Rva003967D0Owner
{
public:
	bool isEqualFour() const;

private:
	unsigned char m_padding[0x10c];
	int m_value;
};

bool Rva003967D0Owner::isEqualFour() const
{
	return m_value == 4;
}
