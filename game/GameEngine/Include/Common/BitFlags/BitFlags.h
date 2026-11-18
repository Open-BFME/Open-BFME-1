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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////


#ifndef BFME1_STANDALONE_BITFLAGS_H
#define BFME1_STANDALONE_BITFLAGS_H
#include <bitset>
#include <string.h>
#ifndef NDEBUG
#include "Common/Debug.h"
#endif
class INI;
class Xfer;
class AsciiString;

// BFME1 standalone declaration, adapted from the existing EA BitFlags header.
// The original int non-type argument and proven contiguous bitset extent stay fixed.
// No broad STLTypedefs or concrete INI/AsciiString object dependency is introduced.
// I/O definitions stay with their existing independently matched providers.
template <int NUMBITS>
class BitFlags
{
private:
	_STL::bitset<NUMBITS>				m_bits;
	static const char*					s_bitNameList[];

public:

	/*
		just a little syntactic sugar so that there is no "foo = 0" compatible constructor
	*/
	enum BogusInitType
	{
		kInit = 0
	};

	inline BitFlags()
	{
	}

	inline BitFlags(BogusInitType k, int idx1)
	{
		m_bits.set(idx1);
	}

	inline BitFlags(BogusInitType k, int idx1, int idx2)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
	}

	inline BitFlags(BogusInitType k, int idx1, int idx2, int idx3)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
	}

	inline BitFlags(BogusInitType k, int idx1, int idx2, int idx3, int idx4)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
		m_bits.set(idx4);
	}

	inline BitFlags(BogusInitType k, int idx1, int idx2, int idx3, int idx4, int idx5)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
		m_bits.set(idx4);
		m_bits.set(idx5);
	}

	inline BitFlags(BogusInitType k,
										int idx1,
										int idx2,
										int idx3,
										int idx4,
										int idx5,
										int idx6,
										int idx7,
										int idx8,
										int idx9,
										int idx10,
										int idx11,
										int idx12
									)
	{
		m_bits.set(idx1);
		m_bits.set(idx2);
		m_bits.set(idx3);
		m_bits.set(idx4);
		m_bits.set(idx5);
		m_bits.set(idx6);
		m_bits.set(idx7);
		m_bits.set(idx8);
		m_bits.set(idx9);
		m_bits.set(idx10);
		m_bits.set(idx11);
		m_bits.set(idx12);
	}

	inline bool operator==(const BitFlags& that) const
	{
		return this->m_bits == that.m_bits;
	}

	inline bool operator!=(const BitFlags& that) const
	{
		return this->m_bits != that.m_bits;
	}

	inline void set(int i, int val = 1)
	{
		m_bits.set(i, val);
	}

	inline bool test(int i) const
	{
		return m_bits.test(i);
	}

	//Tests for any bits that are set in both.
	inline bool testForAny( const BitFlags& that ) const
	{
		BitFlags tmp = *this;
		tmp.m_bits &= that.m_bits;
		return tmp.m_bits.any();
	}

	//All argument bits must be set in our bits too in order to return TRUE
	inline bool testForAll( const BitFlags& that ) const
	{
#ifndef NDEBUG
		DEBUG_ASSERTCRASH( that.any(), ("BitFlags::testForAll is always true if you ask about zero flags.  Did you mean that?") );
#endif


		BitFlags tmp = *this;
		tmp.m_bits.flip();
		tmp.m_bits &= that.m_bits;
		return !tmp.m_bits.any();
	}

	//None of the argument bits must be set in our bits in order to return TRUE
	inline bool testForNone( const BitFlags& that ) const
	{
		BitFlags tmp = *this;
		tmp.m_bits &= that.m_bits;
		return !tmp.m_bits.any();
	}

	inline int size() const
	{
		return m_bits.size();
	}

	inline int count() const
	{
		return m_bits.count();
	}

	inline bool any() const
	{
		return m_bits.any();
	}

	inline void flip()
	{
		m_bits.flip();
	}

	inline void clear()
	{
		m_bits.reset();
	}

	inline int countIntersection(const BitFlags& that) const
	{
		BitFlags tmp = *this;
		tmp.m_bits &= that.m_bits;
		return tmp.m_bits.count();
	}

	inline int countInverseIntersection(const BitFlags& that) const
	{
		BitFlags tmp = *this;
		tmp.m_bits.flip();
		tmp.m_bits &= that.m_bits;
		return tmp.m_bits.count();
	}

	inline bool anyIntersectionWith(const BitFlags& that) const
	{
		/// @todo srj -- improve me.
		BitFlags tmp = that;
		tmp.m_bits &= m_bits;
		return tmp.m_bits.any();
	}

	inline void clear(const BitFlags& clr)
	{
		m_bits &= ~clr.m_bits;
	}

	inline void set(const BitFlags& set)
	{
		m_bits |= set.m_bits;
	}

	inline void clearAndSet(const BitFlags& clr, const BitFlags& set)
	{
		m_bits &= ~clr.m_bits;
		m_bits |= set.m_bits;
	}

	inline bool testSetAndClear(const BitFlags& mustBeSet, const BitFlags& mustBeClear) const
	{
		/// @todo srj -- improve me.
		BitFlags tmp = *this;
		tmp.m_bits &= mustBeClear.m_bits;
		if (tmp.m_bits.any())
			return false;

		tmp = *this;
		tmp.m_bits.flip();
		tmp.m_bits &= mustBeSet.m_bits;
		if (tmp.m_bits.any())
			return false;

		return true;
	}

  static const char** getBitNames()
  {
    return s_bitNameList;
  }

  static const char* getNameFromSingleBit(int i)
  {
    return (i >= 0 && i < NUMBITS) ? s_bitNameList[i] : 0;
  }

  static int getSingleBitFromName(const char* token)
  {
    int i = 0;
	  for(const char** name = s_bitNameList; *name; ++name, ++i )
	  {
		  if( _stricmp( *name, token ) == 0 )
		  {
        return i;
		  }
	  }
		return -1;
  }

  const char* getBitNameIfSet(int i) const
  {
    return test(i) ? s_bitNameList[i] : 0;
  }

  bool setBitByName(const char* token)
  {
    int i = getSingleBitFromName(token);
		if (i >= 0)
		{
      set(i);
			return true;
		}
		else
		{
	    return false;
		}
  }

	void parse(INI* ini, AsciiString* str);
	void parseSingleBit(INI* ini, AsciiString* str);
	void xfer(Xfer* xfer);
	static void parseFromINI(INI* ini, void* /*instance*/, void *store, const void* /*userData*/); ///< Returns a BitFlag
	static void parseSingleBitFromINI(INI* ini, void* /*instance*/, void *store, const void* /*userData*/); ///< Returns an int, the Index of the one bit

	void buildDescription( AsciiString* str ) const;


};

#endif
