// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Owning destructor at the end of the d_00140de0 family.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString
{
public:
	// Retail inlines this forwarder, so the call site encodes
	// StringBase<char>'s copy ctor at 0x00887B60 directly.
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
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
