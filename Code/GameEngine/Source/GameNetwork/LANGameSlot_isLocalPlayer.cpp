// cl: /DNDEBUG /MD /EHsc
// LANGameSlot::isLocalPlayer, retail 0x0068D340 (124 bytes).

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

struct BfmeNetAddress
{
	UnsignedInt ip;
	UnsignedShort port;
};

// The BFME GameSlot carries the address at +0x30.  Its virtual predicate is
// the already-pinned GameSlot::isHuman body reached through the 0x279CB ILT.
class BfmeGameSlot
{
public:
	virtual void reset() = 0;
	Bool isHuman() const;

protected:
	UnsignedByte m_bfmeBeforeAddress[0x2c];
	BfmeNetAddress m_address;
};

class LANGameSlot : public BfmeGameSlot
{
public:
	Bool isLocalPlayer() const;
};

class LANAPI
{
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
	virtual void slot0a() = 0;
	virtual void slot0b() = 0;
	virtual void slot0c() = 0;
	virtual void slot0d() = 0;
	virtual void slot0e() = 0;
	virtual void slot0f() = 0;
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
	virtual void slot1a() = 0;
	virtual void slot1b() = 0;
	virtual void slot1c() = 0;
	virtual void slot1d() = 0;
	virtual void slot1e() = 0;
	virtual void slot1f() = 0;
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
	virtual void slot2a() = 0;
	virtual void slot2b() = 0;
	virtual void slot2c() = 0;
	virtual void slot2d() = 0;
	virtual void slot2e() = 0;
	virtual void slot2f() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual BfmeNetAddress *getLocalAddress() = 0; // vtable slot 55, +0xDC
};

extern LANAPI *TheLAN;

Bool LANGameSlot::isLocalPlayer() const
{
	if (!isHuman() || TheLAN == 0)
		return false;

	BfmeNetAddress *local = TheLAN->getLocalAddress();
	if (local->ip == m_address.ip && local->port == m_address.port)
		return true;

	BfmeNetAddress localAddress = *TheLAN->getLocalAddress();
	localAddress.port = (UnsignedShort)(localAddress.port + 8);
	return localAddress.ip == m_address.ip &&
		localAddress.port == m_address.port;
}
