// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

struct PartitionSolverPair
{
	int m_first;
	int m_second;
};

class PartitionSolver
{
	int m_howToSolve;
	std::vector<PartitionSolverPair> m_data;
	std::vector<PartitionSolverPair> m_spacesForData;
	std::vector<PartitionSolverPair> m_currentSolution;
	unsigned int m_currentSolutionLeftovers;
	std::vector<PartitionSolverPair> m_bestSolution;

public:
	~PartitionSolver();
};

// The constructor at 0x00095FB0 initializes these four STLport vectors and the
// scalar at the offsets released by the retail destructor at 0x002FD3B0.
PartitionSolver::~PartitionSolver()
{
}
