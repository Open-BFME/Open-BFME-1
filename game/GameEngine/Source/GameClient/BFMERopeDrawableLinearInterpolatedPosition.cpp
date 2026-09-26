// BFME Drawable linear interpolation body at retail 0x0041D150.
// This is kept separate from the Hermite rope getter at 0x0041D090.

#define BFME_ONE (*(const float *)0x01075334)

struct BfmeLinearCoord3D
{
	float x;
	float y;
	float z;
};

struct BfmeLinearGameEngine
{
	unsigned char m_unknown[0x38];
	float m_interpolationFactor;
};

extern BfmeLinearGameEngine *TheGameEngine;

class BFMERopeDrawableGetPositionShim
{
private:
	unsigned char m_unknown000[0x38];
	BfmeLinearCoord3D m_basePosition;
	unsigned char m_unknown044[0x0FC - 0x44];
	void *m_object;
	unsigned char m_unknown100[0x230 - 0x100];
	BfmeLinearCoord3D m_interpolatedPosition;
	unsigned char m_unknown23C[0x388 - 0x23C];
	BfmeLinearCoord3D m_position0;
	BfmeLinearCoord3D m_position1;
	unsigned char m_unknown3A0[0x3B4 - 0x3A0];
	bool m_interpolationReady;

	void bfmeRebuild(int force);

public:
	const BfmeLinearCoord3D *getPositionLinear() const;
};

const BfmeLinearCoord3D *BFMERopeDrawableGetPositionShim::getPositionLinear() const
{
	if (!m_object)
		return &m_basePosition;

	BFMERopeDrawableGetPositionShim *self =
		const_cast<BFMERopeDrawableGetPositionShim *>(this);
	if (!m_interpolationReady)
		self->bfmeRebuild(0);

	float factor = TheGameEngine->m_interpolationFactor;
	if (m_position0.x == m_position1.x)
		self->m_interpolatedPosition.x = m_position0.x;
	else
		self->m_interpolatedPosition.x =
			(BFME_ONE - factor) * m_position0.x + factor * m_position1.x;

	float oneMinusFactor = BFME_ONE - factor;
	self->m_interpolatedPosition.y =
		oneMinusFactor * m_position0.y + factor * m_position1.y;
	self->m_interpolatedPosition.z =
		oneMinusFactor * m_position0.z + factor * m_position1.z;
	return &m_interpolatedPosition;
}
