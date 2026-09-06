// ??1Rva00470360@@UAE@XZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??1LivingWorldCampaignManager (0x003B7D30,
// LivingWorldCampaignManagerDestructor.cpp); same single-vtable shape, but this
// body reports a nested value through g_mgr12F19E8 before clearing a pointer
// member and chaining to the already-landed base destructor Gen_uwm_0001ff0a.

void j_0003a4ae();

class BfmeObjMD
{
public:
	void bfmeOneMD(int h);
};

extern BfmeObjMD *g_mgr12F19E8;

class Gen_uwm_0001ff0a
{
public:
	~Gen_uwm_0001ff0a();
};

struct Rva00470360Inner
{
	unsigned char m_pad[0x250];
	int m_value;
};

class Rva00470360 : public Gen_uwm_0001ff0a
{
public:
	virtual ~Rva00470360();

private:
	unsigned char m_pad[0x24 - 4];
	Rva00470360Inner *m_ptr;
};

// ?d_00470360@@YAXXZ
Rva00470360::~Rva00470360()
{
	Rva00470360Inner *p = m_ptr;
	g_mgr12F19E8->bfmeOneMD(p->m_value);
	j_0003a4ae();
	m_ptr = 0;
}
