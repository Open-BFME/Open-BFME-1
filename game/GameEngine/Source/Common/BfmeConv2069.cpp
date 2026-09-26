// cl: /O2

#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP

extern char *g_bfme927Vft;

extern void *Rva006F6AB0_OpenW3DFile(char const *filename);

class BfmeThingGR
{
public:
	BfmeThingGR()
	{
		m_bfmeVftGR = &g_bfme927Vft;
		m_bfmeFlagGR = 0;
		m_bfmeA0GR = 0;
		m_bfmeA1GR = 0;
		m_bfmeA2GR = 0;
		m_bfmeA3GR = 0;
		m_bfmeA4GR = 0;
		m_bfmeA5GR = 0;
		m_bfmeA6GR = 0;
		m_bfmeB0GR = 1;
		m_bfmeB1GR = 1;
		m_bfmeB2GR = 1;
		m_bfmeB3GR = 1;
		m_bfmeOwnerGR = 0;
		m_bfmeC1GR = 0;
		m_bfmeC2GR = 0;
		m_bfmeD0GR = 2;
		m_bfmeD1GR = 0;
	}

	void bfmeApplyGR(int v);

	void *m_bfmeVftGR;
	char m_bfmeFlagGR;
	unsigned char m_bfmePadGR[3];
	int m_bfmeA0GR;
	int m_bfmeA1GR;
	int m_bfmeA2GR;
	int m_bfmeA3GR;
	int m_bfmeA4GR;
	int m_bfmeA5GR;
	int m_bfmeA6GR;
	int m_bfmeB0GR;
	int m_bfmeB1GR;
	int m_bfmeB2GR;
	int m_bfmeB3GR;
	int m_bfmeOwnerGR;
	int m_bfmeC1GR;
	int m_bfmeC2GR;
	int m_bfmeD0GR;
	int m_bfmeD1GR;
};

void BfmeThingGR::bfmeApplyGR(int v)
{
	char filename[260];
	strcpy(filename, (char const *)v);
	char *extension = strrchr(filename, '.');
	if (extension) {
		strcpy(extension, ".dds");
		m_bfmeA1GR = (int)Rva006F6AB0_OpenW3DFile(filename);
		if (!m_bfmeA1GR) {
			strcpy(extension, ".tga");
			m_bfmeA1GR = (int)Rva006F6AB0_OpenW3DFile(filename);
			if (!m_bfmeA1GR) {
				strcpy(extension, ".jpg");
				m_bfmeA1GR = (int)Rva006F6AB0_OpenW3DFile(filename);
				if (m_bfmeA1GR) {
					strcpy(extension, ".png");
					m_bfmeA4GR = (int)Rva006F6AB0_OpenW3DFile(filename);
				}
			}
		}
	}
	if (m_bfmeA1GR)
		*(unsigned char *)(m_bfmeA1GR + 0x0D) = 1;
	if (m_bfmeA4GR)
		*(unsigned char *)(m_bfmeA4GR + 0x0D) = 1;
}

class BfmeHostGR
{
public:
	void bfmeMakeGR();

	unsigned char m_bfmeHeadGR[0x14];
	BfmeThingGR *m_bfmeThingGR;
	int m_bfmeArgGR;
	unsigned char m_bfmeGap2GR[0x14];
	int m_bfme30GR;
	int m_bfme34GR;
	int m_bfme38GR;
};

void BfmeHostGR::bfmeMakeGR()
{
	BfmeThingGR *p = new BfmeThingGR();

	m_bfmeThingGR = p;
	p->m_bfmeOwnerGR = m_bfme30GR;
	m_bfmeThingGR->m_bfmeC2GR = m_bfme34GR;
	m_bfmeThingGR->m_bfmeC1GR = m_bfme38GR;
	m_bfmeThingGR->bfmeApplyGR(m_bfmeArgGR);
}
