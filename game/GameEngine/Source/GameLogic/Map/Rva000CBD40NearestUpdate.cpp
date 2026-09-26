// ?rva000cbd40@@YAHPAX0@Z

int __cdecl rva000cbd40(void *nodeArg, void *bestArg)
{
	if (!bestArg)
		return 1;

	char *node = (char *)nodeArg;
	char *best = (char *)bestArg;

	float dx = *(float *)(node + 0x38) - *(float *)(best + 0);
	float dy = *(float *)(node + 0x3c) - *(float *)(best + 4);
	float distSq = dx * dx + dy * dy;

	if (distSq < *(float *)(best + 0x10))
	{
		if (*(int *)(node + 0x370) >= 0)
		{
			*(float *)(best + 0x10) = distSq;
			*(void **)(best + 0xc) = node;
		}
	}

	return 1;
}
