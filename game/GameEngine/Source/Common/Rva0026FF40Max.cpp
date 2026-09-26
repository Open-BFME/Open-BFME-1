// cl: /O2 /Ob0

float *Rva0026FF40Max(float *a, float *b)
{
	if (*a < *b)
		return b;
	return a;
}
