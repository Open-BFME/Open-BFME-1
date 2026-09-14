// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ExperienceScalarTable scalar-deleting destructor at retail RVA
// 0x0037FB90 (30 bytes). The exact named constructor at 0x0037EF50 and the
// recovered ExperienceLevelSystem ownership path establish the non-virtual
// table type. The wrapper calls its destructor through ILT 0x00016E6E.

class ExperienceScalarTable
{
public:
	~ExperienceScalarTable();
};

void forceExperienceScalarTableDelete(ExperienceScalarTable *table)
{
	delete table;
}
