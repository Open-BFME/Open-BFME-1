// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME7: the retail body at 0x003C1050 removes known upgrade bits from
// a six-word mask and stores the normalized mask at this+0xA8.
// BfmeThingND::bfmeFindND and the UpgradeCenter global prove the lookup path.

typedef unsigned int UnsignedInt;

extern unsigned char g_bfmeTableDH[];

struct UpgradeMaskType
{
	UnsignedInt m_bits[6];

	int checksum(void) const
	{
		int total = 0;
		const unsigned char *first = (const unsigned char *)this;
		const unsigned char *last = first + sizeof(m_bits);
		while (first < last)
		{
			total += g_bfmeTableDH[*first];
			++first;
		}
		return total;
	}

	void clear(UnsignedInt bit)
	{
		m_bits[bit >> 5] &= ~(1u << (bit & 0x1f));
	}
};

struct BfmeNodeND
{
	unsigned char m_head[4];
	UnsignedInt m_field4;
	unsigned char m_gap08[0x18];
	UnsignedInt m_bit;
	unsigned char m_gap24[0xf8];
	unsigned char m_flag11c;
};

class BfmeThingND
{
public:
	BfmeNodeND *bfmeFindND(const UnsignedInt *mask);
};

extern BfmeThingND *TheUpgradeCenter;

class Rva003C1050
{
public:
	void setMask(UpgradeMaskType mask);

private:
	unsigned char m_pad00[0xa8];
	UpgradeMaskType m_mask;
};

// ?setMask@Rva003C1050@@QAEXUUpgradeMaskType@@@Z
void Rva003C1050::setMask(UpgradeMaskType mask)
{
	UpgradeMaskType working(mask);
	for (;;)
	{
		if (working.checksum() <= 0)
			break;
		BfmeNodeND *upgrade = TheUpgradeCenter->bfmeFindND(working.m_bits);
		if (!upgrade)
			break;
		if (!upgrade->m_flag11c || upgrade->m_field4)
			mask.clear(upgrade->m_bit);
		working.clear(upgrade->m_bit);
	}
	m_mask = mask;
}
