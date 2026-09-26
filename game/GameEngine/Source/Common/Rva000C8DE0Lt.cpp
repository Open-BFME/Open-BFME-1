// cl: /O2 /Ob0

class Rva000C8DE0
{
	char m_pad;
	unsigned char m_value;

public:
	bool below(int a);
};

bool Rva000C8DE0::below(int a)
{
	return m_value < a;
}
