// ?bfmeAccept@Gen_00168910@@AAEXPAVBfmeSeedTarget@@@Z
// partial score=0.65 date=2026-09-09
// The named Gen_00168910::bfmeSeed caller reaches this body through ILT
// 0x0004B53D.  The body is a transfer of two intrusive lists and the object
// tail; it is kept here as handoff evidence until the exact class ABI is
// recovered.  This is not a generated or lifted body.

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

struct BfmeSeedPair
{
	UnsignedByte m_first;
	UnsignedByte m_second;
};

struct BfmeXferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct BfmeXferException
{
	char *m_text;
	Int m_tag;
};

// The constructor at retail 0x00161220 initializes this 0x30-byte node and
// installs the already-retail table at 0x01096940.  The first list uses
// m_next04/m_previous08; the second uses m_next0C/m_previous10.
struct BfmeNode_00161220
{
	void *m_vptr;
	BfmeNode_00161220 *m_next04;
	BfmeNode_00161220 *m_previous08;
	BfmeNode_00161220 *m_next0C;
	BfmeNode_00161220 *m_previous10;
	UnsignedInt m_value14;
	UnsignedByte m_value18;
	UnsignedByte m_pad19[3];
	UnsignedInt m_value1C;
	UnsignedInt m_value20;
	UnsignedInt m_value24;
	UnsignedByte m_value28;
	UnsignedByte m_value29;
	UnsignedByte m_value2A;
	UnsignedByte m_pad2B;
	UnsignedInt m_value2C;
};

struct BfmeContext_00168910
{
	UnsignedByte m_pad00[0x24];
	UnsignedInt m_value24;
};

