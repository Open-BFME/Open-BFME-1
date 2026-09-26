// cl: /O2 /Ob0

extern void Rva009C8730SetFlag();

int Rva00060990SetFlagAndReturn()
{
	Rva009C8730SetFlag();
	return 1;
}
