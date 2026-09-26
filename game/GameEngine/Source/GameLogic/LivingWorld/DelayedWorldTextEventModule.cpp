// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

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
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );
};

class InGameUI
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
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	// BFME-only InGameUI slot 22 (+0x58).  Its body at 0x0043BC10
	// forwards these exact arguments to the world-text subsystem at +0x81C.
	virtual void rva0043BC10( const UnicodeString &text, Bool force );
};

extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;

class Xfer;

// BFME's Snapshot order is independently established by the Script and
// LivingWorldSound vtables.  This primary base accounts for slots 0-3; there
// is no secondary-base `this` adjustment on the slot-4 body reconstructed here.
class Snapshot
{
public:
	virtual ~Snapshot();

protected:
	virtual void loadPostProcess() = 0;
	virtual const char *getSnapshotName() const = 0;
	virtual void xfer( Xfer *xfer ) = 0;
};

class DelayedWorldTextEventModule : public Snapshot
{
public:
	virtual ~DelayedWorldTextEventModule();
	// Vtable 0x010ED9C0 slot 4 points at 0x003BC1E0.  No named caller
	// establishes the original spelling, so keep the method name neutral.
	virtual Bool rva003BC1E0();

private:
	// The constructor at 0x003BC090 writes an Int at +4 and a Bool at +8,
	// then copy-constructs this AsciiString at +0xC.  Normal alignment supplies
	// the three bytes between the Bool and string; none is modeled by hand.
	Int m_delayFrame;
	Bool m_flag;
	AsciiString m_text;
};

Bool DelayedWorldTextEventModule::rva003BC1E0()
{
	Bool textExists;
	UnicodeString localizedText = TheGameText->fetch( m_text, &textExists );
	if( !textExists )
		return false;

	TheInGameUI->rva0043BC10( localizedText, false );
	return true;
}
