// cl: /EHsc

// W3DStreakDrawModuleData's matched constructor places its AsciiString texture
// name at +0x20.  Destruction restores the module-data base vptr after tearing
// down that string, exactly as the retail EH-protected body does.

class AsciiString
{
public:
	~AsciiString();
};

class W3DStreakDrawModuleDataBase
{
public:
	virtual ~W3DStreakDrawModuleDataBase() {}

private:
	unsigned int m_word;
};

class W3DStreakDrawModuleData : public W3DStreakDrawModuleDataBase
{
public:
	virtual ~W3DStreakDrawModuleData();

private:
	unsigned char m_fields08[ 0x18 ];
	AsciiString m_textureName;
};

W3DStreakDrawModuleData::~W3DStreakDrawModuleData()
{
}
