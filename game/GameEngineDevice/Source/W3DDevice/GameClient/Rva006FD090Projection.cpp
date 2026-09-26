// Raw-ABI reconstruction of the proven slot-8 body at retail 0x006FD090.
//
// The constructor at 0x006FC970 and scalar destructor at 0x006FD550 install
// the 29-entry table at 0x011207C0.  The target is table slot 8 (+0x20);
// this address-derived view preserves that table count without asserting a
// public class or method name.  The only independently named calls are the
// existing RenderObjClass::Get_Position body and the existing game singleton
// data at 0x012F706C.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class BfmeGameCW
{
public:
	char m_prefix[0xb4];
	float m_bfmeB4;
};

extern BfmeGameCW *g_bfmeGameCW;

class Rva006FD090Owner
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07(float, Vector3 *, Vector3 *) = 0;
	virtual void slot08(float, Vector3 *) = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;

private:
	char m_prefix[0x6c];
	RenderObjClass *m_renderObject;
};

// A returned position lives through the complete projection expression.
static __forceinline float projectX(const Vector3 &position, const Vector3 &sum, float plane)
{
	return position.X + (sum.X - position.X) / (sum.Z - position.Z) * (plane - position.Z);
}

static __forceinline float projectY(const Vector3 &position, const Vector3 &sum, float plane)
{
	return position.Y + (sum.Y - position.Y) / (sum.Z - position.Z) * (plane - position.Z);
}

// ?slot08@Rva006FD090Owner@@UAEXMPAVVector3@@@Z
void Rva006FD090Owner::slot08(float source, Vector3 *result)
{
	Vector3 sum;
	Vector3 first;
	Vector3 second;
	slot07(source, &first, &second);

	sum.X = second.X + first.X;
	sum.Y = second.Y + first.Y;
	sum.Z = second.Z + first.Z;
	source = g_bfmeGameCW->m_bfmeB4;

	result->X = projectX(m_renderObject->Get_Position(), sum, source);
	result->Y = projectY(m_renderObject->Get_Position(), sum, source);
	result->Z = 0.0f;
}
