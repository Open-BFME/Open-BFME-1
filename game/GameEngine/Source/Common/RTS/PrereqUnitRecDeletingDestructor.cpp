// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ProductionPrerequisite::PrereqUnitRec scalar-deleting destructor
// at retail RVA 0x003A64E0 (30 bytes). The exact default constructor and the
// recovered vector<PrereqUnitRec> copy, insertion, erase, clear, and destroy
// paths establish the nested value type. This wrapper calls its destructor
// through ILT 0x000195FB before conditionally invoking operator delete.

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		~PrereqUnitRec();
	};
};

void forcePrereqUnitRecDelete(ProductionPrerequisite::PrereqUnitRec *record)
{
	delete record;
}
