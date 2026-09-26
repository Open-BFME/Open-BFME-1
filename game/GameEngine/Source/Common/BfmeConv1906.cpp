struct BfmeInfoAZ
{
	unsigned char m_bfmeFlagAZ;
	unsigned char m_bfmeLevelAZ;
};

class BfmeAgentAZ
{
public:
	virtual void bfmeSlot00AZ();
	virtual void bfmeSlot01AZ();
	virtual void bfmeSlot02AZ();
	virtual void bfmeSlot03AZ();
	virtual char bfmeSkipAZ();
	virtual void bfmeSlot05AZ();
	virtual void bfmeSlot06AZ();
	virtual void bfmeSlot07AZ();
	virtual void bfmeSlot08AZ();
	virtual void bfmeSlot09AZ();
	virtual void bfmeFillAZ(BfmeInfoAZ *info);
	virtual void bfmeSlot11AZ();
	virtual void bfmeSlot12AZ();
	virtual void bfmeSlot13AZ();
	virtual void bfmeSlot14AZ();
	virtual void bfmeSlot15AZ();
	virtual void bfmeSlot16AZ();
	virtual void bfmeSlot17AZ();
	virtual void bfmeSlot18AZ();
	virtual void bfmeSlot19AZ();
	virtual void bfmeSlot20AZ();
	virtual void bfmeSlot21AZ();
	virtual void bfmeSlot22AZ();
	virtual void bfmeSlot23AZ();
	virtual void bfmeSlot24AZ();
	virtual void bfmeSlot25AZ();
	virtual void bfmeSlot26AZ();
	virtual void bfmeLateAZ(void *dst);
	virtual void bfmeSlot28AZ();
	virtual void bfmeWordAZ(void *dst);
	virtual void bfmeSlot30AZ();
	virtual void bfmeSlot31AZ();
	virtual void bfmeSlot32AZ();
	virtual void bfmeSlot33AZ();
	virtual void bfmeSlot34AZ();
	virtual void bfmeByteAZ(unsigned char *dst);
};

struct Rva005A00B0AudioClient
{
	virtual void bfmeSlot00AU();
	virtual void bfmeSlot01AU();
	virtual void bfmeSlot02AU();
	virtual void bfmeSlot03AU();
	virtual void bfmeSlot04AU();
	virtual void bfmeSlot05AU();
	virtual void bfmeSlot06AU();
	virtual void bfmeSlot07AU();
	virtual void bfmeSlot08AU();
	virtual void bfmeSlot09AU();
	virtual void bfmeSlot10AU();
	virtual void bfmeSlot11AU();
	virtual void bfmeSlot12AU();
	virtual void bfmeSlot13AU();
	virtual void bfmeSlot14AU();
	virtual void bfmeSlot15AU();
	virtual void bfmeSlot16AU();
	virtual void bfmeSlot17AU();
	virtual void bfmeSlot18AU();
	virtual void bfmeSlot19AU();
	virtual void bfmeSlot20AU();
	virtual void bfmeSlot21AU();
	virtual void bfmeSlot22AU();
	virtual void bfmeSlot23AU();
	virtual void bfmeSlot24AU();
	virtual void bfmeSlot25AU();
	virtual void bfmeSlot26AU();
	virtual void bfmeSlot27AU();
	virtual void bfmeSlot28AU();
	virtual void bfmeSlot29AU();
	virtual void bfmeSlot30AU();
	virtual void bfmeSlot31AU();
	virtual void bfmeSlot32AU();
	virtual void bfmeSlot33AU();
	virtual void bfmeSlot34AU();
	virtual void bfmeSlot35AU();
	virtual void bfmeSlot36AU();
	virtual void bfmeSlot37AU();
	virtual void bfmeSlot38AU();
	virtual void bfmeSlot39AU();
	virtual void bfmeSlot40AU();
	virtual void bfmeSlot41AU();
	virtual void bfmeSlot42AU();
	virtual void bfmeSlot43AU();
	virtual void bfmeSlot44AU();
	virtual void bfmeSlot45AU();
	virtual void bfmeSlot46AU();
	virtual void bfmeSlot47AU();
	virtual void bfmeSlot48AU();
	virtual void bfmeSlot49AU();
	virtual void bfmeSlot50AU();
	virtual void bfmeSlot51AU();
	virtual void bfmeSlot52AU();
	virtual void bfmeSlot53AU();
	virtual void bfmeSlot54AU();
	virtual void bfmeSlot55AU();
	virtual void bfmeSlot56AU();
	virtual void bfmeSlot57AU();
	virtual void bfmeSlot58AU();
	virtual void bfmeSlot59AU();
	virtual void bfmeSlot60AU();
	virtual void bfmeSlot61AU();
	virtual void bfmeSlot62AU();
	virtual void bfmeSlot63AU();
	virtual void bfmeSlot64AU();
	virtual void bfmeSlot65AU();
	virtual void bfmeSlot66AU();
	virtual void bfmeSlot67AU();
	virtual void bfmeSlot68AU();
	virtual void bfmeSlot69AU();
	virtual void bfmeSlot70AU();
	virtual void bfmeSlot71AU();
	virtual void bfmeSlot72AU();
	virtual void bfmeSlot73AU();
	virtual void bfmeSlot74AU();
	virtual void bfmeSlot75AU();
	virtual void bfmeSlot76AU();
	virtual void bfmeSlot77AU();
	virtual void bfmeSlot78AU();
	virtual void bfmeSlot79AU();
	virtual void bfmeSlot80AU();
	virtual void bfmeSlot81AU();
	virtual void bfmeAudioAZ(BfmeAgentAZ *ag, void *dst);
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

extern "C" void __cdecl bfmeXferHeadAZ(BfmeAgentAZ *ag, void *dst);
extern "C" void __cdecl bfmeXferTailAZ(BfmeAgentAZ *ag, void *dst);

class BfmeHostAZ
{
public:
	void bfmeSaveAZ(BfmeAgentAZ *ag);
	void bfmeBeginAZ(BfmeAgentAZ *ag);

