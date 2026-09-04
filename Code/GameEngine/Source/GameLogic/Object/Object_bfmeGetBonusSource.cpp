// cl: /DNDEBUG /MD /EHsc

enum NameKeyType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierPoolUpdate;
class Module;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	AttributeModifierPoolUpdate *bfmeFindAttributeModifierPoolUpdate() const;

protected:
	Module *findModule(NameKeyType key) const;
};

AttributeModifierPoolUpdate *Object::bfmeFindAttributeModifierPoolUpdate() const
{
	static NameKeyType key_AttributeModifierPoolUpdate =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return reinterpret_cast<AttributeModifierPoolUpdate *>(findModule(key_AttributeModifierPoolUpdate));
}
