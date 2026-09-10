// cl: /DNDEBUG /DDEBUG_LOGGING /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Oy /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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
// stlport

#include <string>

typedef bool Bool;

typedef void *PEER;
typedef void *qr2_buffer_t;

void qr2_buffer_add(qr2_buffer_t buffer, const char *value) throw();
extern "C" void qr2_buffer_add_int(qr2_buffer_t buffer, int value) throw();

// The retail callback's logging macros retain this value object even in the
// shipped build, but the log sink itself is not part of this body. Literal
// references are verified against the retail strings by the normal gate.
#define BFME_EMPTY_STRING ""
#define BFME_NUMBER_FORMAT "%d"

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

// The by-value format argument is the retail shape: its inline forwarding
// copy/destructor leaves MSVC's saved-ESP store ahead of mov ecx,esp. The
// pointer assignment and two-argument set stay declared-only and resolve to
// the already matched retail bodies.
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const char *text);
	void set(const char *text, int length);
	void format(AsciiString format, ...);
};

// These three retail helpers are already recovered as honest address-derived
// eight-slot getters. Their layouts and boundaries are proven by their own
// matched bodies; this TU only uses the field offsets those bodies establish.
class Rva00642A80
{
public:
	int get(int index);
};

class Rva00642AB0
{
public:
	int get(int index);
};

class Rva00642AE0
{
public:
	int get(int index);
};

class PeerThreadClass
{
public:
	Bool isHosting(void) { return m_isHosting; }
	void stopHostingAlready(PEER peer);
	std::string getPlayerName(int index);

	int getRva00642A80(int index)
	{
		return reinterpret_cast<Rva00642A80 *>(this)->get(index);
	}

	int getRva00642AB0(int index)
	{
		return reinterpret_cast<Rva00642AB0 *>(this)->get(index);
	}

	int getRva00642AE0(int index)
	{
		return reinterpret_cast<Rva00642AE0 *>(this)->get(index);
	}

private:
	unsigned char m_unreconstructed_00[0xAC];
	Bool m_isHosting;                                      // retail +0xAC
};

static void QRPlayerKeyCallback
(
	PEER peer,
	int key,
	int index,
	qr2_buffer_t buffer,
	void *param
)
{
	PeerThreadClass *t = (PeerThreadClass *)param;
	if (!t)
	{
		return;
	}

	if (!t->isHosting())
		t->stopHostingAlready(peer);

#define ADD(x) { qr2_buffer_add(buffer, x); val = x; }
#define ADDINT(x) { qr2_buffer_add_int(buffer, x); val.format(BFME_NUMBER_FORMAT, x); }
	AsciiString val = "";

	switch (key)
	{
	case 62:
		ADD(t->getPlayerName(index).c_str());
		break;
	case 65:
		ADDINT(t->getRva00642A80(index));
		break;
	case 66:
		ADDINT(t->getRva00642AB0(index));
		break;
	case 27:
		ADDINT(t->getRva00642AE0(index));
		break;
	case 63:
		ADDINT(t->getRva00642AB0(index));
		break;
	case 64:
		ADDINT(t->getRva00642AB0(index));
		break;
	default:
		qr2_buffer_add(buffer, BFME_EMPTY_STRING);
		val.set(BFME_EMPTY_STRING, 0);
		break;
	}

#undef ADD
#undef ADDINT
}

typedef void (*QRPlayerKeyCallbackType)(PEER, int, int, qr2_buffer_t, void *);
QRPlayerKeyCallbackType PeerThread_getQRPlayerKeyCallback(void)
{
	return QRPlayerKeyCallback;
}
