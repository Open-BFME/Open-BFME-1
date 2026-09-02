// cl: /O2 /Ob0

struct Rva002EB010Elem
{
	char m_body[20];
};

void rva002EB010Helper(Rva002EB010Elem *first, Rva002EB010Elem *last,
	int zero, void *extra);

void rva002EB010(Rva002EB010Elem *first, Rva002EB010Elem *last, void *extra)
{
	while (last - first > 1)
	{
		rva002EB010Helper(first, last, 0, extra);
		--last;
	}
}
