extern "C" void *bfmeVft1030B[];
extern "C" char *g_bfmeFreeList1150[];
extern "C" int g_bfmeGuardXH;
extern "C" void __cdecl bfmeLockXH(void *guard);

void __cdecl operator delete(void *block);

class BfmeBufXH
{
public:
	void bfmeDtorXH();

	void *volatile m_bfmeVfptrXH;
	unsigned char m_bfmePadXH[8];
	char *volatile m_bfmeStartXH;
	char *m_bfmeMidXH;
	char *volatile m_bfmeEndXH;
};

void BfmeBufXH::bfmeDtorXH()
{
	m_bfmeVfptrXH = bfmeVft1030B;

	char *end = m_bfmeEndXH;
	char *start = m_bfmeStartXH;
	unsigned int used = end - start;

	if (start != 0)
	{
		if (used > 0x80)
		{
			operator delete(start);
		}
		else
		{
			char **list = g_bfmeFreeList1150 + ((used - 1) >> 3);

			bfmeLockXH(&g_bfmeGuardXH);
			*(char **)start = *list;
			*list = start;
			g_bfmeGuardXH = 0;
		}
	}
}
