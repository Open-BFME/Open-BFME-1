// cl: /DNDEBUG /MD /EHsc
// readable body of ?getPasswordForEmail@GameSpyLoginPreferences@@QAE?AVAsciiString@@V2@@Z: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLLoginMenu.cpp
// Open-BFME5: lift GameSpyLoginPreferences::getPasswordForEmail to clean C++.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
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
