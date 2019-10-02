#pragma once

#include "NodalPostprocessor.h"
#include "MooseVariableInterface.h"

class VariableThreshold;

template <>
InputParameters validParams<VariableThreshold>();

class VariableThreshold : public NodalPostprocessor
{
public:
  VariableThreshold(const InputParameters & parameters);

  virtual void initialize() override;
  virtual void finalize() override;
  virtual void execute() override;
  virtual Real getValue() override;
  virtual void threadJoin(const UserObject & y) override;

protected:
  const VariableValue & _variable;
  const Real & _threshold;
  Real _flag;
};
