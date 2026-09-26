// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BfmeAptScreenObjectives::bfmePlayerColor, retail 0x0052BA20, 85 bytes.
// The class and callback name are witnessed by AptScreenFactories.cpp: the
// Objectives vtable is installed at 0x01106DEC and the constructor binds the
// ScoreScreen:PlayerColor callback through ILT 0x0000D314.  The vector and
// screen-type members are the witnessed fields at +0x258 and +0x264.

#include <vector>

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ...);

extern char g_aptPalantirNumberFormat[];

class BfmeAptScreenObjectives
{
public:
	void bfmePlayerColor(const char *selector, void *value, bool setting);

private:
	unsigned char m_unmodelledPrefix[0x258];
	_STL::vector<int> m_players;
	int m_screenType;
};

// ?bfmePlayerColor@BfmeAptScreenObjectives@@QAEXPBDPAX_N@Z
void BfmeAptScreenObjectives::bfmePlayerColor(
	const char *selector, void *value, bool setting)
{
	*(unsigned short *)value = (unsigned short)'0';

	if (setting != 0)
		return;

	if (m_screenType == 1 &&
		!m_players.empty() &&
		(unsigned int)selector < m_players.size())
		sprintf((char *)value, g_aptPalantirNumberFormat,
			m_players[(unsigned int)selector]);
}
