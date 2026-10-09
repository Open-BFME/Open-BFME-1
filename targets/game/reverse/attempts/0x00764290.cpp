// ?method@BfmeRva64290@@QAEXXZ
// partial score=0.9922 date=2026-10-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Iinputs/reference/shims/debugvtable /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/w3dmodeldraw /Iinputs/reference/shims/asciistring8 /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "WW3D2/RendObj.h"
#include "WW3D2/HTree.h"
#include "string_base.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
extern const Real g_rva01075350;
extern Real g_bfmeDefaultBU;

typedef RenderObjClass BfmeRva64290RenderObj;
typedef RenderObjClass BfmeRva64290SubObj;

class BfmeRva64290DebugStream
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual BfmeRva64290DebugStream *logFormat(const void *); // +0x38
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48();
	virtual void flushCrash(int);                              // +0x4c
};

class BfmeRva64290Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4c(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void beginReport();                            // +0x60
	virtual void slot64(); virtual void slot68();
	virtual BfmeRva64290DebugStream *getStream(void *, void *); // +0x6c
};

extern BfmeRva64290Debug *g_BFMEIndexBufferDebug;
extern Bool __cdecl _bfme_debugReportingEnabled();
extern void __cdecl _bfme_debugRecordCallsite(int);

#include "debug/debug.h"
typedef Debug::Format DebugFormat;

class Rva0075C8B0RenderTarget;
class Rva0075C8B0Owner
{
public:
	void update(Rva0075C8B0RenderTarget *, Real);
};

struct BfmeRva64290WeaponBarrel
{
	AsciiString m_name;
	Bool m_hide;
	unsigned char m_pad04[3];
	Real m_f8;
	Real m_fc;
	Real m_f10;
	Real m_f14;

	const char *name() const
	{
		return m_name.str();
	}
};

class BfmeRva64290WeaponBarrelVector
{
public:
	BfmeRva64290WeaponBarrel *m_begin;
	BfmeRva64290WeaponBarrel *m_end;
	BfmeRva64290WeaponBarrel *m_capacity;
	bool empty() const { return m_begin == m_end; }
	BfmeRva64290WeaponBarrel *begin() const { return m_begin; }
	BfmeRva64290WeaponBarrel *end() const { return m_end; }
};

#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/Override.h"
class Rva00764290Template : public Overridable
{
public:
    unsigned char m_pad0c[0x14];
    AsciiString m_name;
};

class Rva00764290Drawable
{
public:
    void *m_pad00;
    OVERRIDE<Rva00764290Template> m_template;
    const Rva00764290Template *getTemplate() const { return m_template; }
};

static void doHideShowBoneSubObjs(Bool state, Int numSubObjects, Int boneIdx, RenderObjClass *fullObject, const HTreeClass *htree)
{
	for (Int i=0; i < numSubObjects; i++) 
	{
		RenderObjClass *childObject = fullObject->Get_Sub_Object(i);
		if (childObject)
		{
			Int parentBoneIndex = fullObject->Get_Sub_Object_Bone_Index(childObject);
			childObject->Release_Ref();
			while (parentBoneIndex > 0 && parentBoneIndex < fullObject->Get_Num_Bones())
			{
				parentBoneIndex = htree->Get_Parent_Index(parentBoneIndex);
				if (parentBoneIndex == boneIdx)
				{
					childObject = fullObject->Get_Sub_Object(i);
					if (childObject)
					{
						childObject->Set_Hidden(state);
						childObject->Release_Ref();
					}
					break;
				}
			}
		}
	}
}


class BfmeRva64290
{
public:
	void method();

	char m_pad00[0x28];
	BfmeRva64290RenderObj *m_renderObject; // +0x28 in the observed view
	char m_pad2c[0x40 - 0x2c];
	union {
		BfmeRva64290WeaponBarrelVector m_vecA;
		struct { BfmeRva64290WeaponBarrel *m_vecABegin; BfmeRva64290WeaponBarrel *m_vecAEnd; char m_pad2[4]; };
	};
	union {
		BfmeRva64290WeaponBarrelVector m_vecB;
		struct { BfmeRva64290WeaponBarrel *m_vecBBegin; BfmeRva64290WeaponBarrel *m_vecBEnd; void *m_capacityB; };
	};
	char m_pad54[0x9c - 0x58];
	int m_debugBudget;             // +0x9c
	char m_pad_a0[0x164 - 0xa0];
	unsigned char m_flag164;       // +0x164
	unsigned char m_flag165;       // +0x165
};

