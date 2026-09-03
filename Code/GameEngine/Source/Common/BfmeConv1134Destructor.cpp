// cl: /DNDEBUG /MD /EHsc
//
// Destructor of BfmeA1134. The constructor TU zeros the same slots that the
// string default ctor would; this TU is the unwind: five AsciiString members
// in reverse declaration order, then the SubsystemInterface base.

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() {}

	StringBase<char> m_string;
};

template <int N>
class BfmeGap1134
{
public:
	char m_bytes[N];
};

class BfmeBase1134
{
public:
	virtual ~BfmeBase1134();

private:
	int m_bfme04;
};

class BfmeA1134 : public BfmeBase1134
{
public:
	virtual ~BfmeA1134();

	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	BfmeGap1134<0xC> m_pad14;
	AsciiString m_at20;
	BfmeGap1134<0x78> m_pad24;
	AsciiString m_at9c;
};

// ??1BfmeA1134@@UAE@XZ
BfmeA1134::~BfmeA1134()
{
}
