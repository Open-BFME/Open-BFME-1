// Byte-matched BFME Drawable transform-history update.
// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc

#include "../../Include/Common/ScalarTypes.h"


#include "../../../Libraries/Source/WWVegas/WWMath/vector3.h"

#include "../../../Libraries/Source/WWVegas/WWMath/vector4.h"

class Matrix3D
{
public:
	Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}

	Vector3 Get_Translation() const
	{
		return Vector3(Row[0][3], Row[1][3], Row[2][3]);
	}

	void Get_Translation(Vector3 *set) const
	{
		set->X = Row[0][3];
		set->Y = Row[1][3];
		set->Z = Row[2][3];
	}

private:
	Vector4 Row[3];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void bfmeRecordTransform(UnsignedInt frame);

private:
	unsigned char m_unmodelled_000[0x08];
	Matrix3D m_transform;
	unsigned char m_unmodelled_038[0x138 - 0x038];
	Matrix3D m_recordedTransform;
	UnsignedInt m_recordedFrame;
	Vector3 m_previousPosition;
	unsigned char m_unmodelled_178[0x184 - 0x178];
	Bool m_recordedTransformValid;
	Bool m_previousPositionValid;
	Bool m_interpolationCacheDirty;
};

void Drawable::bfmeRecordTransform(UnsignedInt frame)
{
	if (m_recordedTransformValid)
	{
		m_recordedTransform.Get_Translation(&m_previousPosition);
	}
	else
	{
		m_transform.Get_Translation(&m_previousPosition);
	}

	m_previousPositionValid = true;
	m_recordedTransform = m_transform;
	m_recordedTransformValid = true;
	m_recordedFrame = frame;
	m_interpolationCacheDirty = false;
}
