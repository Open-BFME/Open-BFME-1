// ?parseLODPreset@INI@@SAXPAV1@@Z
// partial score=0.7 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /O2
//
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

typedef int Int;

class AsciiString;

template <class T> class StringBase
{
    friend class AsciiString;

public:
    StringBase(const StringBase<T> &other);
    void set(const T *text, Int length);

private:
    void releaseBuffer();
};

class AsciiString
{
public:
    AsciiString() : m_text(0) {}
    AsciiString(const AsciiString &other)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&other);
    }
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
    void set(const char *text, Int length)
    {
        ((StringBase<char> *)this)->set(text, length);
    }

private:
    char *m_text;
};

class INI
{
public:
    const char *getNextToken(const char *separators);
    static void parseIndexList(INI *, void *, void *, const void *);
    static void parseInt(INI *, void *, void *, const void *);
    static void parseLODPreset(INI *);
};

class GameLODManager
{
public:
    Int getStaticGameLODIndex(AsciiString name);
};

#define TheGameLODManager (*(GameLODManager **)0x012ed5ac)

struct LODPresetInfo
{
    char bytes[0x20];
};

// BFME's manager keeps the preset counters after the preset storage.  The
// reference header has the Zero Hour layout, so this small view keeps the
// retail addresses local to this parser instead of changing the shared class.
class RetailGameLODManager
{
public:
    LODPresetInfo *newLODPreset(Int index)
    {
        Int *counts = reinterpret_cast<Int *>(reinterpret_cast<char *>(this) + 0x16f0);
        if (counts[index] < 0x20)
        {
            Int count = ++counts[index];
            return reinterpret_cast<LODPresetInfo *>(reinterpret_cast<char *>(this) +
                (((index << 5) + count + 0x0b) << 5));
        }
        return 0;
    }
};

// ?parseLODPreset@INI@@SAXPAV1@@Z
void INI::parseLODPreset(INI *ini)
{
    AsciiString name;
    const char *token = ini->getNextToken(0);

    Int length = 0;
    if (token)
    {
        const char *end = token;
        while (*end)
            ++end;
        length = (Int)(end - token);
    }
    name.set(token, length);

    if (TheGameLODManager)
    {
        Int index = TheGameLODManager->getStaticGameLODIndex(name);
        if (index != -1)
        {
            GameLODManager *manager = TheGameLODManager;
            LODPresetInfo *preset = reinterpret_cast<RetailGameLODManager *>(manager)->newLODPreset(index);
            if (preset)
            {
                INI::parseIndexList(ini, 0, preset, reinterpret_cast<const void *>(0x012a7418));
                INI::parseInt(ini, 0, reinterpret_cast<char *>(preset) + 4, 0);
                INI::parseIndexList(ini, 0, reinterpret_cast<char *>(preset) + 0x0c, reinterpret_cast<const void *>(0x012a742c));
                INI::parseInt(ini, 0, reinterpret_cast<char *>(preset) + 0x14, 0);
                INI::parseInt(ini, 0, reinterpret_cast<char *>(preset) + 0x10, 0);
                INI::parseInt(ini, 0, reinterpret_cast<char *>(preset) + 0x18, 0);
                INI::parseInt(ini, 0, reinterpret_cast<char *>(preset) + 0x1c, 0);
            }
        }
    }
}
