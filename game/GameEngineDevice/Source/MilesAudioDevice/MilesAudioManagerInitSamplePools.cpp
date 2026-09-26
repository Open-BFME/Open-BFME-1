// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail's 0x006A3130 helper is the private initSamplePools member reached by
// MilesAudioManager::openDevice at 0x006B78D0.  The caller and the existing ILT
// entry at 0x0002CA8E establish the class identity. The full boundary ends
// at ret 0x006A31D6, before int3 padding at 0x006A31D7.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef void *HSAMPLE;
typedef void *HDIGDRIVER;

extern "C" __declspec(dllimport) HSAMPLE __stdcall AIL_allocate_sample_handle(
	HDIGDRIVER driver);
extern "C" __declspec(dllimport) void __stdcall AIL_init_sample(
	HSAMPLE sample);
extern "C" __declspec(dllimport) void __stdcall AIL_set_sample_user_data(
	HSAMPLE sample, int index, unsigned int value);

struct AudioSettings
{
	char m_pad00[0x28];
	int m_sampleCount2D;
	int m_sampleCount3D;
	int m_streamCount;
};

class MilesAudioManager
{
	private:
	void initSamplePools(void);

	private:
	void *m_vtable;
	char m_prefix[8];
	AudioSettings *m_audioSettings;
	char m_pad010[0x5f8];
	unsigned int m_num2DSamples;
	char m_pad60c[0xc];
	unsigned int m_numStreams;
	char m_pad61c[0x344];
	HDIGDRIVER m_digitalHandle;
	char m_pad964[0x5c];
	_STL::list<HSAMPLE> m_availableSamples;
};

void MilesAudioManager::initSamplePools(void)
{
	while (m_availableSamples.size() < (unsigned int)m_audioSettings->m_sampleCount2D)
	{
		register HSAMPLE sample = AIL_allocate_sample_handle(m_digitalHandle);
		if (!sample)
			break;
		AIL_init_sample(sample);
		AIL_set_sample_user_data(sample, 0,
			(unsigned int)m_availableSamples.size() + 1);
		m_availableSamples.push_back(sample);
		++m_num2DSamples;
	}

	m_numStreams = m_audioSettings->m_streamCount;
}
