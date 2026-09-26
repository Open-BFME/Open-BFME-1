// cl: /DNDEBUG /MD

class AddressState00191450
{
public:
	int getValue() const;

private:
	unsigned char m_padding[0x18];
	short m_value;
};

int AddressState00191450::getValue() const
{
	return m_value;
}
