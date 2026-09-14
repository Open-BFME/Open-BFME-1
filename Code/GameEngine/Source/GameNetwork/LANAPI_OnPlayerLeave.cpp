// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;
typedef bool Bool;

namespace _STL
{
template <class T> struct less {};
template <class T> class allocator {};
template <class First, class Second> struct pair {};

template <class Key, class Value, class Compare = less<Key>,
    class Allocator = allocator<pair<const Key, Value> > >
class map
{
public:
    Value &operator[](const Key &key);

private:
    void *m_header;
    UnsignedInt m_size;
    UnsignedInt m_allocator;
};
}

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class UnicodeString;

private:
    StringBase(void) : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase(void);

public:
	int compare(const StringBase<T> &other) const;

private:
    void set(const StringBase<T> &other);
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(void) : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString(void) {}

    void format(AsciiString format, ...);

    AsciiString &operator=(const AsciiString &other)
    {
        StringBase<char>::set(other);
        return *this;
    }
};

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString(void) : StringBase<WideChar>() {}
    UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
    ~UnicodeString(void) {}
};

namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const;
};
}

typedef _STL::map<AsciiString, AsciiString, _STL::less<AsciiString>,
    _STL::allocator<_STL::pair<const AsciiString, AsciiString> > >
    PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences(void);
	virtual Bool load(AsciiString filename);
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

class LANPreferences : public UserPreferences
{
public:
    LANPreferences(void);
    virtual ~LANPreferences(void);
};

class GameInfo
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual Int getLocalSlotNum(void) const = 0;
	AsciiString getMap(void) const;
};

struct Rva0068A900Slot
{
	Int getColor(void) const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x0c);
	}

	Int getPlayerTemplate(void) const
	{
		return *(const Int *)((const UnsignedByte *)this + 0x14);
	}
};

struct Rva0068D3E0Slot;

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);
};

class BfmeThing935B
{
public:
	char bfmeGo935B(void);
};

class Rva0068A900LANGameInfo : public GameInfo
{
public:
	Bool isInGame(void) const
	{
		return *(const Bool *)((const UnsignedByte *)this + 0x0c) != 0;
	}

	Bool isGameInProgress(void) const
	{
		return *(const Bool *)((const UnsignedByte *)this + 0x0d) != 0;
	}

	Rva0068A900Slot *getLANSlot(Int index)
	{
		return (Rva0068A900Slot *)
			((Rva0068D3E0Arr *)this)->at(index);
	}

