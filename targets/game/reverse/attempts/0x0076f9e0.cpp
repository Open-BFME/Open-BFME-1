// ?validate@Rva0076F9E0Owner@@QBEXPAURva0076F9E0Names@@@Z
// partial score=0.19 date=2026-09-22
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Ireference/shims/namekeygenerator /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <stdio.h>
#include <vector>

struct Rva0076F9E0Vector4
{
	float m_x;
	float m_y;
	float m_z;
	float m_w;

	Rva0076F9E0Vector4 &operator=(const Rva0076F9E0Vector4 &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		m_z = other.m_z;
		m_w = other.m_w;
		return *this;
	}
};

struct Matrix3D
{
	Rva0076F9E0Vector4 m_row[3];

	void Make_Identity(void)
	{
		m_row[0].m_x = 1.0f;
		m_row[0].m_y = 0.0f;
		m_row[0].m_z = 0.0f;
		m_row[0].m_w = 0.0f;
		m_row[1].m_x = 0.0f;
		m_row[1].m_y = 1.0f;
		m_row[1].m_z = 0.0f;
		m_row[1].m_w = 0.0f;
		m_row[2].m_x = 0.0f;
		m_row[2].m_y = 0.0f;
		m_row[2].m_z = 0.0f;
		m_row[2].m_w = 1.0f;
	}

	Matrix3D &operator=(const Matrix3D &other)
	{
		m_row[0] = other.m_row[0];
		m_row[1] = other.m_row[1];
		m_row[2] = other.m_row[2];
		return *this;
	}
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern void setFPMode(void);

struct Rva0075B660Logic
{
	char m_pad00[0x6b];
	bool m_flag;
};

struct Rva0075B660State
{
	char m_pad00[0x54];
	bool m_flag;
};

extern Rva0075B660Logic *TheBfmeGameLogic;
extern Rva0075B660State *TheGameState;

struct Rva00769260Node
{
	char m_pad00[0x14];
	char m_result[0x30];
	int m_value;
};

struct Rva00769260Iterator
{
	Rva00769260Iterator(const Rva00769260Iterator &);
	Rva00769260Node *m_node;
};

class Rva00769260Tree
{
public:
	Rva00769260Iterator find(void *const &key);
	Rva00769260Node *m_end;
};

class Rva00769260Owner
{
public:
	void *lookup(void *key, int *value);
};

struct Rva0076F9E0AsciiData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_padding;
};

struct Rva0076F9E0AsciiString
{
	Rva0076F9E0AsciiData *m_data;

	bool isEmpty(void) const
	{
		return m_data == 0 || m_data->m_length == 0;
	}

	const char *str(void) const
	{
		return reinterpret_cast<const char *>(m_data) + 8;
	}
};

struct Rva0076F9E0Names
{
	char m_pad00[0x4c];
	Rva0076F9E0AsciiString m_first[4];
	Rva0076F9E0AsciiString m_second[4];
	Rva0076F9E0AsciiString m_third[4];
	Rva0076F9E0AsciiString m_fourth[4];
};

struct ModelConditionInfo
{
	struct WeaponBarrelInfo
	{
		int m_first;
		int m_second;
		int m_third;
		Matrix3D m_projectileOffsetMtx;

		WeaponBarrelInfo(void)
		{
			clear();
		}

		void clear(void)
		{
			m_first = 0;
			m_second = 0;
			m_third = 0;
			m_projectileOffsetMtx.Make_Identity();
		}

		WeaponBarrelInfo(const WeaponBarrelInfo &other);
	};
};

class Rva0076F9E0Owner
{
public:
	void validate(Rva0076F9E0Names *names) const;

private:
	const Matrix3D *findBone(NameKeyType key, int *boneIndex) const
	{
		if ((m_validStuff & 1) == 0)
		{
			if (boneIndex != 0)
				*boneIndex = 0;
			return 0;
		}

		if (key == NAMEKEY_INVALID)
		{
			if (boneIndex != 0)
				*boneIndex = 0;
			return 0;
		}

		void *keyPointer = reinterpret_cast<void *>(static_cast<unsigned int>(key));
		Rva00769260Iterator found = m_pristineBones.find(keyPointer);
		if (found.m_node != m_pristineBones.m_end)
		{
			if (boneIndex != 0)
				*boneIndex = found.m_node->m_value;
			return reinterpret_cast<const Matrix3D *>(found.m_node->m_result);
		}

		if (boneIndex != 0)
			*boneIndex = 0;
		return 0;
	}

