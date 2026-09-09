// ??0Team@@QAE@PAVTeamPrototype@@I@Z
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Clean BFME reconstruction of ??0Team@@QAE@PAVTeamPrototype@@I@Z,
// retail RVA 0x000F7790 (631 bytes).
//
// The BFME member offsets are established by the Team save-game methods and
// the TeamPrototype instance-list family.  The storage-only helpers below
// preserve those offsets while keeping all calls to the existing STLport,
// relation-map, and StringBase<char> identities.

#define BFME_STLP_NODE_ALLOC
#include <list>
#include <vector>
#include <hash_map>
#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

// Canonical by-value forwarding shape.  concat() remains the real
// StringBase<char> method; no local AsciiString alias is attached to that
// shared retail body.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	using StringBase<char>::concat;
};

class Xfer;

// Existing relation-map constructor identities used by Team::Team.
class Rva000DA590PoolObject
{
public:
	Rva000DA590PoolObject() {}
	virtual ~Rva000DA590PoolObject();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class Rva000DA590Map : public Rva000DA590PoolObject
{
public:
	Rva000DA590Map();
	virtual ~Rva000DA590Map();
};

class TeamRelationPoolObject
{
public:
	TeamRelationPoolObject() {}
	virtual ~TeamRelationPoolObject();
};

class TeamRelationMap : public TeamRelationPoolObject
{
public:
	TeamRelationMap();
	virtual ~TeamRelationMap();
};

// Team+0x1C is the 20-byte hash storage established by Team::bfmeCall2440.
// The value is one byte; this is the STLport map shape whose clear body is the
// existing 0x000F1C80 family member.
typedef _STL::pair<const UnsignedInt, UnsignedByte> Rva000F75B0Pair;
typedef _STL::hash_map<UnsignedInt, UnsignedByte, _STL::hash<UnsignedInt>,
	_STL::equal_to<UnsignedInt>, _STL::allocator<Rva000F75B0Pair> >
	Rva000F75B0HashMember;

// The pending-ID list at +0x100 is the real STLport list used by the sibling
// load-post-process body.  The list14 member at +0x104 has a 0x14-byte node
// and a size word.

struct Rva000F7790Node14
{
	UnsignedByte m_flag;
	UnsignedByte m_pad01[3];
	UnsignedInt m_value;
	Rva000F7790Node14 *m_next;
	Rva000F7790Node14 *m_previous;
	UnsignedInt m_tail;
};

class Rva000F7790List14
{
public:
	Rva000F7790List14() : m_head(0)
	{
		m_head = _STL::__new_alloc::allocate(0x14);
		m_size = 0;
		Rva000F7790Node14 *node =
			reinterpret_cast<Rva000F7790Node14 *>(m_head);
		node->m_flag = 0;
		node->m_value = 0;
		node->m_next = node;
		node->m_previous = node;
	}
	~Rva000F7790List14();
private:
	void *m_head;
	UnsignedInt m_size;
};

struct Rva000F7790TeamTemplateInfo
{
	UnsignedByte m_pad00[0x7c];
	void *m_scriptOnAllClearData;
	void *m_scriptOnEnemySightedData;
	UnsignedByte m_tail[0x144 - 0x84];
};

class Team;

// BFME TeamPrototype slice.  The script fields are read only as StringBase
// data pointers; name and owner remain real four-byte AsciiString fields.
class TeamPrototype
{
public:
	void *m_vtable;
	void *m_factory;
	void *m_owner;
	UnsignedInt m_id;
	AsciiString m_name;
	AsciiString m_ownerName;
	UnsignedInt m_flags;
	UnsignedByte m_pad01c[0x12c - 0x1c];
	Rva000F7790TeamTemplateInfo m_template;
	void *m_attackPriorityName;
	Team *m_teamInstanceList;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, bool important);
};

extern ScriptEngine *TheScriptEngine;

