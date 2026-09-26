// cl: /Od
// A run of bytes shifted to a new place, built without optimisation. The
// mover's answer is kept in a temporary nothing reads.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *to, const void *from, unsigned int many);

class BfmeThingON
{
public:
	void bfmeMoveON(char *first, char *last, char *to);
};

void BfmeThingON::bfmeMoveON(char *first, char *last, char *to)
{
	unsigned int many = (unsigned int)(last - first);

	(many == 0) ? (void *)to : memmove(to, first, many);
}
