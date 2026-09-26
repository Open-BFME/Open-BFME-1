// cl: /DNDEBUG /MD

class AddressState0014E5F0
{
public:
	void clearFlag();

private:
	unsigned char m_padding[0x40];
	bool m_flag;
};

void AddressState0014E5F0::clearFlag()
{
	m_flag = false;
}