	Bool amIHost(void)
	{
		return ((BfmeThing935B *)this)->bfmeGo935B() != 0;
	}
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class Gen_000970a0
{
public:
	int bfmeEquals(const Gen_000970a0 *other) const;
};

class Shell
{
public:
	void pop(void);
};

class BfmeObj935C;
extern BfmeObj935C *g_bfme935GlobC;

class BfmeQ1070
{
public:
	void bfmeGo1070A(void);
};

extern Shell *TheShell;
extern Bool LANbuttonPushed;
extern void bfmeGo935C(void);
extern AsciiString AsciiStringToQuotedPrintable(AsciiString original);

class Rva0068A900LANAPI
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot01(void) = 0;
	virtual void bfmeSlot02(void) = 0;
	virtual void bfmeSlot03(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot05(void) = 0;
	virtual void bfmeSlot06(void) = 0;
	virtual void bfmeSlot07(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot09(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot11(void) = 0;
	virtual void bfmeSlot12(void) = 0;
	virtual void bfmeSlot13(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot15(void) = 0;
	virtual void bfmeSlot16(void) = 0;
	virtual void bfmeSlot17(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot19(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void requestSerializedGameInfo(Bool unused,
		TransportAddress *destination) = 0;
	virtual void bfmeSlot22(void) = 0;
	virtual void bfmeSlot23(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot25(void) = 0;
	virtual void bfmeSlot26(void) = 0;
	virtual void bfmeSlot27(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual void bfmeSlot29(void) = 0;
	virtual void bfmeSlot30(void) = 0;
	virtual void bfmeSlot31(void) = 0;
	// ?OnPlayerLeave@LANAPI@@UAEXVUnicodeString@@@Z
	virtual void OnPlayerLeave(UnicodeString player);
	virtual void bfmeSlot33(void) = 0;
	virtual void bfmeSlot34(void) = 0;
	virtual void bfmeSlot35(void) = 0;
	virtual void bfmeSlot36(void) = 0;
	virtual void bfmeSlot37(void) = 0;
	virtual void bfmeSlot38(void) = 0;
	virtual void bfmeSlot39(void) = 0;
	virtual void bfmeSlot40(void) = 0;
	virtual void bfmeSlot41(void) = 0;
	virtual void bfmeSlot42(void) = 0;
	virtual void bfmeSlot43(void) = 0;
	virtual void bfmeSlot44(void) = 0;
	virtual void bfmeSlot45(void) = 0;
	virtual void bfmeSlot46(void) = 0;
	virtual void bfmeSlot47(void) = 0;
	virtual void bfmeSlot48(void) = 0;
	virtual void bfmeSlot49(void) = 0;
	virtual void bfmeSlot50(void) = 0;
	virtual void bfmeSlot51(void) = 0;
	virtual void bfmeSlot52(void) = 0;
	virtual void bfmeSlot53(void) = 0;
	virtual void bfmeSlot54(void) = 0;
	virtual struct BfmeNetAddress *getLocalAddress(void) = 0;

protected:
	UnsignedByte m_bfmeHeadA[0x08 - 0x04];
	void *m_lobbyPlayers;
	UnsignedByte m_bfmeHeadB[0x10 - 0x0c];
	UnicodeString m_name;
	AsciiString m_userName;
	AsciiString m_hostName;
	UnsignedInt m_gameStartTime;
	Int m_gameStartSeconds;
	Int m_pendingAction;
	UnsignedInt m_expiration;
	UnsignedInt m_actionTimeout;
	UnsignedByte m_directConnectRemoteAddress[8];
	UnsignedInt m_lastResendTime;
	Bool m_isInLANMenu;
	Bool m_inLobby;
	UnsignedByte m_bfmeHeadC[2];
	Rva0068A900LANGameInfo *m_currentGame;
};

// ?OnPlayerLeave@LANAPI@@UAEXVUnicodeString@@@Z
void Rva0068A900LANAPI::OnPlayerLeave(UnicodeString player)
{
	if (m_inLobby)
		return;

	Rva0068A900LANGameInfo *game = m_currentGame;
	if (!game || game->isGameInProgress())
		return;

	if (((const StringBase<unsigned short> *)&m_name)->compare(
		*(const StringBase<unsigned short> *)&player) == 0)
	{
		if (game->isInGame() && game->getLocalSlotNum() >= 0)
		{
			LANPreferences pref;
			AsciiString option;
			option.format("%d", m_currentGame->getLANSlot(
				m_currentGame->getLocalSlotNum())->getPlayerTemplate());
			pref["PlayerTemplate"] = option;
			option.format("%d", m_currentGame->getLANSlot(
				m_currentGame->getLocalSlotNum())->getColor());
			pref["Color"] = option;
			if (m_currentGame->amIHost())
				pref["Map"] = AsciiStringToQuotedPrintable(
					m_currentGame->getMap());
			pref.write();
		}

		if (g_bfme935GlobC == 0)
		{
			TheShell->pop();
			LANbuttonPushed = true;
		}
		else
		{
			reinterpret_cast<BfmeQ1070 *>(g_bfme935GlobC)->bfmeGo1070A();
		}
	}
	else
	{
		if (game)
		{
			Gen_000970a0 *gameAddress = (Gen_000970a0 *)
				((UnsignedByte *)game + 0x88);
			if ((UnsignedByte)gameAddress->bfmeEquals(
				(const Gen_000970a0 *)getLocalAddress()))
			{
				m_lastResendTime = 0;
				bfmeGo935C();
				TransportAddress noAddress;
				noAddress.m_ip = 0;
				noAddress.m_port = 0;
				requestSerializedGameInfo(true, &noAddress);
			}
		}
	}
}
