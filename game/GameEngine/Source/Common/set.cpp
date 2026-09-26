// cl: /O2 /Ob0

void set(int *p)
{
	*p = (~*p) & 0x7FF;
}
