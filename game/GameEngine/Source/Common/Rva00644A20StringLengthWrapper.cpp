// cl: /O2
// stlport
// Retail 0x00644A20 computes a null-terminated length before forwarding the
// same object and two arguments to BfmeThingPE::bfmeDoPE.

#include <string.h>

class BfmeThingPE
{
public:
	unsigned int bfmeDoPE(const char *at, unsigned int what, unsigned int many);
};

class Rva00644A20Owner : public BfmeThingPE
{
public:
	void forwardString(char *at, void *what);
};

// ?d_00644a20@@YAXXZ
void Rva00644A20Owner::forwardString(char *at, void *what)
{
	bfmeDoPE(at, (unsigned int)what, strlen(at));
}
