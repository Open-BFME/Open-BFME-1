// cl: /DNDEBUG /MD /O2 /EHsc
// Address-derived xfer body at retail RVA 0x0018C480 (343 bytes).
//
// The owner identity is not recovered, so the field view is deliberately
// local to this translation unit.  The complete retail body proves the
// offsets and the Xfer virtual slots used below.  The two helper types are
// declaration-only dispatch views; no object or vtable is emitted here.

typedef bool Bool;
typedef int Int;
typedef unsigned char UnsignedByte;

struct Rva0018C480XferVersion
{
	UnsignedByte m_byte00;
	UnsignedByte m_byte01;
};

class Rva0018C480Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool stopTransfer();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void transferVersionPair(Rva0018C480XferVersion *);
	virtual void slot11();
	virtual void xferValue(void *);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferField(void *);
	virtual void slot28();
	virtual void xferInt(Int *);
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35(void *);
};

class MidVirtualSlot90Receiver;
extern void Rva0010C040(MidVirtualSlot90Receiver *, void *);

class BfmeSeedTarget;
class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *);
};

class Rva002BD630TeamFactory
{
public:
	void *find(Int);
};

class TeamFactory;
extern TeamFactory *TheTeamFactory;

class Rva0018C480Team
{
public:
	void *m_vptr;
	void *m_owner;
	Int m_id;
	Int getID() const { return m_id; }
};

class Rva0018C480Owner
{
public:
	void xfer(Rva0018C480Xfer *xfer);

private:
	UnsignedByte m_pad00[0x14];
	void *m_value14;
	UnsignedByte m_value18[4];
	UnsignedByte m_value1c[4];
	BfmeSubAccept_0002C41C m_accept20;
	UnsignedByte m_pad21[0x6f];
	Int m_value90;
	Rva0018C480Team *m_team;
	UnsignedByte m_slot90[4];
	Int m_value9c;
	Int m_valuea0;
	UnsignedByte m_valuea4;
	UnsignedByte m_valuea5;
	UnsignedByte m_valuea6;
	UnsignedByte m_valuea7;
	UnsignedByte m_valuea8;
	UnsignedByte m_valuea9;
	UnsignedByte m_valueaa;
	UnsignedByte m_valueab;
};

// ?xfer@Rva0018C480Owner@@QAEXPAVRva0018C480Xfer@@@Z
void Rva0018C480Owner::xfer(Rva0018C480Xfer *xfer)
{
	if (xfer->stopTransfer())
		return;

	Rva0018C480XferVersion version;
	version.m_byte00 = 1;
	version.m_byte01 = 1;
	xfer->transferVersionPair(&version);

	xfer->xferValue(m_value14);
	xfer->xferField(m_value18);
	xfer->xferField(m_value1c);
	xfer->xferInt(&m_value90);

	Rva0010C040(
		reinterpret_cast<MidVirtualSlot90Receiver *>(xfer),
		m_slot90);

	xfer->xferInt(&m_value9c);
	xfer->slot35(&m_valuea4);
	xfer->slot35(&m_valuea5);
	xfer->slot35(&m_valuea6);
	xfer->slot35(&m_valuea7);
	xfer->slot35(&m_valuea8);
	xfer->slot35(&m_valuea9);
	xfer->slot35(&m_valueab);
	xfer->slot35(&m_valueaa);
	xfer->xferInt(&m_valuea0);

	m_accept20.bfmeAccept(reinterpret_cast<BfmeSeedTarget *>(xfer));

	Int teamID = m_team ? m_team->getID() : 0;
	xfer->xferInt(&teamID);
	m_team = reinterpret_cast<Rva0018C480Team *>(reinterpret_cast<Rva002BD630TeamFactory *>(TheTeamFactory)->find(teamID));
}
