// cl: /O2 /Ob0

int classifyRva005A6410Value(int value)
{
	switch (value)
	{
		case 4:
		case 5:
		case 6:
		case 8:
			return 0;

		case 14:
		case 15:
		case 16:
		case 18:
			return 2;

		default:
			return 3;
	}
}
