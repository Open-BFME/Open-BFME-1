// ?d_0041bac0@@YAXXZ
// partial score=0.286331 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath
// Address-qualified reconstruction of retail 0x0041BAC0. Its receiver is the
// vslot+0x28 subobject passed by Pathfinder::updateAt003FA5B0. The receiver
// offsets below are from the retail body; no BFME owner/member identity is
// asserted here.
// Reviewed corrections: indexed query enumeration; an eight-byte query record
// owning its string; destructor before advancing the query index; Waypoint
// strings passed by value; metadata from query word0; independent link bounds.
//
// Callee evidence: callees.py reports 0x4AED->0x418C50,
// 0x107AD->0x1BFAC0, 0x1ADB1->0x1AB600, and 0x3793E->0x3D84A0.
// 0x418C50 is a thiscall vector overflow helper: its body reads begin/end
// pointers from this+0/4 and ends ret 0x14 (position, value, tag, count, end).
// 0x1BFAC0 is the matched Object::getMultiLogicalBonePosition body, thiscall
// with six stack args and ret 0x18. 0x1AB600's complete 550-byte body returns
// this in EAX and ret 0x24; its receiver is the allocated 0xB0 block and the
// nine physical stack args are the sentinel, StringBase handle, Coord3D
// pointer, three StringBase handles, byte flag, count, and final handle.
// 0x3D84A0 takes its receiver in ECX plus one stack pointer and ret 4.
// The four 0x887B60 calls are StringBase<char> copy construction (ret 4),
// 0x888BC0 is StringBase<char>(const char*) (ret 4), and 0x887940 releases a
// StringBase<char> handle. 0x9F6EE4/0x9F6D76 are MSVC array construction /
// destruction helpers: the dump passes destination, stride 12, count 10,
// constructor 0x416C93, destructor 0x41364C, then destination/stride/count/
// destructor 0x41364C.
// Global operator new at 0x881F30 receives the allocation size 0xB0.

#include "ascii_string.h"
#include "coord3d.h"

typedef unsigned char Rva0041BAC0Bool;
typedef int Rva0041BAC0Int;

struct Rva0041BAC0NameRecord
{
	int m_word0;
	AsciiString m_name;
};

template <> inline const char *StringBase<char>::str() const
{ return m_data ? m_data->data : ""; }
template <> inline StringBase<char>::~StringBase() { releaseBuffer(); }
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->~StringBase<char>(); }

class Rva0041BAC0View
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual Rva0041BAC0Bool queryName(Rva0041BAC0Int, Rva0041BAC0NameRecord *);
};

class Rva0041BAC0Target
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual Rva0041BAC0View *slot9C();
};

class Matrix3D;

class Object
{
public:
	int getMultiLogicalBonePosition(const char *boneNamePrefix, int maxBones,
		Coord3D *positions, Matrix3D *transforms, bool convertToWorld, int extra) const;
};

class Rva001AB600Record
{
public:
	virtual void slot00();
	Rva001AB600Record(int id, AsciiString label, const Coord3D *position,
		AsciiString name1, AsciiString name2, AsciiString name3,
		Rva0041BAC0Bool flag, int count, AsciiString name4);

	unsigned char m_body[0xB0 - sizeof(void *)];
};

namespace Rva0041BAC0Detail
{
struct Rva00418C50CopyTag { };

template <class T>
struct PointerVector
{
	T *m_begin;
	T *m_end;
	T *m_capacity;

	void insertOverflow(T *position, const T &value, const Rva00418C50CopyTag &tag,
		unsigned int count, bool atEnd);

	void pushBack(const T &value)
	{
		if (m_end != m_capacity)
		{
			if (m_end != 0) *m_end = value;
			++m_end;
		}
		else insertOverflow(m_end, value, Rva00418C50CopyTag(), 1, true);
	}

};

struct RecordLinks
{
	unsigned char m_prefix[0x20];
	Rva001AB600Record *m_children[8];
	Rva001AB600Record *m_other;
	unsigned char m_gap[8];
	int m_childCount;
};

class Registry
{
public:
	void registerRecord(Rva001AB600Record *record);
};

struct AI
{
	unsigned char m_prefix[0x0C];
	Registry *m_registry;
};

struct Owner
{
	unsigned char m_prefix00[0xFC];
	Object *m_boneSource;
	unsigned char m_prefix100[0x50];
	Rva0041BAC0Target **m_targets;
	unsigned char m_prefix154[0x1A4];
	PointerVector<Rva001AB600Record *> m_records;

	void method0041BAC0();
};
}

void Rva0041BAC0Detail::Owner::method0041BAC0()
{
	Rva0041BAC0Target **target = m_targets;
	Object *boneSource = m_boneSource;
	if (*target == 0) return;
	do
	{
		Rva0041BAC0View *view = (*target)->slot9C();
		if (view != 0)
		{
			Rva0041BAC0NameRecord selected;
			int nameIndex = 0;
			while (view->queryName(nameIndex, &selected))
			{
				{
				__declspec(align(8)) Coord3D positions[10];
				int count = boneSource->getMultiLogicalBonePosition(
					selected.m_name.str(), 10, positions, 0, true, 0);
				Rva001AB600Record *previous = 0;
				if (count >= 2 && count > 0)
				{
					const AsciiString &empty = *(const AsciiString *)0x01336E50;
					for (int i = 0; i < count; ++i)
					{
						Rva001AB600Record *record = new Rva001AB600Record(
							0x7ffffffe, AsciiString("#embed"), &positions[i],
							AsciiString(empty), AsciiString(empty), AsciiString(empty),
							0, selected.m_word0, AsciiString(empty));
						Rva0041BAC0Detail::AI *ai = *(Rva0041BAC0Detail::AI **)0x012EF214;
						ai->m_registry->registerRecord(record);
						if (previous != 0)
						{
							RecordLinks *prior = reinterpret_cast<RecordLinks *>(previous);
							RecordLinks *current = reinterpret_cast<RecordLinks *>(record);
							if (prior->m_childCount < 8) prior->m_children[prior->m_childCount++] = record;
							current->m_other = previous;
							if (current->m_childCount < 8) current->m_children[current->m_childCount++] = previous;
							prior->m_other = record;
						}
						previous = record;
						m_records.pushBack(record);
					}
				}
				}
				++nameIndex;
			}
		}
		++target;
	} while (*target != 0);
}
