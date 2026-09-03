// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Owning destructor at the end of the d_00140de0 family.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

class Bfme0014AE40String : private AsciiString
{
public:
	Bfme0014AE40String(const AsciiString &other) : AsciiString(other) {}
	~Bfme0014AE40String() {}
};

class Bfme0014AE40Owned
{
public:
	virtual ~Bfme0014AE40Owned();
};

class Gen0014AE40
{
public:
	Gen0014AE40(AsciiString name);
	virtual ~Gen0014AE40();

private:
	Bfme0014AE40String m_bfmeMember;
	Bfme0014AE40Owned *m_bfmeOwned;
	void *m_bfmeOther;
};

Gen0014AE40::Gen0014AE40(AsciiString name) :
	m_bfmeMember(name),
	m_bfmeOwned(0),
	m_bfmeOther(0)
{
}

Gen0014AE40::~Gen0014AE40()
{
	if (m_bfmeOwned != 0)
		delete m_bfmeOwned;
	m_bfmeOwned = 0;
}
