// cl: /DNDEBUG /MD /EHsc
// 0x00895430 is called twice by the 0x008961E0 vector-insertion body.  Each
// call supplies a source range and destination of four-byte pointers.  The
// release call at 0x00895260 and the 24-byte sized free establish that those
// pointers own BfmeDropObjectA instances.

extern void (*TheBfmeFree)(void *value, unsigned int bytes);

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA();

	void operator delete(void *value, unsigned int bytes)
	{
		TheBfmeFree(value, bytes);
	}

	int m_refCount;
	char m_rest[0x14];
};

BfmeDropObjectA **Rva00895430Copy(BfmeDropObjectA **first,
	BfmeDropObjectA **last, BfmeDropObjectA **result)
{
	if (first != last)
	{
		do
		{
			BfmeDropObjectA **destination = result++;
			if (first != destination)
			{
				if (*destination != 0)
				{
					BfmeDropObjectA *release = *destination;
					if (--release->m_refCount == 0)
					{
						release = *destination;
						if (release != 0)
							delete release;
					}
				}

				*destination = *first;
				if (*destination != 0)
					++(*destination)->m_refCount;
			}
			++first;
		}
		while (first != last);
	}

	return result;
}
