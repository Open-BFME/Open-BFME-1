// cl: /EHs-c-

// Retail 0x006F8700. Four-argument thiscall: if the last pointer is null,
// return 0; otherwise tail-jump to the 618-byte helper at 0x006F83F0.
// Same unused-this / pMesh-null prologue as Rva006F8720MeshBuffer::getModelIndices.

void d_006f83f0();

class Rva006F8700Owner
{
public:
	int rva006F8700(void *a, int b, void *c, void *p);
	int rva006F83F0(void *a, int b, void *c, void *p);
};

int Rva006F8700Owner::rva006F8700(void *a, int b, void *c, void *p)
{
	if (p == 0)
		return (0);
	union {
		void (*asFunction)(void);
		int (Rva006F8700Owner::*asMember)(void *, int, void *, void *);
	} target;
	target.asFunction = d_006f83f0;
	return (this->*target.asMember)(a, b, c, p);
}
