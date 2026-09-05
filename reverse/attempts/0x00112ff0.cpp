// ?clearScratchPadMaps@GameStateMap@@QAEXXZ
// partial score=0.45 date=2026-09-05
// ------------------------------------------------------------------------------------------------
/** Delete any scratch pad maps in the save directory.  Scratch pad maps are maps that
	* were embedded in previously loaded save game files and temporarily written out as
	* their own file so that those map files could be loaded as a part of the load game
	* process */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: retail hoists the one-time FindFirstFile call
// above the loop instead of using a "first" flag, and BFME extended the
// original ZH scratch-pad cleanup to also delete ".wak" water-track files.
// ?clearScratchPadMaps@GameStateMap@@ present-unmatched
void GameStateMap::clearScratchPadMaps( void )
{

	// remember the current directory
	char currentDirectory[ _MAX_PATH ];
	GetCurrentDirectory( _MAX_PATH, currentDirectory );

	// switch into the save directory
	SetCurrentDirectory( TheGameState->getSaveDirectory().str() );

	// iterate all items in the directory
	AsciiString fileToDelete;
	WIN32_FIND_DATA item;  // search item
	HANDLE hFile = FindFirstFile( "*", &item );
	if( hFile == INVALID_HANDLE_VALUE )
		return;

	Bool done = FALSE;
	while( done == FALSE )
	{

		// first, clear flag for deleting file
		fileToDelete.clear();

		// see if this is a file, and therefore a possible .map/.wak file
		if( !(item.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{

			// see if there is a ".map" or ".wak" at end of this filename
			Char *c = strrchr( item.cFileName, '.' );
			if( c && (!stricmp( c, ".map" ) || !stricmp( c, ".wak" )) )
				fileToDelete.set( item.cFileName );  // we want to delete this one

		}  // end if

		//
		// find the next file before we delete this one, this is probably not necessary
		// to strcuture things this way so that the find next occurs before the file
		// delete, but it seems more correct to do so
		//
		if( FindNextFile( hFile, &item ) == 0 )
			done = TRUE;

		// delete file if set
		if( fileToDelete.isEmpty() == FALSE )
			DeleteFile( fileToDelete.str() );

	}  // end while

	// close search resources
	FindClose( hFile );

	// restore our directory to the current directory
	SetCurrentDirectory( currentDirectory );

}  // end clearScratchPadMaps
