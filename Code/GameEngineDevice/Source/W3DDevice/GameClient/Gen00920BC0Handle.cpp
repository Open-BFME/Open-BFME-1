// cl: /MD /EHsc
// Open-BFME: address-derived DX8 stage-state block at retail 0x00920BC0.
// The three state bases index 5-int stage tables; modes 0 and 1 select the
// alternate state values, while other modes leave that state unchanged.

struct Gen00920BC0Device
{
#define GEN_DEVICE_SLOT(n) virtual void __stdcall slot##n(void);
	GEN_DEVICE_SLOT(0) GEN_DEVICE_SLOT(1) GEN_DEVICE_SLOT(2)
	GEN_DEVICE_SLOT(3) GEN_DEVICE_SLOT(4) GEN_DEVICE_SLOT(5)
	GEN_DEVICE_SLOT(6) GEN_DEVICE_SLOT(7) GEN_DEVICE_SLOT(8)
	GEN_DEVICE_SLOT(9) GEN_DEVICE_SLOT(10) GEN_DEVICE_SLOT(11)
	GEN_DEVICE_SLOT(12) GEN_DEVICE_SLOT(13) GEN_DEVICE_SLOT(14)
	GEN_DEVICE_SLOT(15) GEN_DEVICE_SLOT(16) GEN_DEVICE_SLOT(17)
	GEN_DEVICE_SLOT(18) GEN_DEVICE_SLOT(19) GEN_DEVICE_SLOT(20)
	GEN_DEVICE_SLOT(21) GEN_DEVICE_SLOT(22) GEN_DEVICE_SLOT(23)
	GEN_DEVICE_SLOT(24) GEN_DEVICE_SLOT(25) GEN_DEVICE_SLOT(26)
	GEN_DEVICE_SLOT(27) GEN_DEVICE_SLOT(28) GEN_DEVICE_SLOT(29)
	GEN_DEVICE_SLOT(30) GEN_DEVICE_SLOT(31) GEN_DEVICE_SLOT(32)
	GEN_DEVICE_SLOT(33) GEN_DEVICE_SLOT(34) GEN_DEVICE_SLOT(35)
	GEN_DEVICE_SLOT(36) GEN_DEVICE_SLOT(37) GEN_DEVICE_SLOT(38)
	GEN_DEVICE_SLOT(39) GEN_DEVICE_SLOT(40) GEN_DEVICE_SLOT(41)
	GEN_DEVICE_SLOT(42) GEN_DEVICE_SLOT(43) GEN_DEVICE_SLOT(44)
	GEN_DEVICE_SLOT(45) GEN_DEVICE_SLOT(46) GEN_DEVICE_SLOT(47)
	GEN_DEVICE_SLOT(48) GEN_DEVICE_SLOT(49) GEN_DEVICE_SLOT(50)
	GEN_DEVICE_SLOT(51) GEN_DEVICE_SLOT(52) GEN_DEVICE_SLOT(53)
	GEN_DEVICE_SLOT(54) GEN_DEVICE_SLOT(55) GEN_DEVICE_SLOT(56)
	GEN_DEVICE_SLOT(57) GEN_DEVICE_SLOT(58) GEN_DEVICE_SLOT(59)
	GEN_DEVICE_SLOT(60) GEN_DEVICE_SLOT(61) GEN_DEVICE_SLOT(62)
	GEN_DEVICE_SLOT(63) GEN_DEVICE_SLOT(64) GEN_DEVICE_SLOT(65)
	GEN_DEVICE_SLOT(66) GEN_DEVICE_SLOT(67) GEN_DEVICE_SLOT(68)
	virtual long __stdcall SetTextureStageState(
		unsigned int, unsigned int, unsigned int);
#undef GEN_DEVICE_SLOT
};

struct Rva00920AE0Slot
{
	int m_options[4];
	int m_selected;
};

extern Gen00920BC0Device *Rva01340534Device;
extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340568StageChanges;
extern Rva00920AE0Slot g_bfmeOptionSlots0[8];
extern Rva00920AE0Slot g_bfmeOptionSlotsA[8];
extern Rva00920AE0Slot g_bfmeOptionSlotsB[8];

class Gen00920BC0
{
public:
	int m_stateA;
	int m_stateB;
	int m_stateC;
	int m_modeA;
	int m_modeB;
	void handle(int index);
};

void Gen00920BC0::handle(int index)
{
	int scaled = index * 5;
	Rva01340534Device->SetTextureStageState(index, 6,
		((int *)g_bfmeOptionSlots0)[m_stateA + scaled]);
	Rva01340594DX8Calls++;
	Rva01340568StageChanges++;
	Rva01340534Device->SetTextureStageState(index, 5,
		((int *)g_bfmeOptionSlotsA)[m_stateB + scaled]);
	Rva01340594DX8Calls++;
	Rva01340568StageChanges++;
	Rva01340534Device->SetTextureStageState(index, 7,
		((int *)g_bfmeOptionSlotsB)[m_stateC + scaled]);
	Rva01340594DX8Calls++;
	Rva01340568StageChanges++;
	switch (m_modeA)
	{
	case 0:
		Rva01340534Device->SetTextureStageState(index, 1, 1);
		Rva01340594DX8Calls++;
		Rva01340568StageChanges++;
		break;
	case 1:
		Rva01340534Device->SetTextureStageState(index, 1, 3);
		Rva01340594DX8Calls++;
		Rva01340568StageChanges++;
		break;
	default:
		break;
	}
	switch (m_modeB)
	{
	case 0:
		Rva01340534Device->SetTextureStageState(index, 2, 1);
		Rva01340594DX8Calls++;
		Rva01340568StageChanges++;
		break;
	case 1:
		Rva01340534Device->SetTextureStageState(index, 2, 3);
		Rva01340594DX8Calls++;
		Rva01340568StageChanges++;
		break;
	default:
		break;
	}
}
