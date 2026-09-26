// ?getThis@Rva007874C0Object@@QAEPAV1@XZ
// Retail 0x007874C0 returns its this pointer unchanged. The carved boundary
// and its thunk caller prove the body, but no evidence names an owning class.

class Rva007874C0Object
{
public:
	Rva007874C0Object *getThis();
};

Rva007874C0Object *Rva007874C0Object::getThis()
{
	return this;
}
