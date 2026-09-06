// cl: /DNDEBUG /MD /EHsc
// Address-derived reconstruction of retail RVA 0x0026C260 (151 bytes).
// The owning class is not recovered; these names describe only the proven
// call ABI and object/module field offsets.

typedef unsigned char Byte;
typedef unsigned int UnsignedInt;

// Preserve the retail null-return SEH epilogue scheduling under MSVC7.1.
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)



enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_FORCE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module;

// The retail callee is Object::findModule(NameKeyType).
class Object
{
public:
	Module *findModule(NameKeyType key) const;

	unsigned char m_pad00[0x90];
	UnsignedInt m_status;
};

class Module
{
public:
	unsigned char m_pad00[0x2d];
	Byte m_field2d;
};

class Rva0026C260Owner
{
public:
	Byte check(UnsignedInt argument);
};

// ?check@Rva0026C260Owner@@QAEEI@Z
Byte Rva0026C260Owner::check(UnsignedInt argument)
{
	Object *member = *(Object **)((char *)this - 0x18);
	static NameKeyType key =
		TheNameKeyGenerator->nameToKey("StealthUpdate");
	Module *module = member->findModule(key);
	if (module == 0)
	{
		_ReadWriteBarrier();
		return false;
	}

	if (module->m_field2d)
		return false;

	unsigned char status = (unsigned char)(member->m_status >> 0x12);
	status &= 1;
	return status;
}
