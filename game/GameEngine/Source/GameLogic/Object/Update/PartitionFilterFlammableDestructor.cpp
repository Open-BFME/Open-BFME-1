// cl: /DNDEBUG /MD /EHsc
//
// PartitionFilterFlammable complete destructor at retail 0x00292540
// (7 bytes). ??_GPartitionFilterFlammable (0x00292590, its own TU) calls it
// through ILT 0x0000D378. The derived class has no members to destroy, so
// the body is only the inlined PartitionFilter base destructor: it re-seats
// ??_7PartitionFilter@@6B@ (VA 0x01083B5C) and returns. The base's own
// table is named through its retail symbol rather than redeclaring the
// PartitionFilter class (and re-emitting its vftable) in this TU.

extern "C" const char __identifier("??_7PartitionFilter@@6B@")[];

class __declspec(novtable) PartitionFilterFlammable
{
public:
	virtual ~PartitionFilterFlammable();
};

PartitionFilterFlammable::~PartitionFilterFlammable()
{
	*(const void **)this = __identifier("??_7PartitionFilter@@6B@");
}
