// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD

#include <stdio.h>

class Rva00849C30Owner
{
public:
	int getc00849C30(void);

private:
	char m_pad[0x54];
	FILE *m_file;
};

// ?getc00849C30@Rva00849C30Owner@@QAEHXZ
int Rva00849C30Owner::getc00849C30(void)
{
	int ch = getc(m_file);
	if (ch == -1)
		return -1;
	return ch;
}
