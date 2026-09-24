// ?bfmeReg1024@BfmeP1024@@QAEXPAVBfmeE1024@@@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Retail RVA 0x009EF280, 1042 bytes of code ending in ret 4 at 0x009EF68F; the
// 7-entry jump table that follows (0x009EF694) belongs to this body's switch,
// and the 30-byte routine at 0x009EF6B0 is a separate function.
//
// Identity: the matched caller BfmeE1024::bfmeGo1024E (0x009EB8D0,
// BfmeConv1024.cpp) calls this member on g_bfmeP1024 (0x0134FAAC) passing
// itself, which is the pinned ?bfmeReg1024@BfmeP1024@@QAEXPAVBfmeE1024@@@Z.
// The class and method names are the pinned placeholders, not a claim of the
// original identity.
//
// g_bfmeP1024 is the same receiver the matched Q1Receiver0134FAAC members in
// this directory model (m009F1AE0 documents the layout): the section at
// +0x60, the int budget at +0x20 and seven 0x28-byte STLport deques of
// element pointers from +0x78. The element is the one those members use: a
// vtable (slot +0x38 returns the size charged against +0x20), a volatile
// 8-bit queue number in bits 16..23 of the word at +4, a plain bit 25 and a
// pointer at +8.

#include <deque>
#include <windows.h>

class BfmeE1024
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual int slot38();

	volatile unsigned int m_bits00 : 16;
	volatile unsigned int m_queue : 8;
	unsigned int m_bit24 : 1;
	unsigned int m_bit25 : 1;
	unsigned int m_bit26 : 1;
	int m_key08;
};

typedef _STL::deque<BfmeE1024 *> BfmeP1024Queue;

class BfmeP1024
{
public:
	void bfmeReg1024(BfmeE1024 *item);

private:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	int m_field20;
	unsigned int m_field24;
	unsigned int m_field28;
	CRITICAL_SECTION m_lock2c;
	unsigned char m_unmodelled_044[0x1C];
	CRITICAL_SECTION m_lock60;
	BfmeP1024Queue m_deques78[7];
	unsigned char m_unmodelled_190[0x64];
};

typedef char BfmeP1024SizeCheck[sizeof(BfmeP1024) == 0x1f4 ? 1 : -1];

void BfmeP1024::bfmeReg1024(BfmeE1024 *item)
{
	if (item->m_key08 == 0 || item->m_queue == 7)
		return;

	EnterCriticalSection(&m_lock60);
	while ((item->m_queue == 1 || item->m_queue == 5) &&
		m_deques78[item->m_queue].front() == item)
	{
		LeaveCriticalSection(&m_lock60);
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}
	while (item->m_queue == 8)
	{
		LeaveCriticalSection(&m_lock60);
		Sleep(1);
		EnterCriticalSection(&m_lock60);
	}

	unsigned int i;
	for (i = 0; i < m_deques78[item->m_queue].size(); ++i)
	{
		if (m_deques78[item->m_queue][i] == item)
			break;
	}
	m_deques78[item->m_queue][i] =
		m_deques78[item->m_queue][m_deques78[item->m_queue].size() - 1];
	m_deques78[item->m_queue].pop_back();
	LeaveCriticalSection(&m_lock60);

	item->m_bit25 = 0;
	if (item->m_queue == 3)
	{
		m_field20 -= item->slot38();
		item->m_queue = 4;
		if (m_field20 < 0)
			m_field20 = 0;
	}

	switch (item->m_queue)
	{
	case 0:
		item->slot04();
		item->m_queue = 1;
	case 1:
		item->slot08();
		item->m_queue = 2;
		m_field20 += item->slot38();
	case 2:
		item->slot0C();
		item->m_queue = 4;
		m_field20 -= item->slot38();
		if (m_field20 < 0)
			m_field20 = 0;
	case 4:
		item->slot14();
		item->m_queue = 5;
	case 5:
		item->slot18();
		item->m_queue = 6;
	case 6:
		item->slot1C();
		item->m_queue = 7;
	}
}
