// cl: /O2 /Ob0

float *Rva000C9160Min(float *a, float *b)
{
	if (*a < *b)
		return a;
	return b;
}
