// cl: /DNDEBUG /MD /EHsc

// Retail 0x00730520. Return address of a global.

char g_get_00730520;

// ?get_00730520@@YAPADXZ
char *get_00730520(void)
{
	return &g_get_00730520;
}
