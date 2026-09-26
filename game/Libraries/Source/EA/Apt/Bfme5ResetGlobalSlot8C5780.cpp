// Release a held Apt value before restoring the global fallback.
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

extern char *Rva008A5380Holder;
extern AptValue *g_bfmeFallbackDB;

void __cdecl bfmeResetGlobalSlot8C5780(void)
{
	AptValue *held = *(AptValue **)(Rva008A5380Holder + 0x1240);
	if (held)
	{
		held->Release();
		*(AptValue **)(Rva008A5380Holder + 0x1240) = g_bfmeFallbackDB;
		return;
	}
	*(AptValue **)(Rva008A5380Holder + 0x1240) = g_bfmeFallbackDB;
}
