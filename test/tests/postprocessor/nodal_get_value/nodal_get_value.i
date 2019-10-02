[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 20
  ny = 20
[]

[Variables/u][]

[Kernels]
  [time]
    type = ADTimeDerivative
    variable = u
  []

  [diff]
    type = ADDiffusion
    variable = u
  []
[]

[BCs]
  [left]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 0
  []
  [right]
    type = NeumannBC
    variable = u
    boundary = 'right'
    value = 1
  []
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  dt = 0.1
  num_steps = 15
[]

[Postprocessors]
  [flag]
    type = VariableThreshold
     variable = u
     threshold = 0.88
     execute_on = 'initial timestep_begin'
  []
[]

[Outputs]
  csv = true
[]
