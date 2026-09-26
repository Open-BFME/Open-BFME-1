// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0044B310Flag
{
public:
	void toggleFlag();

private:
	unsigned char m_padding[0x839];
	bool m_flag;
};

void Rva0044B310Flag::toggleFlag()
{
	m_flag = 1 - m_flag;
}
