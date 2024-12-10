#include "Analyze.h"

HP_complex calculate(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& localVars){

	stack<HP_complex> valueStack;
	stack<Operator> operatorStack;
	TokenizerRet tokenizerRet;
	Operator op;

	do {
		tokenizerRet = tokenizer.run(str);
		if (tokenizerRet.type() == "number") {	//	运算数 直接入栈
			valueStack.push(HP_complex(tokenizerRet.value(), "0"));	//	加载运算数
		}
		else if (tokenizerRet.type() == "operator") {
			op = operatorManager.get_operator(tokenizerRet.value()); //	从运算符表中获取运算符	
			while (1) {
				if (operatorStack.empty() || op._PRI > operatorStack.top()._PRI) {	//	运算符栈为空或PRI_1>PRI_top 运算符入栈
					operatorStack.push(op);
					break;
				}
				//	一元运算符or只有数值栈中只有一个数值时，有单元运算法则的双元运算退化为一元运算符
				else if ((operatorStack.top().func_2 == nullptr && operatorStack.top().func_1 != nullptr) || (operatorStack.top().func_2 != nullptr && operatorStack.top().func_1 != nullptr && valueStack.size() == 1)) {
					HP_complex val = valueStack.top();	//	取 运算数栈顶元素 A 计算 C=A op_single 将C入栈
					valueStack.pop();
					valueStack.push(operatorStack.top().func_1(val));
					operatorStack.pop();
				}

				//	双元运算符
				else if (operatorStack.top().func_2 != nullptr) {
					HP_complex val_1, val_2, ans;	//取 运算数栈顶两个元素(先A，后B) 计算 C = A op_top B 将C入栈
					if (valueStack.size() >= 2) {
						val_1 = valueStack.top();
						valueStack.pop();
						val_2 = valueStack.top();
						valueStack.pop();
					}
					ans = operatorStack.top().func_2(val_2, val_1);
					valueStack.push(ans);
					operatorStack.pop();
				}
			}
		}
		else if (tokenizerRet.type() == "block@SmallBrackets") { // 小括号块，计算小括号内表达式的值，将结果压入运算数栈
			HP_complex val = calculate(tokenizerRet.value().substr(1, tokenizerRet.value().length() - 2), operatorManager, tokenizer, funcs, globalVars, localVars);
			valueStack.push(val);
		}

		else if (tokenizerRet.type() == "identifier") {	// 遇到变量名标识符 获取变量值，将值压入运算数栈
			//*
			if (localVars.is_exist(tokenizerRet.value())) {
				HP_complex tmp_val;
				tmp_val.readStr(localVars.get_var(tokenizerRet.value()).value());
				valueStack.push(tmp_val);
			}
			else if (globalVars.is_exist(tokenizerRet.value())) {
				HP_complex tmp_val;
				tmp_val.readStr(localVars.get_var(tokenizerRet.value()).value());
				valueStack.push(tmp_val);
			}
			else if (funcs.is_exist(tokenizerRet.value())) {
				HP_complex tmp_val;
				Func func = funcs.get_func(tokenizerRet.value());
				tokenizerRet = tokenizer.run(str);
				func.load_args(tokenizerRet.value(),operatorManager, tokenizer, funcs, globalVars);
				//Var ans;
				Var ans = func.run(operatorManager, tokenizer, funcs, globalVars);
				if (ans.type() == "complex") {
					tmp_val.readStr(ans.value());
					valueStack.push(tmp_val);
				}
			}
			//*/
		}

		else if (tokenizerRet.type() == "sign") {	//	遇到停止符 则停止对之后语句的计算
			if (tokenizerRet.value() == ",") {
				break;
			}
			else if (tokenizerRet.value() == ";") {
				break;
			}
		}

	} while (tokenizerRet.type() != "#OVER#" && tokenizerRet.type() != "#ERROR#");

	//	最后进行”清空运算符栈“的操作，完成后返回运算数栈的栈顶元素记为表达式的计算结果
	if (valueStack.empty()) return HP_complex();
	while (!operatorStack.empty()) {
		if ((operatorStack.top().func_2 == nullptr && operatorStack.top().func_1 != nullptr) || (operatorStack.top().func_2 != nullptr && operatorStack.top().func_1 != nullptr && valueStack.size() == 1)) {
			HP_complex val = valueStack.top();
			valueStack.pop();
			valueStack.push(operatorStack.top().func_1(val));
			operatorStack.pop();
		}
		else if (operatorStack.top().func_2 != nullptr) {
			HP_complex val_1, val_2, ans;
			if (valueStack.size() >= 2) {
				val_1 = valueStack.top();
				valueStack.pop();
				val_2 = valueStack.top();
				valueStack.pop();
			}
			ans = operatorStack.top().func_2(val_2, val_1);
			valueStack.push(ans);
			operatorStack.pop();
		}
	}
	return valueStack.top();
}

