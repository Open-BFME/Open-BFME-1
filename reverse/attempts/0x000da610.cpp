// ?init@Player@@QAEXPBVPlayerTemplate@@@Z
// partial score=0.2 date=2026-09-19
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep
//
// BFME body conversion for 0x000DA610.  The retail boundary is 2056 bytes:
// the SEH frame starts at +0x00 and the contiguous end is `ret 4` at +0x805.
// The caller evidence names this body Player::init(const PlayerTemplate*):
// PlayerList::init calls the 0x00020AEA ILT, and the retail body stores the
// template at Player+0x04 before touching the BFME-only team list at +0x288.
//
// This is deliberately a raw BFME layout view.  The vendored ZH Player class
// puts several of these fields at different offsets, so using its member names
// here would make a plausible but wrong identity invisible to the byte gate.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

#include <new>
#include <string.h>

class PlayerTemplate;

class Player
{
public:
	void init(const PlayerTemplate *pt);
};

template <class Character>
class StringBase
{
public:
	void releaseBuffer();
	void set(const StringBase<Character> &other);
};

class BFMERetailAsciiString
{
public:
	void releaseBuffer();
	void *m_data;
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);
};

class RetailLayoutString
{
public:
	void set(const char *text, Int length);
};

class RawVirtualDelete
{
public:
	virtual void deleteInstance(Bool destroy);
};

class Rva000C8440
{
public:
	void reset();
};

class Rva000FB1F0
{
public:
	void forward();
};

class Rva000C81E0
{
public:
	void reset();
};

class Rva000D95C0Player
{
public:
	void applyInitialUpgrades();
};

class Rva000DA590Map
{
public:
	Rva000DA590Map();
	void *m_vtable;
	unsigned char m_storage[0x14];
};

class TeamRelationMap
{
public:
	TeamRelationMap();
	void *m_vtable;
	unsigned char m_storage[0x14];
};

class ScoreKeeper
{
public:
	void reset(Int playerIndex);
};

class Money
{
public:
	void deposit(UnsignedInt amount, Bool fromTemplate);
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *memory, unsigned int bytes);
};
}

class NameKeyGenerator
{
public:
	UnsignedInt nameToKey(const char *name);
};

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom(const GameSpyGroupRoom &other);
	BFMERetailAsciiString m_name;
	void *m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
	Int m_bfmeExtra;
};

// These are the exact ILT names printed by tools/callees.py.  The argument
// carrying calls are represented by their resolved typed helpers above where
// the destination ABI is independently landed; the remaining generated calls
// stay address-named until their own bodies are recovered.
extern void j_0000ce7d();
extern void j_0002ca16();
extern void j_0001d4b7();
extern void j_0000bbf9();
extern void j_00035da0();
extern void j_0003481f();
extern void j_00037880();
extern void j_0001219d();
extern void j_0002cf16();

struct RawListNode
{
	RawListNode *m_next;
	RawListNode *m_prev;
	void *m_value;
};

struct RawVector
{
	unsigned char *m_begin;
	unsigned char *m_end;
	unsigned char *m_capacity;
};

struct RawAllocatedBlock
{
	UnsignedInt m_vtable;
	UnsignedInt m_words[6];
};

struct RawPlayerStorage
{
	unsigned char m_data[0x6a0];
};

template <class T>
static __forceinline T &playerField(Player *player, unsigned int offset)
{
	return *reinterpret_cast<T *>(reinterpret_cast<unsigned char *>(player) + offset);
}

template <class T>
static __forceinline const T &playerField(const Player *player,
	unsigned int offset)
{
	return *reinterpret_cast<const T *>(reinterpret_cast<const unsigned char *>(player) + offset);
}

static __forceinline void releaseVirtual(RawVirtualDelete *object)
{
	if (object != 0)
		object->deleteInstance(true);
}

static __forceinline void clearNodeList(RawListNode *head, unsigned int bytes)
{
	if (head == 0)
		return;

	RawListNode *node = head->m_next;
	while (node != head)
	{
		RawListNode *next = node->m_next;
		operator delete(node);
		node = next;
	}
	head->m_next = head;
	head->m_prev = head;
	(void)bytes;
}

