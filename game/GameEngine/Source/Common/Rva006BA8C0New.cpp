// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?bfmeNewRva006C0570@@YAPAVRva006C0570@@XZ
// 86-byte `return new T`: allocate 0x24, construct via ??0Rva006C0570.

class Rva006C0570
{
public:
	Rva006C0570();

private:
	int m_bfmeFields[9];
};

Rva006C0570 *bfmeNewRva006C0570(void)
{
	return new Rva006C0570;
}
