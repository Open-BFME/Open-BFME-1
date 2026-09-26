// cl: /Od
// A run of bytes copied to a new place, built without optimisation with the
// copier spelled out in place. The copier's answer is kept in a temporary
// nothing reads.

extern "C" void *__cdecl memcpy(void *to, const void *from, unsigned int many);
#pragma intrinsic(memcpy)

class BfmeThingQK
{
public:
	void bfmeMoveQK(char *first, char *last, char *to);
};

void BfmeThingQK::bfmeMoveQK(char *first, char *last, char *to)
{
	unsigned int many = (unsigned int)(last - first);

	(many == 0) ? (void *)to : memcpy(to, first, many);
}
