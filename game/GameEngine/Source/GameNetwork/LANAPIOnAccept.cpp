// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// LANAPI host acceptance callback, full205-byte body at RVA0x006889B0.
// Vtable111AF50 slot33 routes through ILT15609. Pointer-plus-status ABI is
// established by handleSetAccept and the LANAPISendPath declaration.
// Both status arms update the global slot through the516BB0 this-adjustor;
// pinning its underlying523380 setter would omit the required+25C adjustment.
// Returns at+BC and+CA; CC padding starts+CD. No EH or embedded tables.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// The pair is eight-byte storage in LANAPI's BFME object: dword IP, word
// port, and the compiler's natural two-byte tail padding.
struct BfmeNetAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

struct TransportAddress
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

// Existing matched accessor at 0x0068D3E0.  Its body is a bounds check and
// `this + 0x58 + index * 0x68`; keeping the address-derived owner avoids
// asserting that the +0x88 address view is a second array.
struct Rva0068D3E0Slot
{
	char m_body[0x68];
};

class Rva0068D3E0Arr
{
public:
	Rva0068D3E0Slot *at(Int index);

private:
	char m_pad[0x58];
	Rva0068D3E0Slot m_items[8];
};

// The GameSlot fields used by the body.  This is a local view of the same
// 0x44-byte GameSlot that owns the already matched unAccept method.
class GameSlot
{
public:
	void unAccept(void);

	void *m_vptr;
	Int m_state;
	Bool m_isAccepted;                  // +0x08
	Bool m_hasMap;
	Bool m_isMuted;
	UnsignedByte m_beforeAddress[0x30 - 0x0B];
	BfmeNetAddress m_address;            // +0x30
	UnsignedByte m_afterAddress[0x44 - 0x38];
};

// Only the address member of each LANGameSlot is read directly by retail.
struct BfmeLANAddressSlot
{
	BfmeNetAddress m_address;
	UnsignedByte m_afterAddress[0x68 - 8];
};

class BfmeLANGameInfoAddressView
{
public:
	UnsignedByte m_beforeAddresses[0x88];
	BfmeLANAddressSlot m_slot[8];
};

// j_00007248 enters wrapper RVA 0x00516BB0, whose first instruction is
// `add ecx,0x25C` before its jump through RVA 0x00048C89 to the underlying
// setter at 0x00523380.
// Keep the wrapper as the call identity: the caller passes the global base.
class Rva00516BB0
{
public:
	void bfmeSetSlot(UnsignedShort index, UnsignedByte value);
};


struct BfmeObj935C
{
	UnsignedByte m_beforeFlag[0x26C];
	UnsignedByte m_bfmeFlag;             // +0x26C
};

extern BfmeObj935C *g_bfme935GlobC;    // retail data 0x012F4998
extern void rva004CAF70(void);        // ILT 0x00039202 -> body 0x004CAF70

// The only LANAPI fields needed here are the established +0x3D/+0x40 pair.
// The virtual declarations preserve the retail call slots used by this body.
class LANGameInfo;

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
	virtual void _bfme_slot17(void) = 0;
	virtual void _bfme_slot18(void) = 0;
	virtual void _bfme_slot19(void) = 0;
	virtual void _bfme_slot20(void) = 0;
	virtual void _bfme_requestSerializedGameInfo(Bool unused,
		TransportAddress *destination) = 0;       // slot 21, +0x54
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
	virtual void OnAccept(BfmeNetAddress *from, UnsignedInt status) = 0;
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
	virtual Int AmIHost(void) = 0;               // slot 46, +0xB8; 32-bit return
	virtual void _bfme_slot47(void) = 0;
	virtual void _bfme_slot48(void) = 0;
	virtual void _bfme_slot49(void) = 0;
	virtual void _bfme_slot50(void) = 0;
	virtual void _bfme_slot51(void) = 0;
	virtual void _bfme_slot52(void) = 0;
	virtual void _bfme_slot53(void) = 0;
	virtual void _bfme_slot54(void) = 0;
	virtual BfmeNetAddress *_bfme_localAddress(void) = 0; // slot 55, +0xDC

protected:
	UnsignedByte m_bfmeBeforeLobby[0x3D - 4];
	Bool m_inLobby;                                  // +0x3D
	UnsignedByte m_bfmeBeforeCurrent[2];
	LANGameInfo *m_currentGame;                      // +0x40
};

// ?OnAccept@LANAPI@@UAEXPAUBfmeNetAddress@@I@Z
// Canonical BFME declaration uses a pointer to the address struct (PAU).
void LANAPI::OnAccept(BfmeNetAddress *from, UnsignedInt status)
{
	// AmIHost returns a 32-bit Int; retail tests its low byte here.
	if ((UnsignedByte)AmIHost() == 0)
		return;

	Int player;
	for (player = 0; player < 8; ++player)
	{
		BfmeNetAddress *slotAddress = &reinterpret_cast<
			BfmeLANGameInfoAddressView *>(m_currentGame)->m_slot[player].m_address;
		if (slotAddress->m_ip == from->m_ip &&
			slotAddress->m_port == from->m_port)
		{
			// Retail reads only the low status byte, then repeats the accessor
			// call in each arm.  The setter receives an immediate 1 or 0.
			if (*((UnsignedByte *)&status))
			{
				Rva0068D3E0Slot *rawSlot =
					reinterpret_cast<Rva0068D3E0Arr *>(m_currentGame)->at(player);
				GameSlot *slot =
					reinterpret_cast<GameSlot *>(rawSlot);
				slot->m_isAccepted = true;

				if (g_bfme935GlobC)
					reinterpret_cast<Rva00516BB0 *>(g_bfme935GlobC)->bfmeSetSlot(
					(UnsignedShort)player, 1);
			}
			else
			{
				Rva0068D3E0Slot *rawSlot =
					reinterpret_cast<Rva0068D3E0Arr *>(m_currentGame)->at(player);
				GameSlot *slot =
					reinterpret_cast<GameSlot *>(rawSlot);
				slot->unAccept();

				if (g_bfme935GlobC)
					reinterpret_cast<Rva00516BB0 *>(g_bfme935GlobC)->bfmeSetSlot(
					(UnsignedShort)player, 0);
			}
			break;
		}
	}

	if (player == 8)
		return;

	// Retail stores only the dword IP and word port of this eight-byte local;
	// the two member assignments leave the alignment padding untouched.
	TransportAddress noAddress;
	noAddress.m_ip = 0;
	noAddress.m_port = 0;
	_bfme_requestSerializedGameInfo(false, &noAddress);

	BfmeObj935C *global = g_bfme935GlobC;
	if (global)
		global->m_bfmeFlag = 1;
	else
		rva004CAF70();
}
