// ??0ObjectSMCHelper@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.88 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc
class Thing;
class ModuleData;

class ObjectHelper
{
public:
	ObjectHelper(Thing *, const ModuleData *);
	~ObjectHelper();
private:
	unsigned char m_bfmeBase[0x20];
};

struct ObjectSMCListNode
{
	ObjectSMCListNode *m_next;
	ObjectSMCListNode *m_prev;
	unsigned int m_value0;
	unsigned int m_value1;
};

class ObjectSMCHelper : public ObjectHelper
{
public:
	ObjectSMCHelper(Thing *thing, const ModuleData *moduleData);
private:
	ObjectSMCListNode *m_list;
};

ObjectSMCHelper::ObjectSMCHelper(Thing *thing, const ModuleData *moduleData)
	: ObjectHelper(thing, moduleData)
{
	*reinterpret_cast<void *volatile *>(this) = reinterpret_cast<void *>(0x0109ebbc);
	*reinterpret_cast<void *volatile *>(reinterpret_cast<char *>(this) + 0x0c) = reinterpret_cast<void *>(0x0109eaf8);
	*reinterpret_cast<void *volatile *>(reinterpret_cast<char *>(this) + 0x10) = reinterpret_cast<void *>(0x0109eaec);
	ObjectSMCListNode *empty = 0;
	m_list = empty;

	ObjectSMCListNode *node = new ObjectSMCListNode;
	node->m_next = node;
	node->m_prev = node;
	m_list = node;
}
