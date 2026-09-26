// cl: /DNDEBUG /MD

class Rva007E4780Field
{
public:
	int get() const;

private:
	unsigned char m_padding[0x30];
	int m_value;
};

int Rva007E4780Field::get() const
{
	return m_value;
}
