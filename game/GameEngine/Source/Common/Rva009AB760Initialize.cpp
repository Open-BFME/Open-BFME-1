// Open-BFME5 conversion of the codec probability-table initializer.

struct Rva009AB760Block
{
	int m_zero;
	int m_minusOne;
	unsigned short m_four;
	unsigned short m_padding;
	int m_tailPadding;
};

extern "C" void * __cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)

struct Rva009AB760Context
{
	unsigned char m_pad0[0xCC];
	Rva009AB760Block m_block0;
	Rva009AB760Block m_block1;
	Rva009AB760Block m_block2;
	Rva009AB760Block m_block3;
};

void Rva009AB760Initialize(Rva009AB760Context *self)
{
	int zero = 0;
	memset(&self->m_block0, zero, sizeof(Rva009AB760Block));
	memset(&self->m_block1, zero, sizeof(Rva009AB760Block));
	memset(&self->m_block2, zero, sizeof(Rva009AB760Block));
	memset(&self->m_block3, zero, sizeof(Rva009AB760Block));

	zero |= 0xFFFFFFFF;
	self->m_block0.m_minusOne = zero;
	self->m_block1.m_minusOne = zero;
	self->m_block2.m_minusOne = zero;
	self->m_block3.m_minusOne = zero;

	unsigned short four = 4;
	self->m_block0.m_four = four;
	self->m_block1.m_four = four;
	self->m_block2.m_four = four;
	self->m_block3.m_four = four;
}