void analyze(string str, OperatorManager& operatorManager, Tokenizer& tokenizer, FuncManager& funcs, VarManager& globalVars, VarManager& localVars)
{
	TokenizerRet tokenizerRet;
	string str_copy = str;
	do {
		tokenizerRet = tokenizer.run(str);
		if (tokenizerRet.type() == "sign") {
			if (tokenizerRet.value() == ";") {
				continue;
			}
		}
		else if (tokenizerRet.type() == "identifier") {
			if (tokenizerRet.value() == "Var") {
				tokenizerRet = tokenizer.run(str); // 获取变量名
				//globalVars.update_var(tokenizerRet.value());
				std::string name = tokenizerRet.value();
				tokenizerRet = tokenizer.run(str);
				if (tokenizerRet.value() == ";")
					continue;
				else if (tokenizerRet.value() == "=") {
					HP_complex value = calculate(str, operatorManager, tokenizer,funcs, globalVars, localVars);
					localVars.update_var(Var(name, "complex", value.ToString(), "1"));
				}
			}
			else if (tokenizerRet.value() == "Func") {
				Func func;
				tokenizerRet = tokenizer.run(str); // 获取函数名
				func.define_name(tokenizerRet.value());
				tokenizerRet = tokenizer.run(str);// 获取参数列表
				func.define_argumentList(tokenizerRet.value());
				tokenizerRet = tokenizer.run(str);// 获取
				if (tokenizerRet.type() == "block@Braces") {
					func.define_body(tokenizerRet.value());
				}
				else if (tokenizerRet.type() == "block@Quotes") {
					func.define_description(tokenizerRet.value());
					tokenizerRet = tokenizer.run(str);// 获取
					func.define_body(tokenizerRet.value());
				}
				funcs.load_func(func);
			}
			else if (tokenizerRet.value() == "echo") {
				HP_complex ANS = calculate(str, operatorManager, tokenizer, funcs, globalVars, localVars);
				ANS.out();
				std::cout << std::endl;
				int pos = str.find(';');
				if (pos == -1)
					break;
				else
					str.erase(0, pos + 1);
			}
			else if (tokenizerRet.value() == "cal") {
				tokenizerRet = tokenizer.run(str); // 截取精度参数
				int precision = stoi(tokenizerRet.value().substr(1, tokenizerRet.value().size()-2));
				/*
				cout << "precision " << precision << endl;
				cout << "str " << str << endl;
				//*/
				HP_complex ANS = calculate(str, operatorManager, tokenizer, funcs, globalVars, localVars);
				//ANS.out();
				ANS.decimal_out(precision);
				std::cout << std::endl;
				int pos = str.find(';');
				if (pos == -1)
					break;
				else
					str.erase(0, pos + 1);
			}
			else if (tokenizerRet.value() == "loop") {
				HP_complex loop_num_complex;

				tokenizerRet = tokenizer.run(str); // 获取循环次数
				loop_num_complex = calculate(tokenizerRet.value(), operatorManager, tokenizer, funcs, globalVars, localVars);


				HP_fraction one;
				HP_fraction loop_num = loop_num_complex.real();

				one.in("1");
				
				
				tokenizerRet = tokenizer.run(str); // 获取循环体
				std::string loop_body = tokenizerRet.value().substr(1, tokenizerRet.value().size() - 2);

				while (!(loop_num < one) ) {
					loop_num = loop_num - one;
					analyze(loop_body, operatorManager, tokenizer, funcs, globalVars, localVars);
				}
			}
			else if (tokenizerRet.value() == "while") {
				HP_complex bool_judger;
				HP_fraction zero("0");
				std::string body;
				std::string judge_body;
				tokenizerRet = tokenizer.run(str); // 获取逻辑式
				judge_body = tokenizerRet.value();
				bool_judger = calculate(judge_body, operatorManager, tokenizer, funcs, globalVars, localVars);

				tokenizerRet = tokenizer.run(str); // 获取循环体
				body = tokenizerRet.value().substr(1, tokenizerRet.value().size() - 2);

				while (!(bool_judger.real() == zero && bool_judger.imag() == zero)) {
					analyze(body, operatorManager, tokenizer, funcs, globalVars, localVars);
					bool_judger = calculate(judge_body, operatorManager, tokenizer, funcs, globalVars, localVars);
				} 
			}
			else if (tokenizerRet.value() == "if") {
				HP_complex bool_judger;
				HP_fraction zero("0");
				std::string body;
				tokenizerRet = tokenizer.run(str); // 获取逻辑式
				bool_judger = calculate(tokenizerRet.value(), operatorManager, tokenizer, funcs, globalVars, localVars);
				
				if (bool_judger.real() == zero && bool_judger.imag() == zero) {
					tokenizerRet = tokenizer.run(str); // 获取if body
					tokenizerRet = tokenizer.run(str); // 获取else
					tokenizerRet = tokenizer.run(str); // 获取else body
					body = tokenizerRet.value().substr(1, tokenizerRet.value().size() - 2);
					analyze(body, operatorManager, tokenizer, funcs, globalVars, localVars);
				}
				else {
					tokenizerRet = tokenizer.run(str); // 获取if body
					body = tokenizerRet.value().substr(1, tokenizerRet.value().size() - 2);
					tokenizerRet = tokenizer.run(str); // 获取else
					tokenizerRet = tokenizer.run(str); // 获取else body
					analyze(body, operatorManager, tokenizer, funcs, globalVars, localVars);
				}
			}
			else if (tokenizerRet.value() == "import") {
				tokenizerRet = tokenizer.run(str); // 获取文件名
				std::string fileNameStr = tokenizerRet.value().substr(1, tokenizerRet.value().size() - 2);
				ifstream inFile;
				char fileName[255];
				strcpy_s(fileName, fileNameStr.c_str());
				inFile.open(fileName);
				std::string fileStr;
				std::string tempStr;
				while (tempStr != "EOF") {
					getline(inFile, tempStr);
					fileStr += tempStr;
				}
				inFile.close();
				analyze(fileStr, operatorManager, tokenizer, funcs, globalVars, globalVars);
				std::cin.clear();
			}
			else if (tokenizerRet.value() == "return") {
				HP_complex ANS = calculate(str, operatorManager, tokenizer, funcs, globalVars, localVars);
				localVars.update_var(Var("#RETURN#", "complex", ANS.ToString(), "1"));
				int pos = str.find(';');
				if (pos == -1)
					break;
				else
					str.erase(0, pos + 1);
			}
			else if (tokenizerRet.value() == "help") {
				Func func;
				tokenizerRet = tokenizer.run(str);
				if (tokenizerRet.type() == "identifier") {
					if (funcs.is_exist(tokenizerRet.value())) {
						func = funcs.get_func(tokenizerRet.value());
						std::cout << tokenizerRet.value() << " : " << func.get_description() << std::endl;
					}

				}
				else {

				}
			}
			continue;
		}
		
		/*
		str = tokenizerRet.value() + str;
		HP_complex ANS = calculate(str, operatorManager, tokenizer, funcs, globalVars, localVars);
		ANS.out();
		std::cout << std::endl;
		int pos = str.find(';');
		if (pos == -1)
			break;
		else
			str.erase(0, pos + 1);

		//*/
	} while (tokenizerRet.type() != "#OVER#" && tokenizerRet.type() != "#ERROR#");
}


