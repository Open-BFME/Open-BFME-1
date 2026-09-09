// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x001E4160 walks a circular handler list at this+0x538. The two
// callers identify the operation as the common handler test used by
// BfmeThingACF::checkAndRun and BfmeC1009::bfmeGo1009C.

class Rva001E4160Handler
{
public:
	virtual void slot0(void) = 0;
	virtual bool accepts(void *second, void *first) = 0;
};

struct Rva001E4160Node
{
	Rva001E4160Node *next;
	unsigned char unused04[4];
	Rva001E4160Handler *handler;
};

class Rva001E4160List
{
public:
	bool any(void *first, void *second);

private:
	unsigned char unused00[0x538];
	Rva001E4160Node *sentinel;
};

bool Rva001E4160List::any(void *first, void *second)
{
	if (!first)
		return false;

	void *secondArgument = second;
	Rva001E4160Node *node = sentinel->next;
	if (node != sentinel)
	{
		do
		{
			if (node->handler->accepts(secondArgument, first))
				return true;
			node = node->next;
		}
		while (node != sentinel);
	}

	return false;
}
