// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct Rva00350500Node
{
	Rva00350500Node *next;
};

static __declspec(noinline) Rva00350500Node *rva00350500(
	Rva00350500Node *node)
{
	if (node)
	{
		Rva00350500Node *next = node->next;
		if (next)
		{
			do
			{
				node = next;
				next = next->next;
			} while (next);
		}
	}
	return node;
}

// absent-from-retail: TU-local caller preserves the observed private EAX input ABI.
Rva00350500Node *rva00350500Caller(Rva00350500Node *node)
{
	return rva00350500(node);
}
