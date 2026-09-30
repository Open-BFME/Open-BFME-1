// ??0OpenContainModuleData@@QAE@XZ
// partial score=1.0 date=2026-09-30
// ??0OpenContainModuleData@@QAE@XZ
// partial score=1.0 date=2026-09-30; EXACT modulo relocation slots only.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: ??0OpenContainModuleData@@QAE@XZ, retail 0x00227200, 398 bytes.
//
// OpenContainModuleData is the constructor identity evidenced by the callers.
// Two historical ledger names share this retail range; this is not proof of ICF.
// S4ModuleData0012A070Constructor.cpp and TransportContainModuleDataCtorThunk.cpp
// independently fix sizeof(OpenContainModuleData) at 0x168.
//
// Every member offset below is read off the body, not guessed: each one is a
// store or a subobject-construction site in the 398 bytes at 0x00227200.  Where
// a name would claim a meaning the bytes do not carry, the name keeps the
// offset.  What the body does prove is written next to each field.
//
// STATE: evidence only, not landed. Probe is 398/398 bytes, EXACT modulo relocations.
// Three levers recover the old bank's scheduling/register residue:
//   - unsigned words[3] cleared with memset at +0x12C;
//   - native STLport vector<AsciiString> at +0x158, explicit erase declaration;
//   - m_sounds.clear() before the plain +0x164 = 100 store.
//
// Landing blockers remain outside instruction shape:
// Rva002551A0DieMuxData and Gen003A0410 are redeclared without shared headers.
// AudioEventRTS is redeclared rather than using the canonical fuller layout.
// The native erase symbol is pinned at 0x00065960 while the ledger's real
// same-symbol body is 0x006FA560. No symbol pins were changed in this attempt.
// link_check could not run because this worktree has no link_index.pkl.
#include "ascii_string.h"

// The vptr-bearing base the body installs at +0x00.  Retail never touches
// +0x04, and the base's own constructor is trivial, so the derived constructor
// installs the derived vtable directly (the same elision
// LargeGroupBonusUpdateModuleDataCtor.cpp records for its base).
class OpenContainModuleDataBase
{
public:
	virtual ~OpenContainModuleDataBase();
};

// Already-landed base module data constructor, byte-verified at retail
// 0x002551A0 in game/GameEngine/Source/GameLogic/Object/Die/DieMuxDataConstructor.cpp.
// 0x2C bytes, which is exactly the gap retail leaves between the +0x08
// subobject-construction site and the +0x34 AudioEventRTS.
class Rva002551A0DieMuxData
{
public:
	Rva002551A0DieMuxData();

private:
	int m_deathTypes;
	int m_veterancyLevels;
	int m_exemptStatus[3];
	int m_requiredStatus[3];
	float m_damageAmountRequired;
	float m_minKillerAngle;
	float m_maxKillerAngle;
};

// Already-landed interned attribute handle, byte-verified at retail 0x003A0410
// in game/GameEngine/Source/GameLogic/Object/Update/Gen003A0410Constructor.cpp.
class Gen003A0410
{
public:
	Gen003A0410();
	~Gen003A0410();

private:
	unsigned int m_handle;
};

// BFME's AudioEventRTS is 0x70 bytes (vptr + 0x6C of storage) and its
// two-argument constructor is the retail call the body makes twice.  The
// mirrored declaration is game/GameEngineDevice/Source/W3DDevice/GameClient/
// Drawable/Draw/W3DTruckDrawConstructor.cpp.
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, int extra );
	virtual ~AudioEventRTS();

private:
	char m_storage[ 0x6C ];
};

// ?Rva01336E50EmptyString@@3VAsciiString@@B - the global the body pushes for
// both AudioEventRTS constructions.
extern const AsciiString Rva01336E50EmptyString;

// The first self-linked container, at +0x11C.  The body allocates exactly one
// 0x24-byte node, points both of the node's links at the node itself, and the
// object holds just the node pointer.
struct Rva00211CListNode
{
	Rva00211CListNode *m_next;
	Rva00211CListNode *m_prev;
	unsigned char m_value[ 0x1C ];
};

class Rva00211CList
{
public:
	~Rva00211CList();

	Rva00211CList()
	{
		m_node = 0;
		Rva00211CListNode *node = static_cast<Rva00211CListNode *>(
			::operator new( sizeof( Rva00211CListNode ) ) );
		node->m_next = node;
		node->m_prev = node;
		m_node = node;
	}

private:
	Rva00211CListNode *m_node;
};

