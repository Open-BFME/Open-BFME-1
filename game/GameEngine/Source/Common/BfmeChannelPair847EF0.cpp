// cl: /O2
// A descriptor holding two four-channel groups, both set to the same 2/3/0/4
// pattern. The table pointer at offset 0 is an ordinary member, not a vptr:
// retail stores the count, tests the argument, and only then writes the table,
// and a vptr store cannot be moved off the top of a constructor.

struct BfmeChannels847EF0
{
	unsigned char m_one;
	unsigned char m_two;
	unsigned char m_three;
	unsigned char m_four;
};

// Retail's table pointer cell is the .rdata address 0x0112FADC (RVA
// 0x00D2FADC), which symbols.csv pins as the STLport 4.5.3
// moneypunct<char> vtable ??_7?$moneypunct@D$00@_STL@@6B@; retail reuses that
// block as the channel table.  Spelled the way the sibling
// BfmeChannelPair8480.cpp spells its own three, so the reference resolves to
// the vtable the STLport TUs define.
extern "C" const void *const __identifier("??_7?$moneypunct@D$00@_STL@@6B@")[];
#define bfmeTable847EF0 __identifier("??_7?$moneypunct@D$00@_STL@@6B@")

class BfmeChannelPair847EF0
{
public:
	BfmeChannelPair847EF0(void *source);

private:
	const void *m_table;
	int m_count;
	bool m_isNull;
	char m_pad[3];
	BfmeChannels847EF0 m_first;
	BfmeChannels847EF0 m_second;
};

// A file-static helper: fully inlined, no COMDAT of its own, and it keeps the
// two groups' stores in retail's order instead of hoisting both constants.
static void bfmeSetChannels847EF0(BfmeChannels847EF0 &channels)
{
	channels.m_one = 2;
	channels.m_two = 3;
	channels.m_three = 0;
	channels.m_four = 4;
}

BfmeChannelPair847EF0::BfmeChannelPair847EF0(void *source)
{
	m_count = 1;
	m_isNull = (source == 0);
	m_table = &bfmeTable847EF0;

	bfmeSetChannels847EF0(m_first);
	bfmeSetChannels847EF0(m_second);
}
