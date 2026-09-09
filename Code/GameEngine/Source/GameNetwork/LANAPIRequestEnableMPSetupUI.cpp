// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// LANAPI::RequestEnableMPSetupUI, retail 0x00686780, 166 bytes.
//
// The retail vtable at 0x0111AF50 identifies this body as slot 17.  Retail's
// message formatter maps type 0x0C to MSG_ENABLE_MPSETUP_UI, and this body
// carries one Bool argument into that message before queueing it.

typedef int Int;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;
typedef unsigned char UnsignedByte;
typedef bool Bool;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(
	WideChar *, const WideChar *, unsigned int);

template <typename T> struct BfmeStringData
{
	Int m_refCount;
	UnsignedShort m_length;
	UnsignedShort m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase(void);
	void releaseBuffer(void);

	BfmeStringData<T> *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(void) : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString(void) {}

	const WideChar *str(void) const
	{
		return m_data ? m_data->m_text
			: (const WideChar *)0x0107388C;
	}
};

// queuePacket uses this BFME-specific packet tag in its decorated name.
#pragma pack(push, 1)
class LANAPIRequestPacket
{
	public:
	Int m_type;
	UnsignedByte m_bfmeHeader[0x22 - 4];
	WideChar m_gameName[17];
	Bool m_enableMPSetupUI;
	UnsignedByte m_bfmeTail[0x1DC - 0x45];
};
#pragma pack(pop)

typedef char BfmePacketSizeCheck[
	sizeof(LANAPIRequestPacket) == 0x1DC ? 1 : -1];

typedef LANAPIRequestPacket LANMessage;

class LANGameInfo
{
public:
	UnicodeString getName(void);
};

class LANAPIMemberObject
{
public:
	void flushQueue(void);
};

class LANAPI
{
public:
	virtual void _bfme_slot00(void) = 0;
	virtual void _bfme_slot01(void) = 0;
	virtual void _bfme_slot02(void) = 0;
	virtual void _bfme_slot03(void) = 0;
	virtual void _bfme_slot04(void) = 0;
	virtual void _bfme_slot05(void) = 0;
	virtual void _bfme_slot06(void) = 0;
	virtual void _bfme_slot07(void) = 0;
	virtual void _bfme_slot08(void) = 0;
	virtual void _bfme_slot09(void) = 0;
	virtual void _bfme_slot10(void) = 0;
	virtual void _bfme_slot11(void) = 0;
	virtual void _bfme_slot12(void) = 0;
	virtual void _bfme_slot13(void) = 0;
	virtual void _bfme_slot14(void) = 0;
	virtual void _bfme_slot15(void) = 0;
	virtual void _bfme_slot16(void) = 0;
	virtual void RequestEnableMPSetupUI(Bool enable);
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_slot21(void) = 0;
	virtual void _bfme_slot22(void) = 0;
	virtual void _bfme_slot23(void) = 0;
	virtual void _bfme_slot24(void) = 0;
	virtual void _bfme_slot25(void) = 0;
	virtual void _bfme_slot26(void) = 0;
	virtual void _bfme_slot27(void) = 0;
	virtual void _bfme_slot28(void) = 0;
	virtual void _bfme_slot29(void) = 0;
	virtual void _bfme_slot30(void) = 0;
	virtual void _bfme_slot31(void) = 0;
	virtual void _bfme_slot32(void) = 0;
	virtual void _bfme_slot33(void) = 0;
	virtual void _bfme_slot34(void) = 0;
	virtual void _bfme_slot35(void) = 0;
	virtual void _bfme_slot36(void) = 0;
	virtual void _bfme_slot37(void) = 0;
	virtual void _bfme_slot38(void) = 0;
	virtual void _bfme_slot39(void) = 0;
	virtual void _bfme_slot40(void) = 0;
	virtual void _bfme_slot41(void) = 0;
	virtual void _bfme_slot42(void) = 0;
	virtual void _bfme_slot43(void) = 0;
	virtual void _bfme_slot44(void) = 0;
	virtual void _bfme_slot45(void) = 0;
	virtual void _bfme_slot46(void) = 0;
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void fillInLANMessage(LANMessage *packet) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual void _bfme_slot55(void) = 0;

	void queuePacket(LANAPIRequestPacket *packet, int ip);

protected:
	UnsignedByte m_bfmeBeforeCurrent[0x40 - 4];
	LANGameInfo *m_currentGame;
	UnsignedByte m_bfmeBeforeMember[0x4C - 0x44];
	LANAPIMemberObject *m_memberObject;
};

// ?RequestEnableMPSetupUI@LANAPI@@UAEX_N@Z
void LANAPI::RequestEnableMPSetupUI(Bool enable)
{
	LANAPIRequestPacket packet;
	packet.m_type = 0x0C;
	fillInLANMessage(&packet);
	wcsncpy(packet.m_gameName,
		m_currentGame ? m_currentGame->getName().str()
			: L"",
		16);
	packet.m_gameName[16] = 0;
	packet.m_enableMPSetupUI = enable;
	queuePacket(&packet, 0);
	m_memberObject->flushQueue();
}
