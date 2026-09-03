// target experiment for ?doNamedSetModelCondition@ScriptActions@@IAEXABVAsciiString@@H_N@Z
// partial score=0.50 date=2026-09-03

typedef int Int;
typedef bool Bool;

class AsciiString { char *m_data; };
class Object {};
class ScriptEngine
{
public:
	virtual void _0()=0; virtual void _1()=0; virtual void _2()=0; virtual void _3()=0;
	virtual void _4()=0; virtual void _5()=0; virtual void _6()=0; virtual void _7()=0;
	virtual void _8()=0; virtual void _9()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};
extern ScriptEngine *TheScriptEngine;
extern void d_002fdef0(Bool);

class ScriptActions
{
protected:
	void doNamedSetModelCondition(const AsciiString &, Int, Bool);
};

void ScriptActions::doNamedSetModelCondition(const AsciiString &name, Int condition, Bool set)
{
	Object *unit = TheScriptEngine->getUnitNamed(name);
	if (!unit) return;
	d_002fdef0(set);
}
