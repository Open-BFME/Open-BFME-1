// cl: /DNDEBUG /MD

class AddressState001516B0
{
public:
	void rewindField();

private:
	unsigned int m_padding;
	int m_field;
};

void AddressState001516B0::rewindField()
{
	m_field -= 12;
}
