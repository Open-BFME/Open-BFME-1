// ?_bfme_initGadgets@BfmeAptScreenCampaignReview@@QAEXXZ
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
//
// CampaignReview.apt InitGadgets callback, retail 0x0050DCF0 (456 bytes).
// The CampaignReview constructor at 0x0050E320 binds this method to
// AptCampaignReview::InitGadgets.  The callback classifies the Living World
// result list and writes the corresponding translated result into the APT
// variable APT:CmpgnRevResult.

#include "StringInline.h"

typedef bool Bool;

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;
extern class GameTextInterface *TheGameText;

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 );
};

class Rva003BEDD0
{
public:
	int classify();
};

// The global at 0x012F1028 is the CampaignObject/Living World result owner.
// Its classify body is the matched Rva003BEDD0 method at 0x003BEDD0.
#define TheLivingWorldLogic (*(Rva003BEDD0 **)0x012F1028)

class BfmeAptScreenCampaignReview
{
public:
	void _bfme_initGadgets();
};

// ?_bfme_initGadgets@BfmeAptScreenCampaignReview@@QAEXXZ
void BfmeAptScreenCampaignReview::_bfme_initGadgets()
{
	if( TheLivingWorldLogic == 0 )
	{
		g_theWindowManager->bfme_setAptText(
			AsciiString( "APT:CmpgnRevResult" ),
			*(const UnicodeString *)0x01336E54 );
		return;
	}

	int result = TheLivingWorldLogic->classify();
	if( result == 2 )
	{
		AsciiString variableName( "APT:CmpgnRevResult" );
		UnicodeString text = TheGameText->fetch( "APT:TotalVictoryCaps", 0 );
		g_theWindowManager->bfme_setAptText( variableName, text );
	}
	else if( result == 1 )
	{
		AsciiString variableName( "APT:CmpgnRevResult" );
		UnicodeString text = TheGameText->fetch( "APT:VictoryCaps", 0 );
		g_theWindowManager->bfme_setAptText( variableName, text );
	}
	else if( result == 0 )
	{
		AsciiString variableName( "APT:CmpgnRevResult" );
		UnicodeString text = TheGameText->fetch( "APT:SurvivedCaps", 0 );
		g_theWindowManager->bfme_setAptText( variableName, text );
	}
	else
	{
		AsciiString variableName( "APT:CmpgnRevResult" );
		g_theWindowManager->bfme_setAptText(
			variableName, *(const UnicodeString *)0x01336E54 );
	}
}
