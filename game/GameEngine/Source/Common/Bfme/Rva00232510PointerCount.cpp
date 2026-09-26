// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00232510 (29 bytes).

class Rva00232510
{
public:
	int pointerCount() const;

private:
	unsigned char m_unmodelled_000[0xD0];
	void *m_first;
	unsigned char m_unmodelled_0D4[4];
	void *m_second;
};

int Rva00232510::pointerCount() const
{
	int count = 0;
	if (m_first != 0)
		count = 1;
	if (m_second != 0)
		++count;
	return count;
}
