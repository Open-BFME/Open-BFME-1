// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
//
// BFME AptPalantir destructor at retail 0x0079D1D0.  The adjacent constructor
// installs the two AptPalantir tables, and TheAptPalantir is a 0x584-byte
// GameClient-derived object.  The three four-element Coord2D arrays are kept
// as real members so MSVC emits the retail eh-vector cleanup sequence.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class GameClient
	: public SubsystemInterface, public Snapshot
{
public:
	virtual ~GameClient();

private:
	char m_base[0x504];
};

class RefCountedPalantirMember
{
public:
	virtual void Release();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03(RefCountedPalantirMember *value);
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
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual bool slot122();
	int m_refCount;

	void releaseRef()
	{
		if (--m_refCount)
			return;
		Release();
	}
};

class TextureClass
{
public:
	void Release_Ref();
};

class AptPalantirTextureRef
{
public:
	~AptPalantirTextureRef()
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

class Coord2D
{
public:
	Coord2D();
	~Coord2D();

	float m_x;
	float m_y;
};

class Rva0079D1D0AptPalantir : public GameClient
{
public:
	virtual ~Rva0079D1D0AptPalantir();

private:
	RefCountedPalantirMember *m_member510;
	RefCountedPalantirMember *m_member514;
	RefCountedPalantirMember *m_member518;
	void *m_member51c;
	AptPalantirTextureRef m_texture520;
	Coord2D m_coords524[4];
	Coord2D m_coords544[4];
	Coord2D m_coords564[4];
};

// ??1AptPalantir@@UAE@XZ
Rva0079D1D0AptPalantir::~Rva0079D1D0AptPalantir()
{
	if (m_member510)
	{
		if (m_member518 && m_member518->slot122())
		{
			m_member510->slot03(m_member518);
		}
	}

	if (m_member518)
	{
		m_member518->releaseRef();
		m_member518 = 0;
	}

	if (m_member514)
	{
		m_member514->releaseRef();
		m_member514 = 0;
	}

	if (m_member510)
	{
		m_member510->releaseRef();
		m_member510 = 0;
	}
}
