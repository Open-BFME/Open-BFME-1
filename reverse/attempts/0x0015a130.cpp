// ?queryContain@Rva0015A130Owner@@QAEXPAVObject@@H@Z
// partial score=0.89 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015A130, 66 bytes. Same-dump leftover as aiGoProne / groupFollow.
// Object contain at +0x1FC, virt +0x144, then helper at ILT 0x00048C43
// (body 0x00159AD0) with a 16-byte stack packet and a trailing unused arg.

class Object;
class ContainModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void slot74() = 0;
	virtual void slot78() = 0;
	virtual void slot7C() = 0;
	virtual void slot80() = 0;
	virtual void slot84() = 0;
	virtual void slot88() = 0;
	virtual void slot8C() = 0;
	virtual void slot90() = 0;
	virtual void slot94() = 0;
	virtual void slot98() = 0;
	virtual void slot9C() = 0;
	virtual void slotA0() = 0;
	virtual void slotA4() = 0;
	virtual void slotA8() = 0;
	virtual void slotAC() = 0;
	virtual void slotB0() = 0;
	virtual void slotB4() = 0;
	virtual void slotB8() = 0;
	virtual void slotBC() = 0;
	virtual void slotC0() = 0;
	virtual void slotC4() = 0;
	virtual void slotC8() = 0;
	virtual void slotCC() = 0;
	virtual void slotD0() = 0;
	virtual void slotD4() = 0;
	virtual void slotD8() = 0;
	virtual void slotDC() = 0;
	virtual void slotE0() = 0;
	virtual void slotE4() = 0;
	virtual void slotE8() = 0;
	virtual void slotEC() = 0;
	virtual void slotF0() = 0;
	virtual void slotF4() = 0;
	virtual void slotF8() = 0;
	virtual void slotFC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual void slot114() = 0;
	virtual void slot118() = 0;
	virtual void slot11C() = 0;
	virtual void slot120() = 0;
	virtual void slot124() = 0;
	virtual void slot128() = 0;
	virtual void slot12C() = 0;
	virtual void slot130() = 0;
	virtual void slot134() = 0;
	virtual void slot138() = 0;
	virtual void slot13C() = 0;
	virtual void slot140() = 0;
	virtual int queryAt144() = 0;				// +0x144
};

class Object
{
public:
	unsigned char m_pad00[0x1FC];
	ContainModuleInterface *m_contain;			// +0x1FC
};

struct Rva0015A130Packet
{
	int m_query;								// +0, filled after the contain virt
	unsigned char m_flag;						// +4
	Object *m_objA;								// +8
	Object *m_objB;								// +12
};

class Rva0015A130Owner
{
public:
	void queryContain(Object *obj, int unused);
	void applyPacket(Rva0015A130Packet *packet, int unused);	// ILT 0x00048C43
};

void Rva0015A130Owner::queryContain(Object *obj, int unused)
{
	ContainModuleInterface *contain = obj->m_contain;
	if (!contain)
		return;

	Rva0015A130Packet packet;
	packet.m_objB = obj;
	packet.m_objA = obj;
	packet.m_flag = 0;
	packet.m_query = contain->queryAt144();
	applyPacket(&packet, 0);
}
