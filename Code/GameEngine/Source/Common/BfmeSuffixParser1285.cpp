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
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
