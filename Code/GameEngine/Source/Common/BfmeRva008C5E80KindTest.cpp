// Kind-bit predicate: true for a fixed set of (bits & 0x3F) values.

class Gen_008C5E80
{
public:
	bool bfmeIsKind(void) const;

private:
	int m_bfmeHead;						// +0x00
	unsigned int m_bfmeBits;				// +0x04
};

// ?bfmeIsKind@Gen_008C5E80@@QBE_NXZ
bool Gen_008C5E80::bfmeIsKind(void) const
{
	switch (m_bfmeBits & 0x3F)
	{
	case 1:
	case 9:
	case 0xA:
	case 0x15:
	case 0x16:
	case 0x1A:
	case 0x1B:
	case 0x1D:
	case 0x1E:
	case 0x21:
	case 0x23:
	case 0x24:
	case 0x29:
	case 0x2A:
		return true;
	default:
		return false;
	}
}
