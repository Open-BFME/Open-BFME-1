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

// Partial observed view: pool recycling calls retail 0x007AEC10 on the
// unchanged shadow receiver. This is separate from complete destruction
// at 0x007AFF00; retain an address-qualified method until its name is proven.
class W3DProjectedShadow
{
public:
	void rva007AEC10(void);

private:
	unsigned char m_shadowData[0x68];
	RefCountedShadowResource *m_references68[2];
	RefCountedShadowResource *m_reference70;
};

static void releaseReference(RefCountedShadowResource *resource)
{
	if (--resource->referenceCount == 0)
		resource->deleteThis();
}

void W3DProjectedShadow::rva007AEC10(void)
{
	for (int i = 0; i < 2; ++i)
	{
		if (m_references68[i] != 0)
		{
			releaseReference(m_references68[i]);
			m_references68[i] = 0;
		}
	}
	if (m_reference70 != 0)
	{
		releaseReference(m_reference70);
		m_reference70 = 0;
	}
}
