// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isUsingAirborneLocomotor() const;
};

bool __stdcall rva001dc880(Object *obj)
{
	return obj->isUsingAirborneLocomotor();
}
