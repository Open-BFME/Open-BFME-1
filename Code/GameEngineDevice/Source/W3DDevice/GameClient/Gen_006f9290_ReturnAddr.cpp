// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F9290. Return address of a global.

char g_get_006f9290;

// ?get_006f9290@@YAPADXZ
char *get_006f9290(void)
{
	return &g_get_006f9290;
}
