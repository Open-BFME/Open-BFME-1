// cl: /DNDEBUG /MD /EHsc
// readable body of ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z: Code/GameEngine/Source/GameClient/InGameUI.cpp
// Lift the InGameUI::findSWInfo __emit thunk to clean C++.
//
// Retail indexes a 12-byte-per-player map array at this+0x5CC (the
// lea eax,[eax+eax*2] / lea esi,[ecx+eax*4+0x5CC] pair is just index*12), looks
// the name up, and bails when the result equals the map's end sentinel at +0x00.
// The hit carries a circular list head at +0x14, which is walked comparing each
// entry's id at SuperweaponInfo+0x18. The SpecialPowerTemplate parameter is
// never read -- retail matches on the ObjectID alone.

class AsciiString;
class SpecialPowerTemplate;
enum ObjectID { OBJECT_ID_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class SuperweaponInfo
{
public:
	unsigned char m_unreconstructed_00[0x18];
	ObjectID m_id;								///< retail this+0x18
};

struct SuperweaponListNode
{
	SuperweaponListNode *m_next;				///< retail this+0x00
	unsigned char m_unreconstructed_04[4];
	SuperweaponInfo *m_info;					///< retail this+0x08
};

struct SuperweaponMapNode
{
	unsigned char m_unreconstructed_00[0x14];
	SuperweaponListNode *m_list;				///< retail this+0x14; circular, head == end
};

class SuperweaponMap
{
public:
	SuperweaponMapNode *find(const AsciiString &);	///< pinned to the ILT thunk at 0x0000DCFB

	SuperweaponMapNode *m_end;					///< retail this+0x00
	unsigned char m_unreconstructed_04[8];		///< keeps the whole map 12 bytes wide
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
protected:
	SuperweaponInfo *findSWInfo(int, const AsciiString &, ObjectID, const SpecialPowerTemplate *);

private:
	unsigned char m_unreconstructed_00[0x5CC];
	SuperweaponMap m_superweapons[1];			///< retail this+0x5CC; one map per player
};

// ?findSWInfo@InGameUI@@IAEPAVSuperweaponInfo@@HABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z
SuperweaponInfo *InGameUI::findSWInfo(int playerIndex, const AsciiString &name, ObjectID id,
									  const SpecialPowerTemplate *)
{
	SuperweaponMap *map = &m_superweapons[playerIndex];

	SuperweaponMapNode *node = map->find(name);
	if (node != map->m_end)
	{
		SuperweaponListNode *head = node->m_list;
		SuperweaponListNode *entry = head->m_next;
		while (entry != head)
		{
			if (entry->m_info->m_id == id)
				return entry->m_info;

			entry = entry->m_next;
		}
	}

	return 0;
}
