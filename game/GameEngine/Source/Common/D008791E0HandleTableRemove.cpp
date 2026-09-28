// ?Rva008791E0Remove@@YAHPAXPAPAX@Z
struct Rva008791E0Table
{
	void *m_vals[20];
	void *m_keys[20];
	int m_count;
};

extern Rva008791E0Table Rva008791E0Handles;

int __cdecl Rva008791E0Remove(void *key, void **out)
{
	int i;

	for (i = 0; i < Rva008791E0Handles.m_count; i++)
	{
		if (Rva008791E0Handles.m_keys[i] == key)
		{
			*out = Rva008791E0Handles.m_vals[i];

			void **p = &Rva008791E0Handles.m_vals[i];
			int count = Rva008791E0Handles.m_count;

			i++;
			if (i < count)
			{
				do
				{
					p[0] = p[1];
					p[20] = p[21];
					p++;
					i++;
				} while (i < count);
			}

			Rva008791E0Handles.m_count = count - 1;
			return 0;
		}
	}

	return -1;
}

// 0x008791B0: append the pair while fewer than 20 entries are live, else -1.
// ?Rva008791B0Add@@YAHPAX0@Z
int __cdecl Rva008791B0Add(void *a, void *b)
{
	int i = Rva008791E0Handles.m_count;
	if (i >= 20)
		return -1;
	Rva008791E0Handles.m_vals[i] = a;
	Rva008791E0Handles.m_keys[i] = b;
	Rva008791E0Handles.m_count = i + 1;
	return 0;
}
