// cl: /O2 /Ob1 /EHs-c-
// The BFME ScienceStore keeps its ScienceInfo pointer vector at +0x08.  The
// generated row at 0x000E7170 is the virtual slot-4 reset body; this TU keeps
// the BFME layout local while expressing the override cleanup as C++.

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

extern "C" __declspec(dllimport) void * __cdecl BfmeMemMove(
	void *destination, const void *source, unsigned int bytes);

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *m_nextOverride;
	bool m_isOverride;

	Overridable *deleteOverrides()
	{
		if (m_isOverride)
		{
			delete this;
			return 0;
		}
		if (m_nextOverride)
			m_nextOverride = m_nextOverride->deleteOverrides();
		return this;
	}
};

class ScienceStore
{
public:
	virtual ~ScienceStore();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void reset();

private:
	char m_subsystemName[4];
	Overridable **m_sciences;
	Overridable **m_sciencesEnd;
	Overridable **m_sciencesCapacity;
};

void ScienceStore::reset()
{
	for (Overridable **it = m_sciences; it != m_sciencesEnd; )
	{
		Overridable *science = *it;
		Overridable *stillValid = science->deleteOverrides();
		if (!stillValid)
		{
			Overridable **next = it + 1;
			if (next != m_sciencesEnd)
				BfmeMemMove(it, next,
					(unsigned int)((char *)m_sciencesEnd - (char *)next));
			--m_sciencesEnd;
		}
		else
		{
			++it;
		}
	}
}
