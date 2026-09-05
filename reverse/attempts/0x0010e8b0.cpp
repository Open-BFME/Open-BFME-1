// ?iterateSaveFiles@GameState@@AAEXP6AXVAsciiString@@PAX@Z1@Z
// partial score=0.3 date=2026-09-05
// ?iterateSaveFiles@GameState@@AAEXP6AXVAsciiString@@PAX@Z1@Z present-unmatched
void GameState::iterateSaveFiles( IterateSaveFileCallback callback, void *userData )
{

	// sanity
	if( callback == NULL )
		return;

	// save the current directory
	char currentDirectory[ _MAX_PATH ];
	GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// switch into the save directory
	SetCurrentDirectory( getSaveDirectory().str() );

	// iterate all items in the directory
	WIN32_FIND_DATA item;  // search item
	HANDLE hFile = INVALID_HANDLE_VALUE;  // handle for search resources
	Bool done = FALSE;
	Bool first = TRUE;
	while( done == FALSE )
	{

		// if our first time through we need to start the search
		if( first )
		{

			// start search
			hFile = FindFirstFile( "*", &item );
			if( hFile == INVALID_HANDLE_VALUE )
				return;

			// we are no longer on our first item
			first = FALSE;

		}  // end if, first

		// see if this is a file, and therefore a possible save file
		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{

			// see if there is a ".sav" at end of this filename
			Char *c = strrchr( item.cFileName, '.' );
			if( c && stricmp( c, ".sav" ) == 0 )
			{

				// construction asciistring filename
				AsciiString filename;
				filename.set( item.cFileName );

				// call the callback
				callback( filename, userData );

			}  // end if, a save file

		}  // end if

		// on to the next file
		if( FindNextFile( hFile, &item ) == 0 )
			done = TRUE;

	}  // end while

	// close search resources
	FindClose( hFile );

	// restore the current directory
	SetCurrentDirectory( currentDirectory );

}  // end iterateSaveFiles
