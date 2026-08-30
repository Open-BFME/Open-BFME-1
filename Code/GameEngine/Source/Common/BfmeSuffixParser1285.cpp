extern "C" int __cdecl isdigit(int value);
extern "C" int __cdecl atoi(const char *text);

struct BfmeStringData1285
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

struct BfmeString1285
{
	BfmeStringData1285 *m_data;
};

extern BfmeStringData1285 g_bfmeEmptyString1285;
extern float g_bfmeDirectionWeight1285;
extern float g_bfmeInvalidScore1285;

static __forceinline int bfmeAbs1285(int value)
{
	return value < 0 ? -value : value;
}

static __declspec(noinline) float bfmeDirectionalScore1285(
	int direction, int referenceFirst, int referenceSecond,
	int candidateFirst, int candidateSecond)
{
	int dy;
	int dx = candidateSecond - referenceSecond;
	dy = candidateFirst - referenceFirst;
	switch (direction) {
	case 14:
		if (dx >= 0)
			return g_bfmeInvalidScore1285;
		{
			int primary = bfmeAbs1285(dx);
			int perpendicular = bfmeAbs1285(dy);
			return (float)perpendicular * g_bfmeDirectionWeight1285 + primary;
		}
	case 15:
		if (dx <= 0)
			return g_bfmeInvalidScore1285;
		return (float)bfmeAbs1285(dy) * g_bfmeDirectionWeight1285 + dx;
	case 1:
		if (dy >= 0)
			return g_bfmeInvalidScore1285;
		{
			int primary = bfmeAbs1285(dy);
			int perpendicular = bfmeAbs1285(dx);
			return (float)perpendicular * g_bfmeDirectionWeight1285 + primary;
		}
	case 2:
		if (dy <= 0)
			return g_bfmeInvalidScore1285;
		return (float)bfmeAbs1285(dx) * g_bfmeDirectionWeight1285 + dy;
	}
	return g_bfmeInvalidScore1285;
}

static __declspec(noinline) bool bfmeParseSuffix1285(
	BfmeString1285 *value, int *first, int *second)
{
	BfmeStringData1285 *data = value->m_data;
	if (data == &g_bfmeEmptyString1285)
		return false;

	char *cursor = &data->m_text[data->m_length - 1];
	if (!isdigit(*cursor))
		return false;
	while (isdigit(*cursor)) {
		--cursor;
	}
	if (second != 0)
		*second = atoi(cursor + 1);
	if (*cursor-- != '_')
		return false;
	if (!isdigit(*cursor))
		return false;
	while (isdigit(*cursor)) {
		--cursor;
	}
	if (first != 0)
		*first = atoi(cursor + 1);
	return true;
}

// ?bfmeUseSuffix1285@@YAHPAUBfmeString1285@@@Z absent-from-retail
int bfmeUseSuffix1285(BfmeString1285 *value)
{
	int first;
	int second;
	if (!bfmeParseSuffix1285(value, &first, &second))
		return 0;
	return first + second;
}

// ?bfmeUseDirectionalScore1285@@YAMHHHHH@Z absent-from-retail
float bfmeUseDirectionalScore1285(
	int direction, int referenceFirst, int referenceSecond,
	int candidateFirst, int candidateSecond)
{
	return bfmeDirectionalScore1285(
		direction, referenceFirst, referenceSecond, candidateFirst, candidateSecond);
}
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
