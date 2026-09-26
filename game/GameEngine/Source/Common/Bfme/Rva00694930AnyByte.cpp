// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00694930 (37 bytes).

class Rva00694930
{
public:
	int anyByte() const;

private:
	unsigned char m_unmodelled_000[0x39];
	unsigned char m_byte0;
	unsigned char m_byte1;
	unsigned char m_byte2;
	unsigned char m_byte3;
};

int Rva00694930::anyByte() const
{
	if (m_byte0 == 0 && m_byte1 == 0 && m_byte2 == 0 && m_byte3 == 0)
		return 0;
	return 1;
}
