// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: MetaMapRec default ctor zeros two dwords at +0x1c and +0x20.

class MetaMapRec
{
public:
	MetaMapRec();

private:
	unsigned char m_pad[0x1c];
	unsigned int m_a;
	unsigned int m_b;
};

// ??0MetaMapRec@@QAE@XZ
MetaMapRec::MetaMapRec()
{
	m_a = 0;
	m_b = 0;
}
