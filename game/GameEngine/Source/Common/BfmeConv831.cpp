// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"
#include "GameClient/ControlBar.h"

// ILT 0x0004B290 routes to the matched resolver at 0x0034CB60.
// Its player-mask result and PlayerList input are both 16-bit.
class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name, bool *found);
};

class BfmeMgrF07
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void* vfn26(void *key);
};
// 0x012F076C is retail's ScriptEngine singleton (defined once in
// GameLogic/ScriptEngine/ScriptEngine.cpp). This TU only needs its vtable
// slice, so it reaches it by casting at each use; DIR32 relocations are
// masked by the byte gate, so the emitted bytes are unchanged.
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

static inline BfmeMgrF07 *mgr12F076C() { return (BfmeMgrF07 *)TheScriptEngine; }

class BfmeLinkedObj
{
public:
	void link(BfmeLinkedObj *other, int zero);
};

struct BfmeObjAF0_2
{
	unsigned char pad[0x230];
	void *m_sub230;
};

void __stdcall bfmeLinkObjectsA70(void *k1, void *k2)
{
	unsigned short id2 = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->
		getPlayerMaskFromAsciiString(*(const AsciiString *)k2, 0);
	unsigned short id1 = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->
		getPlayerMaskFromAsciiString(*(const AsciiString *)k1, 0);
	BfmeLinkedObj *obj2 = (BfmeLinkedObj *)ThePlayerList->getPlayerFromMask(id2);
	BfmeLinkedObj *obj1 = (BfmeLinkedObj *)ThePlayerList->getPlayerFromMask(id1);
	if (obj2 && obj1) {
		obj2->link(obj1, 0);
	}
}

void __stdcall bfmeNotifyLinkedBE0(void *k1, void *p3, void *k2)
{
	unsigned short id2 = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->
		getPlayerMaskFromAsciiString(*(const AsciiString *)k2, 0);
	unsigned short id1 = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->
		getPlayerMaskFromAsciiString(*(const AsciiString *)k1, 0);
	Player *obj2 = ThePlayerList->getPlayerFromMask(id2);
	Player *obj1 = ThePlayerList->getPlayerFromMask(id1);
	if (obj2 && obj1) {
		obj1->setPlayerRelationship(obj2, (Relationship)(int)p3);
	}
}

class BfmeObjVfnAF0
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void vfn20(void *sub);
};

int __cdecl bfmeHelper760(void *obj, int zero);

void __stdcall bfmeAttachSubAF0(void *k1, void *k2)
{
	BfmeObjVfnAF0 *obj1 = (BfmeObjVfnAF0*)mgr12F076C()->vfn26(k1);
	unsigned short id2 = ((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)->
		getPlayerMaskFromAsciiString(*(const AsciiString *)k2, 0);
	BfmeObjAF0_2 *obj2 = (BfmeObjAF0_2*)ThePlayerList->getPlayerFromMask(id2);
	if (obj1 && obj2 && obj2->m_sub230) {
		obj1->vfn20(obj2->m_sub230);
		bfmeHelper760(obj1, 0);
	}
}

class BfmeMgr160_D20
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual bool vfn44(int code);
	virtual void v45();
	virtual bool vfn46(int code);
};
// Retail 0x012F1600 is the tactical-view singleton defined once in
// GameClient/View.cpp; this TU only needs the message-manager vtable slice.
class View;
extern View *TheTacticalView;
static inline BfmeMgr160_D20 *mgr160() { return (BfmeMgr160_D20 *)TheTacticalView; }

void __stdcall bfmeCheckBoolsD20(bool b1, bool b2)
{
	if (mgr160()->vfn46(2)) {
		int code = b2 ? (b1 ? 11 : 12) : (b1 ? 9 : 10);
		if (!mgr160()->vfn44(code)) {
			mgr160()->vfn46(0);
		}
	}
}

class BfmeObj720
{
public:
	unsigned char pad[0x144];
	int m_field144;
};

void __stdcall bfmeCalculateAndStore720(void *key, int val)
{
	// ILT 0x0003B59D routes to ControlBar::findCommandButton at 0x004A0310.
	BfmeObj720 *obj = (BfmeObj720 *)TheControlBar->findCommandButton(
		*(const AsciiString *)key);
	if (obj) {
		int v = (val * 30) / 10;
		if (v % 2 == 1) {
			v++;
		}
		obj->m_field144 = v;
	}
}
