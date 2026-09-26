class AsciiString;

struct AptMovieRecord
{
	char fields[8];
	int index;
};

class AptMovieRegistry
{
public:
	AptMovieRecord *find(const AsciiString &movie);
};

class WindowManager
{
public:
	int findAptMovieIndex(const AsciiString &movie);

private:
	char m_fieldsBeforeAptMovies[0x58];
	AptMovieRegistry m_aptMovies;
};

int WindowManager::findAptMovieIndex(const AsciiString &movie)
{
	AptMovieRecord *record = m_aptMovies.find(movie);
	if (!record)
		return -1;
	return record->index;
}
