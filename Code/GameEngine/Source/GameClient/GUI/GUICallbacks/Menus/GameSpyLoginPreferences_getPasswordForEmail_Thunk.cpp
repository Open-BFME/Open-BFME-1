// cl: /DNDEBUG /MD /EHsc
// readable body of ?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenu.cpp
// Open-BFME5: lift GameSpyLoginPreferences::getPasswordForEmail to clean C++.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

	static AsciiString TheEmptyString;

private:
	void *m_data;
};

struct PassMapNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

class PassMap
{
public:
	PassMapNode *find(const AsciiString &key);
	AsciiString &operator[](const AsciiString &key);
	PassMapNode *end() const { return m_header; }

private:
	PassMapNode *m_header;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	virtual ~UserPreferences();

private:
	unsigned char m_unreconstructed_04[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	AsciiString getPasswordForEmail(AsciiString email);

private:
	PassMap m_emailPasswordMap;
};

// ?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z
AsciiString GameSpyLoginPreferences::getPasswordForEmail(AsciiString email)
{
	if (m_emailPasswordMap.find(email) == m_emailPasswordMap.end())
		return AsciiString::TheEmptyString;
	return m_emailPasswordMap[email];
}
