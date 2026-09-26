// cl: /DNDEBUG /MD /EHsc

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot0a(void);
	virtual void slot0b(void);
	virtual void slot0c(void);
	virtual void slot0d(void);
	virtual void slot0e(void);
	virtual void slot0f(void);
	virtual void Remove(void);
};

struct Rva00943C60Node
{
	Rva00943C60Node *prev;
	Rva00943C60Node *next;
	Rva00943C60Node *next_list;
	void *object;
	void *list;
};

template <class T>
class RefMultiListClass
{
public:
	virtual void slot00(void);
	Rva00943C60Node head;
	void Reset_List(void);
};

class RenderInfoClass;

class SimpleSceneClass
{

protected:
	virtual void Post_Render_Processing(RenderInfoClass &rinfo);

private:
	unsigned char before_render_list[0xa0];
	RefMultiListClass<RenderObjClass> render_list;
};

void SimpleSceneClass::Post_Render_Processing(RenderInfoClass &rinfo)
{
	RefMultiListClass<RenderObjClass> *list = &render_list;
	Rva00943C60Node *node = render_list.head.next;
	Rva00943C60Node *head = &list->head;

	if (node != head) {
		do {
			RenderObjClass *object =
				node->object != 0
					? reinterpret_cast<RenderObjClass *>(
						reinterpret_cast<char *>(node->object) - 8)
					: 0;
			object->Remove();
			node = node->next;
		} while (node != head);
	}

	list->Reset_List();
}
