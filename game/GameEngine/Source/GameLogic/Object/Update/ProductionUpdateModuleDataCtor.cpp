// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: ProductionUpdateModuleData's constructor, retail 0x0029FB70, 159
// bytes, replacing the naked lift that used to carry the row.
//
// IDENTITY: the name is not the lift's guess. The one caller is
// ?friend_newModuleData@ProductionUpdate@@ (ModuleFactory.cpp), the body
// installs vtable 0x010C0F68, and the matched destructor 0x0029E260 restores
// that same vtable and carries the same name.
//
// The record layout is this TU's own. Retail's own words fix the three members
// the matched destructor reads back: the twelve-byte container at +0x1C it
// tears down out of line, the layout string at +0x40 it releases and the
// refcounted pointer at +0x44 it decrements. The five door/time words land at
// +0x08 .. +0x18 because the body zeroes five consecutive words there and then
// walks +0x1C, +0x28 and +0x2C, which is the order the upstream
// ProductionUpdate.h gives its own record once a 0x1C base is added. The Zero
// Hour copy of this constructor still sits in ProductionUpdate.cpp, where the
// shared upstream header fixes a different layout, so it compiles 124 bytes and
// cannot hold this body; it keeps its present-unmatched marker.
//
// TWO STORE SCHEDULES, both visible in the bytes:
//   +0x2C is zeroed by the mem-initializer and given the disabled mask by the
//   body, so the word appears twice; +0x28 is only ever written once, with its
//   final value.
//   ecx is set to +0x1C for the container's constructor and kept there through
//   the state-0 store, while the layout string's address is precomputed into
//   edi one instruction before the +0x2C store and reused by the set() call at
//   the end -- the thiscall argument set up early, not a second cursor.
//
// The state written before the call that can throw is 3, so the record must
// present three destructible subobjects in teardown order -- container, layout
// string, then the +0x44 holder. Giving the destructor to a member class
// wrapping the +0x2C word instead also makes three, but it lands between the
// container and the string, prints 2, and moves the edi precompute behind the
// +0x2C store, so the holder at the end is the one that matches.

#include <vector>

extern const char g_Rva0107301CEmptyString[];

class RetailLayoutString
{
public:
	RetailLayoutString(void) : m_data(0) {}
	~RetailLayoutString(void) { releaseBuffer(); }

	void set(const char *text, int length);

private:
	void releaseBuffer();
	char *m_data;
};

// The eight-byte payload the container at +0x1C carries: retail's erase walks
// it in steps of eight and calls a per-element teardown on each, and retail's
// own container destructor does the same with the string release. This is the
// tree's established address-derived name for that payload shape
// (game/gen_small/tgrid_109.cpp instantiates it), which is what makes the call
// resolve to the body retail encodes.
struct Gen_t_0029e190_p8cd
{
	int a[2];
	~Gen_t_0029e190_p8cd();
};

// The refcounted pointer the matched destructor releases at +0x44.
class ProductionUpdateModuleDataRef
{
public:
	ProductionUpdateModuleDataRef(void) : m_bfme44(0) {}
	~ProductionUpdateModuleDataRef(void);

private:
	unsigned int m_bfme44;
};

// The upstream header, not this body, fixes the base: +0x00 is the vtable this
// constructor installs and +0x04 is never written, so the base is one word past
// it and the derived record starts at +0x08.
class ProductionUpdateModuleDataBase
{
public:
	virtual ~ProductionUpdateModuleDataBase();

private:
	unsigned char m_bfme04[4];
};

class ProductionUpdateModuleData : public ProductionUpdateModuleDataBase
{
public:
	ProductionUpdateModuleData(void);

private:
	int m_bfme08;
	unsigned int m_bfme0c;
	unsigned int m_bfme10;
	unsigned int m_bfme14;
	unsigned int m_bfme18;
	std::vector<Gen_t_0029e190_p8cd> m_bfme1c;
	int m_bfme28;
	unsigned int m_bfme2c;
	bool m_bfme30;
	unsigned int m_bfme34;
	unsigned int m_bfme38;
	bool m_bfme3c;
	bool m_bfme3d;
	RetailLayoutString m_bfme40;
	ProductionUpdateModuleDataRef m_bfme44;
};

// ??0ProductionUpdateModuleData@@QAE@XZ
ProductionUpdateModuleData::ProductionUpdateModuleData(void)
	: m_bfme2c(0)
{
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme18 = 0;
	m_bfme1c.clear();
	m_bfme28 = 20;
	m_bfme2c = 8;
	m_bfme30 = false;
	m_bfme34 = 0;
	m_bfme38 = 0;
	m_bfme3c = false;
	m_bfme3d = false;
	m_bfme40.set(g_Rva0107301CEmptyString, 0);
}
