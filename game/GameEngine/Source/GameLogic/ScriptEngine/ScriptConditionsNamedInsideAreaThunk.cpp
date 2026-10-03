// cl: /O2 /MD /EHsc

class Parameter;

class ScriptConditions
{
	protected:
	// ?evaluateNamedInsideArea@ScriptConditions@@IAE_NPAVParameter@@0@Z
	// The owning header declares this method protected; access does not affect its ABI.
	bool evaluateNamedInsideArea(Parameter *unit, Parameter *trigger);

	public:
	bool evaluateNamedInsideAreaThunk(Parameter *unit, Parameter *trigger);
};

bool ScriptConditions::evaluateNamedInsideAreaThunk(
	Parameter *unit, Parameter *trigger)
{
	return evaluateNamedInsideArea(unit, trigger);
}
