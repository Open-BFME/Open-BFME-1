// Release a held Apt value before restoring the global fallback.
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

// The 0x013377D8 slot retail loads here is the picker world pointer, whose one
// definition is game/GameEngine/Source/Common/BfmePicker1284.cpp's
// g_bfmeHolderBU (?g_bfmeHolderBU@@3PAUBfmePickWorld1284@@A).  The Apt slot at
// +0x1240 lives inside whatever that pointer points at, so the arithmetic is
// done on a byte view of it and the global is re-read each time, as retail's
// three separate `mov eax/ecx, [0x013377D8]` do.
struct BfmePickWorld1284;
extern BfmePickWorld1284 *g_bfmeHolderBU;

extern AptValue *g_bfmeFallbackDB;

void __cdecl bfmeResetGlobalSlot8C5780(void)
{
	AptValue *held = *(AptValue **)((char *)g_bfmeHolderBU + 0x1240);
	if (held)
	{
		held->Release();
		*(AptValue **)((char *)g_bfmeHolderBU + 0x1240) = g_bfmeFallbackDB;
		return;
	}
	*(AptValue **)((char *)g_bfmeHolderBU + 0x1240) = g_bfmeFallbackDB;
}