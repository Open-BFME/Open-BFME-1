// cl: /DNDEBUG /MD

class AddressState0016A300
{
public:
	unsigned int getFlag() const;

private:
	unsigned char m_padding;
	bool m_flag;
};

unsigned int AddressState0016A300::getFlag() const
{
	return m_flag;
}
