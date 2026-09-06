// ?bfmeInitDGD@BfmeThingDGD@@QAEPAV1@PAX@Z
// partial score=0.94 date=2026-09-05
// Retail 0x007F7FA0. Initialize the DGD holder and its four child records.

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Rva007F6D60Child
{
public:
	void init();
};

#pragma comment(linker, "/alternatename:?init@Rva007F6D60Child@@QAEXXZ=?d_007f6d60@@YAXXZ")

class BfmeThingECKb
{
public:
	void *bfmeGoECKb();
};

class BfmeThingDGD
{
public:
	BfmeThingDGD *bfmeInitDGD(void *a);

	volatile unsigned m_v0;
	volatile unsigned m_v4;
	volatile unsigned m_v8;
	void *m_arg;
	void *m_result;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1c;
	unsigned m_20;
	unsigned m_24;
	unsigned m_28;
	unsigned m_2c;
	unsigned m_30;
	unsigned char m_34;
	unsigned char m_35;
	unsigned char m_36;
	unsigned char m_37;
	unsigned m_38;
	unsigned m_3c;
	unsigned m_40;
	unsigned m_44;
	unsigned m_48;
	unsigned m_4c;
	unsigned m_50;
	unsigned m_54;
	unsigned char m_children[0x250];
	unsigned m_2a8;
	unsigned m_2ac;
	unsigned m_2b0;
	unsigned m_2b4;
	unsigned m_2b8;
	unsigned m_2bc;
	unsigned m_2c0;
	unsigned m_2c4;
	unsigned m_2c8;
	unsigned m_2cc;
	unsigned m_2d0;
	unsigned m_2d4;
	unsigned m_2d8;
	unsigned char m_tail[0x400];
	unsigned m_6dc;
};

static __forceinline void initDGDChildren(BfmeThingDGD *self)
{
	Rva007F6D60Child *child = (Rva007F6D60Child *)self->m_children;
	int count = 4;
	do {
		child->init();
		child = (Rva007F6D60Child *)((char *)child + 0x94);
		--count;
	} while (count != 0);
}

BfmeThingDGD *BfmeThingDGD::bfmeInitDGD(void *a)
{
	m_v4 = 0x01118e58;
	m_v8 = 0x0112b680;
	m_v0 = 0x0112b800;
	m_v4 = 0x0112b7f8;
	m_v8 = 0x0112b7f0;
	m_38 = 0;
	m_3c = 0;
	_ReadWriteBarrier();
	m_48 = 0;
	m_4c = 0;
	initDGDChildren(this);

	m_2a8 = 0;
	m_2ac = 0;
	m_2b0 = 0;
	m_2b4 = 0;
	m_2b8 = 0;
	m_2bc = 0;
	m_2c0 = 0;
	m_2c4 = 0;
	m_2c8 = 0;
	m_2cc = 0;
	m_2d0 = 0;
	m_2d4 = 0;
	m_arg = a;
	m_result = ((BfmeThingECKb *)m_arg)->bfmeGoECKb();
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_50 = 0;
	m_2c = 0;
	m_28 = 0;
	m_2d8 = 0;
	m_36 = 0;
	m_44 = 0;
	m_54 = 0;
	m_24 = 0;
	m_30 = 0;
	m_6dc = 0x2710;
	return this;
}