// ?method@BfmeRva64290@@QAEXXZ present-unmatched
void BfmeRva64290::method()
{
	m_flag164 = 0;
	m_flag165 = 0;
	if (!m_renderObject)
		return;

	if (!m_vecA.empty())
	{
		for (BfmeRva64290WeaponBarrel *entry = m_vecA.begin();
			entry != m_vecA.end(); ++entry)
		{
			int objIndex;
			BfmeRva64290RenderObj *subObj =
				m_renderObject->Get_Sub_Object_By_Name(entry->name(), &objIndex);
			if (subObj)
			{
				subObj->Set_Hidden(entry->m_hide);
				HTreeClass *htree =
					(HTreeClass *)m_renderObject->Get_HTree();
				if (htree)
				{
					int boneIdx = m_renderObject->Get_Sub_Object_Bone_Index(0, objIndex);
					if (boneIdx > 0 && boneIdx < m_renderObject->Get_Num_Bones())
					{
						doHideShowBoneSubObjs(entry->m_hide, m_renderObject->Get_Num_Sub_Objects(), boneIdx, m_renderObject, htree);
					}
				}
				((BfmeRva64290SubObj *)subObj)->Release_Ref();
			}
			else
			{
				if (m_debugBudget > 0)
				{
					--m_debugBudget;
					if (_bfme_debugReportingEnabled())
					{
						_bfme_debugRecordCallsite(1);
						g_BFMEIndexBufferDebug->beginReport();
						Rva00764290Drawable *drawable =
							*(Rva00764290Drawable **)((char *)this - 4);
						const Rva00764290Template *thing = drawable->getTemplate();
						const char *templateName =
							thing->m_name.str();
						const char *entryName = entry->name();
						BfmeRva64290DebugStream *stream =
							g_BFMEIndexBufferDebug->getStream(0, 0);
						((Debug *)stream)->Debug::operator<<(DebugFormat(
							"*** ASSET ERROR: SubObject %s not found (%s)!\n",
							entryName, templateName));
						stream->flushCrash(2);
					}
				}
			}
		}
	}

	if (!m_vecB.empty())
	{
		for (BfmeRva64290WeaponBarrel *entry = m_vecB.begin();
			entry != m_vecB.end(); ++entry)
		{
			int objIndex;
			BfmeRva64290RenderObj *subObj =
				m_renderObject->Get_Sub_Object_By_Name(entry->name(), &objIndex);
			if (subObj)
			{
				if (entry->m_f8 != g_rva01075350)
				{
					Rva00764290Drawable *drawable =
						*(Rva00764290Drawable **)((char *)this - 4);
					if (!*((unsigned char *)drawable + 0x3b2))
					{
						entry->m_f10 = 0.0f;
						entry->m_f14 = 0.0f;
						entry->m_fc = entry->m_f8 > g_rva01075350
							? g_bfmeDefaultBU : g_rva01075350;
						entry->m_f8 = 0.0f;
						((Rva0075C8B0Owner *)((char *)this - 0xc))->update(
							(Rva0075C8B0RenderTarget *)subObj, entry->m_fc);
					}
					else if (entry->m_f10 > g_rva01075350 &&
						entry->m_f14 > g_rva01075350)
					{
						entry->m_f14 -= entry->m_f10;
						if (entry->m_f14 <= g_rva01075350)
							entry->m_f14 = 0.0f;
						m_flag165 = 1;
					}
					else
					{
						entry->m_fc += entry->m_f8;
						if (entry->m_fc > g_bfmeDefaultBU)
							entry->m_fc = 1.0f;
						else if (entry->m_fc < g_rva01075350)
							entry->m_fc = 0.0f;
						((Rva0075C8B0Owner *)((char *)this - 0xc))->update(
							(Rva0075C8B0RenderTarget *)subObj, entry->m_fc);
					}
				}
				else
					subObj->Set_Hidden(entry->m_hide);

				HTreeClass *htree =
					(HTreeClass *)m_renderObject->Get_HTree();
				if (htree)
				{
					int boneIdx = m_renderObject->Get_Sub_Object_Bone_Index(0, objIndex);
					if (boneIdx > 0 && boneIdx < m_renderObject->Get_Num_Bones())
					{
						doHideShowBoneSubObjs(entry->m_hide, m_renderObject->Get_Num_Sub_Objects(), boneIdx, m_renderObject, htree);
					}
				}
				((BfmeRva64290SubObj *)subObj)->Release_Ref();
			}
		}
	}
}
