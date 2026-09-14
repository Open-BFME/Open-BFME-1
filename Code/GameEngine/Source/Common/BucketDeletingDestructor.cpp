// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: NameKeyGenerator::Bucket scalar-deleting destructor at retail
// RVA 0x0008F810 (30 bytes). The exact constructor at 0x0008F6F0 installs
// vtable 0x0107F980, whose sole slot routes through ILT 0x0003E88D to this
// wrapper. The wrapper reaches the complete destructor through ILT 0x0000F01F.

class Bucket
{
public:
	virtual ~Bucket();
};

void forceBucketDeletingDestructor()
{
	Bucket value;
}