	unsigned char m_bfmeHeadAZ[0x24];
	unsigned char m_bfmeSlotAAZ[4];
	unsigned char m_bfmeSlotBAZ[4];
	unsigned char m_bfmeSlotCAZ[4];
	unsigned char m_bfmeSlotDAZ[4];
	unsigned char m_bfmeSlotEAZ[4];
	unsigned char m_bfmeSlotFAZ[4];
	unsigned char m_bfmeSlotGAZ[4];
	unsigned char m_bfmeSlotHAZ;
	unsigned char m_bfmePadAZ[3];
	unsigned char m_bfmeSlotIAZ[4];
	unsigned char m_bfmeSlotJAZ[4];
	unsigned char m_bfmeSlotKAZ;
};

void BfmeHostAZ::bfmeSaveAZ(BfmeAgentAZ *ag)
{
	bfmeBeginAZ(ag);

	if (ag->bfmeSkipAZ() != 0)
		return;

	BfmeInfoAZ info;

	info.m_bfmeFlagAZ = 1;
	info.m_bfmeLevelAZ = 3;
	ag->bfmeFillAZ(&info);

	bfmeXferHeadAZ(ag, m_bfmeSlotAAZ);
	ag->bfmeWordAZ(m_bfmeSlotBAZ);
	ag->bfmeWordAZ(m_bfmeSlotCAZ);
	ag->bfmeWordAZ(m_bfmeSlotDAZ);
	ag->bfmeLateAZ(m_bfmeSlotFAZ);
	ag->bfmeWordAZ(m_bfmeSlotGAZ);
	ag->bfmeWordAZ(m_bfmeSlotIAZ);
	TheAudioClientUpdate->bfmeAudioAZ(ag, m_bfmeSlotEAZ);
	ag->bfmeByteAZ(&m_bfmeSlotHAZ);

	if (info.m_bfmeLevelAZ >= 2)
		bfmeXferTailAZ(ag, m_bfmeSlotJAZ);

	if (info.m_bfmeLevelAZ >= 3)
		ag->bfmeByteAZ(&m_bfmeSlotKAZ);
}
