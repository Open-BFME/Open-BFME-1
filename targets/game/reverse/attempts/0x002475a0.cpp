// ?DoXfer@HordeContain@@MAEXAAVXfer@@@Z
// partial score=0.4405 date=2026-11-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/System
// stlport
// HordeContain::DoXfer, retail 0x002475A0 (1814 bytes, ret 4 at +0x713).
// The matched AODHordeContain transfer reaches it as its base transfer through
// ILT 0x00024BDB; ilt_oracle CONFIRMS ?DoXfer@HordeContain@@MAEXAAVXfer@@@Z.
// [BFME 2 donor] Open-BFME-2 45afcff3 HordeContainXfer.cpp (version 13) gave
// the opening order; BFME 1 is version 3 and every field, width and helper
// below is read from the retail body. Container offsets match
// HordeContainDestructors.cpp. Member names are offset labels.
#define _STLP_NO_EXCEPTIONS 1
#include "object.h"
#include "xfer.h"
#include "Libraries/Source/WWVegas/WWMath/coord3d.h"
#include <list>
#include <map>
#include <set>
#include <vector>

struct Rva00226FA0Less : std::less<int> {};
struct Gen_t_000ef440_k4 { int a[1]; };
struct Gen_t_0023db70_m4pod { void *p; };

struct Rva00244A80Element
{
	Rva00244A80Element() : m_id(0), m_flag(true), m_18(0), m_1C(0)
	{
		m_position.x = 0;
		m_position.y = 0;
		m_position.z = 0;
	}
	int m_id;
	Coord3DBase m_position;
	bool m_flag;
	int m_18;
	int m_1C;
};

namespace _STL {
template <> pair<_Rb_tree_iterator<Gen_t_000ef440_k4, _Nonconst_traits<Gen_t_000ef440_k4> >, bool>
_Rb_tree<Gen_t_000ef440_k4, Gen_t_000ef440_k4, _Identity<Gen_t_000ef440_k4>, less<Gen_t_000ef440_k4>, allocator<Gen_t_000ef440_k4> >::insert_unique(const Gen_t_000ef440_k4 &);
template <> void vector<Rva00244A80Element, allocator<Rva00244A80Element> >::_M_fill_insert(Rva00244A80Element *, unsigned int, const Rva00244A80Element &);
template <> void vector<Gen_t_0023db70_m4pod, allocator<Gen_t_0023db70_m4pod> >::_M_insert_overflow(Gen_t_0023db70_m4pod *, const Gen_t_0023db70_m4pod &, const __false_type &, unsigned int, bool);
}
bool operator<(const Gen_t_000ef440_k4 &, const Gen_t_000ef440_k4 &);

class BfmeSeedTarget;
class Gen_0022CD40 { public: void bfmeSeed(BfmeSeedTarget *target); void xfer(Xfer *target) { bfmeSeed((BfmeSeedTarget *)target); } };
class Rva001CB270BitFlags { public: void xfer(Xfer *xfer); unsigned int m_bits[10]; };
class MidVirtualSlot90Receiver;
Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *target, void *context);
void bfmeHandOver_000353C8(BfmeSeedTarget *target, void *item);

struct Rva002475A0Record
{
	Rva002475A0Record() : m_id(0), m_value(-1) {}
	int m_id;
	int m_value;
};

class HordeContain
{
protected:
	virtual void DoXfer(Xfer &xfer);

private:
	char m_head[0xE8 - 0x04];
	bool m_E8;
	bool m_E9;
	char m_unmodelledEA[2];
	Rva001CB270BitFlags m_EC;
	std::set<Gen_t_000ef440_k4> m_set;
	std::map<int, int, Rva00226FA0Less> m_map;
	char m_unmodelled12C[0x138 - 0x12C];
	std::list<int> m_list;
	char m_unmodelled13C[4];
	unsigned int m_140;
	char m_snapshot214[0x1B4 - 0x144];
	int m_objectID1b4;
	int m_1B8;
	int m_objectID1bc;
	std::vector<Gen_t_0023db70_m4pod> m_1C0;
	unsigned int m_1CC;
	int m_1D0;
	int m_1D4;
	std::vector<Rva00244A80Element> m_1D8;
	int m_objectID1e4;
	unsigned int m_1E8;
	unsigned int m_1EC;
	bool m_1F0;
	char m_unmodelled1F1[0x1F8 - 0x1F1];
	int m_1F8;
	bool m_1FC;
	bool m_1FD;
	bool m_1FE;
	char m_unmodelled1FF;
	int m_200;
	bool m_204;
	bool m_205;
	char m_unmodelled206[2];
	int m_208;
	int m_20C;
	char m_unmodelled210[4];
	Coord3DBase m_214;
	bool m_220;
	bool m_221;
};

