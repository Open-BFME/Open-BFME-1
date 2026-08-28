// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail W3DOverlordTruckDrawModuleData constructor at 0x00429460.
//
// The packet's two relocation-masked candidates are separated by their base
// calls: retail calls the 225-byte base at 0x00428590, ruling out the known
// 133-byte W3DTankDrawModuleData constructor.  The Zero Hour Overlord Truck
// body supplies the derived identity.
//
// This translation-unit-local ABI slice preserves retail's member offsets.
// Volatile members retain the original zero -> vtable -> members store order.

extern unsigned char bfme_W3DOverlordTruckDrawModuleData_vtable;

class W3DOverlordTruckModuleDataBase
{
public:
	void *volatile m_vtable;
	char m_baseFields[0xB0];
	W3DOverlordTruckModuleDataBase();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DOverlordTruckDraw.h
class W3DOverlordTruckDrawModuleData : public W3DOverlordTruckModuleDataBase
{
public:
	volatile unsigned int m_unknownB4;
	volatile bool m_unknownB8;

	W3DOverlordTruckDrawModuleData();
};

W3DOverlordTruckDrawModuleData::W3DOverlordTruckDrawModuleData()
{
	unsigned int zero = 0;
	m_vtable = &bfme_W3DOverlordTruckDrawModuleData_vtable;
	m_unknownB4 = zero;
	m_unknownB8 = static_cast<bool>( zero );
}
