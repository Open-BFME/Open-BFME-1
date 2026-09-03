// cl: /DNDEBUG /MD /EHsc
// Retail 0x005171A0: if the 0x012F7730 singleton is live, copy the UnicodeString
// it returns from vslot +0xBC into the by-ref out argument.

template <typename T> class StringBase
{
	friend class UnicodeString;

public:
	void set(const StringBase<T> &other);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	void set(const UnicodeString &other)
	{
		StringBase<unsigned short>::set(other);
	}
};

class LanLobbyNameGuard
{
public:
#define LANLOBBY_NAME_SLOT(N) virtual void slot##N();
	LANLOBBY_NAME_SLOT(0)  LANLOBBY_NAME_SLOT(1)  LANLOBBY_NAME_SLOT(2)
	LANLOBBY_NAME_SLOT(3)  LANLOBBY_NAME_SLOT(4)  LANLOBBY_NAME_SLOT(5)
	LANLOBBY_NAME_SLOT(6)  LANLOBBY_NAME_SLOT(7)  LANLOBBY_NAME_SLOT(8)
	LANLOBBY_NAME_SLOT(9)  LANLOBBY_NAME_SLOT(10) LANLOBBY_NAME_SLOT(11)
	LANLOBBY_NAME_SLOT(12) LANLOBBY_NAME_SLOT(13) LANLOBBY_NAME_SLOT(14)
	LANLOBBY_NAME_SLOT(15) LANLOBBY_NAME_SLOT(16) LANLOBBY_NAME_SLOT(17)
	LANLOBBY_NAME_SLOT(18) LANLOBBY_NAME_SLOT(19) LANLOBBY_NAME_SLOT(20)
	LANLOBBY_NAME_SLOT(21) LANLOBBY_NAME_SLOT(22) LANLOBBY_NAME_SLOT(23)
	LANLOBBY_NAME_SLOT(24) LANLOBBY_NAME_SLOT(25) LANLOBBY_NAME_SLOT(26)
	LANLOBBY_NAME_SLOT(27) LANLOBBY_NAME_SLOT(28) LANLOBBY_NAME_SLOT(29)
	LANLOBBY_NAME_SLOT(30) LANLOBBY_NAME_SLOT(31) LANLOBBY_NAME_SLOT(32)
	LANLOBBY_NAME_SLOT(33) LANLOBBY_NAME_SLOT(34) LANLOBBY_NAME_SLOT(35)
	LANLOBBY_NAME_SLOT(36) LANLOBBY_NAME_SLOT(37) LANLOBBY_NAME_SLOT(38)
	LANLOBBY_NAME_SLOT(39) LANLOBBY_NAME_SLOT(40) LANLOBBY_NAME_SLOT(41)
	LANLOBBY_NAME_SLOT(42) LANLOBBY_NAME_SLOT(43) LANLOBBY_NAME_SLOT(44)
	LANLOBBY_NAME_SLOT(45) LANLOBBY_NAME_SLOT(46)
#undef LANLOBBY_NAME_SLOT
	virtual UnicodeString getName();
};

extern LanLobbyNameGuard *g_Va012F7730;

class BfmeAptScreenLanLobby
{
public:
	void copyGuardName(UnicodeString &dest);
};

// ?copyGuardName@BfmeAptScreenLanLobby@@QAEXAAVUnicodeString@@@Z
void BfmeAptScreenLanLobby::copyGuardName(UnicodeString &dest)
{
	if (g_Va012F7730)
		dest.set(g_Va012F7730->getName());
}
