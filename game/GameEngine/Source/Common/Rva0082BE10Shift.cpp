// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef void (__stdcall *BfmeStdcallIntSlot)(int);

// C linkage so the slot spells as retail's `_Rva01358F30`; the value is the
// pointer the call reads, so only the symbol name changes.
extern "C" BfmeStdcallIntSlot Rva01358F30;

void rva0082BE10Shift(int n)
{
  if (n <= 0x14)
    Rva01358F30(1);
  else
    Rva01358F30(1 << (n - 0x14));
}
