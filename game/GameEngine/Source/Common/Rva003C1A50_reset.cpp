// cl: /DNDEBUG /MD /EHsc
//
// Rva003C1A50::run, retail 0x003C1A50, 84 bytes.
//
// d_003b8450 reset path: clearOwned + clearTwoVec, settle +0x74/+0x80/+0x78/
// +0xC8/+0xCC, singleton go, clearSingleton, set m_at2C, tail-reset UI.

// These existing row owners consume this caller's unadjusted ECX, with no
// stack arguments. Their full native bodies are independently byte-verified.
class Gen_003C0EF0
{
public:
	void bfmeClear();
};
class Gen_003C0F70
{
public:
	void bfmeClear();
};
class Gen_003C0DB0
{
public:
	void bfmeClear();
};
class BfmeThingBLE
{
public:
	void bfmeGoBLE();
};
class Rva0060FFC0Owner
{
public:
	void resetUiState();
};

// Retail 0x012F706C is ?TheLivingWorldManager@@3PAVLivingWorldManager@@A (data_rows.csv,
// LivingWorld/LivingWorldManager.cpp); g_bfmeGameCW was only a pin.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva003C1A50
{
public:
	void run();

private:
	char m_pad00[ 0x2C ];
	bool m_at2C;
	char m_pad2D[ 0x74 - 0x2D ];
	int m_at74;
	bool m_at78;
	char m_pad79[ 0x80 - 0x79 ];
	bool m_at80;
	char m_pad81[ 0xC8 - 0x81 ];
	bool m_atC8;
	char m_padC9[ 0xCC - 0xC9 ];
	int m_atCC;
};

// ?run@Rva003C1A50@@QAEXXZ
void Rva003C1A50::run()
{
	reinterpret_cast<Gen_003C0EF0 *>(this)->bfmeClear();
	reinterpret_cast<Gen_003C0F70 *>(this)->bfmeClear();
	m_at74 = 1;
	m_at80 = false;
	m_at78 = false;
	m_atC8 = true;
	m_atCC = 0x78;
	reinterpret_cast<BfmeThingBLE *>(TheLivingWorldManager)->bfmeGoBLE();
	reinterpret_cast<Gen_003C0DB0 *>(this)->bfmeClear();
	m_at2C = true;
	reinterpret_cast<Rva0060FFC0Owner *>(TheLivingWorldManager)->resetUiState();
}
