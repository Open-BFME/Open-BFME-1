// ?getCDECount@BfmeOwnerCDE@@QAEHPAX@Z
// partial score=0.35 date=2026-09-27
// cl: /O2 /EHsc

template <typename T> class StringBase;

template <>
class StringBase<char>
{
    public:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<char> &other) : m_data(other.m_data) {}
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : public StringBase<char>
{
public:
	BFMERetailAsciiString() : StringBase<char>() {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : StringBase<char>(other) {}
	~BFMERetailAsciiString() { releaseBuffer(); }
};

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual Debug *slot20(float value);
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual Debug *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);
extern float g_bfmeDefaultBU;

Debug &operator<<(Debug &debug, const StringBase<char> &text);

struct Rva000FC640
{
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	float m_offsetX;
	float m_offsetY;
	float m_offsetZ;
	BFMERetailAsciiString m_name;
	bool m_enabled;
	char m_padding[3];

	Rva000FC640()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f), m_minorRadius(1.0f),
		  m_offsetX(0.0f), m_offsetY(0.0f), m_offsetZ(0.0f), m_name(), m_enabled(true)
	{
	}
};

class GeometryInfo
{
public:
	void rva0087E190(Rva000FC640 &out) const;
	bool getIsSmall() const { return m_isSmall; }

	void *m_vtable;
    bool m_isSmall;
};

class CDEVirtualBase
{
public:
	virtual GeometryInfo *getGeometryInfo();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
};

class CDELeading
{
public:
	virtual BFMERetailAsciiString getName();
};

class CDEProvider : public CDELeading, public virtual CDEVirtualBase
{
};

class BfmeShapeEU
{
public:
	int m_kind;
	char m_padding[4];
	float m_a;
	float m_b;
};

class BfmeHostEU
{
public:
	int bfmeStepsEU(const BfmeShapeEU *shape);

	char m_padding[0x20];
	float m_scale;
};

class BfmeOwnerCDE : public BfmeHostEU
{
public:
	int getCDECount(void *what);
};

// ?getCDECount@BfmeOwnerCDE@@QAEHPAX@Z
int BfmeOwnerCDE::getCDECount(void *what)
{
	CDEProvider *provider = (CDEProvider *)what;
	GeometryInfo *geometry = provider->getGeometryInfo();
	Rva000FC640 shape;
	geometry->rva0087E190(shape);

	if (geometry->getIsSmall())
	{
		int count = bfmeStepsEU((const BfmeShapeEU *)&shape);
		if (count >= 10000)
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				operator<<(*TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for "), provider->getName())
					.slot38(" is too large - INI error?\n")->slot4C(2);
			}
		}

		if (count <= 4)
			return 4;

		switch (shape.m_type)
		{
		case 2:
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				operator<<(*TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for "), provider->getName())
					.slot38(" is too large for a small object.\nReduce the length of the diagonal of the box to a value less than ")
					->slot20(g_bfmeDefaultBU / (m_scale + m_scale))
					->slot38(" or make the geometry non-small.\nThe diagonal is calculated as SquareRoot( MajorRad*MajorRad + MinorRad*MinorRad ).")->slot4C(2);
			}
			return 4;

		case 0:
		case 1:
		{
			if (_bfme_debugReportingEnabled())
			{
				_bfme_debugRecordCallsite(1);
				TheBfmeAwakenDebug->slot60();
				operator<<(*TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for "), provider->getName())
					.slot38(" is too large for a small object.\nReduce major radius to a value less than ")
					->slot20(g_bfmeDefaultBU / (m_scale + m_scale))
					->slot38(" or make the geometry non-small.\n")->slot4C(2);
			}
			return 4;
		}
		default:
			return 4;
		}

		return 4;
	}

	int count = bfmeStepsEU((const BfmeShapeEU *)&shape);
	if (count >= 10000)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			operator<<(*TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for "), provider->getName())
				.slot38(" is too large - INI error?\n")->slot4C(2);
		}
	}
	return count;
}
