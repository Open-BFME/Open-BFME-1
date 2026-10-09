// cl: /O2 /DNDEBUG /MD

// Open-BFME7: RVA 0x008B61D0 (782 bytes). Release the 37 lazily created Apt
// property singletons at 0x013383A4 through 0x01338434 through virtual slot +4
// and clear each slot. The same globals are created one per switch case by
// rva008B73B0 (Rva008B73B0Properties.cpp), so this TU shares its symbols;
// called from rva00891E00ReleaseChain. Address-derived identity.

class Rva00899FC0;

class Rva008B61D0Slot
{
public:
	virtual void slot00();
	virtual void release();
};

Rva00899FC0 *g_Va013383A4;
Rva00899FC0 *g_Va013383A8;
Rva00899FC0 *g_Va013383AC;
Rva00899FC0 *g_Va013383B0;
Rva00899FC0 *g_Va013383B4;
Rva00899FC0 *g_Va013383B8;
Rva00899FC0 *g_Va013383BC;
Rva00899FC0 *g_Va013383C0;
Rva00899FC0 *g_Va013383C4;
Rva00899FC0 *g_Va013383C8;
Rva00899FC0 *g_Va013383CC;
Rva00899FC0 *g_Va013383D0;
Rva00899FC0 *g_Va013383D4;
Rva00899FC0 *g_Va013383D8;
Rva00899FC0 *g_Va013383DC;
Rva00899FC0 *g_Va013383E0;
Rva00899FC0 *g_Va013383E4;
Rva00899FC0 *g_Va013383E8;
Rva00899FC0 *g_Va013383EC;
Rva00899FC0 *g_Va013383F0;
Rva00899FC0 *g_Va013383F4;
Rva00899FC0 *g_Va013383F8;
Rva00899FC0 *g_Va013383FC;
Rva00899FC0 *g_Va01338400;
Rva00899FC0 *g_Va01338404;
Rva00899FC0 *g_Va01338408;
Rva00899FC0 *g_Va0133840C;
Rva00899FC0 *g_Va01338410;
Rva00899FC0 *g_Va01338414;
Rva00899FC0 *g_Va01338418;
Rva00899FC0 *g_Va0133841C;
Rva00899FC0 *g_Va01338420;
Rva00899FC0 *g_Va01338424;
Rva00899FC0 *g_Va01338428;
Rva00899FC0 *g_Va0133842C;
Rva00899FC0 *g_Va01338430;
Rva00899FC0 *g_Va01338434;

void rva008B61D0ReleaseGlobals()
{
	Rva00899FC0 *z = 0;
	if (g_Va013383A4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383A4)->release();
		g_Va013383A4 = z;
	}
	if (g_Va013383A8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383A8)->release();
		g_Va013383A8 = z;
	}
	if (g_Va013383AC != z)
	{
		((Rva008B61D0Slot *)g_Va013383AC)->release();
		g_Va013383AC = z;
	}
	if (g_Va013383B0 != z)
	{
		((Rva008B61D0Slot *)g_Va013383B0)->release();
		g_Va013383B0 = z;
	}
	if (g_Va013383B4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383B4)->release();
		g_Va013383B4 = z;
	}
	if (g_Va013383B8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383B8)->release();
		g_Va013383B8 = z;
	}
	if (g_Va013383BC != z)
	{
		((Rva008B61D0Slot *)g_Va013383BC)->release();
		g_Va013383BC = z;
	}
	if (g_Va013383C0 != z)
	{
		((Rva008B61D0Slot *)g_Va013383C0)->release();
		g_Va013383C0 = z;
	}
	if (g_Va013383C4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383C4)->release();
		g_Va013383C4 = z;
	}
	if (g_Va013383C8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383C8)->release();
		g_Va013383C8 = z;
	}
	if (g_Va013383CC != z)
	{
		((Rva008B61D0Slot *)g_Va013383CC)->release();
		g_Va013383CC = z;
	}
	if (g_Va013383D0 != z)
	{
		((Rva008B61D0Slot *)g_Va013383D0)->release();
		g_Va013383D0 = z;
	}
	if (g_Va013383D4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383D4)->release();
		g_Va013383D4 = z;
	}
	if (g_Va013383D8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383D8)->release();
		g_Va013383D8 = z;
	}
	if (g_Va013383DC != z)
	{
		((Rva008B61D0Slot *)g_Va013383DC)->release();
		g_Va013383DC = z;
	}
	if (g_Va013383E0 != z)
	{
		((Rva008B61D0Slot *)g_Va013383E0)->release();
		g_Va013383E0 = z;
	}
	if (g_Va013383E4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383E4)->release();
		g_Va013383E4 = z;
	}
	if (g_Va013383E8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383E8)->release();
		g_Va013383E8 = z;
	}
	if (g_Va013383EC != z)
	{
		((Rva008B61D0Slot *)g_Va013383EC)->release();
		g_Va013383EC = z;
	}
	if (g_Va013383F0 != z)
	{
		((Rva008B61D0Slot *)g_Va013383F0)->release();
		g_Va013383F0 = z;
	}
	if (g_Va013383F4 != z)
	{
		((Rva008B61D0Slot *)g_Va013383F4)->release();
		g_Va013383F4 = z;
	}
	if (g_Va013383F8 != z)
	{
		((Rva008B61D0Slot *)g_Va013383F8)->release();
		g_Va013383F8 = z;
	}
	if (g_Va013383FC != z)
	{
		((Rva008B61D0Slot *)g_Va013383FC)->release();
		g_Va013383FC = z;
	}
	if (g_Va01338400 != z)
	{
		((Rva008B61D0Slot *)g_Va01338400)->release();
		g_Va01338400 = z;
	}
	if (g_Va01338404 != z)
	{
		((Rva008B61D0Slot *)g_Va01338404)->release();
		g_Va01338404 = z;
	}
	if (g_Va01338408 != z)
	{
		((Rva008B61D0Slot *)g_Va01338408)->release();
		g_Va01338408 = z;
	}
	if (g_Va0133840C != z)
	{
		((Rva008B61D0Slot *)g_Va0133840C)->release();
		g_Va0133840C = z;
	}
	if (g_Va01338410 != z)
	{
		((Rva008B61D0Slot *)g_Va01338410)->release();
		g_Va01338410 = z;
	}
	if (g_Va01338414 != z)
	{
		((Rva008B61D0Slot *)g_Va01338414)->release();
		g_Va01338414 = z;
	}
	if (g_Va01338418 != z)
	{
		((Rva008B61D0Slot *)g_Va01338418)->release();
		g_Va01338418 = z;
	}
	if (g_Va0133841C != z)
	{
		((Rva008B61D0Slot *)g_Va0133841C)->release();
		g_Va0133841C = z;
	}
	if (g_Va01338420 != z)
	{
		((Rva008B61D0Slot *)g_Va01338420)->release();
		g_Va01338420 = z;
	}
	if (g_Va01338424 != z)
	{
		((Rva008B61D0Slot *)g_Va01338424)->release();
		g_Va01338424 = z;
	}
	if (g_Va01338428 != z)
	{
		((Rva008B61D0Slot *)g_Va01338428)->release();
		g_Va01338428 = z;
	}
	if (g_Va0133842C != z)
	{
		((Rva008B61D0Slot *)g_Va0133842C)->release();
		g_Va0133842C = z;
	}
	if (g_Va01338430 != z)
	{
		((Rva008B61D0Slot *)g_Va01338430)->release();
		g_Va01338430 = z;
	}
	if (g_Va01338434 != z)
	{
		((Rva008B61D0Slot *)g_Va01338434)->release();
		g_Va01338434 = z;
	}
}
