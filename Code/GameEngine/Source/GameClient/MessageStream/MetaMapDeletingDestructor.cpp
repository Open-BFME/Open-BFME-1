// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME7: MetaMap scalar-deleting destructor at retail RVA 0x005B7320
// (30 bytes). The matched constructor at 0x000A71C0 and vtable 0x0110F024
// establish the class identity; the complete destructor at 0x005B7260 walks
// and releases the MetaMapRec list at +0x08 before chaining to the subsystem
// base. MetaMapDestructor.cpp supplies the exact member-layout evidence.

class MetaMap
{
public:
	virtual ~MetaMap();
};

void forceMetaMapDeletingDestructor()
{
	MetaMap value;
}
