// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva00897260Node
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual int count();
	virtual Rva00897260Node *item(int index);

	unsigned m_flags;
};

void __cdecl bfmeCleanup97260(Rva00897260Node *node);

void __cdecl bfmeCleanup97260(Rva00897260Node *node)
{
	node->m_flags |= 0x4000;
	int count = node->count();
	for (int index = 0; index < count; ++index)
	{
		Rva00897260Node *child = node->item(index);
		if (child)
		{
			unsigned char type = (unsigned char)(child->m_flags >> 14);
			if ((type & 1) == 0)
			bfmeCleanup97260(child);
		}
	}
}

class Rva008972B0Source
{
public:
	void *m_data;
	int (__cdecl *getCount)(void *data);
	Rva00897260Node *(__cdecl *getItem)(void *data, int index);
};

void __cdecl bfmeWalk972B0(Rva008972B0Source *source)
{
	void *data = source->m_data;
	int count = source->getCount(data);
	for (int index = 0; index < count; ++index)
	{
		Rva00897260Node *node = source->getItem(data, index);
		if (node)
		{
			unsigned char type = (unsigned char)(node->m_flags >> 14);
			if ((type & 1) == 0)
				bfmeCleanup97260(node);
		}
	}
}
