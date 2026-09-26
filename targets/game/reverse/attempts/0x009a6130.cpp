// ?d_009a6130@@YAXXZ
// partial score=0.3 date=2026-09-18
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Opaque VP6 codec dispatcher at retail 0x009A6130.  The boundary and the
// field offsets are taken from the retail body; no class identity is claimed.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeGridZJ;
extern void __cdecl bfmeFillZJ(BfmeGridZJ *);

struct Rva009AF200Context;
extern void __cdecl Rva009AF200CopyPlanes(
	Rva009AF200Context *, int, int);

struct Rva009AF320Context;
extern void __cdecl Rva009AF320CopyPlanes(
	Rva009AF320Context *, int, int);

extern void __cdecl d_009a8c50();
extern void __cdecl d_009b2530();
extern void __cdecl d_009b2a50();
extern void __cdecl d_009b3800();

struct Rva009A6130Context
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	unsigned char *m_10;
	unsigned char *m_14;
	int m_18;
	int m_1c;
	int m_20;
	unsigned char m_pad24[0x6c - 0x24];
	void *m_6c;
	unsigned char m_pad70[0x78 - 0x70];
	unsigned int m_78;
	unsigned int m_7c;
	unsigned int m_80;
	unsigned char m_pad84[0x90 - 0x84];
	unsigned int m_90;
	unsigned int m_94;
	unsigned int m_98;
	unsigned char m_pad9c[0xbc - 0x9c];
	unsigned char *m_bc;
	void *m_c0;
	void *m_c4;
};

typedef void (__cdecl *Rva009A6130CopyCallbackA)(
	unsigned char *, unsigned char *, unsigned int, unsigned int, unsigned int);
typedef void (__cdecl *Rva009A6130CopyCallbackB)(
	unsigned char *, unsigned int, unsigned int, unsigned int, unsigned char *);

#define Rva009A6130CallbackA \
	(*(Rva009A6130CopyCallbackA *)0x01356E6C)
#define Rva009A6130CallbackB \
	(*(Rva009A6130CopyCallbackB *)0x01356E60)

class Rva009A6130
{
public:
	static void __cdecl process(
		Rva009A6130Context *, int, int, int, int, int, int, int, int, int);
};

