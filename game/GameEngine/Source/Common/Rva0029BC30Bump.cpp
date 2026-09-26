// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0029BC30Bump
{
public:
	void bump();

private:
	char m_pad[0x24];
	int m_count;
	int m_gap;
	int m_sent;
};

void Rva0029BC30Bump::bump()
{
	m_count++;
	m_sent = -1;
}
