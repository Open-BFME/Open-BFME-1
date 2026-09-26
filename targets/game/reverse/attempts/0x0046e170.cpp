// ?run@Rva0046E170Owner@@QAEXXZ
// partial score=0.45 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Anonymous WindowManager-like APT/JPEG overlay body, retail 0x0046E170,
// size 371. Identity: only address-derived caller evidence (banked
// 0x0046E850 attempt); no proven owner class or method name, so this stays
// an address-keyed free function. Callees: AsciiString(const char*) ctor
// (0x00888BC0 x3), AsciiString::format (0x00888FF0 x2), releaseBuffer
// (0x00887940 x2), a pinned hashtable find (0x00014D49) and a pinned
// GenActionSink::add-style registrar (0x00015235). Globals: g_bfmeJpegSingle
// Message (0x01080FC0) and g_bfmeJpegExtendedMessage (0x01081238).

typedef bool Bool;
typedef int Int;

class BfmeRetString
{
public:
	BfmeRetString(const char *text);			// retail 0x00888BC0
	~BfmeRetString() { releaseBuffer(); }

	void __cdecl format(BfmeRetString fmt, ...);		// retail 0x00888FF0

private:
	void releaseBuffer();					// retail 0x00887940
	void *m_data;
};

class Rva0046E170HashEntry;
class Rva0046E170Hashtable
{
public:
	Rva0046E170HashEntry *find(const BfmeRetString &key);	// pinned retail 0x00014D49
};

class Rva0046E170ActionSink
{
public:
	void add(void *arg1, const char *arg2, Int arg3, void *arg4, Int arg5,
		Int arg6, Int arg7, Int arg8, Int arg9);	// pinned retail 0x00015235
};

struct Rva0046E170Slot
{
	unsigned char m_flags;
	unsigned char m_pad[0x13];
};

class Rva0046E170Owner : public Rva0046E170ActionSink
{
public:
	void run();

private:
	unsigned char m_pad004[0x19c];
	Rva0046E170Hashtable *m_table;				// +0x19c
	unsigned char m_pad1a0[4];
	Bool m_needsRefresh;					// +0x1a4
};

extern int g_bfmeJpegSingleMessage;				// VA 0x01080FC0
extern int g_bfmeJpegExtendedMessage;				// VA 0x01081238

void Rva0046E170Owner::run()
{
	Rva0046E170HashEntry *found = 0;

	if (m_needsRefresh)
	{
		m_needsRefresh = false;

		Rva0046E170Hashtable *table = m_table;
		found = table->find(BfmeRetString("APT"));

		BfmeRetString message(found ? "%s" : "Duplicate JPEG name: %s");
		message.format(BfmeRetString(found ? "%s" : "Duplicate JPEG name: %s"));
	}

	Rva0046E170Slot *slots = (Rva0046E170Slot *)((unsigned char *)this + 0xb8);
	for (int i = 0; i < 12; ++i)
	{
		unsigned char flags = slots[i].m_flags;
		bool hasBit1 = (flags & 2) != 0;
		if (hasBit1)
		{
			bool wantBit3 = (found != 0);
			bool haveBit3 = (flags & 8) != 0;
			if (wantBit3 != haveBit3)
			{
				flags ^= 8;
				slots[i].m_flags = flags;

				int *msg = wantBit3 ? &g_bfmeJpegExtendedMessage : &g_bfmeJpegSingleMessage;
				this->add(0, 0, 1, msg, 0, 0, 0, 0, i);
			}
		}
	}
}
