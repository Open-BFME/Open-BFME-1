// cl: /DNDEBUG /MD /EHsc
// stlport
// ?exitObjectViaDoor@HordeGarrisonContain@@EAEXPAVObject@@W4ExitDoorType@@@Z
// BFME retail HordeGarrisonContain::exitObjectViaDoor at RVA 0x002496E0, 248 bytes.
//
// Identity: the matched HordeGarrisonContain constructor (0x00248F90) installs
// the exit-interface vtable 0x010AFAD4 (slot +0x14 is
// OpenContain::exitObjectInAHurry); its slot +0x08, through ILT 0x00035AEE,
// is this body, the Zero Hour ExitInterface position of exitObjectViaDoor.
// tools/ilt_oracle.py CONFIRMS the private-virtual decoration (EAE) exactly.
// Every path ends in the matched base GarrisonContain::exitObjectViaDoor
// (0x0021FDC0 via ILT 0x0004910C) with the same door argument.
//
// When the exiting object carries a contain whose +0x68 query returns a horde
// view, a copy of that view's member list (+0xEC) is scanned for the first
// member whose byte at +0x368 is clear; that member, else the first member,
// is selected through the view's +0xA0 slot and exits in the object's place.
// The slot meanings are not named here: no caller or table names them.
#include <list>

class Object;
#include "../../../../Include/Common/Enums/ExitDoorType.h"

namespace _STL {
template <> list<Object *, allocator<Object *> >::list(const list<Object *, allocator<Object *> > &);
template <> _List_base<Object *, allocator<Object *> >::~_List_base();
}
typedef _STL::list<Object *> ContainedItemsList;

class HordeView002496E0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void selectSlotA0(Object *obj);						// +0xA0
	virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58();
	virtual const ContainedItemsList *getItemsSlotEC();			// +0xEC
};

class ContainView002496E0
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual HordeView002496E0 *getHordeSlot68();				// +0x68
};

// The two Object fields this body reads.
struct ObjectView002496E0
{
	ContainView002496E0 *getContain() const { return m_contain; }
	bool flag368() const { return m_flag368 != 0; }
private:
	char m_pad000[0x1fc];
	ContainView002496E0 *m_contain;				// +0x1FC
	char m_pad200[0x168];
	unsigned char m_flag368;					// +0x368
};

inline ObjectView002496E0 *view(Object *obj) { return (ObjectView002496E0 *)obj; }

class GarrisonContain
{
public:
	virtual void exitObjectViaDoor(Object *obj, ExitDoorType exitDoor);
};

class HordeGarrisonContain : public GarrisonContain
{
private:
	virtual void exitObjectViaDoor(Object *obj, ExitDoorType exitDoor);
};

void HordeGarrisonContain::exitObjectViaDoor(Object *obj, ExitDoorType exitDoor)
{
	ContainView002496E0 *contain = view(obj)->getContain();
	if (contain)
	{
		HordeView002496E0 *horde = contain->getHordeSlot68();
		if (horde)
		{
			ContainedItemsList items(*horde->getItemsSlotEC());
			for (ContainedItemsList::iterator it = items.begin(); it != items.end(); ++it)
			{
				Object *member = *it;
				if (!view(member)->flag368())
				{
					horde->selectSlotA0(member);
					GarrisonContain::exitObjectViaDoor(member, exitDoor);
					return;
				}
			}
			if (items.begin() != items.end())
			{
				Object *member = items.front();
				horde->selectSlotA0(member);
				GarrisonContain::exitObjectViaDoor(member, exitDoor);
				return;
			}
			GarrisonContain::exitObjectViaDoor(obj, exitDoor);
			return;
		}
	}
	GarrisonContain::exitObjectViaDoor(obj, exitDoor);
}