void Rva009A6130::process(
	Rva009A6130Context *context, int arg2, int arg3, int arg4, int arg5,
	int arg6, int arg7, int arg8, int arg9, int arg10)
{
	register int value3 = arg3;
	register int value2 = arg2;
	register int value6 = arg6;
	context->m_18 = arg8;
	context->m_04 = value3;
	context->m_1c = arg9;
	context->m_00 = value2;
	context->m_08 = arg4;
	context->m_0c = arg5;
	context->m_10 = (unsigned char *)value6;
	context->m_14 = (unsigned char *)arg7;
	context->m_20 = arg10;

	switch (context->m_08)
	{
	case 0:
		if (context->m_6c == 0 || context->m_c0 == 0)
			return;
		{
			unsigned int bytes = context->m_94 * context->m_98;
			bytes <<= 1;
			memcpy((unsigned char *)context->m_7c + arg7,
				(unsigned char *)context->m_7c + arg6, bytes);
			memcpy(context->m_14 + context->m_80,
				context->m_10 + context->m_80, bytes);
			Rva009A6130CallbackA(
				context->m_10 + context->m_78,
				context->m_14 + context->m_78,
				context->m_90 << 3,
				context->m_94 << 3,
				context->m_98);
		}
		return;

	case 8:
		bfmeFillZJ((BfmeGridZJ *)context);
		if (context->m_00 < 2)
		{
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			return;
		}
		if (context->m_6c == 0 || context->m_c0 == 0)
		{
			((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b3800)(
				context, (int)context->m_10, (int)context->m_bc);
			return;
		}
		{
			unsigned int bytes = context->m_94 * context->m_98;
			bytes <<= 1;
			memcpy(context->m_14 + context->m_7c,
				context->m_bc + context->m_7c, bytes);
			memcpy(context->m_14 + context->m_80,
				context->m_bc + context->m_80, bytes);
			Rva009A6130CallbackA(
				context->m_bc + context->m_78,
				context->m_14 + context->m_78,
				context->m_90 << 3,
				context->m_94 << 3,
				context->m_98);
		}
		return;

	case 1:
		bfmeFillZJ((BfmeGridZJ *)context);
		Rva009AF200CopyPlanes(
			(Rva009AF200Context *)context,
			(int)context->m_10, (int)context->m_14);
		return;

	case 2:
	case 3:
	default:
		Rva009AF320CopyPlanes(
			(Rva009AF320Context *)context, arg6, arg7);
		((void (__cdecl *)(Rva009A6130Context *, int))d_009a8c50)(
			context, (int)context->m_14);
		((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2530)(
			context, (int)context->m_14, (int)context->m_14);
		return;

	case 4:
		if (arg2 < 5 || context->m_6c == 0 || context->m_c0 == 0)
		{
			bfmeFillZJ((BfmeGridZJ *)context);
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			return;
		}
		Rva009AF320CopyPlanes(
			(Rva009AF320Context *)context, arg6, arg7);
		return;

	case 5:
	case 6:
		if (arg2 >= 5 && context->m_6c != 0)
		{
			if (context->m_c0 != 0)
			{
				Rva009AF320CopyPlanes(
					(Rva009AF320Context *)context,
					(int)context->m_bc, arg6);
				((void (__cdecl *)(Rva009A6130Context *, int))d_009a8c50)(
					context, (int)context->m_bc);
				((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2a50)(
					context, (int)context->m_bc, (int)context->m_bc);
			}
			else
			{
				Rva009AF320CopyPlanes(
					(Rva009AF320Context *)context, arg6, arg7);
				((void (__cdecl *)(Rva009A6130Context *, int))d_009a8c50)(
					context, (int)context->m_14);
				((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2a50)(
					context, (int)context->m_14, (int)context->m_14);
			}
		}
		else
		{
			bfmeFillZJ((BfmeGridZJ *)context);
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			((void (__cdecl *)(Rva009A6130Context *, int))d_009a8c50)(
				context, (int)context->m_14);
			((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2530)(
				context, (int)context->m_14, (int)context->m_14);
		}
		if (context->m_c4 == 0)
			return;
		Rva009A6130CallbackB(
			context->m_14 + context->m_78,
			context->m_90 << 3,
			context->m_94 << 3,
			context->m_98,
			context->m_14);
		return;

	case 7:
		if (arg2 < 5)
		{
			bfmeFillZJ((BfmeGridZJ *)context);
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			((void (__cdecl *)(Rva009A6130Context *))d_009a8c50)(context);
			((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2530)(
				context, (int)context->m_14, (int)context->m_14);
			return;
		}
		if (context->m_6c == 0)
		{
			bfmeFillZJ((BfmeGridZJ *)context);
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			((void (__cdecl *)(Rva009A6130Context *))d_009a8c50)(context);
			((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2530)(
				context, (int)context->m_14, (int)context->m_14);
			return;
		}
		if (context->m_c0 == 0)
		{
			bfmeFillZJ((BfmeGridZJ *)context);
			Rva009AF200CopyPlanes(
				(Rva009AF200Context *)context,
				(int)context->m_10, (int)context->m_14);
			return;
		}
		Rva009AF320CopyPlanes(
			(Rva009AF320Context *)context, (int)context->m_bc, arg6);
		((void (__cdecl *)(Rva009A6130Context *, int))d_009a8c50)(
			context, (int)context->m_bc);
		((void (__cdecl *)(Rva009A6130Context *, int, int))d_009b2a50)(
			context, (int)context->m_bc, (int)context->m_bc);
		{
			unsigned int bytes = context->m_94 * context->m_98;
			bytes <<= 1;
			memcpy(context->m_14 + context->m_7c,
				context->m_bc + context->m_7c, bytes);
			memcpy(context->m_14 + context->m_80,
				context->m_bc + context->m_80, bytes);
			Rva009A6130CallbackA(
				context->m_bc + context->m_78,
				context->m_14 + context->m_78,
				context->m_90 << 3,
				context->m_94 << 3,
				context->m_98);
		}
		return;
	}
}
