// cl: /DNDEBUG /MD /EHsc

enum NameKeyType {};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BfmeVisionBonusSource;
class Module;

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
