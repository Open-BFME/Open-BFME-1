// Open-BFME5 conversions.

struct BfmeS1209
{
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

// Retail VA 0x013378A4 is the loader-installed handler cell (g_bfmeSlot27VB),
// not an import slot: `ff 15 a4 78 33 01` is a call through that pointer.
extern void (*g_bfmeSlot27VB)(void);
typedef void (__cdecl *RvaNotify1209)(void *a);

class BfmeA1209
{
public:
	void bfmeOp1209(const BfmeS1209 *a);
	float m_bfme00, m_bfme04, m_bfme08, m_bfme0c, m_bfme10, m_bfme14, m_bfme18, m_bfme1c;
};

void BfmeA1209::bfmeOp1209(const BfmeS1209 *a)
{
	m_bfme00 = a->m_bfme00 * m_bfme00;
	m_bfme04 = a->m_bfme04 * m_bfme04;
	m_bfme08 = a->m_bfme08 * m_bfme08;
	m_bfme0c = a->m_bfme0c * m_bfme0c;
	m_bfme10 = a->m_bfme10 + m_bfme10;
	m_bfme14 = a->m_bfme14 + m_bfme14;
	m_bfme18 = a->m_bfme18 + m_bfme18;
	m_bfme1c = a->m_bfme1c + m_bfme1c;
	((RvaNotify1209)g_bfmeSlot27VB)(this);
}
