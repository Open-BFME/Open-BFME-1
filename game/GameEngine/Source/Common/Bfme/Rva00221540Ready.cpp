// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00221540 (32 bytes).

class Rva00221540
{
public:
	int isReady();

private:
	unsigned char m_unmodelled_000[4];
	unsigned char *m_target;
	unsigned char m_unmodelled_008[0xB1];
	unsigned char m_ready;
};

int Rva00221540::isReady()
{
	if (m_ready != 0)
	{
		if (m_target[0x153] != 0)
			return 1;
	}
	return 0;
}
