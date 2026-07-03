// File-factory declarations for the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWLib/ffactory.h): the abstract FileFactoryClass, the
// SimpleFileFactoryClass that ffactory.cpp implements (the default read factory), the
// RawFileFactoryClass used for writing, the file_auto_ptr helper, and the global
// factory pointers. SimpleFileFactoryClass embeds a StringClass and a CriticalSectionClass,
// so their layout headers are pulled in here.
#ifndef FFACTORY_H
#define FFACTORY_H

#include "rawfile.h"
#include "mutex.h"

class FileClass;

class FileFactoryClass {
public:
	virtual ~FileFactoryClass(void){};
	virtual FileClass * Get_File( char const *filename ) = 0;
	virtual void Return_File( FileClass *file ) = 0;
};

//
// Handy auto pointer class.  Prevents you from having to call Return_File manually
//
class file_auto_ptr
{
public:
	explicit	file_auto_ptr(FileFactoryClass *fac, const char *filename);
				~file_auto_ptr();

	operator FileClass*(void) const
		{return (get()); }

	FileClass& operator*() const
		{return (*get()); }

	FileClass *operator->() const
		{return (get()); }

	FileClass *get() const
		{return (_Ptr); }

private:
	// prevent these from getting auto-generated or used
						file_auto_ptr(const file_auto_ptr &other);
	file_auto_ptr	&operator=(const file_auto_ptr &other);


	FileClass			*_Ptr;
	FileFactoryClass	*_Fac;
};

/*
** RawFileFactoryClass is a derived FileFactoryClass which
** gives RawFileClass objects
*/
class	RawFileFactoryClass {
public:
	RawFileClass * Get_File( char const *filename );
	void Return_File( FileClass *file );
};

/*
** SimpleFileFactoryClass is the default read factory: it hands out BufferedFileClass
** objects, honouring an optional (semicolon separated) search path and path stripping.
*/
class	SimpleFileFactoryClass : public FileFactoryClass {

public:
	SimpleFileFactoryClass( void );
	~SimpleFileFactoryClass( void )	{}

	virtual FileClass *	Get_File( char const *filename );
	virtual void			Return_File( FileClass *file );

	// sub_directory may be a semicolon seperated search path.  New files will always
	//   go in the last dir in the path.
	void						Get_Sub_Directory( StringClass& new_dir ) const;
	void						Set_Sub_Directory( const char * sub_directory );
	void						Prepend_Sub_Directory( const char * sub_directory );
	void						Append_Sub_Directory( const char * sub_directory );
	bool						Get_Strip_Path( void ) const								{ return IsStripPath; }
	void						Set_Strip_Path( bool set )									{ IsStripPath = set; }
	void						Reset_Sub_Directory( void )								{ SubDirectory = ""; }

protected:
	StringClass				SubDirectory;
	bool						IsStripPath;

	// Mutex must be mutable because const functions lock on it.
	mutable CriticalSectionClass	Mutex;
};

extern FileFactoryClass	*	_TheFileFactory;
extern SimpleFileFactoryClass	*	_TheSimpleFileFactory;
extern RawFileFactoryClass	*	_TheWritingFileFactory;

#endif
