// cl: /Ob2
// Open-BFME5: TerrainLogic::getWaypointByID, retail 0x001ACE10 (116 bytes).
//
// Retail keeps an ordered waypoint cache in the TerrainTree member at +0x550.
// Its incremental-link calls are the existing 0x000124EF lower-bound helper
// and 0x0002DCA9 value-slot helper.  A cache miss walks the process-global
// waypoint chain at 0x012EF4D0, whose id and next fields are at +0x04 and
// +0x1c, then records either the found waypoint or NULL in the cache.

typedef unsigned int UnsignedInt;

class Waypoint;

struct Rva001ACE10TreeNode
{
	unsigned char m_colour;
	Rva001ACE10TreeNode *m_parent;
	Rva001ACE10TreeNode *m_left;
	Rva001ACE10TreeNode *m_right;
	UnsignedInt m_key;
	Waypoint *m_value;
};

struct Rva001ACE10Tree
{
	Rva001ACE10TreeNode *m_header;
};

extern void j_000124ef();
extern void j_0002dca9();

class Rva001ACE10TreeCall
{
};

// Declaration-only ABI identity. The retail vtable places this method at
// slot 32; the body addresses its BFME-specific tree through raw +0x550 so
// this TU does not invent a complete TerrainLogic object layout or emit a table.
class __declspec(novtable) TerrainLogic
{
public:
	virtual Waypoint *getWaypointByID(UnsignedInt id);
};

Waypoint *TerrainLogic::getWaypointByID(UnsignedInt id)
{
	Rva001ACE10TreeNode *node;
	Rva001ACE10TreeCall *tree = reinterpret_cast<Rva001ACE10TreeCall *>(
		reinterpret_cast<unsigned char *>(this) + 0x550);
	{
		typedef void (Rva001ACE10TreeCall::*FindCall)(
			Rva001ACE10TreeNode **, const UnsignedInt *);
		union
		{
			void *asVoid;
			FindCall asMember;
		} findCast;
		findCast.asVoid = reinterpret_cast<void *>(j_000124ef);
		(tree->*findCast.asMember)(&node, &id);
	}

	if (node != reinterpret_cast<Rva001ACE10Tree *>(
			reinterpret_cast<unsigned char *>(this) + 0x550)->m_header)
		return node->m_value;

	Waypoint *waypoint = *reinterpret_cast<Waypoint **>(0x012EF4D0);
	while (waypoint != 0)
	{
		if (*reinterpret_cast<UnsignedInt *>(
			reinterpret_cast<unsigned char *>(waypoint) + 0x04) == id)
			break;
		waypoint = *reinterpret_cast<Waypoint **>(
			reinterpret_cast<unsigned char *>(waypoint) + 0x1c);
	}

	if (waypoint != 0)
	{
		typedef Waypoint **(Rva001ACE10TreeCall::*ValueCall)(
			const UnsignedInt *);
		union
		{
			void *asVoid;
			ValueCall asMember;
		} valueCast;
		valueCast.asVoid = reinterpret_cast<void *>(j_0002dca9);
		Waypoint **slot = (tree->*valueCast.asMember)(&id);
		*slot = waypoint;
		return waypoint;
	}

	{
		typedef Waypoint **(Rva001ACE10TreeCall::*ValueCall)(
			const UnsignedInt *);
		union
		{
			void *asVoid;
			ValueCall asMember;
		} valueCast;
		valueCast.asVoid = reinterpret_cast<void *>(j_0002dca9);
		Waypoint **slot = (tree->*valueCast.asMember)(&id);
		*slot = 0;
	}
	return 0;
}
