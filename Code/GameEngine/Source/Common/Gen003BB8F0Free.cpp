// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The name is reconstruction-scoped and address-derived.  The matched caller
// at 0x003BB8F0 proves this helper's two-argument ABI: an Xfer interface and a
// pointer to the caller's ref-counted audio-info field.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class AsciiString
{
public:
	static const AsciiString TheEmptyString;

	char *m_data;
};

// Reconstruction aliases for the same one-word StringBase<char> layout.  The
// distinct names select the already-verified retail copy and const-char
// constructor bodies without claiming historical class spellings.
class AsciiStringVZ
{
public:
	AsciiStringVZ(const AsciiStringVZ &other);
	~AsciiStringVZ();

	char *m_data;
};

class AsciiStringYI
{
public:
	AsciiStringYI(const char *text);
	~AsciiStringYI();

	char *m_data;
};

extern const char g_bfmeEmptyAE[];

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	AsciiStringVZ m_name;
};

class Rva00087750Ref
{
public:
	Rva00087750Ref(const Rva00087750Ref &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			InterlockedIncrement(&m_ptr->m_refCount);
	}

	~Rva00087750Ref()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	Rva00087750Ref &operator=(const Rva00087750Ref &other);

	Rva00087750Counted *m_ptr;
};

class GenXferInterface
{
public:
	virtual void slot00(void *field);
	virtual bool isLoading();
	virtual void slot08(void *field);
	virtual void slot0C(void *field);
	virtual void slot10(void *field);
	virtual void slot14(void *field);
	virtual void slot18(void *field);
	virtual void slot1C(void *field);
	virtual void slot20(void *field);
	virtual void slot24(void *field);
	virtual void slot28(void *field);
	virtual void slot2C(void *field);
	virtual void slot30(void *field);
	virtual void slot34(void *field);
	virtual void slot38(void *field);
	virtual void slot3C(void *field);
	virtual void slot40(void *field);
	virtual void slot44(void *field);
	virtual void slot48(void *field);
	virtual void slot4C(void *field);
	virtual void slot50(void *field);
	virtual void slot54(void *field);
	virtual void slot58(void *field);
	virtual void slot5C(void *field);
	virtual void slot60(void *field);
	virtual void slot64(void *field);
	virtual void slot68(void *field);
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69();
	virtual Rva00087750Ref findAudioEventInfo(const AsciiStringYI &name) const;
};

extern AudioManager *TheAudio;

void Gen003BB8F0Free(GenXferInterface *xfer, void *fieldValue)
{
	Rva00087750Ref *field = static_cast<Rva00087750Ref *>(fieldValue);
	Rva00087750Ref saved(*field);

	const AsciiStringVZ &source = saved.m_ptr
		? saved.m_ptr->m_name
		: *reinterpret_cast<const AsciiStringVZ *>(&AsciiString::TheEmptyString);
	AsciiStringVZ name(source);

	xfer->slot68(&name);
	if (xfer->isLoading())
	{
		const char *text = name.m_data ? name.m_data + 8 : g_bfmeEmptyAE;
		*field = TheAudio->findAudioEventInfo(text);
	}
}
