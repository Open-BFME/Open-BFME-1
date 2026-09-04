// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Convert of gen-dump ?d_002f0970@@YAXXZ at 0x002F0970 (87 bytes).
// Two ScriptEngine vslot 26 lookups then Object::findSub(0x2E) at ILT
// 0x0001B185; on success call vslot 1 then vslot 12(other, 2).

class AsciiString;

class BfmeSubVfn9E0
{
public:
	virtual void slot00();
	virtual bool test();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void apply(void *other, int flag);
};

class BfmeObj9E0
{
public:
	BfmeSubVfn9E0 *findSub(int code);
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual BfmeObj9E0 *getUnitNamed(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;

void __stdcall d_002f0970(const AsciiString &first, const AsciiString &second)
{
	BfmeObj9E0 *a = TheScriptEngine->getUnitNamed(first);
	BfmeObj9E0 *b = TheScriptEngine->getUnitNamed(second);
	if (a && b)
	{
		BfmeSubVfn9E0 *sub = a->findSub(0x2e);
		if (sub && sub->test())
			sub->apply(b, 2);
	}
}
