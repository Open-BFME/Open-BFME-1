// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x00516B60: BfmeAptScreenLanLobby thiscall, one bool. If the flag is
// clear, run the +0x25C subobject's dispatchOnce; if set, run its stop path
// only when TheLAN exists and LANAPI::AmIHost (vslot+B8) is false.
// The actual target6852E0 returns int0/1; retail consumes AL, so preserve that
// explicit byte consumption rather than declaring the real method as bool.

class LANAPI
{
public:
#define LANAPI_SLOT(N) virtual void slot##N();
	LANAPI_SLOT(0)  LANAPI_SLOT(1)  LANAPI_SLOT(2)
	LANAPI_SLOT(3)  LANAPI_SLOT(4)  LANAPI_SLOT(5)
	LANAPI_SLOT(6)  LANAPI_SLOT(7)  LANAPI_SLOT(8)
	LANAPI_SLOT(9)  LANAPI_SLOT(10) LANAPI_SLOT(11)
	LANAPI_SLOT(12) LANAPI_SLOT(13) LANAPI_SLOT(14)
	LANAPI_SLOT(15) LANAPI_SLOT(16) LANAPI_SLOT(17)
	LANAPI_SLOT(18) LANAPI_SLOT(19) LANAPI_SLOT(20)
	LANAPI_SLOT(21) LANAPI_SLOT(22) LANAPI_SLOT(23)
	LANAPI_SLOT(24) LANAPI_SLOT(25) LANAPI_SLOT(26)
	LANAPI_SLOT(27) LANAPI_SLOT(28) LANAPI_SLOT(29)
	LANAPI_SLOT(30) LANAPI_SLOT(31) LANAPI_SLOT(32)
	LANAPI_SLOT(33) LANAPI_SLOT(34) LANAPI_SLOT(35)
	LANAPI_SLOT(36) LANAPI_SLOT(37) LANAPI_SLOT(38)
	LANAPI_SLOT(39) LANAPI_SLOT(40) LANAPI_SLOT(41)
	LANAPI_SLOT(42) LANAPI_SLOT(43) LANAPI_SLOT(44)
	LANAPI_SLOT(45)
#undef LANAPI_SLOT
	virtual int AmIHost();
};

extern LANAPI *TheLAN;

class BfmeE976
{
public:
	void bfmeGo976E();
};

class Rva00523340Object
{
public:
	void dispatchOnce();
};

class BfmeAptScreenLanLobby
{
public:
	void toggleSub(bool on);

private:
	char m_unmodelled[0x25C];
	BfmeE976 m_subStop;
};

// ?toggleSub@BfmeAptScreenLanLobby@@QAEX_N@Z
void BfmeAptScreenLanLobby::toggleSub(bool on)
{
	if (on)
	{
		if (TheLAN && !static_cast<unsigned char>(TheLAN->AmIHost()))
			m_subStop.bfmeGo976E();
	}
	else
	{
		((Rva00523340Object *)&m_subStop)->dispatchOnce();
	}
}
