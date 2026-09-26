// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep


#include "multilist.h"
#include "wwmemlog.h"

/*
** Delcare the pool for ListNodes
*/
DEFINE_AUTO_POOL(MultiListNodeClass, 256);


MultiListObjectClass::~MultiListObjectClass(void)
{
	while (ListNode) {
		ListNode->List->Internal_Remove(this);
	}
}


GenericMultiListClass::~GenericMultiListClass(void)
{
	assert(Is_Empty());
}

bool GenericMultiListClass::Contains(MultiListObjectClass * obj)
{
	assert(obj);

	MultiListNodeClass* lnode = obj->Get_List_Node();
	while (lnode) {
		if (lnode->List == this) return true;
		lnode = lnode->NextList;
	}
	return false;
}

int GenericMultiListClass::Count(void)
{
	int counter = 0;
	GenericMultiListIterator it(this);
	for (it.First(); !it.Is_Done(); it.Next()) {
		counter++;
	}
	return counter;
}

bool GenericMultiListClass::Internal_Add(MultiListObjectClass *obj, bool onlyonce)
{
	WWMEMLOG(MEM_GAMEDATA);
	assert(obj);

	if (onlyonce && Is_In_List(obj)) {
		return false;
	}

	// allocate a list node for this object
	MultiListNodeClass *node = new MultiListNodeClass;
	node->Object = obj;

	// link the list node into the list of list nodes for the object
	node->NextList = obj->Get_List_Node();
	obj->Set_List_Node(node);

	// link the node to the objects in *this* list
	node->Prev = &(Head);
	node->Next = Head.Next;
	node->Next->Prev = node;
	node->Prev->Next = node;

	// identify this node as being part of this list
	node->List = this;

	return true;
}

bool GenericMultiListClass::Internal_Add_Tail(MultiListObjectClass * obj,bool onlyonce)
{
	WWMEMLOG(MEM_GAMEDATA);
	assert(obj);

	if (onlyonce && Is_In_List(obj)) {
		return false;
	}

	// allocate a list node for this object
	MultiListNodeClass *node = new MultiListNodeClass;
	node->Object = obj;

	// link the list node into the list of list nodes for the object
	node->NextList = obj->Get_List_Node();
	obj->Set_List_Node(node);

	// link the node to the tail of this list (next should be head, prev should be head.Prev)
	node->Prev = Head.Prev;
	node->Next = &(Head);
	node->Next->Prev = node;
	node->Prev->Next = node;

	// identify this node as being part of this list
	node->List = this;

	return true;
}

bool GenericMultiListClass::Internal_Add_After(MultiListObjectClass * obj,const MultiListObjectClass * existing_list_member,bool onlyonce)
{
	WWMEMLOG(MEM_GAMEDATA);
	assert(obj);
	assert(existing_list_member);

	if (onlyonce && Is_In_List(obj)) {
		return false;
	}

	// find the node hanging off 'existing_list_member' that corresponds to this list (O(numlists))
	MultiListNodeClass * existing_node = existing_list_member->Get_List_Node();
	while ((existing_node->List != this) && (existing_node)) {
		existing_node = existing_node->NextList;
	}

	if (existing_node == NULL) {
		return false;	// he's not in this list!
	}

	// allocate a node
	MultiListNodeClass * node = new MultiListNodeClass;
	node->Object = obj;

	// link the node into the list of list nodes for the object
	node->NextList = obj->Get_List_Node();
	obj->Set_List_Node(node);

	// now, link the new node after existing_node
	node->Prev = existing_node;
	node->Next = existing_node->Next;
	node->Next->Prev = node;
	node->Prev->Next = node;
	node->List = this;

	return true;
}

// ?Internal_Remove@GenericMultiListClass@@IAE_NPAVMultiListObjectClass@@@Z
bool GenericMultiListClass::Internal_Remove(MultiListObjectClass *obj)
{
	// Find the node for this list in the object's list-node chain.
	MultiListNodeClass *lnode = obj->Get_List_Node();
	MultiListNodeClass *prevlnode = 0;

	while ((lnode) && (lnode->List != this)) {
		prevlnode = lnode;
		lnode = lnode->NextList;
	}

	if (lnode == 0) {
		return false;
	}

	lnode->Prev->Next = lnode->Next;
	lnode->Next->Prev = lnode->Prev;

	if (prevlnode) {
		prevlnode->NextList = lnode->NextList;
	} else {
		obj->Set_List_Node(lnode->NextList);
	}

	delete lnode;
	return true;
}

MultiListObjectClass * GenericMultiListClass::Internal_Remove_List_Head(void)
{
	if (Head.Next == &Head) {
		return 0;					// no more objects
	}

	MultiListNodeClass * node = Head.Next;
	MultiListObjectClass * obj = node->Object;

	// remove the object from our list
	Internal_Remove(obj);

	// here you go.
	return obj;
}
