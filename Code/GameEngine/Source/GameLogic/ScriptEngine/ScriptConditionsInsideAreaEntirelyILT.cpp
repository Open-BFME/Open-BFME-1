// cl: /DNDEBUG /MD /EHsc

class Parameter;

class ScriptConditionsEvaluateTeamInsideAreaEntirelyShim
{
public:
	bool evaluate(Parameter *, Parameter *, Parameter *);
};

class Rva00013219ScriptConditionsThunk
{
public:
	bool forward(Parameter *, Parameter *, Parameter *);
};

bool Rva00013219ScriptConditionsThunk::forward(
	Parameter *team, Parameter *trigger, Parameter *type)
{
	return ((ScriptConditionsEvaluateTeamInsideAreaEntirelyShim *)this)->evaluate(
		team, trigger, type);
}