static __forceinline void initialiseAllocatedBlock(void **slot,
	UnsignedInt vtable)
{
	if (*slot != 0)
		releaseVirtual(reinterpret_cast<RawVirtualDelete *>(*slot));

	RawAllocatedBlock *block = reinterpret_cast<RawAllocatedBlock *>(
		operator new(0x1c));
	if (block != 0)
	{
		block->m_vtable = vtable;
		for (Int i = 0; i < 6; ++i)
			block->m_words[i] = 0;
	}
	*slot = block;
}

// The target's generated helpers are all no-argument ILT symbols.  Keep their
// address-derived spelling while retaining the receiver field in the source;
// the helper bodies themselves own the exact sub-object ABI.
class Rva0000CE7DReceiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva0000CE7DReceiver@@QAEXXZ=?j_0000ce7d@@YAXXZ")

class Rva0001D4B7Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva0001D4B7Receiver@@QAEXXZ=?j_0001d4b7@@YAXXZ")

class Rva0002CA16Receiver
{
public:
	void invoke(const void *source);
};
#pragma comment(linker, "/alternatename:?invoke@Rva0002CA16Receiver@@QAEXPBX@Z=?j_0002ca16@@YAXXZ")

class Rva0000BBF9Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva0000BBF9Receiver@@QAEXXZ=?j_0000bbf9@@YAXXZ")

class Rva00035DA0Receiver
{
public:
	void invoke(const void *source);
};
#pragma comment(linker, "/alternatename:?invoke@Rva00035DA0Receiver@@QAEXPBX@Z=?j_00035da0@@YAXXZ")

class Rva0003481FReceiver
{
public:
	void invoke(const void *value);
};
#pragma comment(linker, "/alternatename:?invoke@Rva0003481FReceiver@@QAEXPBX@Z=?j_0003481f@@YAXXZ")

class Rva00037880Receiver
{
public:
	void invoke(const void *value);
};
#pragma comment(linker, "/alternatename:?invoke@Rva00037880Receiver@@QAEXPBX@Z=?j_00037880@@YAXXZ")

class Rva0001219DReceiver
{
public:
	int *invoke(const int &key);
};
#pragma comment(linker, "/alternatename:?invoke@Rva0001219DReceiver@@QAEPAHPBH@Z=?j_0001219d@@YAXXZ")

class Rva0002CF16Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva0002CF16Receiver@@QAEXXZ=?j_0002cf16@@YAXXZ")

class Rva000201A3Receiver
{
public:
	void invoke(const void *source);
};
#pragma comment(linker, "/alternatename:?invoke@Rva000201A3Receiver@@QAEXPBX@Z=?j_000201a3@@YAXXZ")

class Rva00047203Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva00047203Receiver@@QAEXXZ=?j_00047203@@YAXXZ")

class Rva00018679Receiver
{
public:
	void invoke(Int field, Bool flag);
};
#pragma comment(linker, "/alternatename:?invoke@Rva00018679Receiver@@QAEXH_N@Z=?j_00018679@@YAXXZ")

class Rva000A2F4Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva000A2F4Receiver@@QAEXXZ=?j_0000a2f4@@YAXXZ")

class Rva00043022Receiver
{
public:
	void invoke();
};
#pragma comment(linker, "/alternatename:?invoke@Rva00043022Receiver@@QAEXXZ=?j_00043022@@YAXXZ")

class Rva00043C43Receiver
{
public:
	int *invoke(const void *key);
};
#pragma comment(linker, "/alternatename:?invoke@Rva00043C43Receiver@@QAEPAHPBX@Z=?j_00043c43@@YAXXZ")

