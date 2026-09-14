// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: SpawnBehavior scalar-deleting destructor at retail RVA
// 0x0020C020 (30 bytes).  The exact constructor at 0x0020AE30 installs
// the primary vtable 0x010A6CCC whose slot zero routes here; the matched
// complete destructor at 0x0020B180 owns the two spawn lists and the
// UpdateModule/interface base chain.

class SpawnBehavior
{
public:
	virtual ~SpawnBehavior();
};

void forceSpawnBehaviorDeletingDestructor()
{
	SpawnBehavior value;
}
