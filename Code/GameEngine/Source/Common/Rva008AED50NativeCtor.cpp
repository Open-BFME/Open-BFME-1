// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived reconstruction. No ZH twin found; string/call
// fingerprints (AptValue::toInteger, an AptValue-family float coercion, a
// global GFx-style argument stack) place this in the same proprietary
// Scaleform/ActionScript glue family as the blocked body at 0x008B2C60.
// Globals per retail: 0x013377D8 (g_bfmeHolderBU), 0x01338750/0x01338748
// (global argument array base/count), 0x013379BC (g_bfmeFallbackDB).

class AptValue
{
public:
	int toInteger() const;
};

class BfmeE1239
{
public:
	float bfmeF1239();
};

class Rva008AED50Obj
{
public:
	virtual void bfmeRva008AED50Refresh();
private:
	unsigned char m_gap[0x20 - 4];
public:
	float m_field20;
	float m_field24;
};

struct Rva008AED50Holder
{
	unsigned char m_gap0[0x1240];
	Rva008AED50Obj *m_target;              // +0x1240
	float m_rectA;                          // +0x1244
	float m_rectB;                          // +0x1248
	float m_rectC;                          // +0x124C
	float m_rectD;                          // +0x1250
	float m_fallbackX;                       // +0x1254
	float m_fallbackY;                       // +0x1258
	unsigned char m_gap1[0x1274 - 0x125C];
	int m_baseX;                             // +0x1274
	int m_baseY;                             // +0x1278
};

extern Rva008AED50Holder *g_bfmeHolderBU;    // retail 0x013377D8
extern AptValue **g_bfmeArgBase;              // retail 0x01338750
extern int g_bfmeArgCount;                    // retail 0x01338748
extern void *g_bfmeFallbackDB;                 // retail 0x013379BC

void *Rva008AED50Ctor(Rva008AED50Obj *obj, int argc)
{
	obj->bfmeRva008AED50Refresh();

	g_bfmeHolderBU->m_target = obj;
	g_bfmeHolderBU->m_fallbackX = 0.0f;
	g_bfmeHolderBU->m_fallbackY = 0.0f;
	g_bfmeHolderBU->m_rectA = -9999.0f;
	g_bfmeHolderBU->m_rectB = -9999.0f;
	g_bfmeHolderBU->m_rectC = -9999.0f;
	g_bfmeHolderBU->m_rectD = -9999.0f;

	if (argc == 0 || !g_bfmeArgBase[g_bfmeArgCount - 1]->toInteger())
	{
		g_bfmeHolderBU->m_fallbackX = (float)g_bfmeHolderBU->m_baseX - obj->m_field20;
		g_bfmeHolderBU->m_fallbackY = (float)g_bfmeHolderBU->m_baseY - obj->m_field24;
	}

	if (argc > 0)
	{
		g_bfmeHolderBU->m_rectA = ((BfmeE1239 *)g_bfmeArgBase[g_bfmeArgCount - 2])->bfmeF1239();
		g_bfmeHolderBU->m_rectB = 0.0f;
		g_bfmeHolderBU->m_rectC = 0.0f;
		g_bfmeHolderBU->m_rectD = 0.0f;
	}
	if (argc > 1)
	{
		g_bfmeHolderBU->m_rectB = ((BfmeE1239 *)g_bfmeArgBase[g_bfmeArgCount - 3])->bfmeF1239();
	}
	if (argc > 2)
	{
		g_bfmeHolderBU->m_rectC = ((BfmeE1239 *)g_bfmeArgBase[g_bfmeArgCount - 4])->bfmeF1239();
	}
	if (argc > 3)
	{
		g_bfmeHolderBU->m_rectD = ((BfmeE1239 *)g_bfmeArgBase[g_bfmeArgCount - 5])->bfmeF1239();
	}

	return g_bfmeFallbackDB;
}
