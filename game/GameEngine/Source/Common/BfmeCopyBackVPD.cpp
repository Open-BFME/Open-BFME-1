// cl: /DNDEBUG /MD /EHsc

extern void (*TheBfmeFree)(void *p, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);

	void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}

	int m_bfmeRefCount;
	char m_bfmePad04[0x14];
};

BfmeDropObjectA **bfmeCopyBackVPD(BfmeDropObjectA **first,
	BfmeDropObjectA **last, BfmeDropObjectA **result)
{
	BfmeDropObjectA **destination = result;
	int count = last - first;
	--last;
	BfmeDropObjectA **destinationEnd = destination + count - 1;

	if (count)
	{
		int remaining = count;

		do
		{
			if (last != destinationEnd)
			{
				if (*destinationEnd != 0)
				{
					BfmeDropObjectA *release = *destinationEnd;
					if (--release->m_bfmeRefCount == 0)
					{
						release = *destinationEnd;
						if (release != 0)
							delete release;
					}
				}

				*destinationEnd = *last;
				if (*destinationEnd != 0)
					++(*destinationEnd)->m_bfmeRefCount;
			}
			--last;
			--destinationEnd;
		}
		while (--remaining);
	}

	return destinationEnd;
}
