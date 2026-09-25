// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME: anonymous APT movie-property callback at retail 0x00465770
// (487 bytes, __cdecl). It reads "_MovieName", "_Loop", "_UseAlpha",
// "_HoldLastFrame" and "_CallOnLastFrame" out of the query string through
// bfmeGetParamVMZ (retail 0x0046EFA0 via ILT 0x0003C1B4), copies the
// _CallOnLastFrame value into the AsciiString at window+0x268, and sends the
// assembled message to TheWindowManager->winSendSystemMsg (vtable+0xD4) with
// message 0x1D and data 1000. No caller, vtable slot or twin names the body or
// its owner, so the name keeps the address token.

extern "C" unsigned strlen(const char *);
#pragma intrinsic(strlen)

// retail AsciiString view: buffer header with the length word at +4 and the
// characters at +8, inlined by retail at every check below
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void set(const char *text, int length);
	void set(const BFMERetailAsciiString &other);
	const char *str() const { return m_data ? m_data + 8 : ""; }
	unsigned getLength() const { return m_data ? *(const unsigned short *)(m_data + 4) : 0; }

private:
	void releaseBuffer();

	const char *m_data;
};

class BfmeStrVMZ;
char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);
void j_00030477();

class GameWindow;
struct Rva00465770MovieMessage;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52();
	virtual int winSendSystemMsg(GameWindow *window, unsigned message,
		unsigned data1, Rva00465770MovieMessage *data2);	// slot 53, vtable+0xD4
};

extern GameWindowManager *TheWindowManager;

// the 16-byte message block built on the stack and passed as data2
struct Rva00465770MovieMessage
{
	Rva00465770MovieMessage() : flags(0), callback(0), window(0) {}

	BFMERetailAsciiString movieName;	// +0x0 the "_MovieName" value
	unsigned flags;				// +0x4 bits 0x4 / 0x40 / 0x80
	void (*callback)();			// +0x8 ILT 0x00030477 (body 0x00465670)
	GameWindow *window;			// +0xC the window argument
};

static inline BfmeStrVMZ *asParam(BFMERetailAsciiString *s)
{
	return reinterpret_cast<BfmeStrVMZ *>(s);
}

static inline bool containsT(const BFMERetailAsciiString &s)
{
	const char *p = s.str();
	const char *end = p + s.getLength();
	for (; p != end; ++p)
		if (*p == 't')
			return true;
	return false;
}

// ?Rva00465770MovieProperties@@YAXPAXPBDPAVGameWindow@@@Z
// The first parameter is unused in retail; only the query and window are read.
void Rva00465770MovieProperties(void *, const char *query, GameWindow *window)
{
	if (!window)
		return;

	BFMERetailAsciiString param;
	Rva00465770MovieMessage msg;
	char found = bfmeGetParamVMZ(query, "_MovieName", asParam(&param));
	if (found != 0)
	{
		const char *movie = param.str();
		unsigned length = movie ? strlen(movie) : 0;
		msg.movieName.set(movie, length);
		bfmeGetParamVMZ(query, "_Loop", asParam(&param));
		if (containsT(param))
			msg.flags |= 4;
		bfmeGetParamVMZ(query, "_UseAlpha", asParam(&param));
		if (containsT(param))
			msg.flags |= 0x40;
		bfmeGetParamVMZ(query, "_HoldLastFrame", asParam(&param));
		if (containsT(param))
			msg.flags |= 0x80;
		if (bfmeGetParamVMZ(query, "_CallOnLastFrame", asParam(&param)))
		{
			BFMERetailAsciiString &callOnLastFrame =
				*reinterpret_cast<BFMERetailAsciiString *>((char *)window + 0x268);
			callOnLastFrame.set(param);
			msg.callback = j_00030477;
			msg.window = window;
		}
		TheWindowManager->winSendSystemMsg(window, 0x1D, 1000, &msg);
	}
}
