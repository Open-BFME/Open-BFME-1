// cl: /DNDEBUG /MD /EHsc
// BFME's CAMERA_TETHER_NAMED handler at retail RVA 0x002EDB50.

typedef bool Bool;
typedef unsigned int ObjectID;
typedef unsigned int DrawableID;

class AsciiString
{
private:
	char *m_text;
};

class BfmeDrawableWithID
{
public:
	DrawableID bfmeGetID(void);
};

class Object
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual BfmeDrawableWithID *getDrawable(void) const = 0;

private:
	char m_pad[0x70];

public:
	ObjectID m_id;
};

class ScriptEngine
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

class BfmeTacticalView
{
public:
#define BFME_VIEW_SLOT(name) virtual void name(void) = 0;
	BFME_VIEW_SLOT(slot000) BFME_VIEW_SLOT(slot004)
	BFME_VIEW_SLOT(slot008) BFME_VIEW_SLOT(slot00C)
	BFME_VIEW_SLOT(slot010) BFME_VIEW_SLOT(slot014)
	BFME_VIEW_SLOT(slot018) BFME_VIEW_SLOT(slot01C)
	BFME_VIEW_SLOT(slot020) BFME_VIEW_SLOT(slot024)
	BFME_VIEW_SLOT(slot028) BFME_VIEW_SLOT(slot02C)
	BFME_VIEW_SLOT(slot030) BFME_VIEW_SLOT(slot034)
	BFME_VIEW_SLOT(slot038) BFME_VIEW_SLOT(slot03C)
	BFME_VIEW_SLOT(slot040) BFME_VIEW_SLOT(slot044)
	BFME_VIEW_SLOT(slot048) BFME_VIEW_SLOT(slot04C)
	BFME_VIEW_SLOT(slot050) BFME_VIEW_SLOT(slot054)
	BFME_VIEW_SLOT(slot058) BFME_VIEW_SLOT(slot05C)
	BFME_VIEW_SLOT(slot060) BFME_VIEW_SLOT(slot064)
	BFME_VIEW_SLOT(slot068) BFME_VIEW_SLOT(slot06C)
	BFME_VIEW_SLOT(slot070) BFME_VIEW_SLOT(slot074)
	BFME_VIEW_SLOT(slot078) BFME_VIEW_SLOT(slot07C)
	BFME_VIEW_SLOT(slot080) BFME_VIEW_SLOT(slot084)
	BFME_VIEW_SLOT(slot088) BFME_VIEW_SLOT(slot08C)
	BFME_VIEW_SLOT(slot090) BFME_VIEW_SLOT(slot094)
	BFME_VIEW_SLOT(slot098) BFME_VIEW_SLOT(slot09C)
	BFME_VIEW_SLOT(slot0A0) BFME_VIEW_SLOT(slot0A4)
	BFME_VIEW_SLOT(slot0A8) BFME_VIEW_SLOT(slot0AC)
	BFME_VIEW_SLOT(slot0B0) BFME_VIEW_SLOT(slot0B4)
	BFME_VIEW_SLOT(slot0B8) BFME_VIEW_SLOT(slot0BC)
	BFME_VIEW_SLOT(slot0C0) BFME_VIEW_SLOT(slot0C4)
	BFME_VIEW_SLOT(slot0C8) BFME_VIEW_SLOT(slot0CC)
	BFME_VIEW_SLOT(slot0D0) BFME_VIEW_SLOT(slot0D4)
	BFME_VIEW_SLOT(slot0D8) BFME_VIEW_SLOT(slot0DC)
	BFME_VIEW_SLOT(slot0E0) BFME_VIEW_SLOT(slot0E4)
	BFME_VIEW_SLOT(slot0E8) BFME_VIEW_SLOT(slot0EC)
	BFME_VIEW_SLOT(slot0F0) BFME_VIEW_SLOT(slot0F4)
	BFME_VIEW_SLOT(slot0F8) BFME_VIEW_SLOT(slot0FC)
	BFME_VIEW_SLOT(slot100) BFME_VIEW_SLOT(slot104)
	BFME_VIEW_SLOT(slot108) BFME_VIEW_SLOT(slot10C)
	BFME_VIEW_SLOT(slot110) BFME_VIEW_SLOT(slot114)
	BFME_VIEW_SLOT(slot118) BFME_VIEW_SLOT(slot11C)
	BFME_VIEW_SLOT(slot120) BFME_VIEW_SLOT(slot124)
	BFME_VIEW_SLOT(slot128) BFME_VIEW_SLOT(slot12C)
	BFME_VIEW_SLOT(slot130) BFME_VIEW_SLOT(slot134)
	BFME_VIEW_SLOT(slot138) BFME_VIEW_SLOT(slot13C)
	BFME_VIEW_SLOT(slot140) BFME_VIEW_SLOT(slot144)
	BFME_VIEW_SLOT(slot148) BFME_VIEW_SLOT(slot14C)
	BFME_VIEW_SLOT(slot150) BFME_VIEW_SLOT(slot154)
	BFME_VIEW_SLOT(slot158) BFME_VIEW_SLOT(slot15C)
	BFME_VIEW_SLOT(slot160) BFME_VIEW_SLOT(slot164)
	BFME_VIEW_SLOT(slot168) BFME_VIEW_SLOT(slot16C)
	BFME_VIEW_SLOT(slot170) BFME_VIEW_SLOT(slot174)
	BFME_VIEW_SLOT(slot178) BFME_VIEW_SLOT(slot17C)
	virtual void setCameraLock(ObjectID id) = 0;
	virtual void snapToCameraLock(void) = 0;
	virtual void twoArguments(int first, int second) = 0;
	virtual void oneArgument(float value) = 0;
	BFME_VIEW_SLOT(slot190) BFME_VIEW_SLOT(slot194)
	virtual void setCameraLockDrawableID(DrawableID id) = 0;
#undef BFME_VIEW_SLOT
};

extern ScriptEngine *TheScriptEngine;
extern BfmeTacticalView *TheTacticalView;

class ScriptActions
{
protected:
	void doCameraTetherNamed(const AsciiString &unit, Bool snapToUnit, float play);
};

// ?doCameraTetherNamed@ScriptActions@@IAEXABVAsciiString@@_NM@Z
void ScriptActions::doCameraTetherNamed(const AsciiString &unit, Bool snapToUnit, float play)
{
	Object *theObj = TheScriptEngine->getUnitNamed(unit);
	if (theObj)
	{
		TheTacticalView->setCameraLock(theObj->m_id);
		TheTacticalView->setCameraLockDrawableID(theObj->getDrawable()->bfmeGetID());
		if (snapToUnit)
			TheTacticalView->snapToCameraLock();
		TheTacticalView->oneArgument(play);
		TheTacticalView->twoArguments(0, 0);
	}
}
