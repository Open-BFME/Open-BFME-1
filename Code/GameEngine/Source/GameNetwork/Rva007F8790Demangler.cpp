// Retail139B callback atRVA007F8790; ret16 at7F8818 ends7F881BCC.
// Matcheddeletingdtor7F8970 andctor7F8730 writeprimaryvtable112B8A4 atthis0;
// its slot1 directlycontainsVA00BF8790. Secondarytable112B8A0 isatthis4.
// Demangler source/assertstrings establishsubsystem; originalmethodnameunknown.
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

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void slot08();
	virtual void fail( const char *expr, const char *file, int line );
};

Rva007EB810Diag *Rva007EB810Get();

struct Rva00804150ProtoMangleRef;

extern "C" Rva00804150ProtoMangleRef *ProtoMangleCreate(
	const char *server, int port, const char *gameID, const char *lkey );
void Rva008043F0Connect(
	Rva00804150ProtoMangleRef *ref, int myPort, const char *sessID );

struct Rva007E9B70Obj
{
	virtual void v0();
	virtual void v1();
	virtual unsigned int slot08();
};

Rva007E9B70Obj *Rva007E9B70Get();

class BfmeStrTWA
{
public:
	char m_bfmePad[0x10];
	unsigned int m_bfme20;
	unsigned char m_bfme24;
	unsigned char m_bfmePad25[3];
	void (__cdecl *m_bfmeCallback)( void *, void * );
	void *m_bfmeContext;
};

class BfmeThingTWA
{
public:
	void rva007F8790( const char *gameID, int port,
		const char *session, unsigned char flag );
	void *m_bfmeVft0;
	void *m_bfmeVft1;
	Rva00804150ProtoMangleRef *m_bfme08;
	int m_bfme0c;
	BfmeStrTWA m_bfmeStr;
};

void BfmeThingTWA::rva007F8790( const char *gameID, int port,
	const char *session, unsigned char flag )
{
	if( m_bfme0c != 0 )
		Rva007EB810Get()->fail(
			"mState == DEMANGLER_READY", "\\views\\feslbuild_main\\jabba\\fesl\\source\\demangler.cpp", 0x3B );

	Rva00804150ProtoMangleRef *ref = ProtoMangleCreate(
		"demangler.ea.com", 0xE4A, gameID, "" );
	m_bfme08 = ref;
	if( ref == 0 )
	{
		m_bfmeStr.m_bfmeCallback( &m_bfmeStr,
			m_bfmeStr.m_bfmeContext );
		return;
	}

	Rva008043F0Connect( ref, port, session );
	m_bfmeStr.m_bfme24 = flag;
	m_bfmeStr.m_bfme20 = Rva007E9B70Get()->slot08();
	m_bfme0c = 1;
}

