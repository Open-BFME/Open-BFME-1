// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeK1105
{
public:
	void bfmeDrop1105(void);
};

struct BfmeCreate1106
{
	void call(void *output, AsciiString name, int flag, int mode);
};

void j_00022f48(void);

class BfmeResource1106
{
public:
#define BFME_RESOURCE_SLOT(n) virtual void slot##n();
	BFME_RESOURCE_SLOT(0) BFME_RESOURCE_SLOT(1) BFME_RESOURCE_SLOT(2)
	BFME_RESOURCE_SLOT(3) BFME_RESOURCE_SLOT(4) BFME_RESOURCE_SLOT(5)
	BFME_RESOURCE_SLOT(6) BFME_RESOURCE_SLOT(7) BFME_RESOURCE_SLOT(8)
	BFME_RESOURCE_SLOT(9) BFME_RESOURCE_SLOT(10) BFME_RESOURCE_SLOT(11)
	BFME_RESOURCE_SLOT(12) BFME_RESOURCE_SLOT(13) BFME_RESOURCE_SLOT(14)
	BFME_RESOURCE_SLOT(15) BFME_RESOURCE_SLOT(16) BFME_RESOURCE_SLOT(17)
	BFME_RESOURCE_SLOT(18) BFME_RESOURCE_SLOT(19) BFME_RESOURCE_SLOT(20)
	BFME_RESOURCE_SLOT(21) BFME_RESOURCE_SLOT(22) virtual void slot23(void *);
	BFME_RESOURCE_SLOT(24) BFME_RESOURCE_SLOT(25) BFME_RESOURCE_SLOT(26)
	BFME_RESOURCE_SLOT(27) BFME_RESOURCE_SLOT(28) BFME_RESOURCE_SLOT(29)
	BFME_RESOURCE_SLOT(30) BFME_RESOURCE_SLOT(31) BFME_RESOURCE_SLOT(32)
	BFME_RESOURCE_SLOT(33) BFME_RESOURCE_SLOT(34) BFME_RESOURCE_SLOT(35)
	BFME_RESOURCE_SLOT(36) BFME_RESOURCE_SLOT(37) BFME_RESOURCE_SLOT(38)
	BFME_RESOURCE_SLOT(39) BFME_RESOURCE_SLOT(40) BFME_RESOURCE_SLOT(41)
	BFME_RESOURCE_SLOT(42) BFME_RESOURCE_SLOT(43) BFME_RESOURCE_SLOT(44)
	BFME_RESOURCE_SLOT(45) BFME_RESOURCE_SLOT(46) BFME_RESOURCE_SLOT(47)
	BFME_RESOURCE_SLOT(48) BFME_RESOURCE_SLOT(49) BFME_RESOURCE_SLOT(50)
	BFME_RESOURCE_SLOT(51) BFME_RESOURCE_SLOT(52) BFME_RESOURCE_SLOT(53)
	BFME_RESOURCE_SLOT(54) BFME_RESOURCE_SLOT(55) BFME_RESOURCE_SLOT(56)
	BFME_RESOURCE_SLOT(57) BFME_RESOURCE_SLOT(58) BFME_RESOURCE_SLOT(59)
	BFME_RESOURCE_SLOT(60) BFME_RESOURCE_SLOT(61) BFME_RESOURCE_SLOT(62)
	BFME_RESOURCE_SLOT(63) BFME_RESOURCE_SLOT(64) BFME_RESOURCE_SLOT(65)
	BFME_RESOURCE_SLOT(66) BFME_RESOURCE_SLOT(67) BFME_RESOURCE_SLOT(68)
	BFME_RESOURCE_SLOT(69) BFME_RESOURCE_SLOT(70) BFME_RESOURCE_SLOT(71)
	BFME_RESOURCE_SLOT(72) BFME_RESOURCE_SLOT(73) BFME_RESOURCE_SLOT(74)
	BFME_RESOURCE_SLOT(75) BFME_RESOURCE_SLOT(76) BFME_RESOURCE_SLOT(77)
	BFME_RESOURCE_SLOT(78) BFME_RESOURCE_SLOT(79) BFME_RESOURCE_SLOT(80)
	BFME_RESOURCE_SLOT(81) BFME_RESOURCE_SLOT(82) BFME_RESOURCE_SLOT(83)
	BFME_RESOURCE_SLOT(84) BFME_RESOURCE_SLOT(85) BFME_RESOURCE_SLOT(86)
	BFME_RESOURCE_SLOT(87) BFME_RESOURCE_SLOT(88) BFME_RESOURCE_SLOT(89)
	BFME_RESOURCE_SLOT(90) BFME_RESOURCE_SLOT(91) BFME_RESOURCE_SLOT(92)
	BFME_RESOURCE_SLOT(93) BFME_RESOURCE_SLOT(94) BFME_RESOURCE_SLOT(95)
	BFME_RESOURCE_SLOT(96) BFME_RESOURCE_SLOT(97) BFME_RESOURCE_SLOT(98)
	BFME_RESOURCE_SLOT(99) BFME_RESOURCE_SLOT(100) BFME_RESOURCE_SLOT(101)
	BFME_RESOURCE_SLOT(102) BFME_RESOURCE_SLOT(103) BFME_RESOURCE_SLOT(104)
	BFME_RESOURCE_SLOT(105) BFME_RESOURCE_SLOT(106) BFME_RESOURCE_SLOT(107)
	virtual void slot108(bool); BFME_RESOURCE_SLOT(109) virtual void slot110(bool);
#undef BFME_RESOURCE_SLOT
};