void HordeContain::DoXfer(Xfer &xfer)
{
	((Gen_0022CD40 *)this)->xfer(&xfer);
	if (xfer.IsLightCRC())
		return;

	Xfer::Version version;
	version.data[0] = 1;
	version.data[1] = 3;
	xfer == version;

	xfer == m_E8;
	xfer == m_140;
	xfer == m_E9;
	xfer == m_1FE;

	int listCount = m_list.size();
	xfer == listCount;
	if (xfer.IsLoading())
	{
		int value = 0;
		for (int i = 0; i < listCount; ++i)
		{
			xfer == value;
			m_list.push_back(value);
		}
	}
	else
	{
		for (std::list<int>::iterator it = m_list.begin(); it != m_list.end(); ++it)
		{
			int value = *it;
			xfer == value;
		}
	}

	int mapCount = m_map.size();
	xfer == mapCount;
	if (xfer.IsLoading())
	{
		int key = 0;
		int value = 0;
		for (int i = 0; i < mapCount; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &key);
			xfer == value;
			m_map[key] = value;
		}
	}
	else
	{
		for (std::map<int, int, Rva00226FA0Less>::iterator it = m_map.begin(); it != m_map.end(); ++it)
		{
			int key = it->first;
			int value = it->second;
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &key);
			xfer == value;
		}
	}

	m_EC.xfer(&xfer);

	int setCount = m_set.size();
	xfer == setCount;
	if (xfer.IsLoading())
	{
		int id = 0;
		for (int i = 0; i < setCount; ++i)
		{
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &id);
			m_set.insert(*(Gen_t_000ef440_k4 *)&id);
		}
	}
	else
	{
		for (std::set<Gen_t_000ef440_k4>::iterator it = m_set.begin(); it != m_set.end(); ++it)
		{
			int id = it->a[0];
			Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &id);
		}
	}

	if (version.data[1] < 3)
	{
		int count = m_1C0.size();
		xfer == count;
		if (xfer.IsLoading())
		{
			for (int i = 0; i < count; ++i)
			{
				Rva002475A0Record *record = new Rva002475A0Record;
				Xfer::Version recordVersion;
				recordVersion.data[0] = 1;
				recordVersion.data[1] = 1;
				xfer == recordVersion;
				bfmeHandOver_000353C8((BfmeSeedTarget *)&xfer, record);
				xfer == record->m_value;
				Gen_t_0023db70_m4pod entry;
				entry.p = record;
				m_1C0.push_back(entry);
			}
		}
		else
		{
			for (int i = 0; i < count; ++i)
			{
				Rva002475A0Record *record = (Rva002475A0Record *)m_1C0[i].p;
				Xfer::Version recordVersion;
				recordVersion.data[0] = 1;
				recordVersion.data[1] = 1;
				xfer == recordVersion;
				bfmeHandOver_000353C8((BfmeSeedTarget *)&xfer, record);
				xfer == record->m_value;
			}
		}
	}

	xfer == m_1FC;
	xfer == m_1FD;

	int recordCount = m_1D8.size();
	xfer == recordCount;
	if (xfer.IsLoading())
	{
		m_1D8.resize(recordCount);
	}
	for (int i = 0; i < recordCount; ++i)
	{
		Rva00244A80Element record;
		if (!xfer.IsLoading())
			record = m_1D8[i];
		xfer == record.m_position;
		xfer == record.m_flag;
		if (xfer.IsLoading())
			m_1D8[i] = record;
	}

	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_objectID1e4);
	xfer == m_1E8;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_objectID1b4);
	xfer == m_1B8;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_objectID1bc);
	xfer == m_20C;
	xfer == m_1CC;
	xfer == m_1D0;
	xfer == m_1D4;
	(xfer == m_214) == m_220;
	xfer == m_1EC;
	xfer == m_1F0;
	xfer == m_1EC;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_1F8);
	xfer == m_200;
	xfer == m_204;
	xfer == m_205;
	Rva0010C3C0((MidVirtualSlot90Receiver *)&xfer, &m_208);
	if (version.data[1] > 1)
		xfer == m_221;
}
// bank s532: 1795/1814 B shape 0.914; frame 0x60 vs 0x40 (see attempt_support/20261102-002475a0-hordecontain-doxfer.md)
