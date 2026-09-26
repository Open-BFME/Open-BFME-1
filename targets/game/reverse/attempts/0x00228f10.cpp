// ?positionContainedObjectsRelativeToContainer@OpenContain@@UAEXABV?$list@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@AAV?$map@IHU?$less@I@_STL@@V?$allocator@U?$pair@$$CBIH@_STL@@@2@@3@@Z
// partial score=0.35 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE

#include "Common/AsciiString.h"
#include "matrix3d.h"
#include <bitset>
#include <list>
#include <map>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt ObjectID;

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

template <int NUMBITS>
class BitFlags
{
public:
	 enum BogusInitType
	{
		kInit = 0
	};

	BitFlags()
	{
	}

	BitFlags(BogusInitType, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;
class ModelConditionFlags
{
public:
	ModelConditionFlags()
	{
	}

	ModelConditionFlags(Int tag, UnsignedInt a02, UnsignedInt a03,
		UnsignedInt a04, UnsignedInt a05, UnsignedInt a06);

private:
	_STL::bitset<320> m_bits;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva221A50Triple
{
	UnsignedInt first;
	UnsignedInt second;
	UnsignedInt third;
};

class Object
{
public:
	Int getMultiLogicalBonePosition(const char *name, Int max,
		Coord3D *positions, Matrix3D *matrices, Bool relative,
		Int *indices);
	Bool getSingleLogicalBonePosition(const char *name, Coord3D *position,
		Matrix3D *matrix);
	Bool getSingleLogicalBonePositionOnTurret(Int turret, const char *name,
		Coord3D *position, Matrix3D *matrix);
	void setStatus(const ObjectStatusMaskType &mask, Bool set);
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
	void setTransformMatrix(const Matrix3D *matrix);
	void setPosition(const Coord3D *position);

	void *m_vtable;
	void *m_template;
	Matrix3D m_transform;
	unsigned char m_unmodelled_038[0x3c];
	ObjectID m_id;
	unsigned char m_unmodelled_078[0x1c];
	union
	{
		UnsignedInt m_statusFlags;
		signed char m_statusSign;
	};
};

class OpenContainModuleData
{
public:
	unsigned char m_unmodelled_000[0x120];
	std::map<Int, ModelConditionFlags> m_modelConditions;
	unsigned char m_unmodelled_124[0x29];
	Bool m_passengersInTurret;
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
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
	virtual void setContainedObject(Object *object, Bool set);
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual Rva221A50Triple getStatus(Object *object) const;
};

typedef std::list<Object *> ContainedItemsList;
typedef std::map<ObjectID, Int> ObjectIndexMap;
typedef std::map<ObjectID, AsciiString> BoneNameMap;

class __declspec(novtable) OpenContain
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Bool isEnclosingContainerFor(const Object *object) const = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void positionContainedObjectsRelativeToContainer(
		const ContainedItemsList &list, ObjectIndexMap &indices);

	AsciiString getPassengerBoneName(Object *object);
	Object *getObject()
	{
		return m_object;
	}
	OpenContainModuleData *getOpenContainModuleData()
	{
		return m_moduleData;
	}

	OpenContainModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_00c[0x14];
	ContainModuleInterface m_moduleInterface;
	unsigned char m_unmodelled_024[0x1c];
	BoneNameMap m_boneNames;
};

void OpenContain::positionContainedObjectsRelativeToContainer(
	const ContainedItemsList &list, ObjectIndexMap &indices)
{
	Int boneCount;
	AsciiString current((const char *)0x0107301c);
	Bool useIndexSuffix = true;
	__declspec(align(8)) Matrix3D boneMatrices[32];
	Int boneIndices[32];
	Matrix3D matrix;
	boneCount = 0;

	for (ContainedItemsList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		Object *passenger = *it;
		if ((passenger->m_statusSign & 0x80) != 0)
			continue;

		AsciiString bone = getPassengerBoneName(passenger);
		if (bone.compare(current) != 0)
		{
			boneCount = getObject()->getMultiLogicalBonePosition(
				bone.str(), 32, 0, boneMatrices, true, boneIndices);
			current.set(bone);

			if (boneCount == 0 && getObject()->getSingleLogicalBonePosition(
				bone.str(), 0, &boneMatrices[0]))
			{
				boneCount = 1;
				useIndexSuffix = false;
			}
		}

		ObjectID passengerID = passenger->m_id;
		Int boneIndex = -1;
		ObjectIndexMap::iterator indexIt = indices.lower_bound(passengerID);
		if (indexIt != indices.end() && passengerID >= indexIt->first)
		{
			Int &storedIndex = indices[passengerID];
			if (storedIndex < boneCount)
				boneIndex = storedIndex;
		}
		else
		{
			Int candidateIndex = 0;
			while (candidateIndex < boneCount)
			{
				AsciiString candidate = bone;
				if (useIndexSuffix)
				{
					char digits[12];
					_itoa(candidateIndex + 1, digits, 10);
					if (candidateIndex < 10)
					{
						char zero = '0';
						((StringBase<char> *)&candidate)->concat(&zero, 1);
					}
					((StringBase<char> *)&candidate)->concat(digits, strlen(digits));
				}

				Bool found = false;
				for (BoneNameMap::iterator nameIt = m_boneNames.begin();
					nameIt != m_boneNames.end(); ++nameIt)
				{
					if (candidate.compare(nameIt->second) == 0)
					{
						found = true;
						break;
					}
				}
				if (!found)
					break;
				++candidateIndex;
			}

			boneIndex = candidateIndex;
			indices[passengerID] = boneIndex;
		}

		ContainModuleInterface *interfaceObject = &m_moduleInterface;
		if (boneIndex != -1)
		{
			if ((interfaceObject->getStatus(passenger).first & 2) != 0)
			{
				if ((interfaceObject->getStatus(passenger).second & 0x10000000) == 0)
				{
					ObjectStatusMaskType mask(ObjectStatusMaskType::kInit, 37);
					passenger->setStatus(mask, false);
				}
			}

			AsciiString candidate = bone;
			if (useIndexSuffix)
			{
				char digits[12];
				_itoa(boneIndex + 1, digits, 10);
				if (boneIndex < 10)
				{
					char zero = '0';
					((StringBase<char> *)&candidate)->concat(&zero, 1);
				}
				((StringBase<char> *)&candidate)->concat(digits, strlen(digits));
			}

			m_boneNames[passengerID].set(candidate);
			if (getOpenContainModuleData()->m_passengersInTurret)
			{
				getObject()->getSingleLogicalBonePositionOnTurret(
					0, candidate.str(), 0, &matrix);
			}
			else
			{
				matrix = boneMatrices[boneIndex];
			}

			ModelConditionFlags setFlags(0, 0xbc, 0xbb, 0xba, 0xb9, 0xb8);
			ModelConditionFlags clearFlags;
			getObject()->clearAndSetModelConditionFlags(clearFlags, setFlags);

			std::map<Int, ModelConditionFlags>::iterator conditionIt =
				getOpenContainModuleData()->m_modelConditions.lower_bound(boneIndices[boneIndex]);
			if (conditionIt != getOpenContainModuleData()->m_modelConditions.end() &&
				conditionIt->first == boneIndices[boneIndex])
			{
				ModelConditionFlags clearFlags2;
				getObject()->clearAndSetModelConditionFlags(clearFlags2,
					conditionIt->second);
			}

			interfaceObject->setContainedObject(passenger, false);
		}
		else
		{
			if ((interfaceObject->getStatus(passenger).first & 2) != 0)
			{
				if ((interfaceObject->getStatus(passenger).second & 0x10000000) == 0)
				{
					ObjectStatusMaskType mask(ObjectStatusMaskType::kInit, 37);
					passenger->setStatus(mask, true);
				}
			}

			matrix = getObject()->m_transform;
			interfaceObject->setContainedObject(passenger, true);
		}

		if ((passenger->m_statusFlags & 0x10000000) == 0)
		{
			if (isEnclosingContainerFor(passenger))
			{
				passenger->setTransformMatrix(&matrix);
			}
			else
			{
				Coord3D position;
				position.x = matrix[0][3];
				position.y = matrix[1][3];
				position.z = matrix[2][3];
				passenger->setPosition(&position);
			}
		}
	}
}
