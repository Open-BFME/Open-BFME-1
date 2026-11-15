#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenCampaignReview destructor, retail 0x0050DBD0 (159 bytes).
// The CampaignReview constructor and callback name identify this cleanup
// body, which resets both interface vtables before it closes the screen.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
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

class __multiple_inheritance AptCampaignReview
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~AptCampaignReview();
};

AptCampaignReview::~AptCampaignReview()
{
	_bfme_closeAptScreen(AsciiString("AptCampaignReview::InitGadgets"));

	if(TheShell)
		TheShell->hide(false);

	g_obj12F495C = 0;
}
