// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModuleInfo::Nugget dtor. dual strings: first@+0 body, tag@+4 ILT.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	unsigned char m_pad[4];
};

class ModuleTagString
{
public:
	~ModuleTagString();

private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
	class Nugget
	{
	public:
		~Nugget();

	private:
		AsciiString first;
		ModuleTagString m_moduleTag;
	};
};

// ??1Nugget@ModuleInfo@@QAE@XZ
ModuleInfo::Nugget::~Nugget()
{
}
