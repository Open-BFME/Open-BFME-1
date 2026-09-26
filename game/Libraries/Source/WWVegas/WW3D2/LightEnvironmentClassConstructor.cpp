// cl: /DNDEBUG /MD /EHsc

// Clean C++ conversion of LightEnvironmentClass::LightEnvironmentClass at retail RVA 0x0094AAF0.
// BFME stores a leading byte before LightCount. The member constructors below
// reproduce the retail zeroing order for the four input lights, four output
// lights, and the fill light.

struct LightEnvironmentVector3
{
	float x, y, z;
	LightEnvironmentVector3() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {}
};

struct LightEnvironmentZeroFloat
{
	float value;
	LightEnvironmentZeroFloat() : value( 0.0f ) {}
};

struct LightEnvironmentInputLight
{
	LightEnvironmentVector3 direction;
	LightEnvironmentVector3 ambient;
	LightEnvironmentVector3 diffuse;
	bool diffuseRejected;
	bool point;
	LightEnvironmentVector3 center;
	LightEnvironmentZeroFloat innerRadius;
	LightEnvironmentZeroFloat outerRadius;
	LightEnvironmentVector3 pointAmbient;
	LightEnvironmentVector3 pointDiffuse;
	LightEnvironmentInputLight() : diffuseRejected( false ), point( false ) {}
};

struct LightEnvironmentOutputLight
{
	LightEnvironmentVector3 direction;
	LightEnvironmentVector3 diffuse;
};

class LightEnvironmentPrefix
{
protected:
	unsigned char prefix;
	unsigned char padding[3];
	int lightCount;
	LightEnvironmentVector3 objectCenter;
	LightEnvironmentPrefix() : prefix( 0 ), lightCount( 0 ) {}
};

class LightEnvironmentClass : public LightEnvironmentPrefix
{
public:
	LightEnvironmentClass();

private:
	LightEnvironmentInputLight inputLights[4];
	LightEnvironmentVector3 outputAmbient;
	LightEnvironmentOutputLight outputLights[4];
	LightEnvironmentInputLight fillLight;
	float fillIntensity;
};

LightEnvironmentClass::LightEnvironmentClass()
	: LightEnvironmentPrefix(), fillIntensity( 0.0f )
{
}
