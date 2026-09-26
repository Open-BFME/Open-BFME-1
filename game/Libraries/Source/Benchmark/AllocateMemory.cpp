// cl: /O2 /GR- /EHsc-

typedef unsigned long ulong;

extern "C" __declspec(dllimport) void *__cdecl malloc(unsigned int);

extern ulong mem_array[2][20];
extern int mem_array_ents;
extern int global_align;

static int AddMemArray(ulong true_addr, ulong adj_addr)
{
	if (mem_array_ents >= 20)
		return -1;

	mem_array[0][mem_array_ents] = true_addr;
	mem_array[1][mem_array_ents] = adj_addr;
	mem_array_ents++;
	return 0;
}

void *AllocateMemory(unsigned long nbytes, int *errorcode)
{
	void *returnval;
	ulong true_addr;
	ulong adj_addr;

	returnval = malloc((unsigned int)(nbytes + 2L * (long)global_align));
	if (returnval == (void *)0)
		*errorcode = 1;
	else
		*errorcode = 0;

	adj_addr = true_addr = (ulong)returnval;
	if (global_align == 0)
	{
		if (AddMemArray(true_addr, adj_addr))
			*errorcode = 2;
		return returnval;
	}

	if (global_align == 1)
	{
		if (true_addr % 2 == 0)
			adj_addr++;
	}
	else
	{
		while (adj_addr % global_align != 0)
			++adj_addr;
		if (adj_addr % (global_align * 2) == 0)
			adj_addr += global_align;
	}
	returnval = (void *)adj_addr;
	if (AddMemArray(true_addr, adj_addr))
		*errorcode = 2;
	return returnval;
}
