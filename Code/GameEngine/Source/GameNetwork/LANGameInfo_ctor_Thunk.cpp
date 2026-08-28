// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct LANAddress {
	UnsignedInt m_address;
	UnsignedInt m_port;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot {
protected:
	unsigned char m_storage[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot {
public:
	LANGameSlot();
	~LANGameSlot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo {
public:
	GameInfo();
	virtual ~GameInfo();
	virtual Int getLocalSlotNum() const;

	void setSlotPointer(Int index, GameSlot *slot);

protected:
	unsigned char m_gap04[0x30];
	LANAddress m_localAddress;
	unsigned char m_gap3c[0x1c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString {
public:
	__forceinline UnicodeString() : m_data(0) {}
	~UnicodeString();

private:
	void *m_data;
};

class LANInterface {
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot1A() = 0;
	virtual void slot1B() = 0;
	virtual void slot1C() = 0;
	virtual void slot1D() = 0;
	virtual void slot1E() = 0;
	virtual void slot1F() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot2A() = 0;
	virtual void slot2B() = 0;
	virtual void slot2C() = 0;
	virtual void slot2D() = 0;
	virtual void slot2E() = 0;
	virtual void slot2F() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual const LANAddress &getLocalAddress() = 0;
};

extern LANInterface *TheLAN;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameInfo : public GameInfo {
public:
	LANGameInfo();
	virtual ~LANGameInfo();
	virtual Int getLocalSlotNum() const;

private:
	LANGameSlot m_slots[8];
	LANGameInfo *m_next;
	UnsignedInt m_lastHeard;
	UnicodeString m_gameName;
	Bool m_isDirectConnect;
};

// ??0LANGameInfo@@QAE@XZ
LANGameInfo::LANGameInfo()
	: m_next(0), m_lastHeard(0), m_isDirectConnect(false)
{
	for (UnsignedInt i = 0; i < 8; ++i)
		setSlotPointer(i, &m_slots[i]);

	m_localAddress = TheLAN->getLocalAddress();
}
