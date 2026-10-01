extern char g_bfmeEmptyEHR[];

struct BfmeStrDataEHR
{
	int m_bfmeRefEHR;
	int m_bfmeLenEHR;
	char m_bfmeTextEHR[1];
};

class BfmeStrEHR
{
public:
	~BfmeStrEHR() { releaseBuffer(); }

	const char *bfmeTextEHR() const
	{
		return m_bfmeDataEHR ? m_bfmeDataEHR->m_bfmeTextEHR : g_bfmeEmptyEHR;
	}

	BfmeStrDataEHR *m_bfmeDataEHR;

private:
	void releaseBuffer();
};

class BfmeObjEHR
{
public:
	BfmeStrEHR bfmeNameEHR();

	unsigned char m_bfmeHeadEHR[0x268];
	BfmeStrEHR m_bfmeTagEHR;
};

class BfmeMgrEHR
{
public:
	void bfmeAddEHR(void *win, const char *tag, int count, const char *name,
		int p1, int p2, int p3, int p4);
};

// Retail's WindowManager global at 0x012F19E8, under the one linked-build
// spelling.  BfmeMgrEHR above is this TU's view of the same object.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

static inline BfmeMgrEHR *bfmeMgrEHRView(void)
{
	return (BfmeMgrEHR *)g_rva012F19E8WindowManager;
}

void *bfmeWinEHR(BfmeObjEHR *obj);

void bfmeReportEHR(BfmeObjEHR *obj)
{
	if (obj == 0)
		return;

	void *win = bfmeWinEHR(obj);
	bfmeMgrEHRView()->bfmeAddEHR(win, obj->m_bfmeTagEHR.bfmeTextEHR(), 1,
		obj->bfmeNameEHR().bfmeTextEHR(), 0, 0, 0, 0);
}
