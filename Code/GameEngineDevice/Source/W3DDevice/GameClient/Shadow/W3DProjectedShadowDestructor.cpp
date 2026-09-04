// cl: /DNDEBUG /MD
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
*/

class RefCountedShadowResource
{
public:
	virtual void deleteThis(void) = 0;
	unsigned long referenceCount;
};

class W3DProjectedShadow
{
public:
	~W3DProjectedShadow(void);

private:
	unsigned char m_shadowData[0x68];
	RefCountedShadowResource *m_shadowTexture[2];
	RefCountedShadowResource *m_shadowProjector;
};

static void releaseReference(RefCountedShadowResource *resource)
{
	if (--resource->referenceCount == 0)
		resource->deleteThis();
}

W3DProjectedShadow::~W3DProjectedShadow(void)
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_shadowTexture[i] != 0)
		{
			releaseReference(m_shadowTexture[i]);
			m_shadowTexture[i] = 0;
		}
	}
	if (m_shadowProjector != 0)
	{
		releaseReference(m_shadowProjector);
		m_shadowProjector = 0;
	}
}
