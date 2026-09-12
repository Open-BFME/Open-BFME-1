// cl: /DNDEBUG /MD /EHsc
// BFME Coord3D copy constructor (retail 0x0005BC20) copies scalar fields.
// Keeping that constructor visible reproduces the otherwise elusive x87
// schedule around the two local position copies and Vector3 normalization.
struct Coord3D {
    float x, y, z;
    Coord3D() {}
    Coord3D(const Coord3D &v) { x=v.x; y=v.y; z=v.z; }
};
class Matrix3D;
class WWMath {public:static float __fastcall Inv_Sqrt(float);};
class Vector3 {public:
 float X,Y,Z;
 Vector3(float x,float y,float z){X=x;Y=y;Z=z;}
 Vector3(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;}
 Vector3&operator=(const Vector3&v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
 __forceinline void Normalize() {
    float len2 = X*X + Y*Y + Z*Z;
    if (len2 != 0.0f) {
        float oolen = WWMath::Inv_Sqrt(len2);
        X *= oolen; Y *= oolen; Z *= oolen;
    }
 }
};
__forceinline Vector3 operator*(const Vector3&a,float k){return Vector3(a.X*k,a.Y*k,a.Z*k);}
class Object {public:
 void convertBonePosToWorldPos(const Coord3D*,const Matrix3D*,Coord3D*,Matrix3D*)const;
 bool isUsingAirborneLocomotor()const;
 char pad[0x38];
 Coord3D position;
 char pad44[0x78];
 float majorRadius;
 const Coord3D*getPosition()const{return &position;}
};
struct FindPositionOptions {
 int flags;float minRadius,maxRadius,startAngle,maxZDelta;const Object *ignoreObject,*sourceToPathToDest,*relationshipObject;
 FindPositionOptions(){flags=0;minRadius=0;maxRadius=0;startAngle=-99999.9f;maxZDelta=1e10f;ignoreObject=0;sourceToPathToDest=0;relationshipObject=0;}
};
bool findPositionAround(const Coord3D*,const FindPositionOptions*,Coord3D*);
class DockUpdate {public:
 char pad0[8];
 Object *owner;
 char padc[0x40];
 int m_numberApproachPositionBones;
 bool m_positionsLoaded;
 Coord3D *m_approachPositions;
protected:
 void loadDockPositions();
Coord3D computeApproachPosition(int,Object*);
 Object*getObject(){return owner;}
};
Coord3D DockUpdate::computeApproachPosition(int positionIndex,Object*forWhom)
{
	// load dock positions if not loaded yet
	if( m_positionsLoaded == false )
		loadDockPositions();

	Coord3D bestPosition;// This answer is the best, as it includes findPositionAround
	Coord3D workingPosition;// But if findPositionAround fails, we need to say something.
	
	FindPositionOptions fpOptions;
	// Start with the pristine bone, then convert it to the world, then find a clean spot around it.
	
	Object *us = getObject();
	us->convertBonePosToWorldPos( &m_approachPositions[positionIndex], 0, &workingPosition, 0 );

	if( m_numberApproachPositionBones == 0 )
	{
		Coord3D ourPosition = *us->getPosition();
		Coord3D theirPosition = *forWhom->getPosition();
		// A Boneless building wants to bias towards the caller for the arbitrary position
		Vector3 offset( theirPosition.x - ourPosition.x, theirPosition.y - ourPosition.y, theirPosition.z - ourPosition.z );
		offset.Normalize();
		offset = offset * (us->majorRadius / 2);

		workingPosition.x += offset.X;
		workingPosition.y += offset.Y;
		workingPosition.z += offset.Z;
	}

	fpOptions.minRadius = 0.0f;
	fpOptions.maxRadius = 100.0f;
	fpOptions.sourceToPathToDest = forWhom;// This makes it find a place forWhom can get to.
	if( forWhom->isUsingAirborneLocomotor() )
		fpOptions.ignoreObject = getObject();// Flyers can ignore us, so they can approach right over us if they want.

	bool spotFound = findPositionAround( &workingPosition, &fpOptions, &bestPosition );

	if( spotFound)
		return bestPosition;

	return workingPosition;
}

