// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: AI scalar-deleting destructor at retail RVA 0x0014C600
// (30 bytes). The matched constructor at 0x0014C170 installs vtable
// 0x010959A8, whose first slot routes here through ILT 0x00042654. The
// wrapper calls the matched AI complete destructor at 0x0014C3B0 through
// ILT 0x00002527 before conditionally invoking scalar operator delete.

class AI
{
public:
	virtual ~AI();
};

void forceAIDeletingDestructor()
{
	AI value;
}
