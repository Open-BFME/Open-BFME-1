#pragma once

#ifndef _DRAWABLE_H_
#define _DRAWABLE_H_

#include "WWMath/Matrix3D.h"

class Object;

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0,
	DRAWABLE_STATUS_DRAWS_IN_MIRROR = 1,
	DRAWABLE_STATUS_SHADOWS = 2,
	DRAWABLE_STATUS_TINT_COLOR_LOCKED = 4,
	DRAWABLE_STATUS_NO_STATE_PARTICLES = 8,
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

class Drawable
{
public:
	Object *getObject() { return *(Object **)((char *)this + 0xfc); }
	const Matrix3D *getInstanceMatrix() const
	{
		return (const Matrix3D *)((const char *)this + 0x198);
	}
	Bool isVisible() const { return *(const Bool *)((const char *)this + 0x3b1); }
	void setInstanceMatrix(const Matrix3D *instance, Bool preservePrevious);
};

#endif
