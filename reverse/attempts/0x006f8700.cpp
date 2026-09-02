// ?rva006F8700@@YGXHHHPAX@Z
// partial score=0.8 date=2026-09-02
// cl: /EHs-c-
//
// Four-argument stdcall forwarder: if the fourth argument is null, ret 16;
// otherwise overwrite that slot with itself and tail-jump into the already-
// claimed 618-byte helper at 0x006F83F0.

void __stdcall d_006f83f0_body(int a, int b, int c, void *p);

void __stdcall rva006F8700(int a, int b, int c, void *p)
{
	void *t = p;
	if (t == 0)
		return;
	d_006f83f0_body(a, b, c, t);
}
