// ?updateBones@W3DTruckDraw@@IAEXXZ
// partial score=0.76 date=2026-09-02
// cl: /DNDEBUG /DBFME_MODULE_NO_MPO /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/debugvtable /Ireference/shims/w3dmodeldraw /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Benchmark /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "W3DDevice/GameClient/Module/W3DTruckDraw.h"

class Debug
{
public:
	class Format
	{
		char m_buffer[512];
	public:
		explicit Format(const char *format, ...);
	};
};

class TruckBoneCrashMessage
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual TruckBoneCrashMessage *setText(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void show(int mode);
};

class TruckBoneDebugManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void beginReport();
	virtual void slot64(); virtual void slot68();
	virtual TruckBoneCrashMessage *getCrashMessage(void *first, void *second);
};

extern TruckBoneDebugManager *g_BFMEIndexBufferDebug;
bool _bfme_debugReportingEnabled();
void _bfme_debugRecordCallsite(int kind);

#undef DEBUG_ASSERTCRASH
#define DEBUG_ASSERTCRASH(condition, message) do { \
	if (!(condition) && _bfme_debugReportingEnabled()) { \
		_bfme_debugRecordCallsite(1); \
		TruckBoneDebugManager *manager = g_BFMEIndexBufferDebug; \
		manager->beginReport(); \
		manager = g_BFMEIndexBufferDebug; \
		TruckBoneCrashMessage *crash = manager->getCrashMessage(0, 0); \
		Debug::Format formatted message; \
		crash->setText((const char *)&formatted)->show(2); \
	} \
} while (0)

static __forceinline AsciiString &bfmeTruckBoneName(W3DTruckDraw *draw, unsigned int offset)
{
	return *(AsciiString *)(*(char **)((char *)draw + 4) + offset);
}

static __forceinline Int &bfmeTruckBoneIndex(W3DTruckDraw *draw, unsigned int offset)
{
	return *(Int *)((char *)draw + offset);
}

