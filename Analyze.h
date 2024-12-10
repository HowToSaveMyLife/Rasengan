#pragma once
#include <string>
#include <stack>
#include <fstream>
#include <cstdio>
//#include <istring>
#include "HP_complex.h"
#include "Operator.h"
#include "VarManager.h"
#include "Tokenizer.h"
#include "FuncManager.h"

//class FuncManager;
//class Func;

HP_complex calculate(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& localVars);

void analyze(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& funcVars);