class BfmeSeedTarget
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isStoring();
	virtual void slot03();
	virtual Bool skipTransfer();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(BfmeXferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
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
	virtual void xferObjectID(void *value);
	virtual void slot25();
	virtual void slot26();
	virtual void xferString(void *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
};

extern void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *value);
extern "C" BfmeXferException *__cdecl bfmeFormatText(
	BfmeXferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern void j_0002fee6();
extern void j_00008224();
extern void j_0003e81f();

typedef BfmeNode_00161220 *(__cdecl *BfmeNext04)(BfmeNode_00161220 *node);
typedef BfmeNode_00161220 *(__cdecl *BfmeNext0C)(BfmeNode_00161220 *node);
typedef void (__cdecl *BfmeFieldXfer)(BfmeSeedTarget *target, void *value);

class Gen_00168910
{
public:
	void bfmeAccept(BfmeSeedTarget *target);

private:
	void *m_vptr;
	BfmeNode_00161220 *m_list04;
	BfmeNode_00161220 *m_list08;
	BfmeContext_00168910 *m_context0C;
	UnsignedByte m_field10;
	UnsignedByte m_field11;
	UnsignedByte m_pad12[2];
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	UnsignedByte m_pad38[8];
	Int m_field40;
	Int m_field44;
	Int m_field48;
	Int m_field4C;
	Int m_field50;
	Int m_field54;
	UnsignedByte m_pad58[8];
	Int m_field60;
	UnsignedByte m_field64;
	UnsignedByte m_field65;
	UnsignedByte m_pad66[2];
	Int m_field68;
	Int m_field6C;
	UnsignedByte m_field70[4];
	UnsignedByte m_field74[4];
	UnsignedByte m_item78;
	UnsignedByte m_pad79[3];
	UnsignedByte m_item7C;
	UnsignedByte m_pad7D[3];
	UnsignedByte m_item80;
	UnsignedByte m_pad81[3];
	UnsignedByte m_item84;
	UnsignedByte m_pad85[3];
	UnsignedByte m_item88;
	UnsignedByte m_pad89[3];
	UnsignedByte m_item8C;
	UnsignedByte m_pad8D[3];
	UnsignedByte m_item90;
	UnsignedByte m_pad91[3];
	UnsignedByte m_item94;

	static void clearNode(BfmeNode_00161220 *node)
	{
		node->m_vptr = (void *)0x01096940;
		node->m_next04 = 0;
		node->m_previous08 = 0;
		node->m_next0C = 0;
		node->m_previous10 = 0;
		node->m_value14 = 0;
		node->m_value18 = 0;
		node->m_value1C = 0;
		node->m_value20 = 0;
		node->m_value24 = 0;
		node->m_value28 = 0;
		node->m_value29 = 0;
		node->m_value2A = 0;
		node->m_pad2B = 0;
		node->m_value2C = 0;
	}

	static void append04(BfmeNode_00161220 **head, BfmeNode_00161220 *node)
	{
		if (*head == 0)
			*head = node;
		else
		{
			BfmeNode_00161220 *last = *head;
			while (last->m_next04 != 0)
				last = last->m_next04;
			last->m_next04 = node;
			node->m_previous08 = last;
		}
	}

	static void append0C(BfmeNode_00161220 **head, BfmeNode_00161220 *node)
	{
		if (*head == 0)
			*head = node;
		else
		{
			BfmeNode_00161220 *last = *head;
			while (last->m_next0C != 0)
				last = last->m_next0C;
			last->m_next0C = node;
			node->m_previous10 = last;
		}
	}
};

void Gen_00168910::bfmeAccept(BfmeSeedTarget *target)
{
	BfmeXferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 2;

	if (target->skipTransfer())
		return;

	target->xferVersion(&version);
	bfmeHandOver_0000C9B4(target, m_field70);

	UnsignedShort firstCount = 0;
	BfmeNode_00161220 *node;
	for (node = m_list04; node; node = ((BfmeNext04)j_0002fee6)(node))
		++firstCount;
	target->xferUnsignedShort(&firstCount);

	if (target->isStoring())
	{
		for (node = m_list04; node; node = ((BfmeNext04)j_0002fee6)(node))
			target->xferSnapshot(node);
	}
	else
	{
		if (m_list04 != 0)
		{
			BfmeXferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (void *)0x011DFE5C);
		}

		for (UnsignedShort i = 0; i < firstCount; ++i)
		{
			node = (BfmeNode_00161220 *)::operator new(0x30);
			if (node)
			{
				clearNode(node);
				append04(&m_list04, node);
				target->xferSnapshot(node);
			}
		}
	}

	UnsignedShort secondCount = 0;
	for (node = m_list08; node; node = ((BfmeNext0C)j_00008224)(node))
		++secondCount;
	target->xferUnsignedShort(&secondCount);

	if (target->isStoring())
	{
		for (node = m_list08; node; node = ((BfmeNext0C)j_00008224)(node))
			target->xferSnapshot(node);
	}
	else
	{
		if (m_list08 != 0)
		{
			BfmeXferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (void *)0x011DFE5C);
		}

		for (UnsignedShort i = 0; i < secondCount; ++i)
		{
			node = (BfmeNode_00161220 *)::operator new(0x30);
			if (node)
			{
				clearNode(node);
				append0C(&m_list08, node);
				target->xferSnapshot(node);
			}
		}
	}

	UnsignedInt contextValue = m_context0C->m_value24;
	target->xferUnsignedInt(&contextValue);
	if (contextValue != m_context0C->m_value24)
	{
		BfmeXferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	target->xferBool((Bool *)&m_field10);
	target->xferBool((Bool *)&m_field11);
	target->xferUnsignedInt((UnsignedInt *)&m_field14);
	target->xferUnsignedInt((UnsignedInt *)&m_field18);
	target->xferUnsignedInt((UnsignedInt *)&m_field20);
	target->xferUnsignedInt((UnsignedInt *)&m_field24);
	target->xferUnsignedInt((UnsignedInt *)&m_field1C);
	((BfmeFieldXfer)bfmeHandOver_0000C9B4)(target, m_field74);
	target->xferUnsignedInt((UnsignedInt *)&m_field28);
	((BfmeFieldXfer)j_0003e81f)(target, &m_field2C);
	target->xferUnsignedInt((UnsignedInt *)&m_field30);
	target->xferObjectID(&m_field34);
	target->xferBool((Bool *)&m_field40);
	target->xferString(&m_field44);
	((BfmeFieldXfer)bfmeHandOver_0000C9B4)(target, &m_field48);
	((BfmeFieldXfer)bfmeHandOver_0000C9B4)(target, &m_field4C);
	((BfmeFieldXfer)bfmeHandOver_0000C9B4)(target, &m_field50);
	target->xferUnsignedInt((UnsignedInt *)&m_field60);
	target->xferBool((Bool *)&m_field64);
	target->xferBool((Bool *)&m_field65);
	target->xferUnsignedInt((UnsignedInt *)&m_field68);
	if (version.m_currentVersion >= 2)
		target->xferInt(&m_field6C);
}
