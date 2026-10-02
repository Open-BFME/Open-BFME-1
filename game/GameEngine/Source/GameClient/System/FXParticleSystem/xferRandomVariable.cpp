// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWLib

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void reserved00(), reserved01();
	virtual bool isSaving();
	virtual void reserved03(), reserved04(), reserved05(), reserved06(), reserved07(), reserved08(), reserved09();
	virtual void xferVersion(unsigned char *version);
	virtual void reserved11(), reserved12(), reserved13(), reserved14(), reserved15(), reserved16(), reserved17(), reserved18();
	virtual void reserved19(), reserved20(), reserved21(), reserved22(), reserved23(), reserved24(), reserved25(), reserved26();
	virtual void xferReal(float *value);
	virtual void reserved28(), reserved29(), reserved30(), reserved31(), reserved32(), reserved33(), reserved34(), reserved35();
	// Retail 0x0010C4D0 pushes ONE .rdata address (0x010890F0) followed by the
	// 4-byte value pointer and the literal 4: the same
	// xferEnum(const char *name, void *data, unsigned int size) shape as
	// XferScienceElement.cpp's receiver->xferEnum("ScienceType", science, 4).
	// The .rdata word at 0x010890F0 is not a pointer array at all: it is the
	// string literal "GameClientRandomVariable::DistributionType", the enum
	// type name. So there is no names-table global to link against.
	virtual void xferEnum(const char *name, void *data, unsigned int size);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ClientRandomValue.h
class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM,
		GAUSSIAN,
		TRIANGULAR
	};

	void setRange(float low, float high, DistributionType type);

	DistributionType m_type;
	float m_low;
	float m_high;
};



Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var)
{
	struct Locals
	{
		float high;
		float low;
		unsigned char version[2];
	} locals;
	locals.version[0] = 1;
	locals.version[1] = 1;
	xfer.xferVersion(locals.version);

	GameClientRandomVariable::DistributionType type;
	locals.low = 0.0f;
	locals.high = 0.0f;
	type = GameClientRandomVariable::CONSTANT;
	if (xfer.isSaving()) {
		locals.low = var.m_low;
		locals.high = var.m_high;
		type = var.m_type;
	}

	xfer.xferReal(&locals.low);
	xfer.xferReal(&locals.high);
	xfer.xferEnum("GameClientRandomVariable::DistributionType", &type, 4);

	if (!xfer.isSaving()) {
		var.setRange(locals.low, locals.high, type);
	}
	return xfer;
}
