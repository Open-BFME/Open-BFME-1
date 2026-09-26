void __cdecl bfmeSortZV(int *first, int *last, int *hint, char (__cdecl *comp)(int, int))
{
	if (first == last)
		return;

	for (int *p = first; p != last; p++)
	{
		int value = *p;
		int *hole = p;
		int *prev = p - 1;

		if (comp(value, *prev) != 0)
		{
			do
			{
				*hole = *prev;
				hole = prev;
				prev--;
			}
			while (comp(value, *prev) != 0);
		}

		*hole = value;
	}
}
