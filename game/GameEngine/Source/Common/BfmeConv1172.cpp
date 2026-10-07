// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5 conversions.
// Same layout as AssetManagerImpl in
// game/Libraries/Source/assetmanager/Get_Current_Asset.cpp: lock at +0x2C,
// hash_map<int, Gen_t_009f14c0_p12cd> at +0x44, its iterator at +0x58. Retail
// calls the map's begin() at 0x009EE0F0, pinned under that type in symbols.csv.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *p);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *p);

struct Gen_t_009f14c0_p12cd
{
	void *m_asset;
	int a[2];
	Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd(const Gen_t_009f14c0_p12cd &);
	~Gen_t_009f14c0_p12cd();
	Gen_t_009f14c0_p12cd &operator=(const Gen_t_009f14c0_p12cd &);
};

typedef _STL::hash_map<int, Gen_t_009f14c0_p12cd> BfmeMap1172;

class BfmeF1172 : public BfmeMap1172
{
};

class BfmeQ1172
{
public:
	void bfmeGo1172(int a);
	char m_bfmePad0[0x2c];
	char m_bfme2c;
	char m_bfmePad1[0x17];
	BfmeF1172 m_bfme44;
	BfmeMap1172::iterator m_bfme58;
	char m_bfmePad3[0x188];
	int m_bfme1e8;
};

void BfmeQ1172::bfmeGo1172(int a)
{
	void *p = &m_bfme2c;

	EnterCriticalSection(p);
	m_bfme58 = m_bfme44.begin();
	m_bfme1e8 = a;
	LeaveCriticalSection(p);
}
