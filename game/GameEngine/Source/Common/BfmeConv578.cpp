template <typename T> class StringBase
{
	friend class AsciiString;

	private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget(const AsciiString &name);
};

extern WindowManager *g_theWindowManager;

class BfmeThingCDA
{
public:
	void bfmeStepCDA();
	void bfmeGoCDA(void *what);

	unsigned char m_bfmeFlag;
	unsigned char m_bfmeReady;
	unsigned char m_bfmePad02[2];
	void *m_bfmeVal;
	unsigned char m_bfmeCommandReady;
	unsigned char m_bfmePad09[0x13];
	unsigned char m_bfmePortraitReady;
	unsigned char m_bfmePad1D[0x0b];
	void *m_bfmePortrait;
};

void j_00001f32();
void j_0002d817();
void j_0001587f();
void j_000361dd(int index);

class BfmeLayoutVHH
{
};

void bfmeGoVHH(char index, BfmeLayoutVHH *name);

class Gen_00588A30
{
public:
	void bfmeReset(int index);
};

void BfmeThingCDA::bfmeGoCDA(void *what)
{
	if (what != m_bfmeVal || !m_bfmeFlag)
	{
		bfmeStepCDA();
		m_bfmeVal = what;
		m_bfmeFlag = true;
	}
}

// ?bfmeStepCDA@BfmeThingCDA@@QAEXXZ
void BfmeThingCDA::bfmeStepCDA()
{
	if (m_bfmeReady)
	{
		if (m_bfmeCommandReady)
		{
			j_00001f32();
			m_bfmeCommandReady = 0;
		}

		j_0002d817();
		m_bfmePortraitReady = 0;
		j_0001587f();
		m_bfmeReady = 0;

		if (m_bfmePortrait != 0)
		{
			{
				AsciiString name("CommandUI/Portrait");
				g_theWindowManager->_bfme_removeNamedAptGadget(name);
			}
			m_bfmePortrait = 0;
		}

		AsciiString name;
		for (int index = 0; index < 6; ++index)
		{
			bfmeGoVHH((char)index, (BfmeLayoutVHH *)&name);
			g_theWindowManager->_bfme_removeNamedAptGadget(name);
		}
	}

	m_bfmeFlag = 0;
	m_bfmeVal = 0;
	for (int index = 0; index < 6; ++index)
		((Gen_00588A30 *)this)->bfmeReset(index);
}
