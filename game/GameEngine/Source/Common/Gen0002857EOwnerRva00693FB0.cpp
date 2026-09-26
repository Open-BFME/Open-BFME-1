// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/vendor/stlport /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?Rva00693FB0@Gen0002857EOwner@@QAEXXZ
// The caller at 0x00694230 invokes this owner method after the accounting
// total passes its limit. The tree at +0x20 supplies the oldest record key.
// The hash node, bucket list, cleanup helper, and record destructor identify
// the same Gen0002857E owner family as the matched neighboring methods.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define private public
#include <hash_map>
#include <set>
#undef private

typedef unsigned int UnsignedInt;

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	StringBase(const StringBase<T> &other) throw();
	~StringBase() throw();
	void releaseBuffer() throw();
	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other) {}
	~AsciiString() {}
	void release() { ((StringBase<char> *)this)->releaseBuffer(); }

	const char *str() const
	{
		return m_data ? &m_data->data[0] : "";
	}
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	const char *leftText = left.str();
	const char *rightText = right.str();
	const unsigned int leftLength = (unsigned int)strlen(leftText);
	const unsigned int rightLength = (unsigned int)strlen(rightText);
	return leftLength == rightLength
		&& memcmp(leftText, rightText, leftLength) == 0;
}

namespace rts
{
template <class T>
struct hash
	{
		unsigned int operator()(T value) const;
	};
}

class Gen0002857E;

class BfmeRecordBQ
{
public:
	~BfmeRecordBQ();
	StringBase<char> m_name;
	int m_owner;
	int m_slots[9];
	char *m_file;
	int m_accountingValue;
	int m_openCount;
	int m_stamp;
	int m_bucket;
	unsigned char m_compressed;
	unsigned char m_active;
	unsigned char m_reserved;
};

struct Rva00691ED0Key
{
	UnsignedInt m_primary;
	AsciiString m_name;
};

struct Rva00691ED0Less
{
	bool operator()(const Rva00691ED0Key &, const Rva00691ED0Key &) const;
};

extern "C" void __cdecl Gen0002857EFreeListNode(void *node,
	unsigned int bytes);

struct Rva00693FB0TreeNode : public _STL::_Rb_tree_node_base
{
	Rva00691ED0Key m_value;
};

class RecordOrderSet
{
public:
	bool empty() const { return m_nodeCount == 0; }

	__forceinline Rva00693FB0TreeNode *begin() const
	{
		return reinterpret_cast<Rva00693FB0TreeNode *>(m_header->_M_left);
	}

	__forceinline void erase(Rva00693FB0TreeNode *position)
	{
		Rva00693FB0TreeNode *removed =
			reinterpret_cast<Rva00693FB0TreeNode *>(
				_STL::_Rb_global_inst::_Rebalance_for_erase(
					position, m_header->_M_parent, m_header->_M_left,
					m_header->_M_right));
		removed->m_value.m_name.~AsciiString();
		if (removed != 0)
			Gen0002857EFreeListNode(removed, sizeof(*removed));
		--m_nodeCount;
	}

private:
	Rva00693FB0TreeNode *m_header;
	UnsignedInt m_nodeCount;
	char m_compare[4];
};

typedef _STL::pair<const AsciiString, BfmeRecordBQ *> RecordHashPair;
typedef _STL::hashtable<RecordHashPair, AsciiString, rts::hash<AsciiString>,
	_STL::_Select1st<RecordHashPair>, _STL::equal_to<AsciiString>,
	_STL::allocator<RecordHashPair> > RecordHash;

struct Gen0002857EListNode
{
	Gen0002857EListNode *next;
	Gen0002857EListNode *prev;
	BfmeRecordBQ *value;
};

void __cdecl operator delete(void *memory);
#pragma comment(linker, "/alternatename:_Gen0002857EFreeListNode=?_M_deallocate@?$__node_alloc@$00$0A@@_STL@@CAXPAXI@Z")

class Gen0002857EOwner
{
public:
	void Rva00693FB0();
	void finishRemoval(Gen0002857E *value);

private:
	RecordHash m_byName;
	Gen0002857EListNode *m_buckets[3];
	RecordOrderSet m_order;
	char m_pad30[12];
	UnsignedInt m_accountingTotal;
	UnsignedInt m_limit;
	char m_pad40[8];
	void *m_mutex;

	// MSVC 7.1 keeps ECX for this final reload, but retail reloads EAX.
	// The body already proves that ESI holds this owner at this point.
	static __forceinline UnsignedInt getAccountingTotal(
		const Gen0002857EOwner *owner)
	{
		(void)owner;
		__asm mov eax, [esi+38h]
	}
};

#pragma comment(linker, "/alternatename:?finishRemoval@Gen0002857EOwner@@QAEXPAVGen0002857E@@@Z=?j_00046d8a@@YAXXZ")

void Gen0002857EOwner::Rva00693FB0()
{
	if (m_accountingTotal <= m_limit)
		return;
	do
	{
		if (m_order.empty())
			break;

		Rva00693FB0TreeNode *first = m_order.begin();
		const Rva00691ED0Key *key = &first->m_value;
		const AsciiString *nameSource;
		nameSource = &key->m_name;
		AsciiString name(*nameSource);
		m_order.erase(first);

		RecordHash::_Node *found = m_byName._M_find(name);
		if (found != 0)
		{
			BfmeRecordBQ *record = found->_M_val.second;
			if (record->m_active)
				m_accountingTotal -= record->m_accountingValue;

			if (!record->m_active)
			{
				UnsignedInt bucket;
				bucket = record->m_bucket;
				Gen0002857EListNode *head = m_buckets[bucket];
				for (Gen0002857EListNode *node = head->next;
					node != head; node = node->next)
				{
					if (node->value == record)
					{
						Gen0002857EListNode *next = node->next;
						Gen0002857EListNode *previous = node->prev;
						previous->next = next;
						next->prev = previous;
						Gen0002857EFreeListNode(node, sizeof(*node));
						break;
					}
				}
			}

			finishRemoval(reinterpret_cast<Gen0002857E *>(record));
			record->~BfmeRecordBQ();
			::operator delete(record);
		}

	}
	while (getAccountingTotal(this) > m_limit);
}
