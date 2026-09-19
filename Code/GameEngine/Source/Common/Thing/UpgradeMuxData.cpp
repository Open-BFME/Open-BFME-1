// cl: /DNDEBUG /MD /EHsc
// readable body of ?muxDataProcessUpgradeRemoval@UpgradeMuxData@@: Code/GameEngine/Source/Common/Thing/Module.cpp
// readable body of ?performUpgradeFX@UpgradeMuxData@@: Code/GameEngine/Source/Common/Thing/Module.cpp

class UpgradeTemplate;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	bool isEmpty() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

	bool isNone() const;

	const char *str() const
	{
		return m_data ? m_data->text : "";
	}

private:
	struct Data
	{
		int references;
		unsigned short length;
		unsigned short reserved;
		char text[1];
	};
	Data *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void removeUpgrade(const UpgradeTemplate *upgrade);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	char *m_failureMessage;
	int m_argCount;
	INIException(int argCount, const char *message, ...);
	INIException(const INIException &that);
	~INIException();
};

extern UpgradeCenter *TheUpgradeCenter;

class AsciiStringVector
{
public:
	typedef const AsciiString *const_iterator;
	bool empty() const { return m_begin == m_end; }
	const_iterator begin() const { return m_begin; }
	const_iterator end() const { return m_end; }

private:
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_storageEnd;
};

class UpgradeMuxData
{
public:
	void performUpgradeFX(Object *object) const;
	void muxDataProcessUpgradeRemoval(Object *object) const;

private:
	char m_priorVectors[0x48];
	AsciiStringVector m_removalUpgradeNames;
	const FXList *m_fxListUpgrade;
};

void UpgradeMuxData::performUpgradeFX(Object *object) const
{
	const FXList *fx = m_fxListUpgrade;
	if (fx && !fx->isEmpty())
		fx->doFXObj(object, 0);
}

void UpgradeMuxData::muxDataProcessUpgradeRemoval(Object *object) const
{
	if (!m_removalUpgradeNames.empty())
	{
		AsciiStringVector::const_iterator it;
		for (it = m_removalUpgradeNames.begin();
			it != m_removalUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(*it);
			if (!upgrade && !it->isEmpty() && !it->isNone())
			{
				throw INIException(3,
					"An upgrade module references %s, which is not an Upgrade", it->str());
			}

			object->removeUpgrade(upgrade);
		}
	}
}
