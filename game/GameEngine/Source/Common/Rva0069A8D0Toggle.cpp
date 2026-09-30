// ?Rva0069A8D0Toggle@@YGXPAVBfmeHolderLK@@@Z (identity unknown)
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *handle);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(void *handle);

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

void __stdcall Rva0069A8D0Toggle(BfmeHolderLK *holder)
{
	BfmeThingLK *thing = holder->m_bfmeThingLK;
	if (thing->m_bfmeALK)
		goto ON;
	if (thing->m_bfmeBLK)
		goto ON;
	if (thing->m_bfmeCLK)
		goto ON;
	if (thing->m_bfmeDLK)
		goto ON;
	AIL_resume_sample(thing->m_bfmeHandleLK);
	return;
ON:
	AIL_stop_sample(thing->m_bfmeHandleLK);
}
