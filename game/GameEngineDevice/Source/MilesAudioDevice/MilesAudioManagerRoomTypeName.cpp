// cl: /O2 /GR- /EHsc-
// MilesAudioManager room-type name accessor at retail 0x0069D240.
//
// The body reads the selected 3D provider handle and asks Miles for the EAX
// room type in force, then turns that number into its display name.  The
// method name is not recoverable, so it keeps its retail address; the class
// is MilesAudioManager, proved by the layout the byte-exact
// ?createListener@MilesAudioManager@@QAEXXZ at 0x0069B1D0 reads: the same
// selected-provider index at this+0x958 and the same provider id at
// this+0x658+12*index.

extern "C" __declspec(dllimport) int __stdcall AIL_3D_room_type(
	unsigned int provider);

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &other);
	~BFMERetailAsciiString();

	void *m_data;
};

// The 26 EAX room types and their display names, at VA 0x0111BAC8.  The
// ledger pins the table under the address of the other body that reads it.
struct Rva006A16B0Entry
{
	const char *m_name;
	int m_roomType;
};

extern Rva006A16B0Entry Rva006A16B0Table[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
struct ProviderInfo
{
	void *name;
	unsigned int id;
	int isValid;
};

enum { MAXPROVIDERS = 64 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h
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

	BFMERetailAsciiString rva0069D240RoomTypeName(void) const;

private:
	char m_pad[0x650];
	ProviderInfo m_provider3D[MAXPROVIDERS];
	unsigned int m_providerCount;
	unsigned int m_selectedProvider;
	unsigned int m_lastProvider;
	unsigned int m_selectedSpeakerType;
	void *m_listener;
};

static const char *roomTypeName(int roomType)
{
	for (unsigned int i = 0; i < 26; ++i)
		if (roomType == Rva006A16B0Table[i].m_roomType)
			return Rva006A16B0Table[i].m_name;

	return "<Unknown>";
}

// ?rva0069D240RoomTypeName@MilesAudioManager@@QBE?AVBFMERetailAsciiString@@XZ
BFMERetailAsciiString MilesAudioManager::rva0069D240RoomTypeName(void) const
{
	return BFMERetailAsciiString(roomTypeName(AIL_3D_room_type(m_provider3D[m_selectedProvider].id)));
}
