// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME5: BFME Object vtable slot 18, retail 0x001CBC20 (257 bytes).
// The real class/member name is not recovered.  The address-derived owner is
// intentional: the vtable lookup proves this body is Object's slot 18, while
// the body proves the BFME defection-completion state transition.

typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef int Int;

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0, OBJECT_STATUS_LAST = 85
};

enum NameKeyType
{
	INVALID_NAME_KEY = 0, NAME_KEY_MIN = (-2147483647 - 1), NAME_KEY_MAX = 2147483647
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator; // retail 0x012ED600

class Module
{
public:
	unsigned char m_pad_000[0x2c];
	unsigned char m_field2c;
};

template <int NUM_BITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<NUM_BITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class ContainModuleInterface
{
public:
	// Declaration-only dispatch view.  No object or vtable is emitted here;
	// slot 62 is the BFME containment-release call at vtable +0xf8.
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void releaseContainment() = 0;
};

class ObjectDispatchView
{
public:
	// Object vtable slot 19 is the restore-original-team operation used by
	// retail immediately after clearing the defection status.
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void restoreOriginalTeam() = 0;
};

class BfmeThingEW
{
public:
	void bfmeSwapEW(); // retail ILT 0x000359BD
};

class BfmeThingGT
{
public:
	void bfmeSwapGT(); // retail ILT 0x00025B12
};

class Object
{
public:
	void clearStatus(ObjectStatusTypes status);
	Module *findModule(NameKeyType key) const;
	void setStatus(const ObjectStatusMaskType &status, Bool set = true);
	void bfmeAbortActiveSpecialAbilities() const;

	Module *getContain() const { return (Module *)m_contain; }
	void *getAI() const { return m_ai; }

protected:
	void *m_vtable;
	unsigned char m_pad_004[0x90 - 4];
	UnsignedInt m_status[3];
	unsigned char m_pad_09c[0x1fc - 0x9c];
	void *m_contain;
	void *m_bfme_gap_200;
	void *m_ai;
};

class Rva0038AD90Object
{
public:
	void bfmeRefreshCompletedUpgrades(); // retail ILT 0x0001B9A5
};

// ?rva001CBC20@Rva001CBC20Object@@QAEXXZ
class Rva001CBC20Object : public Object
{
public:
	void rva001CBC20();
};

void Rva001CBC20Object::rva001CBC20()
{
	if ((m_status[1] & 0x20000000u) == 0)
		return;

	Module *contain = getContain();
	clearStatus((ObjectStatusTypes)0x3d);
	((ObjectDispatchView *)this)->restoreOriginalTeam();

	static NameKeyType key_TemporarilyDefectUpdate =
		TheNameKeyGenerator->nameToKey("TemporarilyDefectUpdate");

	Module *update = findModule(key_TemporarilyDefectUpdate);
	update->m_field2c = 1;

	if (contain != 0)
		((ContainModuleInterface *)contain)->releaseContainment();

	if ((m_status[1] & 0x20u) == 0)
	{
		void *ai = getAI();
		if (ai != 0)
		{
			if ((m_status[2] & 0x20u) != 0)
				bfmeAbortActiveSpecialAbilities();

			((BfmeThingEW *)ai)->bfmeSwapEW();
			((BfmeThingGT *)ai)->bfmeSwapGT();
		}
	}

	ObjectStatusMaskType status(ObjectStatusMaskType::kInit, 81);
	setStatus(status, true);
	((Rva0038AD90Object *)this)->bfmeRefreshCompletedUpgrades();
}
