// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BuffNuggetFXNugget destructor at 0x0042D7D0 (175B).
// Member offsets match the landed ctor thunk: six AsciiString templates
// at +0xC0..+0xD4, then the 12-byte tail at +0xE8, then the FXNugget base.
// The tail dtor is the ILT at 0x00026AB2 already pinned as
// ??1BuffNuggetFXNuggetMember@@QAE@XZ.

typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class BuffNuggetFXNuggetMember
{
public:
	BuffNuggetFXNuggetMember();
	~BuffNuggetFXNuggetMember();

	void *m_start;
	void *m_finish;
	void *m_end;
};

class __declspec(novtable) BuffNuggetFXNugget : public FXNugget
{
public:
	BuffNuggetFXNugget();
	virtual ~BuffNuggetFXNugget();

private:
	int m_buffType;
	Bool m_isComplexBuff;
	unsigned char m_padB9[3];
	UnsignedInt m_buffLifeTime;
	AsciiString m_buffThingTemplate;
	AsciiString m_buffOrcTemplate;
	AsciiString m_buffInfantryTemplate;
	AsciiString m_buffCavalryTemplate;
	AsciiString m_buffTrollTemplate;
	AsciiString m_buffMumakilTemplate;
	Real m_extrusion;
	RGBColor m_color;
	BuffNuggetFXNuggetMember m_member;
};

// ??1BuffNuggetFXNugget@@UAE@XZ
BuffNuggetFXNugget::~BuffNuggetFXNugget()
{
}
