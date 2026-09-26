// cl: /DNDEBUG /MD /EHs-c-

// The 0x0039B2B0 body is a small BFME snapshot transfer.  The retail class
// name is not recovered, so the owner remains address-derived; the field
// offsets and every dispatch target come from the retail instructions.

typedef unsigned char UnsignedByte;

struct Rva0039B2B0Version
{
	UnsignedByte m_byte00;
	UnsignedByte m_byte01;
};

class Xfer
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void transferVersionPair(Rva0039B2B0Version *version); // +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68(void *value); // +0x68
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C(void *value); // +0x7C
};

// The three address-derived xferEnum-style forwarders are real clean C++
// bodies in MidVirtualSlot90Forwarders.cpp.  This declaration-only view is
// used for dispatch and does not emit a vtable in this TU.
class MidVirtualSlot90Receiver;
extern void Rva0010C280(MidVirtualSlot90Receiver *receiver, void *context);
extern void Rva0010C2A0(MidVirtualSlot90Receiver *receiver, void *context);
extern void Rva0010C2C0(MidVirtualSlot90Receiver *receiver, void *context);

class ClientSubsystem
{
public:
#define RVA0039B2B0_AUDIO_PAD(N) virtual void slot##N();
	RVA0039B2B0_AUDIO_PAD(000) RVA0039B2B0_AUDIO_PAD(004)
	RVA0039B2B0_AUDIO_PAD(008) RVA0039B2B0_AUDIO_PAD(00C)
	RVA0039B2B0_AUDIO_PAD(010) RVA0039B2B0_AUDIO_PAD(014)
	RVA0039B2B0_AUDIO_PAD(018) RVA0039B2B0_AUDIO_PAD(01C)
	RVA0039B2B0_AUDIO_PAD(020) RVA0039B2B0_AUDIO_PAD(024)
	RVA0039B2B0_AUDIO_PAD(028) RVA0039B2B0_AUDIO_PAD(02C)
	RVA0039B2B0_AUDIO_PAD(030) RVA0039B2B0_AUDIO_PAD(034)
	RVA0039B2B0_AUDIO_PAD(038) RVA0039B2B0_AUDIO_PAD(03C)
	RVA0039B2B0_AUDIO_PAD(040) RVA0039B2B0_AUDIO_PAD(044)
	RVA0039B2B0_AUDIO_PAD(048) RVA0039B2B0_AUDIO_PAD(04C)
	RVA0039B2B0_AUDIO_PAD(050) RVA0039B2B0_AUDIO_PAD(054)
	RVA0039B2B0_AUDIO_PAD(058) RVA0039B2B0_AUDIO_PAD(05C)
	RVA0039B2B0_AUDIO_PAD(060) RVA0039B2B0_AUDIO_PAD(064)
	RVA0039B2B0_AUDIO_PAD(068) RVA0039B2B0_AUDIO_PAD(06C)
	RVA0039B2B0_AUDIO_PAD(070) RVA0039B2B0_AUDIO_PAD(074)
	RVA0039B2B0_AUDIO_PAD(078) RVA0039B2B0_AUDIO_PAD(07C)
	RVA0039B2B0_AUDIO_PAD(080) RVA0039B2B0_AUDIO_PAD(084)
	RVA0039B2B0_AUDIO_PAD(088) RVA0039B2B0_AUDIO_PAD(08C)
	RVA0039B2B0_AUDIO_PAD(090) RVA0039B2B0_AUDIO_PAD(094)
	RVA0039B2B0_AUDIO_PAD(098) RVA0039B2B0_AUDIO_PAD(09C)
	RVA0039B2B0_AUDIO_PAD(0A0) RVA0039B2B0_AUDIO_PAD(0A4)
	RVA0039B2B0_AUDIO_PAD(0A8) RVA0039B2B0_AUDIO_PAD(0AC)
	RVA0039B2B0_AUDIO_PAD(0B0) RVA0039B2B0_AUDIO_PAD(0B4)
	RVA0039B2B0_AUDIO_PAD(0B8) RVA0039B2B0_AUDIO_PAD(0BC)
	RVA0039B2B0_AUDIO_PAD(0C0) RVA0039B2B0_AUDIO_PAD(0C4)
	RVA0039B2B0_AUDIO_PAD(0C8) RVA0039B2B0_AUDIO_PAD(0CC)
	RVA0039B2B0_AUDIO_PAD(0D0) RVA0039B2B0_AUDIO_PAD(0D4)
	RVA0039B2B0_AUDIO_PAD(0D8) RVA0039B2B0_AUDIO_PAD(0DC)
	RVA0039B2B0_AUDIO_PAD(0E0) RVA0039B2B0_AUDIO_PAD(0E4)
	RVA0039B2B0_AUDIO_PAD(0E8) RVA0039B2B0_AUDIO_PAD(0EC)
	RVA0039B2B0_AUDIO_PAD(0F0) RVA0039B2B0_AUDIO_PAD(0F4)
	RVA0039B2B0_AUDIO_PAD(0F8) RVA0039B2B0_AUDIO_PAD(0FC)
	RVA0039B2B0_AUDIO_PAD(100) RVA0039B2B0_AUDIO_PAD(104)
	RVA0039B2B0_AUDIO_PAD(108) RVA0039B2B0_AUDIO_PAD(10C)
	RVA0039B2B0_AUDIO_PAD(110) RVA0039B2B0_AUDIO_PAD(114)
	RVA0039B2B0_AUDIO_PAD(118) RVA0039B2B0_AUDIO_PAD(11C)
	RVA0039B2B0_AUDIO_PAD(120) RVA0039B2B0_AUDIO_PAD(124)
	RVA0039B2B0_AUDIO_PAD(128) RVA0039B2B0_AUDIO_PAD(12C)
	RVA0039B2B0_AUDIO_PAD(130) RVA0039B2B0_AUDIO_PAD(134)
	RVA0039B2B0_AUDIO_PAD(138) RVA0039B2B0_AUDIO_PAD(13C)
	RVA0039B2B0_AUDIO_PAD(140) RVA0039B2B0_AUDIO_PAD(144)
	virtual void takeItem148(void *xfer, void *value); // +0x148
#undef RVA0039B2B0_AUDIO_PAD
};

// The call site only needs the singleton's proven global identity and the
// virtual slot at +0x148.  The declaration above deliberately keeps all
// preceding slots so the compiler emits the real indirect dispatch offset.
extern ClientSubsystem *TheAudioClientUpdate;

class BfmeOwnerCGF
{
public:
	void bfmeOneCGF(void *what);

	char m_opaque[4];
};

class Rva0039B2B0
{
public:
	void xfer(Xfer *xfer);

private:
	char m_vptr[4];
	int m_field04;
	int m_field08;
	int m_field0C;
	BfmeOwnerCGF m_owner10;
	int m_field14;
	int m_field18;
	int m_field1C;
};

void Rva0039B2B0::xfer(Xfer *xfer)
{
	Rva0039B2B0Version version;
	version.m_byte00 = 1;
	version.m_byte01 = 2;
	xfer->transferVersionPair(&version);

	Rva0010C280((MidVirtualSlot90Receiver *)xfer, &m_field04);
	TheAudioClientUpdate->takeItem148(xfer, &m_field08);
	Rva0010C2A0((MidVirtualSlot90Receiver *)xfer, &m_field0C);
	m_owner10.bfmeOneCGF(xfer);
	xfer->slot68(&m_field14);
	Rva0010C2C0((MidVirtualSlot90Receiver *)xfer, &m_field18);

	if (version.m_byte01 >= 2)
		xfer->slot7C(&m_field1C);
}