void Player::init(const PlayerTemplate *pt)
{
	playerField<const PlayerTemplate *>(this, 0x04) = pt;
	Player *self = this;

	// PlayerTeamList is a one-pointer STLport list at +0x288.  Its node is
	// 0x0c bytes, exactly the allocator contract in the retail body.
	RawListNode *teamHead = playerField<RawListNode *>(self, 0x288);
	{
		RawListNode *node = teamHead->m_next;
		while (node != teamHead)
		{
			RawListNode *next = node->m_next;
			_STL::__node_alloc<true, 0>::_M_deallocate(node, 0x0c);
			node = next;
		}
		teamHead->m_next = teamHead;
		teamHead->m_prev = teamHead;
	}

	playerField<StringBase<unsigned short> >(self, 0x08).releaseBuffer();
	reinterpret_cast<Rva0000CE7DReceiver *>(self)->invoke();

	playerField<Int>(self, 0x58) = 0;
	playerField<Int>(self, 0x5c) = 0;
	playerField<UnsignedByte>(self, 0x60) = 0;
	playerField<Int>(self, 0x64) = 0;
	playerField<Int>(self, 0x68) = 0;
	playerField<Int>(self, 0x6c) = 0;
	if (playerField<RawVirtualDelete *>(self, 0x70) != 0)
	{
		playerField<RawVirtualDelete *>(self, 0x70)->deleteInstance(true);
		playerField<RawVirtualDelete *>(self, 0x70) = 0;
	}
	playerField<Int>(self, 0xa8) = 0;
	playerField<Int>(self, 0xac) = 0;
	playerField<Player *>(self, 0xb0) = self;
	reinterpret_cast<Rva000C8440 *>(reinterpret_cast<unsigned char *>(self) + 0xb4)->reset();

	if (playerField<RawVirtualDelete *>(self, 0x1c0) != 0)
	{
		playerField<RawVirtualDelete *>(self, 0x1c0)->deleteInstance(true);
		playerField<RawVirtualDelete *>(self, 0x1c0) = 0;
	}
	if (playerField<RawVirtualDelete *>(self, 0x220) != 0)
	{
		playerField<RawVirtualDelete *>(self, 0x220)->deleteInstance(true);
		playerField<RawVirtualDelete *>(self, 0x220) = 0;
	}
	playerField<Int>(self, 0x224) = 0;
	if (playerField<RawVirtualDelete *>(self, 0x228) != 0)
	{
		playerField<RawVirtualDelete *>(self, 0x228)->deleteInstance(true);
		playerField<RawVirtualDelete *>(self, 0x228) = 0;
	}
	if (playerField<RawVirtualDelete *>(self, 0x22c) != 0)
	{
		playerField<RawVirtualDelete *>(self, 0x22c)->deleteInstance(true);
		playerField<RawVirtualDelete *>(self, 0x22c) = 0;
	}
	playerField<Int>(self, 0x230) = 0;
	playerField<Int>(self, 0x260) = 0;

	RawVector &unidentifiedVector = playerField<RawVector>(self, 0x27c);
	if (unidentifiedVector.m_begin != unidentifiedVector.m_capacity)
	{
		UnsignedInt bytes = static_cast<UnsignedInt>(
			unidentifiedVector.m_capacity - unidentifiedVector.m_begin);
		memmove(unidentifiedVector.m_begin, unidentifiedVector.m_end, bytes);
		unidentifiedVector.m_capacity = unidentifiedVector.m_begin + bytes;
	}
	unidentifiedVector.m_begin = 0;

	if (playerField<RawVirtualDelete *>(self, 0x28c) != 0)
		playerField<RawVirtualDelete *>(self, 0x28c)->deleteInstance(true);
	playerField<void *>(self, 0x28c) = new Rva000DA590Map();

	if (playerField<RawVirtualDelete *>(self, 0x290) != 0)
		playerField<RawVirtualDelete *>(self, 0x290)->deleteInstance(true);
	playerField<void *>(self, 0x290) = new TeamRelationMap();

	playerField<UnsignedByte>(self, 0x294) = 1;
	playerField<UnsignedByte>(self, 0x295) = 1;
	playerField<UnsignedByte>(self, 0x296) = 0;
	playerField<UnsignedByte>(self, 0x297) = 0;
	playerField<float>(self, 0x298) = 1.0f;
	playerField<UnsignedByte>(self, 0x29c) = 1;
	playerField<UnsignedByte>(self, 0x29d) = 0;
	playerField<UnsignedByte>(self, 0x29e) = 0;
	for (Int i = 0; i < 0x20; ++i)
		playerField<UnsignedByte>(self, 0x29f + i) = 0;
	for (Int i = 0; i < 0x20; ++i)
		playerField<Int>(self, 0x2c4 + i * 4) = 0;
	playerField<Int>(self, 0x2c0) = 0;
	playerField<short>(self, 0x344) = 0;

	playerField<ScoreKeeper>(self, 0x348).reset(
		playerField<Int>(self, 0x24));

	playerField<Int>(self, 0x63c) = 0;
	playerField<Int>(self, 0x644) = 0;
	playerField<Int>(self, 0x648) = 0;
	void **squads = reinterpret_cast<void **>(
		reinterpret_cast<unsigned char *>(self) + 0x654);
	for (Int i = 0; i < 10; ++i)
		initialiseAllocatedBlock(&squads[i], 0x01083e78);
	initialiseAllocatedBlock(&playerField<void *>(self, 0x67c), 0x01083e78);
	playerField<UnsignedByte>(self, 0x680) = 0;
	playerField<UnsignedByte>(self, 0x681) = 1;
	reinterpret_cast<Rva000FB1F0 *>(reinterpret_cast<unsigned char *>(self) + 0x684)->forward();

	if (pt != 0)
	{
		const unsigned char *templateBytes = reinterpret_cast<const unsigned char *>(pt);
		unsigned char *playerBytes = reinterpret_cast<unsigned char *>(self);
		for (Int i = 0; i < 4; ++i)
			reinterpret_cast<UnsignedInt *>(playerBytes + 0x0c)[i] =
				reinterpret_cast<const UnsignedInt *>(templateBytes + 0x0c)[i];
		reinterpret_cast<BFMERetailAsciiString *>(playerBytes + 0x1c)->releaseBuffer();
		reinterpret_cast<UnicodeString *>(playerBytes + 0x28)->set(
			*reinterpret_cast<const UnicodeString *>(templateBytes + 0x08));
		playerField<Int>(self, 0x20) = 0;
		playerField<Int>(self, 0x2c) = 1;
		playerField<UnsignedInt>(self, 0x4c) =
			reinterpret_cast<const UnsignedInt *>(templateBytes + 0x20)[0];
		playerField<UnsignedInt>(self, 0x50) =
			reinterpret_cast<const UnsignedInt *>(templateBytes + 0x24)[0];

		if (playerField<UnsignedInt>(self, 0x4c) == 0)
		{
			// The retail receiver is the BFME sub-object at +0x1cc; this is
			// the exact Money::deposit contract printed for the body.
			struct RawGlobalData
			{
				unsigned char m_prefix[0xc54];
				UnsignedInt m_defaultStartingCash;
			};
			RawGlobalData *globalData = *reinterpret_cast<RawGlobalData **>(0x012ed5c8);
			UnsignedInt startingCash = globalData->m_defaultStartingCash;
			reinterpret_cast<Money *>(playerBytes + 0x1cc)->deposit(startingCash, false);
		}

		double multiplier = *reinterpret_cast<const double *>(0x0107f948);
		Int red = static_cast<Int>(*reinterpret_cast<const float *>(templateBytes + 0x28) * multiplier);
		Int green = static_cast<Int>(*reinterpret_cast<const float *>(templateBytes + 0x2c) * multiplier);
		Int blue = static_cast<Int>(*reinterpret_cast<const float *>(templateBytes + 0x30) * multiplier);
		UnsignedInt colour = (static_cast<UnsignedInt>(green) | 0xffffff00u) << 8;
		colour = (colour | static_cast<UnsignedInt>(blue)) << 8;
		colour |= static_cast<UnsignedInt>(red);
		playerField<UnsignedInt>(self, 0x1c4) = colour;
		playerField<UnsignedInt>(self, 0x1c8) = colour;

		// The target passes template+0x60 into the generated map helper.  Its
		// ILT is kept address-named until the generated deque body is replaced.
		Rva0002CA16Receiver *colourMap =
			reinterpret_cast<Rva0002CA16Receiver *>(playerBytes + 0x1cc);
		colourMap->invoke(reinterpret_cast<const void *>(templateBytes + 0x60));
		reinterpret_cast<Rva0001D4B7Receiver *>(playerBytes + 0x1d8)->invoke();
		reinterpret_cast<Rva000201A3Receiver *>(playerBytes + 0x1d8)->invoke(
			reinterpret_cast<const void *>(templateBytes + 0x6c));
		reinterpret_cast<Rva0001D4B7Receiver *>(playerBytes + 0x1ec)->invoke();
	reinterpret_cast<Rva000201A3Receiver *>(playerBytes + 0x1ec)->invoke(
			reinterpret_cast<const void *>(playerBytes + 0x1d8));
		reinterpret_cast<Rva0000BBF9Receiver *>(playerBytes + 0x200)->invoke();
		reinterpret_cast<Rva00035DA0Receiver *>(playerBytes + 0x214)->invoke(
			reinterpret_cast<const void *>(templateBytes + 0x80));

		// The vector contains 4-byte map entries.  Its key/value work is
		// delegated to the address-named generated helper until that helper
		// gets a typed row of its own.
		RawVector &entries = playerField<RawVector>(self, 0x1d8);
		for (unsigned char **bucket = reinterpret_cast<unsigned char **>(entries.m_begin);
			bucket != reinterpret_cast<unsigned char **>(entries.m_end); ++bucket)
		{
			unsigned char *node = *bucket;
			while (node != 0)
			{
				int *mapped = reinterpret_cast<Rva00043C43Receiver *>(
					playerBytes + 0x200)->invoke(node + 4);
				*mapped = 0;
				GameSpyGroupRoom room(
					*reinterpret_cast<const GameSpyGroupRoom *>(node + 4));
				const unsigned char *nameData =
					*reinterpret_cast<const unsigned char **>(&room);
				const char *name = nameData != 0 ?
					reinterpret_cast<const char *>(nameData + 8) :
					reinterpret_cast<const char *>(0x0107388b);
				int hash = 0;
				while (*name != 0)
				{
					hash = hash * 5 + static_cast<signed char>(*name);
					++name;
				}
				reinterpret_cast<BFMERetailAsciiString *>(&room)->releaseBuffer();
				node = *reinterpret_cast<unsigned char **>(node);
			}
		}
		playerField<UnsignedByte>(self, 0x296) =
			templateBytes[0xbc];
		playerField<UnsignedByte>(self, 0x680) =
			templateBytes[0xbc];
	}
	else
	{
		playerField<StringBase<unsigned short> >(self, 0x08).set(
			*reinterpret_cast<const StringBase<unsigned short> *>(0x01336e54));
		reinterpret_cast<Rva000C81E0 *>(reinterpret_cast<unsigned char *>(self) + 0x0c)->reset();
		playerField<UnicodeString>(self, 0x1c).set(
			*reinterpret_cast<const UnicodeString *>(0x01336e50));
		const unsigned char *neutralName =
			*reinterpret_cast<const unsigned char **>(0x01336e50);
		const char *neutralText = neutralName != 0 ?
			reinterpret_cast<const char *>(neutralName + 8) :
			reinterpret_cast<const char *>(0x0107388b);
		UnsignedInt neutralKey =
			(*reinterpret_cast<NameKeyGenerator **>(0x012ed600))->nameToKey(
				neutralText);
		playerField<UnsignedInt>(self, 0x20) = neutralKey;
		reinterpret_cast<RetailLayoutString *>(reinterpret_cast<unsigned char *>(self) + 0x28)->set(
			reinterpret_cast<const char *>(0x0107301c), 0);
		playerField<UnsignedInt>(self, 0x50) = playerField<UnsignedInt>(self, 0x24);
		playerField<UnsignedInt>(self, 0x2c) = 1;
		playerField<UnsignedInt>(self, 0x4c) = 0;
		playerField<UnsignedInt>(self, 0x1c4) =
			*reinterpret_cast<const UnsignedInt *>(0x012a8ba8);
		playerField<UnsignedInt>(self, 0x1c8) =
			playerField<UnsignedInt>(self, 0x1c4);
		reinterpret_cast<Rva0003481FReceiver *>(reinterpret_cast<unsigned char *>(self) + 0x1cc)->invoke(
			0);
		reinterpret_cast<Rva00037880Receiver *>(reinterpret_cast<unsigned char *>(self) + 0x214)->invoke(
			0);
		reinterpret_cast<Rva0000BBF9Receiver *>(reinterpret_cast<unsigned char *>(self) + 0x200)->invoke();
	}

	// Neutral-player relation and science-vector cleanup, followed by the
	// already-landed Player::applyInitialUpgrades body.
	Int relationKey = playerField<Int>(self, 0x24);
	Rva0001219DReceiver *playerRelations = reinterpret_cast<Rva0001219DReceiver *>(
		*reinterpret_cast<unsigned char **>(reinterpret_cast<unsigned char *>(self) + 0x28c) + 4);
	*playerRelations->invoke(relationKey) = 2;
	playerField<Int>(self, 0x30) = 2;
	reinterpret_cast<Rva0002CF16Receiver *>(reinterpret_cast<unsigned char *>(self) + 0x30)->invoke();
	Rva00018679Receiver *mapState = reinterpret_cast<Rva00018679Receiver *>(
		reinterpret_cast<unsigned char *>(self) + 0x30);
	if (pt != 0)
		mapState->invoke(playerField<Int>(self, 0x24),
			*reinterpret_cast<const UnsignedByte *>(
				reinterpret_cast<const unsigned char *>(pt) + 0x118));
	else
		mapState->invoke(playerField<Int>(self, 0x24), false);
	reinterpret_cast<Rva000A2F4Receiver *>(self)->invoke();
	if (pt != 0)
		playerField<UnsignedByte>(self, 0x296) =
			reinterpret_cast<const unsigned char *>(pt)[0x118];

	reinterpret_cast<Rva000D95C0Player *>(self)->applyInitialUpgrades();

	RawVector &scienceA = playerField<RawVector>(self, 0x240);
	RawVector &scienceB = playerField<RawVector>(self, 0x24c);
	if (scienceA.m_begin != scienceA.m_end)
	{
		unsigned char *read = scienceA.m_begin;
		unsigned char *write = scienceA.m_end;
		while (read != scienceA.m_end)
		{
			*reinterpret_cast<UnsignedInt *>(write) =
				*reinterpret_cast<UnsignedInt *>(read);
			read += 4;
			write += 4;
		}
		scienceA.m_end = write;
	}
	if (scienceB.m_begin != scienceB.m_end)
	{
		unsigned char *read = scienceB.m_begin;
		unsigned char *write = scienceB.m_end;
		while (read != scienceB.m_end)
		{
			*reinterpret_cast<UnsignedInt *>(write) =
				*reinterpret_cast<UnsignedInt *>(read);
			read += 4;
			write += 4;
		}
		scienceB.m_end = write;
	}
	reinterpret_cast<Rva00043022Receiver *>(self)->invoke();

	// The final two list releases are separate in retail: +0x650 has 0x10-byte
	// nodes and +0x640 has 0x0c-byte nodes.  Keep the two boundaries explicit.
	clearNodeList(playerField<RawListNode *>(self, 0x650), 0x10);
	clearNodeList(playerField<RawListNode *>(self, 0x640), 0x0c);
	RawListNode *lastList = playerField<RawListNode *>(self, 0x64c);
	clearNodeList(lastList, 0x0c);
	playerField<BFMERetailAsciiString>(self, 0x698).releaseBuffer();
}
