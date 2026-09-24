// cl: /DNDEBUG /MD /EHsc
// Open-BFME: leftover of d_00153d10.asm at 0x0015A130, 66 bytes, ret 8.
// Only caller is GameLogic::logicMessageDispatcher (0x00397540 via ILT
// 0x0000DD0A), which passes the looked-up object and 0. The body reads the
// object's pointer at +0x1FC, and when it is set fills a 16-byte stack request
// {slot-81 virtual result, 0, object, object} for the shared apply helper at
// ILT 0x00048C43 (body 0x00159AD0), second argument 0.
//
// The request is filled inside the null test, not after an early return: the
// early-return spelling stores the flag byte ahead of the vftable load, the
// guarded block puts the flag byte between the vftable load and the call as
// retail does.
class BfmeThingCH
{
public:
	virtual void bfmeSlot00CH();
	virtual void bfmeSlot01CH();
	virtual void bfmeSlot02CH();
	virtual void bfmeSlot03CH();
	virtual void bfmeSlot04CH();
	virtual void bfmeSlot05CH();
	virtual void bfmeSlot06CH();
	virtual void bfmeSlot07CH();
	virtual void bfmeSlot08CH();
	virtual void bfmeSlot09CH();
	virtual void bfmeSlot10CH();
	virtual void bfmeSlot11CH();
	virtual void bfmeSlot12CH();
	virtual void bfmeSlot13CH();
	virtual void bfmeSlot14CH();
	virtual void bfmeSlot15CH();
	virtual void bfmeSlot16CH();
	virtual void bfmeSlot17CH();
	virtual void bfmeSlot18CH();
	virtual void bfmeSlot19CH();
	virtual void bfmeSlot20CH();
	virtual void bfmeSlot21CH();
	virtual void bfmeSlot22CH();
	virtual void bfmeSlot23CH();
	virtual void bfmeSlot24CH();
	virtual void bfmeSlot25CH();
	virtual void bfmeSlot26CH();
	virtual void bfmeSlot27CH();
	virtual void bfmeSlot28CH();
	virtual void bfmeSlot29CH();
	virtual void bfmeSlot30CH();
	virtual void bfmeSlot31CH();
	virtual void bfmeSlot32CH();
	virtual void bfmeSlot33CH();
	virtual void bfmeSlot34CH();
	virtual void bfmeSlot35CH();
	virtual void bfmeSlot36CH();
	virtual void bfmeSlot37CH();
	virtual void bfmeSlot38CH();
	virtual void bfmeSlot39CH();
	virtual void bfmeSlot40CH();
	virtual void bfmeSlot41CH();
	virtual void bfmeSlot42CH();
	virtual void bfmeSlot43CH();
	virtual void bfmeSlot44CH();
	virtual void bfmeSlot45CH();
	virtual void bfmeSlot46CH();
	virtual void bfmeSlot47CH();
	virtual void bfmeSlot48CH();
	virtual void bfmeSlot49CH();
	virtual void bfmeSlot50CH();
	virtual void bfmeSlot51CH();
	virtual void bfmeSlot52CH();
	virtual void bfmeSlot53CH();
	virtual void bfmeSlot54CH();
	virtual void bfmeSlot55CH();
	virtual void bfmeSlot56CH();
	virtual void bfmeSlot57CH();
	virtual void bfmeSlot58CH();
	virtual void bfmeSlot59CH();
	virtual void bfmeSlot60CH();
	virtual void bfmeSlot61CH();
	virtual void bfmeSlot62CH();
	virtual void bfmeSlot63CH();
	virtual void bfmeSlot64CH();
	virtual void bfmeSlot65CH();
	virtual void bfmeSlot66CH();
	virtual void bfmeSlot67CH();
	virtual void bfmeSlot68CH();
	virtual void bfmeSlot69CH();
	virtual void bfmeSlot70CH();
	virtual void bfmeSlot71CH();
	virtual void bfmeSlot72CH();
	virtual void bfmeSlot73CH();
	virtual void bfmeSlot74CH();
	virtual void bfmeSlot75CH();
	virtual void bfmeSlot76CH();
	virtual void bfmeSlot77CH();
	virtual void bfmeSlot78CH();
	virtual void bfmeSlot79CH();
	virtual void bfmeSlot80CH();
	virtual void *bfmeMakeCH();
};

class BfmeSrcCH
{
public:
	unsigned char m_bfmeHeadCH[0x1fc];
	BfmeThingCH *m_bfmeTargetCH;
};

struct BfmeReqCH
{
	void *m_bfmeACH;
	unsigned char m_bfmeBCH;
	unsigned char m_bfmePadCH[3];
	BfmeSrcCH *m_bfmeCCH;
	BfmeSrcCH *m_bfmeDCH;
};

struct Rva0015A190Packet;

// The apply helper is pinned under the owner spelling its 0x0015A190 sibling
// landed with; the receiver is the same object, cast through as
// ScriptActions_doTeamMoveToNearestObjectOfKindof.cpp does.
class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, int b);
};

class BfmeHostCH
{
public:
	void bfmeSendCH(BfmeSrcCH *src, void *unused);
};

// ?bfmeSendCH@BfmeHostCH@@QAEXPAVBfmeSrcCH@@PAX@Z
void BfmeHostCH::bfmeSendCH(BfmeSrcCH *src, void *unused)
{
	BfmeThingCH *t = src->m_bfmeTargetCH;

	if (t != 0)
	{
		BfmeReqCH req;

		req.m_bfmeDCH = src;
		req.m_bfmeCCH = src;
		req.m_bfmeBCH = 0;
		req.m_bfmeACH = t->bfmeMakeCH();

		((Rva0015A190Owner *)this)->applyPacket((Rva0015A190Packet *)&req, 0);
	}
}
