// Open-BFME5: near-twin of ??1LivingWorldCampaignManager (0x003B7D30,
// LivingWorldCampaignManagerDestructor.cpp) and of the two-callee chained
// destructor at 0x007E4A00 (Rva007E4A00Destructor.cpp): same single-vtable
// shape. This body reports a nested value through the unidentified manager
// global at VA 0x012F19E8 (bfmeOneMD thiscall, still a dump reached through
// ILT thunk 0x00033857), calls a still-unidentified thiscall member (reached
// through ILT thunk 0x0003A4AE) with no other arguments, clears a pointer
// member at +0x24, then chains to the already-landed base destructor
// Gen_uwm_0001ff0a (through ILT thunk 0x0001FF0A). Real class, field and
// callee names not recovered; started from reverse/attempts/0x00470360.cpp
// (partial score 0.55), which called the thiscall callee as a bare free
// function (missing its ecx=this argument) -- fixed here by modelling it as
// a member call so the compiler reloads ecx=esi itself, matching retail.

class BfmeMgr19E
{
public:
	void bfmeOneMD( int h );
};

extern BfmeMgr19E *g_mgr12F19E8;

class Rva0001FF0ABase
{
public:
	virtual ~Rva0001FF0ABase();
};

struct Rva00470360Inner
{
	unsigned char m_pad[ 0x250 ];
	int m_value;
};

// Reinterpret-cast helper for the vtable-slot-+0x20 callee at 0x0003A4AE
// (tools/vtable_lookup.py): retail's destructor calls it directly (ecx=this,
// no other args), matching the two-callee chained destructor's own idiom at
// 0x007E4A00 (Rva007E4A00Destructor.cpp, Gen009A4D60_0081C330).
class Gen0003A4AE
{
public:
	void cleanupRva0003A4AE();
};

class Rva00470360 : public Rva0001FF0ABase
{
public:
	virtual ~Rva00470360();

private:
	unsigned char m_pad[ 0x24 - 4 ];
	Rva00470360Inner *m_ptr;
};

// ??1Rva00470360@@UAE@XZ
Rva00470360::~Rva00470360()
{
	Rva00470360Inner *p = m_ptr;
	g_mgr12F19E8->bfmeOneMD( p->m_value );
	( (Gen0003A4AE *)this )->cleanupRva0003A4AE();
	m_ptr = 0;
}
