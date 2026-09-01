class Matrix3D
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setOrientation(float);
	void setTransformMatrix(Matrix3D const *);
};

class ThingSetTransformMatrixShim
{
public:
	void setTransformMatrix(Matrix3D const *a0);
};

void Thing::setTransformMatrix(Matrix3D const *a0)
{
	((ThingSetTransformMatrixShim *)this)->setTransformMatrix(a0);
}
