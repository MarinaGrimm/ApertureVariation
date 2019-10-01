//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "NodalGetValue.h"

// MOOSE includes
//#include "MooseMesh.h"
#include "MooseVariable.h"
#include "SubProblem.h"
#include "MooseTypes.h"

//#include "libmesh/node.h"

registerMooseObject("SaintBernardApp", NodalGetValue);

template <>
InputParameters
validParams<NodalGetValue>()
{
  InputParameters params = validParams<NodalPostprocessor>();
  params.addRequiredCoupledVar("variable",
                               "The name of the variable that this postprocessor operates on");
  params.addRequiredCoupledVar("limit_value", "A value that the variable will be monitored to");
  params.addClassDescription("Outputs 1 if the variable exceed the limit or 0 if not");
  return params;
}

NodalGetValue::NodalGetValue(const InputParameters & parameters)
  : NodalPostprocessor(parameters), 
    MooseVariableInterface<Real>(this,
                                 true,
                                 "variable",
                                 Moose::VarKindType::VAR_ANY,
                                 Moose::VarFieldType::VAR_FIELD_STANDARD),
    _u(coupledValue("variable")),
   _limit_value(coupledValue("limit_value")),
   _flag(0)
{
}

void 
NodalGetValue::initialize()
{
  _flag = 0.0;
}

void
NodalGetValue::execute()
{
  if (_u[_qp] > _limit_value[_qp])
    _flag = 1.0;
  else
    _flag = 0.0;
}

Real
NodalGetValue::getValue()
{

  return _flag;

}

void
NodalGetValue::threadJoin(const UserObject & y)
{
 const NodalGetValue & pps = static_cast<const NodalGetValue &>(y);
 _flag += pps._flag;
}
