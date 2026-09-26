// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// Open-BFME5: OCLSpecialPower module-data constructor.
//
// The retail object is 0x230 bytes.  Its matched destructor proves an
// vector of eight-byte Upgrades elements at +0x210 and an AsciiString vector at +0x224;
// the two scalar words between them are the default OCL and create-location
// fields.  The reference header's single AsciiString tail is from a different
// source revision and does not describe this retail layout.

#include <vector>

class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();
	virtual ~BfmeSpecialPowerModuleDataBase();

private:
	unsigned char m_unmodelled_04[ 0x210 - 4 ];
};

struct BFMERetailAsciiString
{
	~BFMERetailAsciiString();

	char *m_data;
};

class OCLSpecialPowerModuleData
	: public BfmeSpecialPowerModuleDataBase
{
public:
	struct Upgrades
	{
		int m_science;
		const void *m_ocl;
	};

	OCLSpecialPowerModuleData();
	virtual ~OCLSpecialPowerModuleData();

private:
	_STL::vector<Upgrades> m_upgradeOCL;             // +0x210
	const void *m_defaultOCL;                       // +0x21c
	unsigned int m_createLoc;                       // +0x220
	_STL::vector<BFMERetailAsciiString> m_names;    // +0x224
};

typedef char OCLModuleDataSizeMustBe230[
	sizeof(OCLSpecialPowerModuleData) == 0x230 ? 1 : -1];

// The named module-data factory at 0x00120230 allocates 0x230 bytes and
// calls this constructor through ILT 0x0003EFB8. The runtime-object factory
// at 0x001201B0 is distinct. Retail ends at ret 0x00263227 (padding +0x78).
// ??0OCLSpecialPowerModuleData@@QAE@XZ
OCLSpecialPowerModuleData::OCLSpecialPowerModuleData()
{
	m_defaultOCL = 0;
	m_upgradeOCL.clear();
	m_createLoc = 0;
}
