// cl: /DNDEBUG /MD /EHsc
// upstream TU: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Helper/ObjectDefectionHelper.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	enum ObjectPrivateStatusBits
	{
		UNDETECTED_DEFECTOR = (1 << 1)
	};

	unsigned char m_unreconstructed_00[0x344];
	unsigned char m_privateStatus;				///< retail this+0x344
};

class GameLogicFrameSource
{
public:
	unsigned char m_unreconstructed_00[0x3C];
	unsigned int m_frame;						///< retail this+0x3C
};

extern GameLogicFrameSource *TheGameLogic;		///< retail [0x012F0898]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h
class ObjectHelper
{
public:
	ObjectHelper(Thing *, const ModuleData *);	///< pinned at 0x00021BE8
};

extern "C" char ObjectDefectionHelper_vtbl0;	///< retail 0x0109E574
extern "C" char ObjectDefectionHelper_vtbl0C;	///< retail 0x0109E4B0
extern "C" char ObjectDefectionHelper_vtbl10;	///< retail 0x0109E4A0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectDefectionHelper.h
class ObjectDefectionHelper : public ObjectHelper
{
public:
	ObjectDefectionHelper(Thing *thing, const ModuleData *modData);

	void startDefectionTimer(unsigned int numFrames, bool withDefectorFX);
	void applyDefectionFrame(Object *, int);	///< pinned to the ILT thunk at 0x000157DA; upstream reaches it as UpdateModule::setWakeFrame

private:
	unsigned char m_unreconstructed_00[0x08];		///< base vtable slot and module data; the stub ObjectHelper above carries neither
	Object *m_owner;								///< retail this+0x08; upstream ObjectModule::m_object
	unsigned char m_unreconstructed_0C[0x20 - 0x0C];	///< the two interface vtable slots restamped by the ctor
	unsigned int  m_defectionDetectionStart;		///< retail this+0x20
	unsigned int  m_defectionDetectionEnd;			///< retail this+0x24
	float         m_defectionDetectionFlashPhase;	///< retail this+0x28
	bool          m_doDefectorFX;					///< retail this+0x2C
};

// ??0ObjectDefectionHelper@@QAE@PAVThing@@PBVModuleData@@@Z
ObjectDefectionHelper::ObjectDefectionHelper(Thing *thing, const ModuleData *modData) :
	ObjectHelper(thing, modData)
{
	m_defectionDetectionEnd = 0;
	m_defectionDetectionFlashPhase = 0.0f;
	m_defectionDetectionStart = 0;
	m_doDefectorFX = false;

	// The stub ObjectHelper base declares no virtuals, so this class installs the
	// three vtables (ObjectHelper, UpdateModuleInterface, BehaviorModuleInterface)
	// the real hierarchy would have emitted for it.
	*reinterpret_cast<char **>(this) = &ObjectDefectionHelper_vtbl0;
	*reinterpret_cast<char **>(reinterpret_cast<char *>(this) + 0x0C) = &ObjectDefectionHelper_vtbl0C;
	*reinterpret_cast<char **>(reinterpret_cast<char *>(this) + 0x10) = &ObjectDefectionHelper_vtbl10;
}

// ?startDefectionTimer@ObjectDefectionHelper@@QAEXI_N@Z
void ObjectDefectionHelper::startDefectionTimer(unsigned int numFrames, bool withDefectorFX)
{
	Object *obj = m_owner;

	if ((obj->m_privateStatus & Object::UNDETECTED_DEFECTOR) == 0)
	{
		applyDefectionFrame(obj, UPDATE_SLEEP_FOREVER);
		return;
	}

	unsigned int now = TheGameLogic->m_frame;
	m_defectionDetectionStart = now;
	m_defectionDetectionEnd = now + numFrames;
	m_defectionDetectionFlashPhase = 0.0f;
	m_doDefectorFX = withDefectorFX;

	applyDefectionFrame(obj, UPDATE_SLEEP_NONE);
}
