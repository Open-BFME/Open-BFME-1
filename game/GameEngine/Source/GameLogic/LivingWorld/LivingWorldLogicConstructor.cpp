// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// LivingWorldLogic constructor, retail 0x003C2FC0 (394 bytes); bases and members follow the retail unwind map.

#include <string.h>
#include <list>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "GameEngine/Source/Common/System/subsystem_interface.h"
#include "GameEngine/Source/Common/System/snapshot.h"

struct Rva003C15C0Element
{
	UnicodeString m_text;
	int m_word4;
	int m_word8;

	Rva003C15C0Element()
		: m_text(), m_word4(0), m_word8(3)
	{
	}
	~Rva003C15C0Element() {}
};

typedef _STL::list<Rva003C15C0Element> Rva003C15C0List;

// Region manager; its constructor 0x003C8880 is landed under this name.
class Rva003C8880
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	char m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

public:
	Rva003C8880();
};

class Rva000DD310Wide
{
public:
	~Rva000DD310Wide();

private:
	void *m_data;
};

struct Rva000DD310Fields
{
	char m_padding[0x14];
	Rva000DD310Wide m_wide;
	AsciiString m_tail;
};

struct Rva000DD310Entry
{
	AsciiString m_ascii;
	char m_padding[0x40];
	Rva000DD310Fields m_fields;

	~Rva000DD310Entry();
};

// Retail destroys +0x0C, +0x38, +0x50/+0x5C and +0x94 through four distinct
// 4-byte-element vector instantiations whose element types are not recovered.
typedef _STL::vector<int> Rva003C38Vector;
typedef _STL::vector<int> Rva003C0CVector;
typedef _STL::vector<int> Rva003C50Vector;
typedef _STL::vector<int> Rva003C5CVector;
typedef _STL::vector<Rva000DD310Entry> Rva003C68Vector;
typedef _STL::vector<unsigned short> Rva003C84Vector;
typedef _STL::vector<int> Rva003C94Vector;

class Rva003C18InitialState
{
public:
	Rva003C18InitialState()
		: m_word0(0), m_byte4(0), m_word8(0), m_wordC(0)
	{
	}

private:
	UnsignedInt m_word0;
	unsigned char m_byte4;
	unsigned char m_pad5[3];
	UnsignedInt m_word8;
	UnsignedInt m_wordC;
};

// Six words at +0xA8 cleared as one block before the list is built.
struct Rva003CA8Block
{
	UnsignedInt m_a8;
	UnsignedInt m_ac;
	UnsignedInt m_b0;
	UnsignedInt m_b4;
	UnsignedInt m_b8;
	UnsignedInt m_bc;

	Rva003CA8Block() { memset(this, 0, sizeof(*this)); }
};

class LivingWorldLogic : public SubsystemInterface, public Snapshot
{
public:
	LivingWorldLogic();
	// The retail destructor is provided by LivingWorldLogicDestructor.cpp.
	virtual ~LivingWorldLogic();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

private:
	Rva003C0CVector m_at0c;
	Rva003C18InitialState m_at18;
	Rva003C8880 *m_regionManager;
	unsigned char m_unk2c;
	unsigned char m_unk2d;
	unsigned char m_pad2e[2];
	AsciiString m_currentRegionName;
	UnsignedInt m_unk34;
	Rva003C38Vector m_at38;
	unsigned char m_at44;
	unsigned char m_at45;
	unsigned char m_pad46[2];
	UnsignedInt m_at48;
	unsigned char m_at4c;
	unsigned char m_at4d;
	unsigned char m_at4e;
	unsigned char m_pad4f;
	Rva003C50Vector m_at50;
	Rva003C5CVector m_at5c;
	Rva003C68Vector m_at68;
	UnsignedInt m_at74;
	unsigned char m_at78;
	unsigned char m_pad79[3];
	UnsignedInt m_at7c;
	unsigned char m_at80;
	unsigned char m_pad81[3];
	Rva003C84Vector m_at84;
	UnsignedInt m_at90;
	Rva003C94Vector m_at94;
	UnsignedInt m_a0;
	UnsignedInt m_a4;
	Rva003CA8Block m_atA8;
	Rva003C15C0List m_list;
	UnsignedInt m_c4;
	unsigned char m_c8;
	unsigned char m_padC9[3];
	UnsignedInt m_cc;
	UnsignedInt m_d0;
	UnsignedInt m_d4;
	UnsignedInt m_d8;
};

// ??0LivingWorldLogic@@QAE@XZ
LivingWorldLogic::LivingWorldLogic()
	: SubsystemInterface(), Snapshot()
	, m_at0c()
	, m_at18()
	, m_unk2c(0)
	, m_unk2d(1)
	, m_currentRegionName()
	, m_unk34(0)
	, m_at38()
	, m_at44(0)
	, m_at45(0)
	, m_at48(0)
	, m_at4c(0)
	, m_at4d(0)
	, m_at4e(0)
	, m_at50()
	, m_at5c()
	, m_at68()
	, m_at74(1)
	, m_at78(0)
	, m_at7c(0)
	, m_at80(0)
	, m_at84()
	, m_at90(1)
	, m_at94()
	, m_a0(1)
	, m_a4(0)
	, m_atA8()
	, m_list(0)
	, m_c4(0)
	, m_c8(0)
	, m_cc(0)
	, m_d0(0)
	, m_d4(0)
	, m_d8(0)
{
	m_regionManager = new Rva003C8880();
}
