// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ExperienceLevelSystem scalar-deleting destructor at retail RVA
// 0x00381610 (30 bytes).  The exact constructor at 0x00381480 installs the
// ExperienceLevelSystem vtable 0x010EA948, whose complete virtual destructor
// is the matched 340-byte body at 0x00380D30.  The existing destructor owns
// the default level, scalar-table vector, pending list, level map, and base.

class ExperienceLevelSystem
{
public:
	virtual ~ExperienceLevelSystem();
};

void forceExperienceLevelSystemDeletingDestructor()
{
	ExperienceLevelSystem value;
}
