// cl: /DNDEBUG /MD /EHsc
// Retail body [0x001C1EA0, 0x001C1F3B), 155 bytes.
//
// The RVA-derived Object helper at 1C1EA0 calls both EnragedBehavior arms:
// its full retail body resolves the verified "EnragedBehavior" key, finds
// the module, and dispatches ILT 0x00042F7D or ILT 0x0001F960.  The first
// target is the existing matched BfmeHostXT::bfmeRunXT body at 0x001FAEE0;
// the second is the exact EnragedBehavior::rva001FAF60 body at 0x001FAF60.
// Those real owner names provide the two existing ILT routes without
// inventing enable/disable arm names or semantic virtual-slot labels.

typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
class Module;

class Object
{
protected:
	Module *findModule(NameKeyType key) const;
};

// Existing matched body and genuine owner for retail ILT 0x00042F7D.
class BfmeHostXT
{
public:
	void bfmeRunXT();
};

// Exact real C++ body landed for retail ILT 0x0001F960.
class EnragedBehavior
{
public:
	void rva001FAF60();
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva001C1EA0Object : public Object
{
public:
	void rva001C1EA0(Bool flag);
};

// ?rva001C1EA0@Rva001C1EA0Object@@QAEX_N@Z
void Rva001C1EA0Object::rva001C1EA0(Bool flag)
{
	static NameKeyType enragedBehaviorKey =
		TheNameKeyGenerator->nameToKey("EnragedBehavior");
	Module *module = findModule(enragedBehaviorKey);
	if (module != 0)
	{
		if (flag)
			reinterpret_cast<BfmeHostXT *>(module)->bfmeRunXT();
		else
			reinterpret_cast<EnragedBehavior *>(module)->rva001FAF60();
	}
}
