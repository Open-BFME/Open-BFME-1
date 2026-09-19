// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: module getModuleNameKey bodies, converted out of machine byte
// dumps.
//
// Each is the same four lines -- a function-local static initialised once from
// TheNameKeyGenerator->nameToKey("<module>") -- so the code cannot say which
// module it belongs to and the guard byte, the static and the string pointer
// are all relocation sites the byte gate masks. The string itself is not
// masked: verify_string_refs reads the literal out of the source and compares
// it to the bytes the retail push points at, so the module name each body
// carries is what assigns it, and a wrong name fails the gate rather than
// landing quietly.

enum NameKeyType { };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class ObjectRecoveryHelper
{
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?getModuleNameKey@ObjectRecoveryHelper@@UBE?AW4NameKeyType@@XZ
NameKeyType ObjectRecoveryHelper::getModuleNameKey() const
{
	static NameKeyType nk = TheNameKeyGenerator->nameToKey("ObjectRecoveryHelper");
	return nk;
}
