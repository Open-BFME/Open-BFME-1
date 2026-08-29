// cl: /DNDEBUG /MD /EHsc

enum NameKeyType {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeVisionBonusSource;
class Module;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
private:
	BfmeVisionBonusSource *bfmeGetBonusSource() const;

protected:
	Module *findModule(NameKeyType key) const;
};

BfmeVisionBonusSource *Object::bfmeGetBonusSource() const
{
	static NameKeyType key_AttributeModifierPoolUpdate =
		TheNameKeyGenerator->nameToKey("AttributeModifierPoolUpdate");
	return reinterpret_cast<BfmeVisionBonusSource *>(findModule(key_AttributeModifierPoolUpdate));
}
