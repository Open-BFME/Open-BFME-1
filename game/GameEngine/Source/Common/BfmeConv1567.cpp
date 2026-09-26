// Open-BFME5 conversions.

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

extern "C" unsigned int __cdecl strlen(const char *text);
extern "C" char *__cdecl strcpy(char *dest, const char *text);

class BfmeStrVSB
{
public:
	BfmeStrVSB &bfmeAssignVSB(const BfmeStrVSB &src);
	char *m_bfme00;
	int m_bfme04;
};

BfmeStrVSB &BfmeStrVSB::bfmeAssignVSB(const BfmeStrVSB &src)
{
	if (this != &src)
	{
		delete [] m_bfme00;

		if (src.m_bfme00 != 0)
		{
			m_bfme00 = new char[strlen(src.m_bfme00) + 1];
			strcpy(m_bfme00, src.m_bfme00);
		}
		else
			m_bfme00 = 0;

		m_bfme04 = src.m_bfme04;
	}

	return *this;
}
