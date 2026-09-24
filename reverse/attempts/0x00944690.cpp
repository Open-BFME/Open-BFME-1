// ?method@Rva00944690Scene@@UAEXPAVCameraClass@@@Z
// partial score=0.55 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad
#include "../WWLib/always.h"
#include <stdlib.h>
#include "../WWLib/bittype.h"
#include "../WWDebug/wwdebug.h"
#define MEMPOOL_H
template <class T, int N> class AutoPoolClass {};
#include "../WWLib/multilist.h"
#include "camera.h"
#include "rendobj.h"
#include "robjlist.h"
#include "../WWMath/colmath.h"
#include "../WWMath/sphere.h"

template <> void RefMultiListClass<RenderObjClass>::Reset_List(void);

class Rva00944690Scene;

class Gen_00943CF0
{
	void first(void *object, int *first, int *second, int *third);
	void link(void *object, int first, int second, int third);
	void unlink(void *object);
	friend class Rva00944690Scene;
};

class Rva00944430
{
	void rva00944430(void **head, CameraClass *camera, int flags);
	friend class Rva00944690Scene;
};

class Rva00944690NonRefList : public NonRefRenderObjListClass
{
public:
	MultiListObjectClass *remove_head() { return Internal_Remove_List_Head(); }
	bool add(RenderObjClass *object) { return Internal_Add(object, true); }
};

class Rva00944690RefList : public RefRenderObjListClass
{
public:
	MultiListObjectClass *remove_head() { return Internal_Remove_List_Head(); }
	bool add(RenderObjClass *object) { return Internal_Add(object, true); }
};

class Rva00944690Scene
{
public:
	virtual ~Rva00944690Scene();
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26();
	virtual void method(CameraClass *camera);

	char prefix[0x30];
	char grid[0x28];
	Rva00944690NonRefList list_5c;
	Rva00944690NonRefList list_74;
	Rva00944690NonRefList list_8c;
	Rva00944690NonRefList list_a4;
	Rva00944690NonRefList list_bc;
	Rva00944690NonRefList list_d4;
	Rva00944690RefList list_ec;
	unsigned int generation;
};

#define RVA00944690_SLOT(n) virtual void slot##n()
class Rva00944690RenderObjectSlots
{
public:
RVA00944690_SLOT(0); RVA00944690_SLOT(1); RVA00944690_SLOT(2); RVA00944690_SLOT(3);
RVA00944690_SLOT(4); RVA00944690_SLOT(5); RVA00944690_SLOT(6); RVA00944690_SLOT(7);
RVA00944690_SLOT(8); RVA00944690_SLOT(9); RVA00944690_SLOT(10); RVA00944690_SLOT(11);
RVA00944690_SLOT(12); RVA00944690_SLOT(13); RVA00944690_SLOT(14); RVA00944690_SLOT(15);
RVA00944690_SLOT(16); RVA00944690_SLOT(17); RVA00944690_SLOT(18); RVA00944690_SLOT(19);
RVA00944690_SLOT(20); RVA00944690_SLOT(21); RVA00944690_SLOT(22); RVA00944690_SLOT(23);
RVA00944690_SLOT(24); RVA00944690_SLOT(25); RVA00944690_SLOT(26); RVA00944690_SLOT(27);
RVA00944690_SLOT(28); RVA00944690_SLOT(29); RVA00944690_SLOT(30); RVA00944690_SLOT(31);
RVA00944690_SLOT(32); RVA00944690_SLOT(33); RVA00944690_SLOT(34); RVA00944690_SLOT(35);
RVA00944690_SLOT(36); RVA00944690_SLOT(37); RVA00944690_SLOT(38); RVA00944690_SLOT(39);
RVA00944690_SLOT(40); RVA00944690_SLOT(41); RVA00944690_SLOT(42); RVA00944690_SLOT(43);
RVA00944690_SLOT(44); RVA00944690_SLOT(45); RVA00944690_SLOT(46); RVA00944690_SLOT(47);
RVA00944690_SLOT(48); RVA00944690_SLOT(49); RVA00944690_SLOT(50); RVA00944690_SLOT(51);
RVA00944690_SLOT(52); RVA00944690_SLOT(53); RVA00944690_SLOT(54); RVA00944690_SLOT(55);
RVA00944690_SLOT(56); RVA00944690_SLOT(57); RVA00944690_SLOT(58); RVA00944690_SLOT(59);
RVA00944690_SLOT(60); RVA00944690_SLOT(61); RVA00944690_SLOT(62); RVA00944690_SLOT(63);
RVA00944690_SLOT(64); RVA00944690_SLOT(65); RVA00944690_SLOT(66); RVA00944690_SLOT(67);
RVA00944690_SLOT(68); RVA00944690_SLOT(69); RVA00944690_SLOT(70); RVA00944690_SLOT(71);
RVA00944690_SLOT(72); RVA00944690_SLOT(73); RVA00944690_SLOT(74); RVA00944690_SLOT(75);
RVA00944690_SLOT(76); RVA00944690_SLOT(77); RVA00944690_SLOT(78); RVA00944690_SLOT(79);
RVA00944690_SLOT(80); RVA00944690_SLOT(81); RVA00944690_SLOT(82); RVA00944690_SLOT(83);
RVA00944690_SLOT(84); RVA00944690_SLOT(85); RVA00944690_SLOT(86); RVA00944690_SLOT(87);
RVA00944690_SLOT(88); RVA00944690_SLOT(89); RVA00944690_SLOT(90); RVA00944690_SLOT(91);
RVA00944690_SLOT(92); RVA00944690_SLOT(93); RVA00944690_SLOT(94); RVA00944690_SLOT(95);
RVA00944690_SLOT(96); RVA00944690_SLOT(97);
	virtual void slot98(Rva00944690Scene *scene, unsigned int generation);
RVA00944690_SLOT(99); RVA00944690_SLOT(100); RVA00944690_SLOT(101); RVA00944690_SLOT(102);
	virtual int slot103();
};
#undef RVA00944690_SLOT

