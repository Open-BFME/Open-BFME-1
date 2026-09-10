// ?xferDrawableModules@Drawable@@IAEXPAVXfer@@@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ?xferDrawableModules@Drawable@@IAEXPAVXfer@@@Z: Code/GameEngine/Source/GameClient/Drawable.cpp
// Open-BFME5: real C++ body for Drawable::xferDrawableModules.
//
// The retail BFME Xfer interface differs from the Zero Hour header used by the
// neighboring Drawable.cpp facade.  Its slots are proven by this body's calls:
// IsStoring +0x08, xferVersion +0x28, xferSnapshot +0x30,
// xferAsciiString +0x68, and xferUnsignedShort +0x7c.  The block API takes the
// literal "DrawableModule"; the load path uses skipBlock when its module tag is
// absent.  These declarations are a TU-local ABI view, not a new Xfer identity.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

// This is the proven BFME vtable sequence.  The unnamed entries preserve slots
// whose semantics are not used by this body; they intentionally have no
// definitions or generated fallback symbols.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool IsStoring();
	virtual void slot03();
	virtual void slot04();
	virtual int beginBlock(const char *name);
	virtual void endBlock();
	virtual void skipBlock(const char *name);
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(class Module *module);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(class AsciiString *value);
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void xferUnsignedShort(UnsignedShort *value);
};

// BFME's Module view has Snapshot as its sole polymorphic prefix here, placing
// m_moduleData at +0x04.  ModuleData's tag is at +0x04.  Both offsets are read
// directly by the retail body, so the padding-free view preserves those reads
// without asserting the rest of either hierarchy.
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEYTYPE_FORCE_LONG = 0x7fffffff
};

class ModuleData
{
public:
	NameKeyType getModuleTagNameKey() const
	{
		return m_moduleTagNameKey;
	}

private:
	void *m_vtable;
	NameKeyType m_moduleTagNameKey;
};

class Module
{
public:
	NameKeyType getModuleTagNameKey() const
	{
		return m_moduleData->getModuleTagNameKey();
	}

private:
	void *m_vtable;
	ModuleData *m_moduleData;
};

// BFME's AsciiString is the one-word handle used by the proven StringBase<char>
// implementation.  The wrapper operations below are the real ABI operations:
// copy/set use StringBase<char>::set and cleanup uses its matched
// releaseBuffer body.  No local destructor/copy implementation invents string
// semantics or a new retail address.
class AsciiString
{
public:
	AsciiString() : m_text(0) {}

	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(
			*(const StringBase<char> *)&that);
		return *this;
	}

	const char *str() const
	{
		return m_text ? (const char *)(m_text + 8) : "";
	}

private:
	char *m_text;
};

class NameKeyGenerator
{
public:
	AsciiString keyToName(NameKeyType key);
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Drawable
{
protected:
	void xferDrawableModules(Xfer *xfer);

private:
	unsigned char m_opaque[0x150];
	Module **m_modules[3];
};

// ?xferDrawableModules@Drawable@@IAEXPAVXfer@@@Z
void Drawable::xferDrawableModules(Xfer *xfer)
{
	{
		XferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}
	xfer->IsStoring();

	UnsignedShort moduleTypes = 3;
	xfer->xferUnsignedShort(&moduleTypes);

	AsciiString moduleIdentifier;
	for (UnsignedShort curModuleType = 0; curModuleType < moduleTypes;
		++curModuleType)
	{
		Module **m;
		UnsignedShort moduleCount = 0;
		for (m = m_modules[curModuleType]; m && *m; ++m)
			++moduleCount;
		xfer->xferUnsignedShort(&moduleCount);

		if (xfer->IsStoring())
		{
			for (m = m_modules[curModuleType]; m && *m; ++m)
			{
				moduleIdentifier = TheNameKeyGenerator->keyToName(
					(*m)->getModuleTagNameKey());
				xfer->xferAsciiString(&moduleIdentifier);
				xfer->beginBlock("DrawableModule");
				xfer->xferSnapshot(*m);
				xfer->endBlock();
			}
		}
		else
		{
			for (UnsignedShort j = 0; j < moduleCount; ++j)
			{
				xfer->xferAsciiString(&moduleIdentifier);
				NameKeyType moduleIdentifierKey =
					TheNameKeyGenerator->nameToKey(moduleIdentifier.str());

				Module *module = 0;
				for (Module **m = m_modules[curModuleType]; m && *m; ++m)
				{
					if (moduleIdentifierKey == (*m)->getModuleTagNameKey())
					{
						module = *m;
						break;
					}
				}

				if (module == 0)
				{
					xfer->skipBlock("DrawableModule");
				}
				else
				{
					xfer->beginBlock("DrawableModule");
					xfer->xferSnapshot(module);
					xfer->endBlock();
				}
			}
		}
	}
}
