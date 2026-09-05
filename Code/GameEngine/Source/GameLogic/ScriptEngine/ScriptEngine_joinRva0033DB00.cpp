// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0033DB00. No matched caller names this helper; the body is
// helper3398F0(name) + "/" + name. The joining method uses an address-derived name.

template <typename T>
struct StringHeader
{
	int ref_count;
	unsigned short length;
	unsigned short capacity;
	T data[1];
};

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void concat(const T *str, int len);

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase();

	StringHeader<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	const char *str() const { return m_data ? m_data->data : ""; }
	int getLength() const { return m_data ? m_data->length : 0; }
	void concat(const char *str, int len)
	{
		((StringBase<char> *)this)->concat(str, len);
	}
};

class BFMEScriptEngineFlagLookup
{
	AsciiString canonicalFlagName(const AsciiString &name);

public:
	AsciiString joinRva0033DB00(AsciiString name);
};

// ?joinRva0033DB00@BFMEScriptEngineFlagLookup@@QAE?AVAsciiString@@V2@@Z
AsciiString BFMEScriptEngineFlagLookup::joinRva0033DB00(AsciiString name)
{
	AsciiString canonical = canonicalFlagName(name);
	__declspec(align(4)) char slash = '/';
	canonical.concat(&slash, 1);
	canonical.concat(name.str(), name.getLength());
	return canonical;
}
