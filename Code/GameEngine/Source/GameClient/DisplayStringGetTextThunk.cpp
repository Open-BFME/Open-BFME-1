// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DisplayString::getText returns UnicodeString member at +4.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const UnicodeString &);
	~UnicodeString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText();
private:
	UnicodeString m_text;
};

// ?getText@DisplayString@@UAE?AVUnicodeString@@XZ
UnicodeString DisplayString::getText()
{
	return m_text;
}
