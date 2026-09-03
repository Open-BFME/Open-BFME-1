// cl: /DNDEBUG /MD /GR-

typedef float Real;

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class ShadowOffset
{
public:
	Real X;
	Real Y;
	Real Z;

	Real Length2() const
	{
		return X * X + Y * Y + Z * Z;
	}

	Real Length2D() const
	{
		return X * X + Y * Y;
	}
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class Open2Triple
{
public:
	Real m_x;
	Real m_y;
	Real m_z;
};

class Open27110B0Source
{
public:
	const Open2Triple *fetch(int which);
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual Real getGroundHeight(Real x, Real y, void *normal) const;
};

class BaseHeightMapRenderObjClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void v93();
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
	virtual void v129();
	virtual void v130();
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual void v137();
	virtual void v138();
	virtual void v139();
	virtual void v140();
	virtual void v141();
	virtual void v142();
	virtual void v143();
	virtual void v144();
	virtual void v145();
	virtual Real getHeightMapHeight(Real x, Real y, void *normal) const;
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
	static __forceinline Real Sqrt(Real value)
	{
		Real retval;
		__asm {
			fld [value]
			fsqrt
			fstp [retval]
		}
		return retval;
	}
};

extern Open27110B0Source *TheOpen27110B0Source;
extern TerrainLogic *TheTerrainLogic;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern const Real BfmeZeroRange;
extern const Real BfmeShadowZLimit;
extern const Real BfmeShadowScale;

class W3DVolumetricShadow
{
	unsigned char m_unreconstructed_000[0x74];
	RenderObjClass *m_robj;
	unsigned char m_unreconstructed_078[0x0c];
	Real m_extraExtrusionPadding;
	Real m_shadowLengthScale;
	Real m_lightOffsetZAdd;
	union
	{
		struct
		{
			Real m_lightOffsetX;
			Real m_lightOffsetY;
			Real m_lightOffsetZ;
		};
		ShadowOffset m_lightOffset;
	};

public:
	void updateShadowState();
};

void W3DVolumetricShadow::updateShadowState()
{
	Vector3 pos = m_robj->Get_Position();
	m_lightOffsetX = pos.X;
	m_lightOffsetY = pos.Y;
	m_lightOffsetZ = pos.Z;

	const Open2Triple *light = TheOpen27110B0Source->fetch(0);
	m_lightOffsetX = m_lightOffsetX - (Real)light->m_x;
	m_lightOffsetY = m_lightOffsetY - (Real)light->m_y;
	m_lightOffsetZ = *(volatile Real *)&m_lightOffsetZ - (Real)light->m_z;

	Real lengthSquared = m_lightOffset.Length2();
	if (lengthSquared != BfmeZeroRange)
	{
		Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
		m_lightOffsetX *= inverseLength;
		m_lightOffsetY *= inverseLength;
		m_lightOffsetZ *= inverseLength;
	}

	if (m_shadowLengthScale > BfmeZeroRange)
	{
		Real horizontalSquared = m_lightOffset.Length2D();
		horizontalSquared *= m_shadowLengthScale;
		horizontalSquared *= m_shadowLengthScale;
		if (horizontalSquared > m_lightOffsetZ)
			m_lightOffsetZ = WWMath::Sqrt(horizontalSquared);
	}

	if (!(m_lightOffsetZ > BfmeShadowZLimit))
	{
		Real groundHeight;
		if (TheTerrainLogic)
			groundHeight = TheTerrainLogic->getGroundHeight(pos.X, pos.Y, 0);
		else
			groundHeight = TheTerrainRenderObject->getHeightMapHeight(pos.X,
				pos.Y, 0);

		Real scale = (pos.Z + m_extraExtrusionPadding - groundHeight +
			m_lightOffsetZAdd) * (BfmeShadowScale / m_lightOffsetZ);
		m_lightOffsetX *= scale;
		m_lightOffsetY *= scale;
		m_lightOffsetZ *= scale;
	}
}
