// cl: /O2

class Rva0036AD90
{
public:
	void *getAt1C();

private:
	char m_padding[0x1c];
	char m_value;
};

void *Rva0036AD90::getAt1C()
{
	return &m_value;
}
