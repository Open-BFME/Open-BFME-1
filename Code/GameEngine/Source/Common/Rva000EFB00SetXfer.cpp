// cl: /DNDEBUG /MD
// Retail 0x000EFB00: cdecl xfer of a pointer-header int set (BfmeObjectIDTree).
// Strings: "std::set" at 0x01085E5C and "Set must be empty on load" at 0x01085E3C.

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

struct XferException
{
	char *m_text;
	int m_tag;
};

struct BfmeInsertResult
{
	void *m_iterator;
	bool m_inserted;
};

struct RbNode
{
	int m_color;
	RbNode *m_parent;
	RbNode *m_left;
	RbNode *m_right;
	int m_value;
};

class BfmeObjectIDTree
{
public:
	RbNode *m_header;
	unsigned int m_size;
	BfmeInsertResult insertUnique(const int &id);
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading();
	virtual bool IsStoring();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(unsigned int *value);
};

namespace _STL {
struct _Rb_tree_node_base;
template <class T>
struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *);
};
}

extern "C" XferException *__cdecl bfmeFormatText(XferException *, int, const char *, ...);
extern "C" int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern void __cdecl bfmeCalcTGC(void *, int *);

Xfer *xferObjectIDSet(Xfer *xfer, BfmeObjectIDTree *tree)
{
	Xfer *x = xfer;
	BfmeObjectIDTree *t = tree;

	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	x->xferVersion(&version);

	unsigned int count = t->m_size;
	x->xferTypeName("std::set").xferUnsignedInt(&count);

	if (x->IsStoring())
	{
		RbNode *sent = t->m_header;
		RbNode *node = sent->m_left;
		while (node != sent)
		{
			bfmeCalcTGC(x, &node->m_value);
			node = (RbNode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)node);
		}
	}
	else
	{
		if (t->m_size != 0)
		{
			XferException error;
			bfmeFormatText(&error, 4, "Set must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		while (count)
		{
			--count;
			int value;
			bfmeCalcTGC(x, &value);
			t->insertUnique(value);
		}
	}
	return x;
}
