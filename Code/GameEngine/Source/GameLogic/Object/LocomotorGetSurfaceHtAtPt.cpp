// cl: /DNDEBUG /MD /EHsc-
// Retail 0x001B4860 is Locomotor::getSurfaceHtAtPt.  The method returns the
// water height under a point, or the ground height when the point is not under
// water.  TerrainLogic slots 6 and 19 provide the two calls in the retail body.

typedef unsigned char Bool;
typedef float Real;

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real, Real, Real * = 0) const;
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual Bool isUnderwater(Real, Real, Real *, Real *);
};

extern TerrainLogic *TheTerrainLogic;

class Locomotor
{
protected:
	Real getSurfaceHtAtPt(Real, Real);
};

Real Locomotor::getSurfaceHtAtPt(Real x, Real y)
{
	Real waterZ;
	if (TheTerrainLogic->isUnderwater(x, y, &waterZ, 0))
		return waterZ;
	return TheTerrainLogic->getGroundHeight(x, y, 0);
}