	char m_pad00[0x70];
	mutable Rva00769260Tree m_pristineBones;
	char m_pad74[8];
	mutable _STL::vector<ModelConditionInfo::WeaponBarrelInfo> m_weaponBarrelInfoVec[4];
	mutable unsigned char m_validStuff;
	char m_padAD[0x73];
	mutable unsigned char m_hasRecoilBonesOrMuzzleFlashes[4];
};

void Rva0076F9E0Owner::validate(Rva0076F9E0Names *names) const
{
	if ((m_validStuff & 8) != 0)
		return;

	if (TheBfmeGameLogic == 0 || !TheBfmeGameLogic->m_flag)
	{
		if (TheGameState == 0 || !TheGameState->m_flag)
			return;
	}

	setFPMode();

	for (int wslot = 0; wslot < 4; ++wslot)
	{
		_STL::vector<ModelConditionInfo::WeaponBarrelInfo> &barrelVec =
			m_weaponBarrelInfoVec[wslot];
		barrelVec.clear();
		m_hasRecoilBonesOrMuzzleFlashes[wslot] = false;

		const Rva0076F9E0AsciiString &firstName = names->m_first[wslot];
		const Rva0076F9E0AsciiString &secondName = names->m_second[wslot];
		const Rva0076F9E0AsciiString &thirdName = names->m_third[wslot];
		const Rva0076F9E0AsciiString &fourthName = names->m_fourth[wslot];

		if (firstName.isEmpty() && fourthName.isEmpty())
			continue;

		volatile int previousBone = 0;
		char buffer[256];
		for (int i = 1; i <= 99; ++i)
		{
			ModelConditionInfo::WeaponBarrelInfo info;
			info.m_projectileOffsetMtx.Make_Identity();
			if (!secondName.isEmpty())
			{
				sprintf(buffer, "%s%02d", secondName.str(), i);
				NameKeyType key = TheNameKeyGenerator->nameToKey(buffer);
				int bone = 0;
				const Matrix3D *matrix = findBone(key, &bone);
				if (matrix != 0)
					info.m_first = bone;
			}
			if (!thirdName.isEmpty())
			{
				sprintf(buffer, "%s%02d", thirdName.str(), i);
				NameKeyType key = TheNameKeyGenerator->nameToKey(buffer);
				int bone = 0;
				const Matrix3D *matrix = findBone(key, &bone);
				if (matrix != 0)
					info.m_third = bone;
			}
			if (!firstName.isEmpty())
			{
				sprintf(buffer, "%s%02d", firstName.str(), i);
				NameKeyType key = TheNameKeyGenerator->nameToKey(buffer);
				int bone = 0;
				const Matrix3D *matrix = findBone(key, &bone);
				if (matrix != 0)
					info.m_second = bone;
				if (info.m_second == 0 && info.m_third != 0)
					info.m_second = previousBone;
			}

			int projectileBone = 0;
			if (!fourthName.isEmpty())
			{
				sprintf(buffer, "%s%02d", fourthName.str(), i);
				NameKeyType key = TheNameKeyGenerator->nameToKey(buffer);
				const Matrix3D *matrix = findBone(key, &projectileBone);
				if (matrix != 0)
					info.m_projectileOffsetMtx = *matrix;
			}

			if (info.m_first == 0 && info.m_second == 0 &&
					info.m_third == 0 && projectileBone == 0)
				break;

			barrelVec.push_back(info);
			if (info.m_first != 0 || info.m_third != 0)
				m_hasRecoilBonesOrMuzzleFlashes[wslot] = true;
			previousBone = info.m_second;
		}

		if (barrelVec.empty())
		{
			ModelConditionInfo::WeaponBarrelInfo info;
			const Matrix3D *projectileMatrix = 0;
			if (!fourthName.isEmpty())
			{
				NameKeyType key = TheNameKeyGenerator->nameToKey(fourthName.str());
				projectileMatrix = findBone(key, 0);
			}
			if (projectileMatrix != 0)
				info.m_projectileOffsetMtx = *projectileMatrix;
			else
				info.m_projectileOffsetMtx.Make_Identity();

			if (!firstName.isEmpty())
			{
				NameKeyType key = TheNameKeyGenerator->nameToKey(firstName.str());
				Rva00769260Owner *lookupOwner = const_cast<Rva00769260Owner *>(
					reinterpret_cast<const Rva00769260Owner *>(this));
				lookupOwner->lookup(reinterpret_cast<void *>(static_cast<unsigned int>(key)), &info.m_second);
			}

			if (info.m_second != 0 || projectileMatrix != 0)
			{
				barrelVec.push_back(info);
				if (info.m_first != 0 || info.m_third != 0)
					m_hasRecoilBonesOrMuzzleFlashes[wslot] = true;
			}
		}
	}

	m_validStuff |= 8;
}
