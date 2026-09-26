// cl: /O2 /Ob0

bool __stdcall rva00694b60(const int *a, const int *b)
{
	if (a && b)
		return a[2] == b[2];
	return a == b;
}
