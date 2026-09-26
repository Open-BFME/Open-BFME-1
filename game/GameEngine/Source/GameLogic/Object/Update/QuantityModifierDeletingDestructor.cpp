// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: QuantityModifier scalar-deleting destructor at retail RVA
// 0x00127970 (30 bytes). The wrapper calls the element destructor through
// retail ILT 0x00022FE3 before conditionally invoking operator delete.
// ProductionUpdate's recovered parser and vector<QuantityModifier> erase and
// clear paths establish this non-virtual value type.

class QuantityModifier
{
public:
	~QuantityModifier();
};

void forceQuantityModifierDelete(QuantityModifier *modifier)
{
	delete modifier;
}