void W3DTruckDraw::updateBones(void)
{
	if (*(void **)((char *)this + 4))
	{
		if (!bfmeTruckBoneName(this, 0x168).isEmpty())
		{
			bfmeTruckBoneIndex(this, 0x2b4) = getRenderObject()->Get_Bone_Index(bfmeTruckBoneName(this, 0x168).str());
			DEBUG_ASSERTCRASH(bfmeTruckBoneIndex(this, 0x2b4), ("Missing front-left tire bone %s in model %s\n", bfmeTruckBoneName(this, 0x168).str(), getRenderObject()->Get_Name()));
		}

		if (!bfmeTruckBoneName(this, 0x16c).isEmpty())
		{
			bfmeTruckBoneIndex(this, 0x2b8) = getRenderObject()->Get_Bone_Index(bfmeTruckBoneName(this, 0x16c).str());
			DEBUG_ASSERTCRASH(bfmeTruckBoneIndex(this, 0x2b8), ("Missing front-right tire bone %s in model %s\n", bfmeTruckBoneName(this, 0x16c).str(), getRenderObject()->Get_Name()));
		}

		if (!bfmeTruckBoneName(this, 0x170).isEmpty())
		{
			bfmeTruckBoneIndex(this, 0x2bc) = getRenderObject()->Get_Bone_Index(bfmeTruckBoneName(this, 0x170).str());
			DEBUG_ASSERTCRASH(bfmeTruckBoneIndex(this, 0x2bc), ("Missing rear-left tire bone %s in model %s\n", bfmeTruckBoneName(this, 0x170).str(), getRenderObject()->Get_Name()));
		}

		if (!bfmeTruckBoneName(this, 0x174).isEmpty())
		{
			bfmeTruckBoneIndex(this, 0x2c0) = getRenderObject()->Get_Bone_Index(bfmeTruckBoneName(this, 0x174).str());
			DEBUG_ASSERTCRASH(bfmeTruckBoneIndex(this, 0x2c0), ("Missing rear-left tire bone %s in model %s\n", bfmeTruckBoneName(this, 0x174).str(), getRenderObject()->Get_Name()));
		}

		if (!getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.isEmpty())
		{
			m_midFrontLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midFrontLeftTireBone, ("Missing mid-front-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midFrontLeftTireBoneName.str(), getRenderObject()->Get_Name()));

			m_midFrontRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midFrontRightTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midFrontRightTireBone, ("Missing mid-front-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midFrontRightTireBoneName.str(), getRenderObject()->Get_Name()));

			if (!m_midFrontRightTireBone)
				m_midFrontLeftTireBone = 0;
		}

		if (!getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.isEmpty())
		{
			m_midRearLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midRearLeftTireBone, ("Missing mid-rear-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midRearLeftTireBoneName.str(), getRenderObject()->Get_Name()));

			m_midRearRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midRearRightTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midRearRightTireBone, ("Missing mid-rear-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midRearRightTireBoneName.str(), getRenderObject()->Get_Name()));

			if (!m_midRearRightTireBone)
				m_midRearLeftTireBone = 0;
		}

		if (!getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.isEmpty())
		{
			m_midMidLeftTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midMidLeftTireBone, ("Missing mid-mid-left tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midMidLeftTireBoneName.str(), getRenderObject()->Get_Name()));

			m_midMidRightTireBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_midMidRightTireBoneName.str());
			DEBUG_ASSERTCRASH(m_midMidRightTireBone, ("Missing mid-mid-right tire bone %s in model %s\n", getW3DTruckDrawModuleData()->m_midMidRightTireBoneName.str(), getRenderObject()->Get_Name()));

			if (!m_midMidRightTireBone)
				m_midMidLeftTireBone = 0;
		}

		// BFME adds three more left/right tire pairs after the Zero Hour layout.
		char *bfmeModuleData = *(char **)((char *)this + 4);
		AsciiString *secondaryFrontLeftName = (AsciiString *)(bfmeModuleData + 0x190);
		AsciiString *secondaryFrontRightName = (AsciiString *)(bfmeModuleData + 0x194);
		Int &secondaryFrontLeftBone = *(Int *)((char *)this + 0x2dc);
		Int &secondaryFrontRightBone = *(Int *)((char *)this + 0x2e0);
		if (!secondaryFrontLeftName->isEmpty())
		{
			secondaryFrontLeftBone = getRenderObject()->Get_Bone_Index(secondaryFrontLeftName->str());
			DEBUG_ASSERTCRASH(secondaryFrontLeftBone, ("Missing secondary front-left tire bone %s in model %s\n", secondaryFrontLeftName->str(), getRenderObject()->Get_Name()));
			secondaryFrontRightBone = getRenderObject()->Get_Bone_Index(secondaryFrontRightName->str());
			DEBUG_ASSERTCRASH(secondaryFrontRightBone, ("Missing secondary front-right tire bone %s in model %s\n", secondaryFrontRightName->str(), getRenderObject()->Get_Name()));
			if (!secondaryFrontRightBone)
				secondaryFrontLeftBone = 0;
		}

		AsciiString *secondaryRearLeftName = (AsciiString *)(bfmeModuleData + 0x198);
		AsciiString *secondaryRearRightName = (AsciiString *)(bfmeModuleData + 0x19c);
		Int &secondaryRearLeftBone = *(Int *)((char *)this + 0x2e4);
		Int &secondaryRearRightBone = *(Int *)((char *)this + 0x2e8);
		if (!secondaryRearLeftName->isEmpty())
		{
			secondaryRearLeftBone = getRenderObject()->Get_Bone_Index(secondaryRearLeftName->str());
			DEBUG_ASSERTCRASH(secondaryRearLeftBone, ("Missing secondary rear-left tire bone %s in model %s\n", secondaryRearLeftName->str(), getRenderObject()->Get_Name()));
			secondaryRearRightBone = getRenderObject()->Get_Bone_Index(secondaryRearRightName->str());
			DEBUG_ASSERTCRASH(secondaryRearRightBone, ("Missing secondary rear-left tire bone %s in model %s\n", secondaryRearRightName->str(), getRenderObject()->Get_Name()));
			if (!secondaryRearRightBone)
				secondaryRearLeftBone = 0;
		}

		AsciiString *secondaryMidMidLeftName = (AsciiString *)(bfmeModuleData + 0x1a0);
		AsciiString *secondaryMidMidRightName = (AsciiString *)(bfmeModuleData + 0x1a4);
		Int &secondaryMidMidLeftBone = *(Int *)((char *)this + 0x2ec);
		Int &secondaryMidMidRightBone = *(Int *)((char *)this + 0x2f0);
		if (!secondaryMidMidLeftName->isEmpty())
		{
			secondaryMidMidLeftBone = getRenderObject()->Get_Bone_Index(secondaryMidMidLeftName->str());
			DEBUG_ASSERTCRASH(secondaryMidMidLeftBone, ("Missing secondary mid-mid-left tire bone %s in model %s\n", secondaryMidMidLeftName->str(), getRenderObject()->Get_Name()));
			secondaryMidMidRightBone = getRenderObject()->Get_Bone_Index(secondaryMidMidRightName->str());
			DEBUG_ASSERTCRASH(secondaryMidMidRightBone, ("Missing secondary mid-mid-right tire bone %s in model %s\n", secondaryMidMidRightName->str(), getRenderObject()->Get_Name()));
			if (!secondaryMidMidRightBone)
				secondaryMidMidLeftBone = 0;
		}

		if (!getW3DTruckDrawModuleData()->m_cabBoneName.isEmpty())
		{
			m_cabBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_cabBoneName.str());
			DEBUG_ASSERTCRASH(m_cabBone, ("Missing cab bone %s in model %s\n", getW3DTruckDrawModuleData()->m_cabBoneName.str(), getRenderObject()->Get_Name()));
			m_trailerBone = getRenderObject()->Get_Bone_Index(getW3DTruckDrawModuleData()->m_trailerBoneName.str());
		}
	}

	m_prevRenderObj = getRenderObject();
	m_prevNumBones = m_prevRenderObj->Get_Num_Bones();
}