struct Rva00944690Node
{
	Rva00944690Node *next;
	RenderObjClass *object;
};

namespace _STL {
template <bool threads, int inst> class __node_alloc {
public:
	static void _M_deallocate(void *node, unsigned int size);
};
}

struct Rva00944690LocalList
{
	Rva00944690Node *head;
	Rva00944690LocalList() : head(0) {}
	~Rva00944690LocalList()
	{
		Rva00944690Node *node = head;
		while (node) {
			Rva00944690Node *next = node->next;
			_STL::__node_alloc<true, 0>::_M_deallocate(node, 8);
			node = next;
		}
	}
};

void Rva00944690Scene::method(CameraClass *camera)
{
	Gen_00943CF0 *grid = (Gen_00943CF0 *)((char *)this + 0x34);
	NonRefRenderObjListIterator grid_objects(&list_bc);
	for (grid_objects.First(); !grid_objects.Is_Done(); ) {
		RenderObjClass *object = grid_objects.Peek_Obj();
		int first;
		int second;
		int third;
		grid->first(object, &first, &second, &third);
		int old_key = *(int *)((char *)object + 0x94);
		if (old_key < 0) {
			grid->link(object, first, second, third);
		} else {
			int key = ((first << 10) | second) << 10 | third;
			if (old_key != key) {
				grid->unlink(object);
				grid->link(object, first, second, third);
			}
		}
		grid_objects.Next();
	}

	while (!list_bc.Is_Empty())
		list_bc.remove_head();
	++generation;
	list_ec.Reset_List();

	Rva00944690LocalList local;
	((Rva00944430 *)((char *)this + 0x34))->rva00944430(
		(void **)&local.head, camera, 0);
	Rva00944690Node *node = local.head;
	while (node) {
		RenderObjClass *object = node->object;
		Rva00944690RenderObjectSlots *slots =
			(Rva00944690RenderObjectSlots *)object;
		if (slots->slot103() ||
			CollisionMath::Overlap_Test(camera->Get_Frustum(),
				object->Get_Bounding_Sphere()) != CollisionMath::OUTSIDE) {
			if (list_ec.add(object))
				++*(int *)((char *)object + 4);
			slots->slot98(this, generation);
		}
		node = node->next;
	}

	MultiListIterator<RenderObjClass> extra_objects(&list_d4);
	for (extra_objects.First(); !extra_objects.Is_Done(); extra_objects.Next()) {
		RenderObjClass *object = extra_objects.Peek_Obj();
		if (list_ec.add(object))
			++*(int *)((char *)object + 4);
	}
}
