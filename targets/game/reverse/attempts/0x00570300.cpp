// ?provideBattleStat@BfmeAptScreenScoreScreen@@QAEXHPAD_N@Z
// partial score=0.86 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

extern "C" int __declspec(dllimport) __cdecl sprintf(
	char *buffer, const char *format, ... );

class BfmeAptScreenScoreScreen
{
public:
	void provideBattleStat( int index, char *text, bool setting );
};

void BfmeAptScreenScoreScreen::provideBattleStat(
	int index, char *text, bool setting )
{
	if (setting)
		return;

	char *output = text;
	int columns = 3;
	int group = index / columns;
	int column = index % columns;
	*(short *)output = '0';
	if (group < 0)
		return;
	if (group >= 7)
		return;
	if (column < 0)
		return;
	if (column >= columns)
		return;

	if (column == 1) {
		int value = *(int *)((char *)this + 0x298 + group * 12);
		sprintf(output, "x %d", value);
		return;
	}

	int tableIndex = group + 0x37 + column * 2;
	sprintf(output, "%d", ((int *)this)[tableIndex]);
}
