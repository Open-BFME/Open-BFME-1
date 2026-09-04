// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x004EBA70 chooses the notification implementation from the game
// logic mode.  It is called by the BFME notification wrapper and by the
// buddy-response paths with the two string arguments passed by value.

template <class T>
class StringBase
{
public:
	StringBase(const StringBase<T> &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	void *m_data;
};

class UnicodeString
{
public:
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}
	~UnicodeString();

private:
	void *m_data;
};

class GameLogicRva004EBA70
{
private:
	int m_padding[0x10c / sizeof(int)];

public:
	int m_gameType;
};

#define TheGameLogic004EBA70 (*(GameLogicRva004EBA70 **)0x012F0898)

void bfme_notificationModeFive(AsciiString, UnicodeString);
void bfme_notificationOtherMode(AsciiString, UnicodeString);

void Rva004EBA70NotificationDispatch(AsciiString nick, UnicodeString message)
{
	int gameType = TheGameLogic004EBA70->m_gameType;
	if (gameType != 5)
		bfme_notificationModeFive(nick, message);
	else
		bfme_notificationOtherMode(nick, message);
}
