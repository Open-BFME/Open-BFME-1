// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// MilesAudioManager::createListener, ported from
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp

extern "C" __declspec(dllimport) void *__stdcall AIL_open_3D_listener(
	unsigned int provider);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
struct ProviderInfo
{
	void *name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
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
	virtual bool isOn(int which) const;

	void createListener();

private:
	char m_pad[0x650];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	unsigned int m_lastProvider;
	unsigned int m_selectedSpeakerType;
	void *m_listener;
};

// ?createListener@MilesAudioManager@@AAEXXZ
void MilesAudioManager::createListener()
{
	if (!(isOn(4) && m_selectedProvider < m_providerCount))
		return;

	m_listener = AIL_open_3D_listener(m_provider3D[m_selectedProvider].id);
}
