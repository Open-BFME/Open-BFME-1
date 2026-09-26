// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Rva003BF540::applyOwner, retail 0x003BF190, 444 bytes.
//
// Identity: reviewed ILT 0x00025798 and the three calls from the matched
// Rva003BF540::run at 0x003BF3C0. The body forwards the node to
// Rva003BF540::run(arg) (0x003BF010), then under the same gates run uses
// (campaign open, allowed, not disabled, none ready, a control bar) looks the
// node's name (0x003A4390, the string at node +0x04) up in the game logic
// (0x00383890), builds a label from it (0x003870F0), appends "Army" unless the
// node byte at +0x44 is set, fetches the label's text through GameText slot 9
// when the label is non-empty, and hands a temporary 12-byte message (ctor
// 0x003BD700, dtor 0x003BD770) to the control bar (0x004C15D0).
//
// An empty label still posts the message, with empty text: retail's isEmpty
// branch jumps past the fetch straight to the message construction.

#include "ascii_string.h"
#include "unicode_string.h"

inline AsciiString::~AsciiString()
{
	((StringBase<char> *)this)->releaseBuffer();
}
inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &other)
{
	((StringBase<unsigned short> *)this)->set(
		*(const StringBase<unsigned short> *)&other);
	return *this;
}

class Glo012F706CType
{
public:
	bool isOpen() const;
};

extern Glo012F706CType *g_bfmeGameCW;

class Gen_00609320
{
public:
	unsigned char bfmeDisabled() const;
};

extern Gen_00609320 *g_bfmeStateDF;

class Rva003BF010Arg;

class Gen003BD7D0Node
{
public:
	AsciiString rva003a4390();

	char m_pad00[0x44];
	bool m_at44;
};

struct Rva00367E30Logic
{
	int rva00383890(const AsciiString &name);
	AsciiString rva003870f0(const AsciiString &name);
};

extern Rva00367E30Logic *TheBfmeGameLogic;

// Constructed by 0x003BD700 (vptr, wide string copy at +4, int at +8) and
// destroyed by 0x003BD770 in the same caller frame slot.
class Rva003BD770
{
public:
	Rva003BD770(const UnicodeString &text, int id);
	~Rva003BD770();

private:
	void *m_at00;
	UnicodeString m_text;
	int m_id;
};

class ControlBar
{
public:
	void rva004c15d0(const Rva003BD770 &message);
};

extern ControlBar *TheControlBar;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	virtual UnicodeString fetch(AsciiString label, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class Rva003BF540
{
public:
	void run(Rva003BF010Arg *arg);
	bool allowed();
	bool anyReady() const;
	void applyOwner(Gen003BD7D0Node *owner);
};

void Rva003BF540::applyOwner(Gen003BD7D0Node *owner)
{
	run((Rva003BF010Arg *)owner);

	if (owner == 0 || !g_bfmeGameCW->isOpen() || !allowed()
		|| g_bfmeStateDF->bfmeDisabled() || anyReady() || TheControlBar == 0)
		return;

	int id = TheBfmeGameLogic->rva00383890(owner->rva003a4390());
	if (id < 0)
		return;

	AsciiString label = TheBfmeGameLogic->rva003870f0(owner->rva003a4390());
	if (!owner->m_at44)
		label += "Army";

	UnicodeString text;
	if (!label.isEmpty())
		text = TheGameText->fetch(label);

	TheControlBar->rva004c15d0(Rva003BD770(text, id));
}
