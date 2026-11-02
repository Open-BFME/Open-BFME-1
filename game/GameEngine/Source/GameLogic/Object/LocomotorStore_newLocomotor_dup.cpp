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
// The mangled LocomotorStore::newLocomotor name is the matched 98-byte row at
// 0x001B6920; retail was linked without identical-COMDAT folding, so this
// different 95-byte body cannot share that identity. Nothing in retail .text
// calls it or its ILT 0x00018F52, so it keeps an address-derived owner name and
// no longer emits a second definition of the matched symbol.

class LocomotorTemplate;
class Rva00465AB0LocomotorStore;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
protected:
	Locomotor(const LocomotorTemplate *tmpl);		// ILT 0x0002EDF7

	friend class Rva00465AB0LocomotorStore;

private:
	char m_bfmeBody[0x2C];
};

// Shape of ZH LocomotorStore::newLocomotor (upstream layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h).
class Rva00465AB0LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl) const;
};

// ?newLocomotor@Rva00465AB0LocomotorStore@@QBEPAVLocomotor@@PBVLocomotorTemplate@@@Z
Locomotor *Rva00465AB0LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
	return new Locomotor(tmpl);
}
