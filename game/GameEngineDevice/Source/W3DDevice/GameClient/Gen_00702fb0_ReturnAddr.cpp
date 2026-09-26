// cl: /DNDEBUG /MD /EHsc

// Retail 0x00702FB0. Return address of a global.

char g_get_00702fb0;

// ?get_00702fb0@@YAPADXZ
char *get_00702fb0(void)
{
	return &g_get_00702fb0;
}
