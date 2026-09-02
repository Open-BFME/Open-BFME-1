// cl: /DNDEBUG /MD /EHsc

// Ported from the Zero Hour OCLSpecialPower::findOCL twin.

enum ScienceType {};
class ObjectCreationList;

class Player
{
public:
	bool hasScience( ScienceType science ) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		ScienceType m_science;
		const ObjectCreationList *m_ocl;
	};

	unsigned char m_lead[ 0x210 ];
	Upgrades *m_upgradeBegin;
	Upgrades *m_upgradeEnd;
	Upgrades *m_upgradeCapacity;
	const ObjectCreationList *m_defaultOCL;
};

class OCLSpecialPower
{
public:
	const ObjectCreationList *findOCL() const;
private:
	unsigned char m_vptr[ 4 ];
	OCLSpecialPowerModuleData *m_data;
	Object *m_object;
};

const ObjectCreationList *OCLSpecialPower::findOCL() const
{
	const OCLSpecialPowerModuleData *data = m_data;
	const Player *controller = m_object->getControllingPlayer();
	if ( controller != 0 )
	{
		for ( const OCLSpecialPowerModuleData::Upgrades *it = data->m_upgradeBegin;
			it != data->m_upgradeEnd; ++it )
		{
			if ( controller->hasScience( it->m_science ) )
				return it->m_ocl;
		}
	}
	return data->m_defaultOCL;
}
