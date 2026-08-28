// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1ObjectCreationListStore@@UAE@XZ: Code/GameEngine/Source/GameLogic/Object/ObjectCreationList.cpp
// Open-BFME5: clean C++ lift of the retail ObjectCreationListStore destructor.

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	int m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
public:
	virtual ~ObjectCreationNugget();
	void deleteInstance() { delete this; }
};

class ObjectCreationListMap
{
public:
	~ObjectCreationListMap();

private:
	void *m_data[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationListStore : public SubsystemInterface
{
public:
	virtual ~ObjectCreationListStore();

private:
	ObjectCreationListMap m_ocls;
	std::vector<ObjectCreationNugget *> m_nuggets;
};

ObjectCreationListStore::~ObjectCreationListStore()
{
	for (std::vector<ObjectCreationNugget *>::iterator i = m_nuggets.begin(); i != m_nuggets.end(); ++i) {
		if (*i)
			(*i)->deleteInstance();
	}
	m_nuggets.clear();
}
