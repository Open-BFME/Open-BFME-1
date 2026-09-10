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
