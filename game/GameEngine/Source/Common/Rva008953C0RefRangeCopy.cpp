// cl: /DNDEBUG /MD /EHsc
// The 0x00895F30 body calls 0x008953C0 three times while rotating two
// four-byte pointer ranges through temporary storage.  Its release target at
// 0x00895260 and 24-byte sized free establish BfmeDropObjectA ownership.

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

BfmeDropObjectA **Rva008953C0Copy(BfmeDropObjectA **first,
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
