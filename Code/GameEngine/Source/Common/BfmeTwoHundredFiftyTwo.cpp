// cl: /Od
// The byte at a place taken out by pulling everything after it down one, built
// without optimisation. The mover's answer is kept in a temporary nothing
// reads.

extern "C" __declspec(dllimport) void *__cdecl memmove(void *to, const void *from, unsigned int many);

class BfmeThingOO
{
public:
	char *bfmeEraseOO(char *at);

private:
	unsigned char m_bfmeHead[4];		// 0x0
	char *m_bfmeEnd;			// 0x4
};

char *BfmeThingOO::bfmeEraseOO(char *at)
{
	unsigned int many = (unsigned int)(m_bfmeEnd - at);

	(many == 0) ? (void *)at : memmove(at, at + 1, many);

	m_bfmeEnd = m_bfmeEnd - 1;

	return at;
}
