// readable body of ?setDisabledUntil@Object@@: Code/GameEngine/Source/GameLogic/Object/Object.cpp
enum DisabledType
{
	DisabledTypePlaceholder
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	void setDisabledUntil(DisabledType, unsigned int);
};

class ObjectSetDisabledUntilShim
{
public:
	void setDisabledUntil(DisabledType type, unsigned int frame);
};

void Object::setDisabledUntil(DisabledType type, unsigned int frame)
{
	((ObjectSetDisabledUntilShim *)this)->setDisabledUntil(type, frame);
}
