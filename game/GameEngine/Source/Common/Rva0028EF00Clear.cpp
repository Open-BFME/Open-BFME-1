// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0028EF00Clear
{
public:
	void clearAt(int index);

private:
	char m_pad[0x24];
	char m_bytes[1];
};

void Rva0028EF00Clear::clearAt(int index)
{
	m_bytes[index] = 0;
}
