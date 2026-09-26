// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef void (__stdcall *BfmeStdcallIntSlot)(int);

extern BfmeStdcallIntSlot Data00F58F30;

void rva0082BE10Shift(int n)
{
  if (n <= 0x14)
    Data00F58F30(1);
  else
    Data00F58F30(1 << (n - 0x14));
}
