// cl: /DNDEBUG /MD /EHsc
// stlport

#include <algorithm>

// WorldHeightMap's legacy blend-tile reader widens a temporary vector of
// signed shorts into its integer index arrays.  Retail keeps this outer
// STLport copy instantiation out of line at 0x0074D6A0.
template int *_STL::copy<short *, int *>(short *, short *, int *);
