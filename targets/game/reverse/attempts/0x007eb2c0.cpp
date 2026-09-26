// ??1Rva007EB2C0Object@@UAE@XZ
// partial score=0.88 date=2026-09-06
// ??1Rva007EB2C0Object@@UAE@XZ

class T_007ea120
{
public:
	virtual void vslot0(int value);
	void m(void);
};

struct Rva0130A588State
{
	T_007ea120 *m_obj;
	char m_flagC;
	char m_flagD;
};

extern Rva0130A588State g_Va0130A588;

extern void Rva007EB830Release(void);
extern void Rva007F0060(void);

class Rva007EB2C0Object
{
public:
	virtual ~Rva007EB2C0Object();
};

Rva007EB2C0Object::~Rva007EB2C0Object()
{
	if (g_Va0130A588.m_obj)
		g_Va0130A588.m_obj->m();

	if (g_Va0130A588.m_obj)
		g_Va0130A588.m_obj->vslot0(1);

	g_Va0130A588.m_obj = 0;

	if (g_Va0130A588.m_flagD)
		Rva007EB830Release();

	if (g_Va0130A588.m_flagC)
		Rva007F0060();
}