// The second self-linked container, at +0x120.  The body allocates exactly one
// 0x3C-byte node, zeroes its two leading words, points the node's two links at
// the node itself, and the object holds the node pointer plus a zero word.  The
// node's leading word is written as a byte store and the second as a dword
// store, which is what the body does.
struct Rva002120ListNode
{
	unsigned char m_zero0;
	unsigned int m_zero4;
	Rva002120ListNode *m_next;
	Rva002120ListNode *m_prev;
	unsigned char m_rest[ 0x2C ];
};

class Rva002120List
{
public:
	~Rva002120List();

	Rva002120List()
	{
		m_node = 0;
		m_node = static_cast<Rva002120ListNode *>(
			::operator new( sizeof( Rva002120ListNode ) ) );
		m_word124 = 0;
		m_node->m_zero0 = 0;
		m_node->m_zero4 = 0;
		m_node->m_next = m_node;
		m_node->m_prev = m_node;
	}

private:
	Rva002120ListNode *m_node;
	unsigned int m_word124;
};

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
class Rva00212CThreePointer {
public:
 Rva00212CThreePointer() { memset(m_words,0,sizeof(m_words)); }
private:
 unsigned int m_words[3];
};
typedef _STL::vector<AsciiString> Rva002158StringVector;
template <> _STL::vector<AsciiString>::iterator
_STL::vector<AsciiString>::erase(iterator first, iterator last);

class OpenContainModuleData : public OpenContainModuleDataBase
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned int m_word04;                             // +0x04, untouched by retail
	Rva002551A0DieMuxData m_dieMuxData;                 // +0x08, ctor called
	AudioEventRTS m_enterSound;                         // +0x34, ctor called
	AudioEventRTS m_exitSound;                          // +0xA4, ctor called
	Gen003A0410 m_handle114;                            // +0x114, ctor called
	Gen003A0410 m_handle118;                            // +0x118, ctor called
	Rva00211CList m_list11C;                            // +0x11C
	Rva002120List m_list120;                            // +0x120
	unsigned int m_word128;                             // +0x128, untouched by retail
	Rva00212CThreePointer m_three12C;                   // +0x12C
	float m_real138;                                    // +0x138
	unsigned int m_zero13C;                             // +0x13C
	int m_containMax;                                   // +0x140
	int m_numberOfExitPaths;                            // +0x144
	unsigned int m_word148;                             // +0x148
	bool m_flag14C;                                     // +0x14C
	bool m_flag14D;                                     // +0x14D
	bool m_flag14E;                                     // +0x14E
	bool m_flag14F;                                     // +0x14F
	bool m_flag150;                                     // +0x150
	bool m_flag151;                                     // +0x151
	bool m_flag152;                                     // +0x152
	bool m_flag153;                                     // +0x153
	bool m_flag154;                                     // +0x154
	bool m_flag155;                                     // +0x155
	bool m_flag156;                                     // +0x156
	Rva002158StringVector m_sounds;                     // +0x158
	unsigned int m_doorOpenTime;                       // +0x164
};

// ??0OpenContainModuleData@@QAE@XZ
OpenContainModuleData::OpenContainModuleData()
	: m_enterSound( Rva01336E50EmptyString, 0 )
	, m_exitSound( Rva01336E50EmptyString, 0 )
{
	m_containMax = -1;
	m_real138 = -1000.0f;
	m_flag155 = false;
	m_numberOfExitPaths = 1;
	m_zero13C = 0;
	m_word148 = 1;
	m_flag14C = false;
	m_flag14D = true;
	m_flag14E = true;
	m_flag14F = true;
	m_flag150 = true;
	m_flag151 = true;
	m_flag152 = true;
	m_flag153 = false;
	m_flag154 = true;
	m_flag156 = false;
	m_sounds.clear();
	m_doorOpenTime = 100;
}

typedef char VerifyDieMuxSize[sizeof( Rva002551A0DieMuxData ) == 0x2C ? 1 : -1];
typedef char VerifyAudioSize[sizeof( AudioEventRTS ) == 0x70 ? 1 : -1];
typedef char VerifyHandleSize[sizeof( Gen003A0410 ) == 4 ? 1 : -1];
typedef char VerifyList11CSize[sizeof( Rva00211CList ) == 4 ? 1 : -1];
typedef char VerifyList120Size[sizeof( Rva002120List ) == 8 ? 1 : -1];
typedef char VerifyThree12CSize[sizeof( Rva00212CThreePointer ) == 12 ? 1 : -1];
typedef char VerifyVectorSize[sizeof( Rva002158StringVector ) == 12 ? 1 : -1];
typedef char VerifyObjectSize[sizeof( OpenContainModuleData ) == 0x168 ? 1 : -1];
