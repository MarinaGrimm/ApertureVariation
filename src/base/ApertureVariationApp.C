#include "ApertureVariationApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<ApertureVariationApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

ApertureVariationApp::ApertureVariationApp(InputParameters parameters) : MooseApp(parameters)
{
  ApertureVariationApp::registerAll(_factory, _action_factory, _syntax);
}

ApertureVariationApp::~ApertureVariationApp() {}

void
ApertureVariationApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"ApertureVariationApp"});
  Registry::registerActionsTo(af, {"ApertureVariationApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
ApertureVariationApp::registerApps()
{
  registerApp(ApertureVariationApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
ApertureVariationApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ApertureVariationApp::registerAll(f, af, s);
}
extern "C" void
ApertureVariationApp__registerApps()
{
  ApertureVariationApp::registerApps();
}
