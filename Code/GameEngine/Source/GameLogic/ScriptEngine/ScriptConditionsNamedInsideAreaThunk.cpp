// cl: /O2 /MD /EHsc

class Parameter;

class ScriptConditions
{
public:
	bool evaluateNamedInsideArea(Parameter *unit, Parameter *trigger);
	bool evaluateNamedInsideAreaThunk(Parameter *unit, Parameter *trigger);
};

bool ScriptConditions::evaluateNamedInsideAreaThunk(
	Parameter *unit, Parameter *trigger)
{
	return evaluateNamedInsideArea(unit, trigger);
}
