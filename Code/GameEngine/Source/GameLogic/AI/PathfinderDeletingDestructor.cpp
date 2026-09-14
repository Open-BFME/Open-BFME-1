// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Pathfinder scalar-deleting destructor at retail RVA
// 0x003DE910 (30 bytes). The wrapper calls the exact complete Pathfinder
// destructor at 0x003DC040 through ILT 0x0001D46C. Pathfinder's constructor
// ILT 0x0000DF12 and the matched BFME multiple-inheritance destructor layout
// establish the class identity alongside its recovered pathfinding methods.

class Pathfinder
{
public:
	virtual ~Pathfinder();
};

void forcePathfinderDeletingDestructor()
{
	Pathfinder value;
}
