// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail RVA 0x008D6010, 163 bytes. Owner identity remains unproven.
// This body is slot 1 of tables 0x011376D0, 0x01137720 and 0x01137770.
// Evidence: targets/game/reverse/identity_evidence/008d6010-packed-release.md
//
// The late count reload reads the high WORD after clearing the tagged value.
// Reading only that view as volatile retains the retail load without making
// the initial bitfield reads volatile or adding a compiler barrier.

class BfmeThing936F
{
public:
	void bfmeGo936F();
};

class Rva008D6010Value
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeDropValue();

	unsigned int m_kind;
};

extern Rva008D6010Value *g_bfmeFallbackDB;

class Rva008D6010Node
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeDrop();
	virtual void bfmeFinish();


private:
	union
	{
		struct
		{
			unsigned int m_low : 16;
			unsigned int m_count : 12;
			unsigned int m_high : 4;
		};
		unsigned int m_packed;
		struct
		{
			unsigned short m_word04;
			volatile unsigned short m_word06;
		};
	};
	unsigned char m_pad08[ 0x14 - 8 ];
	unsigned int volatile m_valueBits;
	unsigned char m_pad18[ 0x2C - 0x18 ];
	BfmeThing936F *m_notify;
};

void Rva008D6010Node::bfmeDrop()
{
	unsigned int count = m_count;
	Rva008D6010Value *value = (Rva008D6010Value *)(m_valueBits & ~1u);
	if ( value != 0 && value != g_bfmeFallbackDB && count == 2 )
	{
		unsigned int kind = value->m_kind;
		if ( (kind & 0x3f) == 0x1c &&
			!((unsigned char)(~(kind >> 15)) & 1) &&
			(kind & 0x0fff0000) == 0x00010000 )
		{
			Rva008D6010Value *owned = (Rva008D6010Value *)(m_valueBits & ~1u);
			if ( owned != 0 )
				owned->bfmeDropValue();
			m_valueBits = 0;
			count = m_word06 & 0xfff;
		}
	}

	--count;
	m_notify->bfmeGo936F();

	unsigned int stored = count;
	if ( stored > 0xfff )
		stored = 0xfff;
	m_packed = (m_packed & 0xf000ffff) | (stored << 16);
	if ( count == 0 )
		bfmeFinish();
}
