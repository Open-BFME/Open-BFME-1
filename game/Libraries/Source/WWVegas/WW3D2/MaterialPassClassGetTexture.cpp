//
// Command & Conquer Generals Zero Hour(tm)
// Copyright 2025 Electronic Arts Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// MaterialPass texture-stage handle accessor at retail RVA 0x00933500.
// The complete 34-byte body ends at 0x00933522 followed by CC padding.
// The neighboring MaterialPass constructor at 0x009333A0 constructs eight
// four-byte owning handles at +8. This accessor copies one indexed handle
// into a hidden return buffer and increments its ushort reference count at +4.
// No named caller establishes its original method name: retain an RVA name.
// A separate identical helper already exists at 0x00933540; this claim covers
// only 0x00933500. Shared WW3D2 headers retain their existing declarations.

class BFMETextureRelease
{
public:
	void Release_Ref(void);
};

class BfmeThingCX : public BFMETextureRelease
{
public:
	int m_bfmeHead;
	unsigned short m_bfmeRefs;
};

class BfmeHandleCX
{
public:
	BfmeHandleCX(void)
	{
		m_bfmeThing = 0;
	}

	BfmeHandleCX(const BfmeHandleCX &other)
	{
		BfmeThingCX *thing = other.m_bfmeThing;

		m_bfmeThing = thing;

		if (thing)
			++thing->m_bfmeRefs;
	}

	~BfmeHandleCX(void)
	{
		if (m_bfmeThing)
			m_bfmeThing->Release_Ref();
	}

	BfmeThingCX *m_bfmeThing;
};

// MaterialPassClass's vtable and refcount occupy the first two dwords;
// the eight owning texture handles begin at +0x08 in the retail object.
class MaterialPassClass
{
public:
	BfmeHandleCX Rva00933500(int stage) const;

private:
	int m_bfmeHead[2];
	BfmeHandleCX m_bfmeHandles[8];
};

// ?Rva00933500@MaterialPassClass@@QBE?AVBfmeHandleCX@@H@Z
BfmeHandleCX MaterialPassClass::Rva00933500(int stage) const
{
	return m_bfmeHandles[stage];
}
