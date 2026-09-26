// cl: /O2
// Three more descriptors of the shape landed in BfmeChannelPair847EF0.cpp: two
// four-channel groups, both set to 2/3/0/4, and a table pointer at offset 0
// that is an ordinary member rather than a vptr -- retail writes it after the
// count and after the argument test, which is a place no vptr store can reach.

struct BfmeChannels8480
{
	unsigned char m_one;
	unsigned char m_two;
	unsigned char m_three;
	unsigned char m_four;
};

// A file-static helper: fully inlined, no COMDAT of its own, and it keeps the
// two groups' stores in retail's order instead of hoisting both constants.
static void bfmeSetChannels8480(BfmeChannels8480 &channels)
{
	channels.m_one = 2;
	channels.m_two = 3;
	channels.m_three = 0;
	channels.m_four = 4;
}

struct BfmeTable847F90;
extern const BfmeTable847F90 *const bfmeTable847F90;

class BfmeChannelPair847F90
{
public:
	BfmeChannelPair847F90(void *source);

private:
	const void *m_table;
	int m_count;
	bool m_isNull;
	char m_pad[3];
	BfmeChannels8480 m_first;
	BfmeChannels8480 m_second;
};

BfmeChannelPair847F90::BfmeChannelPair847F90(void *source)
{
	m_count = 1;
	m_isNull = (source == 0);
	m_table = &bfmeTable847F90;

	bfmeSetChannels8480(m_first);
	bfmeSetChannels8480(m_second);
}

struct BfmeTable848030;
extern const BfmeTable848030 *const bfmeTable848030;

class BfmeChannelPair848030
{
public:
	BfmeChannelPair848030(void *source);

private:
	const void *m_table;
	int m_count;
	bool m_isNull;
	char m_pad[3];
	BfmeChannels8480 m_first;
	BfmeChannels8480 m_second;
};

BfmeChannelPair848030::BfmeChannelPair848030(void *source)
{
	m_count = 1;
	m_isNull = (source == 0);
	m_table = &bfmeTable848030;

	bfmeSetChannels8480(m_first);
	bfmeSetChannels8480(m_second);
}

struct BfmeTable8480D0;
extern const BfmeTable8480D0 *const bfmeTable8480D0;

class BfmeChannelPair8480D0
{
public:
	BfmeChannelPair8480D0(void *source);

private:
	const void *m_table;
	int m_count;
	bool m_isNull;
	char m_pad[3];
	BfmeChannels8480 m_first;
	BfmeChannels8480 m_second;
};

BfmeChannelPair8480D0::BfmeChannelPair8480D0(void *source)
{
	m_count = 1;
	m_isNull = (source == 0);
	m_table = &bfmeTable8480D0;

	bfmeSetChannels8480(m_first);
	bfmeSetChannels8480(m_second);
}
