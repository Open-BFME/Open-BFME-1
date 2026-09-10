// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /GX- /D_STLP_USE_STATIC_LIB
// stlport
// BezierProjectileBehavior primary projectile-path update, retail
// 0x001F1B90, 260 bytes.  The owner class and its primary offsets are
// established by the neighbouring Bezier bodies: module data at +4, Object
// at +8, path vector at +44/+48, and the packet counter at +78.
// The base view models storage only; no unused virtual slots are invented.

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

typedef bool Bool;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct BezierPathPod
{
	Real x;
	Real y;
	Real z;
};

struct BezierPathVector
{
	BezierPathPod *m_begin;
	BezierPathPod *m_end;

	int size() const
	{
		return (int)(m_end - m_begin);
	}

	BezierPathPod *begin() const
	{
		return m_begin;
	}
};

class Object
{
public:
	char m_unreconstructed00[0x38];
	Coord3D m_position;
};

class BezierProjectileBehaviorModuleData
{
public:
	char m_unreconstructed00[0x19];
	Bool m_flag19;
	char m_unreconstructed1a[0x06];
	Real m_pathScale;
};

class UpdateModule
{
protected:
	char m_unreconstructed00[0x08];
	Object *m_object;
	char m_unreconstructed0c[0x14];

	void setWakeFrame(Object *object, UpdateSleepTime whenToWakeUp);
};

class TerrainLogic
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal) const = 0;
};

extern TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;

// Constructor1F1470 writes tableVA10A253C; slot2C routes30E72 to1F0480.
// The complete846B callee consumes Object and position pointers and returns ret8.
class BezierProjectileBehaviorPrimaryView
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void rva001F0480(Object *victim,
		const Coord3D *victimPos) = 0;
};

class WWMath
{
public:
	static Real __fastcall Inv_Sqrt(Real value);
};

class BezierProjectileBehavior : public UpdateModule
{
public:
	void rva001F1B90(register Bool flag);
	void rva001F1620(Bool flag);

private:
	char m_unreconstructed20[0x24];
	BezierPathVector m_path;
	char m_unreconstructed4c[0x2c];
	int m_packetCounter;
};

// ?rva001F1B90@BezierProjectileBehavior@@QAEX_N@Z
void BezierProjectileBehavior::rva001F1B90(register Bool flag)
{
	const BezierProjectileBehaviorModuleData *data =
		*(BezierProjectileBehaviorModuleData **)((char *)this + 0x04);
	Object *object = *(Object **)((char *)this + 0x08);

	if (!data->m_flag19 && !flag)
		setWakeFrame(object, UPDATE_SLEEP_NONE);

	++m_packetCounter;
	int pathCount = m_path.size();
	if (pathCount < 2)
	{
		rva001F1620(flag);
		return;
	}

	Coord3D delta;
	delta.x = m_path.begin()[pathCount - 1].x -
		m_path.begin()[pathCount - 2].x;
	delta.y = m_path.begin()[pathCount - 1].y -
		m_path.begin()[pathCount - 2].y;
	Real lengthSquared = delta.x * delta.x + delta.y * delta.y;
	if (lengthSquared != BfmeZeroRange)
	{
		Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
		delta.x *= inverseLength;
		delta.y *= inverseLength;
	}

	Coord3D position;
	position.x = object->m_position.x + delta.x * data->m_pathScale;
	position.y = object->m_position.y + delta.y * data->m_pathScale;
	position.z = TheTerrainLogic->getGroundHeight(position.x,
		position.y, 0);

	((BezierProjectileBehaviorPrimaryView *)this)
		->rva001F0480(0, &position);
}
