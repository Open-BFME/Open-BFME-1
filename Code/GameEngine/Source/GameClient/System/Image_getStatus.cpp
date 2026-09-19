// cl: /O2

typedef unsigned int UnsignedInt;

class Image
{
private:
	char m_unmodeled_00[0x30];
	UnsignedInt m_status;

public:
	UnsignedInt getStatus(void) const;
};

// ?getStatus@Image@@QBEIXZ
UnsignedInt Image::getStatus(void) const
{
	return m_status;
}
