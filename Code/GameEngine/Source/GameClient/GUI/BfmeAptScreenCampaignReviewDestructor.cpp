// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenCampaignReview destructor, retail 0x0050DBD0 (159 bytes).
// The CampaignReview constructor and callback name identify this cleanup
// body, which resets both interface vtables before it closes the screen.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[0x214];
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

class Shell
{
public:
	void hide(bool shutdownImmediate);
};

void _bfme_closeAptScreen(const AsciiString &name);

extern const void *BfmeAptScreenCampaignReviewVftable[];
extern const void *BfmeAptScreenCampaignReviewSecondaryVftable[];
extern Shell *TheShell;
extern void *g_obj12F495C;

class __multiple_inheritance BfmeAptScreenCampaignReview
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenCampaignReview();
};

BfmeAptScreenCampaignReview::~BfmeAptScreenCampaignReview()
{
	_bfme_closeAptScreen(AsciiString("AptCampaignReview:"));

	if(TheShell)
		TheShell->hide(false);

	g_obj12F495C = 0;
}
