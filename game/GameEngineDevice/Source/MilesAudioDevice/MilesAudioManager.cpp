// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <string.h>

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef __int64 Time64;
typedef void *HDIGDRIVER;
typedef void *HMDIDRIVER;
typedef int HTIMER;
typedef void *HPROENUM;
typedef void *HPROVIDER;

#define HPROENUM_FIRST NULL

extern "C" __declspec(dllimport) Time64 __cdecl _time64(Time64 *time);
extern "C" __declspec(dllimport) void __stdcall AIL_set_redist_directory(const char *directory);
extern "C" __declspec(dllimport) void __stdcall AIL_startup(void);
extern "C" __declspec(dllimport) int __stdcall AIL_quick_startup(
	int useDigital, int useMidi, int outputRate, int outputBits, int outputChannels);
extern "C" __declspec(dllimport) int __stdcall AIL_quick_handles(
	HDIGDRIVER *digital, HMDIDRIVER *midi, void *provider);
extern "C" __declspec(dllimport) HTIMER __stdcall AIL_register_timer(void (__cdecl *callback)(void));
extern "C" __declspec(dllimport) void __stdcall AIL_set_timer_period(HTIMER timer, int period);
extern "C" __declspec(dllimport) void __stdcall AIL_start_timer(HTIMER timer);
extern "C" __declspec(dllimport) int __stdcall AIL_enumerate_filters(
	HPROENUM *next, HPROVIDER *provider, char **name);

struct GlobalData
{
	unsigned char m_prefix[0xa6c];
	Bool m_audioOn;
};

extern GlobalData *TheWritableGlobalData;

struct AudioSettings
{
	unsigned char m_prefix[0x18];
	Bool m_useDigital;
	Bool m_useMidi;
	unsigned char m_gap1[2];
	int m_outputRate;
	int m_outputBits;
	int m_outputChannels;
	unsigned char m_gap2[0x28];
	UnsignedInt m_timerNumerator;
	UnsignedInt m_timerDenominator;
};

class OptionPreferences
{
public:
	OptionPreferences(void);
	virtual ~OptionPreferences();
	Bool getUseEAX3(void);

private:
	unsigned char m_body[0x10];
};

class MilesAudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45();
	virtual Bool isOn(int which) const;
	virtual void setOn(Bool turnOn, int which);
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void refreshCachedVariables(void);

	void openDevice(void);

private:
	void buildProviderList(void);
	void setHardwareAccelerated(Bool accelerated);
	void initSamplePools(void);
	void initDelayFilter(void);

	unsigned char m_prefix[8];
	AudioSettings *m_audioSettings;
	unsigned char m_gap[0x644];
	unsigned char m_providerData[0x30c];
	HDIGDRIVER m_digitalHandle;
	void *m_listener;
	HPROVIDER m_delayFilter;
};

#pragma comment(linker, "/alternatename:?buildProviderList@MilesAudioManager@@AAEXXZ=?j_0003972f@@YAXXZ")
#pragma comment(linker, "/alternatename:?setHardwareAccelerated@MilesAudioManager@@AAEXE@Z=?j_0001f046@@YAXXZ")
#pragma comment(linker, "/alternatename:?initSamplePools@MilesAudioManager@@AAEXXZ=?j_0002ca8e@@YAXXZ")

extern void j_00010221(void);
extern int bfmeGo937A(void);

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual void v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);

void MilesAudioManager::openDevice(void)
{
	register int retval = 0;
	*reinterpret_cast<Time64 *>(reinterpret_cast<unsigned char *>(this) + 0xb68) = _time64(0);

	if (!TheWritableGlobalData->m_audioOn)
		return;

	AIL_set_redist_directory("MSS\\");
	bfmeGo937A();
	AIL_startup();
	retval = AIL_quick_startup(m_audioSettings->m_useDigital, m_audioSettings->m_useMidi,
		m_audioSettings->m_outputRate, m_audioSettings->m_outputBits, m_audioSettings->m_outputChannels);

	AIL_quick_handles(&m_digitalHandle, 0, 0);
	if (retval)
		buildProviderList();
	else
		setOn(0, 0x1f);

	OptionPreferences prefs;
	setHardwareAccelerated(prefs.getUseEAX3());
	initSamplePools();
	refreshCachedVariables();

	HTIMER timer = AIL_register_timer(j_00010221);
	*reinterpret_cast<HTIMER *>(reinterpret_cast<unsigned char *>(this) + 0xb4c) = timer;
	if (timer == (HTIMER)-1) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)->v38(
				"3D Loop Callback system could not initialize. 3D Looping sounds will not work.")->v4c(2);
		}
	}
	if (timer != (HTIMER)-1) {
		int period = m_audioSettings->m_timerNumerator / m_audioSettings->m_timerDenominator;
		if (period < 1)
			period = 1;
		period *= 1000;
		AIL_set_timer_period(timer, period);

		if (*reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0xb50) > 0)
			AIL_start_timer(*reinterpret_cast<HTIMER *>(reinterpret_cast<unsigned char *>(this) + 0xb4c));
	}

	if (*reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 0x958) <
		*reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 0x954))
		initDelayFilter();
}

void MilesAudioManager::initDelayFilter(void)
{
	if (m_delayFilter != NULL)
		return;

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
