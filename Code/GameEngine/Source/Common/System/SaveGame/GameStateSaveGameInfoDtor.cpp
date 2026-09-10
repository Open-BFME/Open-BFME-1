// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// SaveGameInfo's BFME layout is six reference-counted strings around a
// 16-byte SaveDate/mission-number region.  The direct SaveGameInfo destructor
// route at ILT 0x0000AB78 and named callers from GameState::~GameState and
// addGameToAvailableList establish that this is the owner of 0x0010D700,
// formerly mislabelled BfmeOwnVUN.

template <typename T> struct BfmeStringData
{
	int refs;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	BfmeStringData<T> *m_data;

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<unsigned short>(other) {}
	~UnicodeString() {}
};

struct SaveDate
{
	unsigned short day;
	unsigned short dayOfWeek;
	unsigned short hour;
	unsigned short milliseconds;
	unsigned short minute;
	unsigned short month;
	unsigned short second;
	unsigned short year;
};

class SaveGameInfo
{
public:
	~SaveGameInfo();

	AsciiString saveGameMapName;
	AsciiString pristineMapName;
	AsciiString mapLabel;
	SaveDate date;
	AsciiString campaignSide;
	int missionNumber;
	UnicodeString description;
	int saveFileType;
	AsciiString missionMapName;
};

// ??1SaveGameInfo@@QAE@XZ
SaveGameInfo::~SaveGameInfo()
{
}
