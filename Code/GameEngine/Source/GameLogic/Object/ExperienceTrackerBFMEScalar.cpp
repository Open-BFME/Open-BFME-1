// Byte-matched BFME ExperienceTracker scalar-table helper.

typedef float Real;

class ExperienceTracker;
template <class T> class OVERRIDE;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	__inline const Overridable *getFinalOverride() const;

private:
	void *m_vtable;
	Overridable *m_nextOverride;

	friend class ThingTemplate;
	template <class T> friend class OVERRIDE;
	friend class Object;
	friend class ExperienceTracker;
};

__inline const Overridable *Overridable::getFinalOverride() const
{
	if (m_nextOverride)
		return m_nextOverride->getFinalOverride();
	return this;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
private:
	unsigned char m_unreconstructed_008[0xC8 - 0x08];
	unsigned char m_kindOfLowByte;

	friend class ExperienceTracker;
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Override.h
class OVERRIDE
{
public:
	__forceinline operator const T *() const;
	__forceinline const T *operator->() const;

private:
	const T *m_overridable;
};

template <class T>
__forceinline OVERRIDE<T>::operator const T *() const
{
	if (!m_overridable)
		return 0;
	return static_cast<const T *>(m_overridable->getFinalOverride());
}

template <class T>
__forceinline const T *OVERRIDE<T>::operator->() const
{
	return operator const T *();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	__forceinline const ThingTemplate *getTemplate() const;

private:
	virtual ~Thing();
	OVERRIDE<ThingTemplate> m_template;

	friend class ExperienceTracker;
};

__forceinline const ThingTemplate *Thing::getTemplate() const
{
	return m_template;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	bool isLivingWorld();
};

extern GameLogic *TheGameLogic;

class BfmeThingEFE
{
public:
	Real bfmeAt(int count);

private:
	void *m_vtable;
	ExperienceTracker *m_tracker;
	Real m_scalar;
	int m_baseCount;
	void *m_vec;

	friend class ExperienceTracker;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ExperienceTracker.h
class ExperienceTracker
{
public:
	Real bfmeScaleLivingWorldExperience(Real amount) const;
	void bfmeSetScalarIndex(int index);
	void bfmeSetScalarBaseCount(int count);
	void bfmeResetScalarBaseCount();

private:
	void *m_vtable;
	Object *m_parent;
	unsigned char m_unreconstructed_008[0x28 - 0x08];
	int m_scalarIndex;
	BfmeThingEFE *m_scalarTable;
};

void ExperienceTracker::bfmeSetScalarIndex(int index)
{
	if (index == 0 || m_scalarIndex == index)
		return;

	m_scalarIndex = index;
	BfmeThingEFE *table = m_scalarTable;
	table->m_scalar = table->bfmeAt(table->m_tracker->m_scalarIndex);
}

void ExperienceTracker::bfmeSetScalarBaseCount(int count)
{
	BfmeThingEFE *table = m_scalarTable;
	table->m_baseCount = count;
	table->m_scalar = table->bfmeAt(count);
}

void ExperienceTracker::bfmeResetScalarBaseCount()
{
	BfmeThingEFE *table = m_scalarTable;
	table->m_baseCount = m_scalarIndex;
	table->m_scalar = table->bfmeAt(table->m_baseCount);
}

Real ExperienceTracker::bfmeScaleLivingWorldExperience(Real amount) const
{
	const unsigned char bfmeKindOfStructure = 0x80;
	if (TheGameLogic->isLivingWorld())
	{
		if (!(m_parent->getTemplate()->m_kindOfLowByte &
			bfmeKindOfStructure))
			return amount * m_scalarTable->m_scalar;
	}

	return amount;
}