struct BfmeEntry1106
{
	AsciiString m_name;
	void *m_resource;
	char m_padding[0xc];
};

class Glo012F1028Type
{
public:
	char m_padding[0x28];
	BfmeCreate1106 *m_create;
};

extern Glo012F1028Type *Glo012F1028;

class BfmeK1106
{
public:
	void bfmeDrop1106(void);
	char m_padding00[0x14];
	BfmeEntry1106 *m_begin;
	BfmeEntry1106 *m_end;
	char m_padding1c[8];
	void *m_callbackData;
};

void BfmeK1106::bfmeDrop1106(void)
{
	BfmeK1106 *self = this;
	reinterpret_cast<BfmeK1105 *>(self)->bfmeDrop1105();

	BfmeCreate1106 *creator = Glo012F1028->m_create;
	BfmeEntry1106 *entry = self->m_begin;
	if (entry != self->m_end)
	{
		do
		{
			if (creator != 0)
			{
				union
				{
					void (*raw)();
					void (BfmeCreate1106::*member)(void *, AsciiString, int, int);
				} createCast;
				createCast.raw = j_00022f48;
				(creator->*createCast.member)(
					&entry->m_resource,
					AsciiString(*(const AsciiString *)entry), 0, 1);
			}

			if (entry->m_resource != 0)
			{
				reinterpret_cast<BfmeResource1106 *>(entry->m_resource)->slot110(true);
				reinterpret_cast<BfmeResource1106 *>(entry->m_resource)->slot108(true);
				reinterpret_cast<BfmeResource1106 *>(entry->m_resource)->slot23(
					self->m_callbackData);
			}

			entry = reinterpret_cast<BfmeEntry1106 *>(
				reinterpret_cast<char *>(entry) + 0x14);
		} while (entry != self->m_end);
	}
}

struct BfmeNode1106
{
	char m_bfmePad[8];
	BfmeNode1106 *m_bfme08;
	char m_bfmePad1[8];
	BfmeK1106 *m_bfme14;
	char m_bfmePad2[0x18];
	int m_bfme30;
	int m_bfme34;
};

BfmeNode1106 *__cdecl bfmeNext1106(BfmeNode1106 *p);

class BfmeW1106
{
public:
	void bfmeGo1106A(void);
	int bfmeGo1106B(void);
	BfmeNode1106 *m_bfme00;
	char m_bfmePad[0x20];
	BfmeNode1106 *m_bfme24;
};

void BfmeW1106::bfmeGo1106A(void)
{
	BfmeNode1106 *h = m_bfme00;
	BfmeNode1106 *p = h->m_bfme08;

	while (p != h) {
		if (p->m_bfme14)
			p->m_bfme14->bfmeDrop1106();
		p = bfmeNext1106(p);
		h = m_bfme00;
	}
}

int BfmeW1106::bfmeGo1106B(void)
{
	BfmeNode1106 *h = m_bfme24;
	BfmeNode1106 *p = h->m_bfme08;
	int n = 0xf;

	while (p != h) {
		if (!p->m_bfme30) {
			int v = p->m_bfme34 + 0xf;

			if (n < v)
				n = v;
		}
		p = bfmeNext1106(p);
	}
	return n;
}
