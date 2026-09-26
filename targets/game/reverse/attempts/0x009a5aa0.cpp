// ?Rva009A5AA0InstallFilter@@YAXPAX00H@Z
// partial score=0.9 date=2026-09-10
// ?Rva009A5AA0InstallFilter@@YAXPAX00H@Z
// Retail RVA 0x009A5AA0, 193 bytes.  Rva009A4D00Init calls this helper
// directly with three table pointers and a codec tier selector.  The helper
// builds the signed-byte clamp table, copies the selected 64-entry table into
// the codec's working table, publishes the three table pointers, and selects
// the CPU dispatch tables for the requested tier.
//
// The byte-addressed copy is intentional: retail keeps the source/destination
// distance in bytes while stepping the destination by four bytes.
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern void __cdecl bfmeInstallCpuDispatchTable(void);

typedef void (__cdecl *Rva009A5AA0Dispatch)(int);
typedef int (__cdecl *Rva009A5AA0DispatchUnsigned)(unsigned);
typedef int (__cdecl *Rva009A5AA0DispatchLong)(long);

extern void *g_rva01356A98;
extern void (__cdecl *g_rva01356AA0)();
extern unsigned g_rva01356A88;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _WriteBarrier(void);
#pragma intrinsic(_WriteBarrier)



void __cdecl Rva009A5AA0InstallFilter(
	void *firstTable, void *secondTable, void *sourceTable, int tier)
{
	int index;
	for (index = -256; index < 512; ++index)
	{
		int value;
		if (index < 0)
			value = 0;
		else
		{
			value = index;
			if (value > 255)
				value = 255;
		}
		((unsigned char *)0x01356FE0)[index] = (unsigned char)value;
	}

	Rva009A5AA0Dispatch first = (Rva009A5AA0Dispatch)firstTable;
	Rva009A5AA0Dispatch second = (Rva009A5AA0Dispatch)secondTable;
	g_rva01356AA0 = (void (__cdecl *)())first;
	g_rva01356A98 = (void *)second;
	unsigned char *source = (unsigned char *)sourceTable;
	unsigned char *destination = (unsigned char *)0x01356940;
	g_rva01356A88 = (unsigned)source;
	int sourceValue = (int)source;
	sourceValue -= (int)destination;
	source = (unsigned char *)sourceValue;
	_ReadWriteBarrier();
	do
	{
		*(int *)destination = *(int *)(destination + (unsigned int)source);
		destination += 4;
	}
	while ((int)destination < 0x01356A40);

	unsigned channel = (unsigned)tier;
	Rva009A5AA0Dispatch dispatch =
		reinterpret_cast<Rva009A5AA0Dispatch>(bfmeInstallCpuDispatchTable);
	if (channel >= 6)
	{
		_WriteBarrier();
		*(int **)0x01356A7C = (int *)0x012D7E58;
		*(int **)0x01356A9C = (int *)0x012D7A58;
		dispatch(channel);
		return;
	}

	if (channel >= 5)
	{
		_WriteBarrier();
		*(int **)0x01356A7C = (int *)0x012D7D58;
		*(int **)0x01356A9C = (int *)0x012D7958;
		dispatch(channel);
		return;
	}

	_WriteBarrier();
	*(int **)0x01356A7C = (int *)0x012D7C58;
	*(int **)0x01356A9C = (int *)0x012D7858;
	dispatch(channel);
}
