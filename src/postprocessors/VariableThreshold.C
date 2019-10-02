#include "VariableThreshold.h"

registerMooseObject("ApertureVariationApp", VariableThreshold);

template <>
InputParameters
validParams<VariableThreshold>()
{
  InputParameters params = validParams<NodalPostprocessor>();
  params.addRequiredCoupledVar("variable", "The name of the variable that shall be examined.");
  params.addRequiredParam<Real>("threshold", "A threshold value to compare variable value against.");
  params.addClassDescription("Postprocessor that monitors if the coupled variable exceeds a prescribed threshold, it outputs 1 if the variable exceed the limit or 0 otherwise.");
  return params;
}

VariableThreshold::VariableThreshold(const InputParameters & parameters)
  : NodalPostprocessor(parameters),
    _variable(coupledValue("variable")),
    _threshold(getParam<Real>("threshold")),
    _flag(0)
{
}

void
VariableThreshold::initialize()
{
  _flag = 0.0;
}

void
VariableThreshold::finalize()
{
  gatherMax(_flag);
}

void
VariableThreshold::execute()
{
  if (_variable[_qp] > _threshold)
    _flag = 1.0;
  else
    _flag = 0.0;
}

Real
VariableThreshold::getValue()
{
  return _flag;
}

void
VariableThreshold::threadJoin(const UserObject & y)
{
 const VariableThreshold & pps = static_cast<const VariableThreshold &>(y);
 if (pps._flag == 1.0)
   _flag = 1.0;
}
