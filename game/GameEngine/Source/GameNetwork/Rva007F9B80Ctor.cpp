// cl: /O2 /GX-
// Rva007F9B80's constructor at 0x007F9B80.

class Rva007F01B0
{
public:
	Rva007F01B0(void) throw();
};

class Gen_00800540
{
public:
	void *m(void);
};

class BfmeThingECMa;
BfmeThingECMa *bfmeGoECMa(void);

class Rva007F9B80
{
public:
	Rva007F9B80(void *owner) throw();

private:
	char m_body[0x6b8];
};

Rva007F9B80::Rva007F9B80(void *owner) throw()
{
	volatile unsigned int *base = (volatile unsigned int *)this;
	base[1] = 0x0112B9C0;
	base[2] = 0x0112B89C;
	base[0] = 0x0112BAE0;
	base[1] = 0x0112BAD0;
	base[2] = 0x0112BACC;

	unsigned int *slot = (unsigned int *)((char *)this + 0x28);
	unsigned int count = 0x20;
	unsigned int zero = 0;
	do {
		slot[1] = zero;
		slot[0] = zero;
		slot[2] = zero;
		slot[3] = zero;
		slot[4] = zero;
		slot[5] = zero;
		slot[6] = zero;
		slot += 7;
	} while (--count != 0);

	char *item = (char *)this + 0x3a8;
	count = 0x20;
	do {
		*(unsigned char *)item = 0;
		((Rva007F01B0 *)(item + 4))->Rva007F01B0::Rva007F01B0();
		*(unsigned int *)(item + 0x10) = zero;
		*(unsigned int *)(item + 0x14) = zero;
		item += 0x18;
	} while (--count != 0);

	((Gen_00800540 *)((char *)this + 0x6ac))->m();
	*(void **)((char *)this + 0x20) = owner;
	*(unsigned int *)((char *)this + 0x0c) = zero;
	*(unsigned int *)((char *)this + 0x10) = zero;
	*(unsigned int *)((char *)this + 0x18) = zero;
	*(unsigned int *)((char *)this + 0x1c) = zero;
	*(unsigned int *)((char *)this + 0x24) = zero;

	slot = (unsigned int *)((char *)this + 0x30);
	count = 0x20;
	do {
		slot[-1] = zero;
		slot[-2] = zero;
		slot[0] = zero;
		slot[1] = zero;
		slot[2] = zero;
		slot[3] = zero;
		slot[4] = zero;
		slot += 7;
	} while (--count != 0);

	*(void **)((char *)this + 0x6a8) = bfmeGoECMa();
	*(unsigned int *)((char *)this + 0x14) = zero;
}
