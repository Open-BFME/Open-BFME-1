// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: the per-TU copy of LocomotorStore::newLocomotor, retail
// 0x00465AB0, 95 bytes, from the zh_sweep packet for that address -- no ledger
// row claimed it and no inventory row confirmed the start, which the int3
// padding at 0x00465B0F and the frame this body sets up now do.
//
// It is one new expression and nothing else: 0x2C bytes from operator new, and
// when that comes back non-null the protected Locomotor constructor runs on it
// with the template. The null path returns zero without calling anything.
//
// The frame exists for that constructor: the unwind state is written once, over
// the fresh allocation, so the memory is released again if the constructor
// throws. The callee is the per-site copy of the constructor the ledger already
// pins at the ILT, not the body it names at 0x001B60E0.
//
// The row is named for its address rather than the symbol: the mangled name is
// already claimed at 0x001B6920 by a different 98-byte copy of the same
// function.

class LocomotorTemplate;
class LocomotorStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
protected:
	Locomotor(const LocomotorTemplate *tmpl);		// ILT 0x0002EDF7

	friend class LocomotorStore;

private:
	char m_bfmeBody[0x2C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl) const;
};

// ?newLocomotor@LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z
Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
	return new Locomotor(tmpl);
}
