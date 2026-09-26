extern "C" void *bfmeVftYX[];
extern "C" void __stdcall bfmeFreeAYX(void *p);
extern "C" void __stdcall bfmeFreeBYX(void *p);

void __cdecl operator delete[](void *block);

class BfmeOwnerYX
{
public:
	void bfmeCleanupYX();

	void bfmeShutdownYX();

	void **m_bfmeVfptrYX;
	unsigned char m_bfmePadYX[8];
	unsigned char *m_bfmeArrayYX;
	unsigned char m_bfmeMidYX[8];
	void *m_bfmeBYX;
	void *m_bfmeAYX;
};

void BfmeOwnerYX::bfmeCleanupYX()
{
	m_bfmeVfptrYX = bfmeVftYX;

	bfmeShutdownYX();

	if (m_bfmeAYX != 0)
		bfmeFreeAYX(m_bfmeAYX);

	if (m_bfmeBYX != 0)
		bfmeFreeBYX(m_bfmeBYX);

	if (m_bfmeArrayYX != 0)
		delete [] m_bfmeArrayYX;
}
