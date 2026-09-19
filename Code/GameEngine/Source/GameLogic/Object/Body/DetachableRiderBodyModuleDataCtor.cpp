// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DetachableRiderBodyModuleData's constructor, retail 0x002131B0, 50
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real.
//
// The base constructor runs, the derived vtable goes over the base one, a
// sub-object at +0x5C is constructed through its own constructor, and three
// fields are set: one at +0xCC, a byte at +0xC8 and 1.0f at +0xC4.
//
// The three are assignments in the constructor body, which is what lets the
// compiler share one zeroed register between the two zeros and put them ahead
// of the float. Their order within that pair follows the source, so the word
// is written before the byte.

typedef int Int;
typedef float Real;
typedef bool Bool;

class ModuleDataBase
{
public:
	ModuleDataBase();					// ILT 0x00036818
	virtual void slot();

	char m_bfmeHead[0x5C - 0x04];
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();					// ILT 0x0000F0A6

	char m_bfmeBody[0xC4 - 0x5C];
};

class DetachableRiderBodyModuleData : public ModuleDataBase
{
public:
	DetachableRiderBodyModuleData();
	virtual void slot();

private:
	UpgradeModuleDataSub m_bfmeSub;				// +0x5C
	Real m_bfmeC4;						// +0xC4
	Bool m_bfmeC8;						// +0xC8
	char m_bfmePadC9[3];
	Int m_bfmeCC;						// +0xCC
};

// ??0DetachableRiderBodyModuleData@@QAE@XZ
DetachableRiderBodyModuleData::DetachableRiderBodyModuleData()
{
	m_bfmeC4 = 1.0f;
	m_bfmeCC = 0;
	m_bfmeC8 = false;
}
