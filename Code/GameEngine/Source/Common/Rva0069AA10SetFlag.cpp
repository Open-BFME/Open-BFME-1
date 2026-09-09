// ?bfmeShowLK@@YGXPAVBfmeHolderLK@@@Z (identity unknown)
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) void __stdcall bfmeApiLK(void *handle, int flag);

class BfmeThingLK
{
public:
	unsigned char m_bfmeHeadLK[8];
	void *m_bfmeHandleLK;
	unsigned char m_bfmeGapLK[0x2d];
	char m_bfmeALK;
	char m_bfmeBLK;
	char m_bfmeCLK;
	char m_bfmeDLK;
};

class BfmeHolderLK
{
public:
	BfmeThingLK *m_bfmeThingLK;
};

void __stdcall bfmeShowLK(BfmeHolderLK *holder)
{
	BfmeThingLK *thing = holder->m_bfmeThingLK;
	int flag;
	if (thing->m_bfmeALK || thing->m_bfmeBLK || thing->m_bfmeCLK || thing->m_bfmeDLK)
		flag = 1;
	else
		flag = 0;

	bfmeApiLK(thing->m_bfmeHandleLK, (unsigned char)flag);
}