class Team
{
public:
	Team(TeamPrototype *prototype, UnsignedInt id);

private:
	volatile void *m_vtable;                        // +0x00
	TeamPrototype *m_proto;                         // +0x04
	UnsignedInt m_id;                               // +0x08
	void *m_firstMember;                            // +0x0C
	Team *m_prevInPrototype;                        // +0x10
	Team *m_nextInPrototype;                        // +0x14
	UnsignedInt m_word18;                           // +0x18
	Rva000F75B0HashMember m_hashMember;             // +0x1C
	UnsignedByte m_flag30;                          // +0x30
	UnsignedByte m_flag31;                          // +0x31
	UnsignedByte m_flag32;                          // +0x32
	UnsignedByte m_flag33;                          // +0x33
	UnsignedByte m_flag34;                          // +0x34
	UnsignedByte m_flag35;                          // +0x35
	UnsignedByte m_flag36;                          // +0x36
	UnsignedByte m_flag37;                          // +0x37
	UnsignedInt m_word38;                           // +0x38
	UnsignedInt m_word3c;                           // +0x3C
	UnsignedInt m_word40;                           // +0x40
	UnsignedByte m_genericScriptFlags[0x20];       // +0x44
	void *m_genericScriptData[0x20];                // +0x64
	UnsignedByte m_byteE4;                          // +0xE4
	UnsignedByte m_byteE5;                          // +0xE5
	UnsignedByte m_byteE6;                          // +0xE6
	UnsignedByte m_byteE7;                          // +0xE7
	UnsignedInt m_commonAttackTarget;               // +0xE8
	TeamRelationMap *m_teamRelations;               // +0xEC
	Rva000DA590Map *m_playerRelations;              // +0xF0
	UnsignedInt m_wordF4;                            // +0xF4
	UnsignedInt m_wordF8;                            // +0xF8
	UnsignedByte m_byteFC;                           // +0xFC
	_STL::list<UnsignedInt> m_xferMemberIDList;     // +0x100
	Rva000F7790List14 m_list14;                     // +0x104
};

// ??0Team@@QAE@PAVTeamPrototype@@I@Z
Team::Team(TeamPrototype *prototype, UnsignedInt id)
	: m_vtable(reinterpret_cast<void *>(0x01085f88)),
	  m_proto(prototype),
	  m_id(id),
	  m_firstMember(0),
	  m_prevInPrototype(0),
	  m_nextInPrototype(0),
	  m_word18(0),
	  m_flag30(0),
	  m_flag31(0),
	  m_flag32(0),
	  m_flag33(0),
	  m_flag34(0),
	  m_flag35(0),
	  m_flag36(0),
	  m_flag37(0),
	  m_word38(0),
	  m_word3c(0),
	  m_word40(0),
	  m_byteE4(0),
	  m_byteE5(0),
	  m_byteE6(0),
	  m_byteE7(0),
	  m_wordF4(0),
	  m_wordF8(0),
	  m_byteFC(0)
{
	m_commonAttackTarget = 0;
	m_playerRelations = 0;
	m_playerRelations = new Rva000DA590Map;
	m_teamRelations = new TeamRelationMap;
	m_hashMember.clear();

	if (prototype)
	{
		if (prototype->m_teamInstanceList != this &&
			m_prevInPrototype == 0 && m_nextInPrototype == 0)
		{
			m_nextInPrototype = prototype->m_teamInstanceList;
			if (prototype->m_teamInstanceList)
				prototype->m_teamInstanceList->m_prevInPrototype = this;
			prototype->m_teamInstanceList = this;
		}

		void *script = prototype->m_template.m_scriptOnEnemySightedData;
		bool hasScript = script != 0 &&
			*reinterpret_cast<const unsigned short *>(
				reinterpret_cast<const char *>(script) + 4) != 0;
		if (!hasScript)
		{
			script = prototype->m_template.m_scriptOnAllClearData;
			hasScript = script != 0 &&
				*reinterpret_cast<const unsigned short *>(
					reinterpret_cast<const char *>(script) + 4) != 0;
		}
		if (hasScript)
		{
			m_flag34 = 1;
			AsciiString teamName(prototype->m_name);
			teamName.concat("/", 1);
			void *ownerData = *(void **)&prototype->m_ownerName;
			unsigned short ownerLength = ownerData ?
				*reinterpret_cast<const unsigned short *>(
					reinterpret_cast<const char *>(ownerData) + 4) : 0;
			const char *owner = ownerData ?
				reinterpret_cast<const char *>(ownerData) + 8 :
				reinterpret_cast<const char *>(0x0107388b);
			teamName.concat(owner, ownerLength);
			teamName.concat(" - creating team instance.", 0x1a);
			TheScriptEngine->AppendDebugMessage(teamName, false);
		}
	}

	for (UnsignedInt i = 0; i < 0x20; ++i)
	{
		m_genericScriptFlags[i] = 1;
		m_genericScriptData[i] = 0;
	}
}
