// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
//
// BFME's GameSpyInfo keeps the last one hundred received buddy messages.  The
// target body is the STLport list append plus the bounded-list eviction; the
// list node and BuddyMessage layouts are the same ones used by the converted
// BuddyMessage list helpers in this directory.

class GameSpyInfoInterface;
extern GameSpyInfoInterface *TheGameSpyInfo;

class AsciiString
{
public:
	~AsciiString();

private:
	void *m_data;
};

class UnicodeString
{
public:
	~UnicodeString();

private:
	void *m_data;
};

class BuddyMessage
{
public:
	BuddyMessage(const BuddyMessage &);
	~BuddyMessage();

	unsigned int m_timestamp;
	unsigned int m_senderID;
	AsciiString m_senderNick;
	unsigned int m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};

void __cdecl constructBuddyMessageAt(void *dest, const BuddyMessage &source);
void *__cdecl bfmeAllocNode(unsigned int size);
void __cdecl bfmeDeallocate(void *memory, unsigned int size);

namespace _STL
{
	struct _List_node_base
	{
		_List_node_base *_M_next;
		_List_node_base *_M_prev;
	};

	template <class T>
	struct _List_node : public _List_node_base
	{
		T _M_data;
	};

	template <class T>
	struct _Nonconst_traits
	{
 	};

	template <class T, class Traits>
	struct _List_iterator
	{
		_List_iterator(_List_node_base *node) : _M_node(node) {}
		_List_node_base *_M_node;
	};

	template <class T, class Allocator>
	class _List_base
	{
	public:
		typedef _List_node<T> _Node;
		_Node *_M_node;
	};

	template <class T, class Allocator>
	class list : public _List_base<T, Allocator>
	{
	public:
		typedef _List_node<T> _Node;
		typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

		iterator insert(iterator position, const T &value)
		{
			_Node *node = _M_create_node(value);
			_List_node_base *at = position._M_node;
			_List_node_base *before = at->_M_prev;
			node->_M_prev = before;
			node->_M_next = at;
			before->_M_next = node;
			at->_M_prev = node;
			return iterator(node);
		}

		void push_back(const T &value)
		{
			insert(iterator(this->_M_node), value);
		}

		unsigned int size() const
		{
			_List_node_base *node = this->_M_node->_M_next;
			_List_node_base *head = this->_M_node;
			unsigned int count = 0;
			while (node != head)
			{
				node = node->_M_next;
				++count;
			}
			return count;
		}

		void pop_front()
		{
			_List_node_base *node = this->_M_node->_M_next;
			_List_node_base *next = node->_M_next;
			_List_node_base *previous = node->_M_prev;
			previous->_M_next = next;
			next->_M_prev = previous;
			((_Node *)node)->_M_data.~T();
			bfmeDeallocate(node, sizeof(_Node));
		}

	private:
		_Node *_M_create_node(const T &value)
		{
			_Node *node = (_Node *)bfmeAllocNode(sizeof(_Node));
			constructBuddyMessageAt(&node->_M_data, value);
			return node;
		}
	};
}

typedef _STL::list<BuddyMessage, int> BuddyMessageList;

class GameSpyInfoView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual BuddyMessageList *getBuddyMessages() = 0;
};

void addBuddyMessage(const BuddyMessage &message)
{
	BuddyMessageList *messages =
		((GameSpyInfoView *)TheGameSpyInfo)->getBuddyMessages();
	messages->push_back(message);
	if (messages->size() > 100)
		messages->pop_front();
}
