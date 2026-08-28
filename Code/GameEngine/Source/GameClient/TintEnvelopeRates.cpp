// cl: /DNDEBUG /MD /EHsc
// readable body of ?setAttackFrames@TintEnvelope@@AAEXI@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// readable body of ?setDecayFrames@TintEnvelope@@AAEXI@Z: Code/GameEngine/Source/GameClient/Drawable.cpp

// FILE: TintEnvelopeRates.cpp //////////////////////////////////////////////
//
// TintEnvelope::setDecayFrames, retail 0x00412320, and setAttackFrames, retail
// 0x00412270 -- the two rate setters, blocked on one shared fact.
//
// Drawable.cpp compiles it at 69 of 81 bytes and every one of the twelve is the
// same fact: retail reads m_peakColor at +0x1c and writes m_decayRate at +0x10,
// four bytes ahead of where the reference GameClient/Drawable.h puts them.
// There TintEnvelope derives from both MemoryPoolObject and Snapshot, so it
// carries two vtable pointers and its first Vector3 starts at +0x8.  BFME's
// carries one, and m_attackRate starts at +0x4.
//
// Drawable.h is included by well over a hundred sources and Drawable.cpp itself
// owns a large block of matched rows, so the single vptr is asserted here on a
// stand-in with one polymorphic base and nothing else.
//
///////////////////////////////////////////////////////////////////////////////

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef float Real;
typedef unsigned int UnsignedInt;

class Vector3
{
public:

	Vector3(void) {}
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }

	void Set(const Vector3 &that) { X = that.X; Y = that.Y; Z = that.Z; }
	void Scale(const Vector3 &that) { X *= that.X; Y *= that.Y; Z *= that.Z; }

	static void Subtract(const Vector3 &a, const Vector3 &b, Vector3 *result)
	{
		result->X = a.X - b.X;
		result->Y = a.Y - b.Y;
		result->Z = a.Z - b.Z;
	}

	Real X;
	Real Y;
	Real Z;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
class MemoryPoolObject
{
protected:
	virtual ~MemoryPoolObject() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class TintEnvelope : public MemoryPoolObject
{
private:

	void setAttackFrames( UnsignedInt frames );
	void setDecayFrames( UnsignedInt frames );

	// vptr @0x0
	Vector3 m_attackRate;					// @0x4
	Vector3 m_decayRate;					// @0x10
	Vector3 m_peakColor;					// @0x1c
	Vector3 m_currentColor;				// @0x28

};

// Retail 0x00412270, the sibling directly ahead of setDecayFrames and the same
// four-byte shift: m_attackRate at +0x4, m_currentColor at +0x28.
void TintEnvelope::setAttackFrames( UnsignedInt frames )
{
	Real recipFrames = 1.0f / (Real)MAX(1,frames);
	m_attackRate.Set( m_currentColor );
	Vector3::Subtract( m_peakColor, m_attackRate, &m_attackRate);
	m_attackRate.Scale( Vector3(recipFrames, recipFrames, recipFrames) );
}

void TintEnvelope::setDecayFrames( UnsignedInt frames )
{
	Real recipFrames = ( -1.0f ) / (Real)MAX(1,frames);
	m_decayRate.Set( m_peakColor );
	m_decayRate.Scale( Vector3(recipFrames, recipFrames, recipFrames) );
}
