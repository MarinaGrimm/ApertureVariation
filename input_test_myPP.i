[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = -1
  xmax = 1
  ymin = -1
  ymax = 1
  nx = 20
  ny = 20
[]

[Functions]
  [./exact_fn]
    type = ParsedFunction
    value = (sin(pi*t))
  [../]

  [./forcing_fn]
    type = ParsedFunction
    value = sin(pi*t)
  [../]

  [./flag_func]
    type = ParsedFunction
    vals = 'get_flag_var'
    vars = 'flag_var'
    value = 'flag_var'
  [../]

[]

[AuxVariables]

 [./u_control]
    initial_condition = 0.5
 [../]

 [./flag_var]
  initial_condition = 0.0
 [../]

[]

[AuxKernels]

  [./get_flag]
    type = FunctionAux
    variable = flag_var
    function = flag_func
    execute_on = 'timestep_begin'
  [../]
[]


[Variables]
  active = 'u'

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  active = 'diff' #ffn'

  [./ie]
    type = TimeDerivative
    variable = u
  [../]

  [./diff]
    type = Diffusion
    variable = u
  [../]

  [./ffn]
    type = BodyForce
    variable = u
    function = forcing_fn
  [../]
[]

[BCs]
  [./all]
    type = FunctionDirichletBC
    variable = u
    boundary = '0 1 2 3'
    function = exact_fn
  [../]
[]

[Executioner]
  type = Transient

  solve_type = 'PJFNK'

  dt = 0.1
  start_time = 0
  num_steps = 20
[]

[Postprocessors]
  [./max_nodal_val]
    type = NodalMaxValue
    variable = u
  [../]

  [./get_flag_var]
  type = NodalGetValue
  variable = u
  limit_value = u_control
  execute_on = 'initial timestep_begin'
  [../]
[]

[Outputs]
  print_linear_residuals = false
  print_perf_log = true
  csv = true
  [./out]
  type = Exodus
  execute_on = 'initial timestep_end'
  [../]
[]
