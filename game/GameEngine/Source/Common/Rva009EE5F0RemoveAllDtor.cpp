// cl: /DNDEBUG /MD /EHsc
//
// 0x009EE5F0 (11 bytes): mov dword ptr [ecx],<vftable 0x011457BC> /
// jmp 0x009EDD30.  It sat in an unclaimed gap (16-byte-aligned start after
// int3 padding, int3 after the jmp) and nothing references it.
//
// The body is a destructor: it re-seats the vftable whose only slot is the
// matched deleting destructor at 0x009EEA70, then tail-jumps with `this`
// unchanged into 0x009EDD30, matched as ?Remove_All@?$SList@VTagBlockIndex@@@@
// (that row's TU is the layout source used here).  Retail's vftable has no
// Remove_All slot and that body walks 45007 hash buckets, so the SList name of
// the callee is itself unproven; this destructor therefore takes an
// address-derived class, derived from the callee's class only so the call
// resolves to the matched row with no new pin.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the address.

class TagBlockIndex;

template <class T>
class SList
{
private:
	struct Node
	{
		Node *next;
		~Node();
	};

public:
	virtual void Remove_All();

private:
	Node *m_buckets[45007];
};

class Rva009EE5F0Owner : public SList<TagBlockIndex>
{
public:
	virtual ~Rva009EE5F0Owner();
};

Rva009EE5F0Owner::~Rva009EE5F0Owner()
{
	SList<TagBlockIndex>::Remove_All();
}
