// cl: /DNDEBUG /MD /EHsc

class Parameter;

class ScriptConditions
{
protected:
	bool evaluateTeamInsideAreaEntirely(Parameter *, Parameter *, Parameter *);
};

class Rva00013219ScriptConditionsThunk : public ScriptConditions
{
public:
	bool forward(Parameter *, Parameter *, Parameter *);
};

bool Rva00013219ScriptConditionsThunk::forward(
	Parameter *team, Parameter *trigger, Parameter *type)
{
	return evaluateTeamInsideAreaEntirely(team, trigger, type);
}
