#include "mss.h"
#include <string.h>

typedef void *HPROENUM;
#define HPROENUM_FIRST NULL
extern "C" __declspec(dllimport) S32 __stdcall AIL_enumerate_filters(
	HPROENUM *next, HPROVIDER *provider, char **name);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
class MilesAudioManager
{
private:
	unsigned char m_retailPrefix[0x968];
	HPROVIDER m_delayFilter;

	void initDelayFilter(void);
};

void MilesAudioManager::initDelayFilter(void)
{
	if (m_delayFilter != NULL) {
		return;
	}

	char *filterName;
	HPROENUM enumFLTs = HPROENUM_FIRST;
	HPROVIDER currentProvider;

	while (AIL_enumerate_filters(&enumFLTs, &currentProvider, &filterName)) {
		if (strcmp(filterName, "Mono Delay Filter") == 0) {
			m_delayFilter = currentProvider;
			break;
		}
	}
}
