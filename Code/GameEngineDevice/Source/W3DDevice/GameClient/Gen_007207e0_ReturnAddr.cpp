// cl: /DNDEBUG /MD /EHsc

// Retail 0x007207E0. Return address of a global.

char g_007207e0;

// ?get@Gen_007207e0@@YAPADXZ
char *get_007207e0(void)
{
	return &g_007207e0;
}
