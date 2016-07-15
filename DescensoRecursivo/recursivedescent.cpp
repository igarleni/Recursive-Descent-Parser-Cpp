#include "recursivedescent.h"

int main(int argc, char* argv[])
{
	////FIRST
	NonTerminal mainT;
	mainT.first.resize(1);
	mainT.first[0] = INICIO;

	statementsT.first.resize(1);
	statementsT.first[0] = INICIO;

	statementT.first.resize(1);
	statementT.first[0] = INICIO;

	assignmentT.first.resize(2);
	assignmentT.first[0] = INICIO;
	assignmentT.first[1] = ASIGNACION;

	declarationT.first.resize(2);
	declarationT.first[0] = MATRIXINICIO;
	declarationT.first[1] = STRING;

	expressionT.first.resize(6);
	expressionT.first[0] = IDENTIFICADORFUNC;
	expressionT.first[1] = NEGACIONLOGICA;
	expressionT.first[2] = NUMERO;
	expressionT.first[3] = VARIABLE;
	expressionT.first[4] = PALABRA;
	expressionT.first[5] = INICIO;

	valuesT.first.resize(4);
	valuesT.first[0] = NUMERO;
	valuesT.first[1] = VARIABLE;
	valuesT.first[2] = PALABRA;
	valuesT.first[3] = INICIO;

	valueT.first.resize(4);
	valueT.first[0] = NUMERO;
	valueT.first[1] = VARIABLE;
	valueT.first[2] = PALABRA;
	valueT.first[3] = INICIO;

	functionT.first.resize(4);
	functionT.first[0] = FLOAT;
	functionT.first[1] = MATRIX;
	functionT.first[2] = ARRAY;
	functionT.first[3] = STRING;

	typesT.first.resize(4);
	typesT.first[0] = FLOAT;
	typesT.first[1] = MATRIX;
	typesT.first[2] = ARRAY;
	typesT.first[3] = STRING;

	variablesT.first.resize(4);
	variablesT.first[0] = FLOAT;
	variablesT.first[1] = MATRIX;
	variablesT.first[2] = ARRAY;
	variablesT.first[3] = STRING;

	bucle_forT.first.resize(1);
	bucle_forT.first[0] = FOR;

	bucle_whileT.first.resize(1);
	bucle_whileT.first[0] = WHILE;

	cond_ifT.first.resize(1);
	cond_ifT.first[0] = IF;
	
	//initialize file read	
	/*
	if (argc > 1)
	{
		std::string filein(argv[1]);
		file.open(filein, std::ifstream::in);
	}
	else
		exit(1);*/
	file.open("prueba.txt", std::ifstream::in);

	iterPointer = 0;
	stringMode = false;
	word.clear();
	token = yylex();
	mainf();
	std::cout << "INTRODUCE UN NUMERO PARA TERMINAR: " << token << "\n";
	int test;
	std::cin >> test;
}

void mainf()
{
	if (token == INICIO)
	{
		token = yylex();
		types();
		if (token == VARIABLE)
		{
			token = yylex();
			if (token == MAIN)
			{
				token = yylex();
				if (token == INICIO)
				{
					token = yylex();
					variables();
					if (token == FIN)
					{
						token = yylex();
						statements();
						if (token == FIN)
						{
							while ((token = yylex()) == INICIO)
							{
								token = yylex();
								funct();
								if (token != FIN)
								{
									tokenError("Error en main");
								}
							}
						}
						else
						{
							tokenError("Error en main");
						}
					}
					else
					{
						tokenError("Error en main");
					}
				}
				else
				{
					tokenError("Error en main");
				}
			}
			else
			{
				tokenError("Error en main");
			}
		}
		else
		{
			tokenError("Error en main");
		}
	}
	else
	{
		tokenError("Error en main");
	}
}

void statements()
{
	while (checkFirst(statementT))
	{
		statement();
	}
}

void statement()
{
	if (token == INICIO)
	{
		token = yylex();
		if (token == VARIABLE)
		{
			token = yylex();
			if (checkFirst(declarationT))
			{
				declaration();
			}
			else if (checkFirst(assignmentT))
			{
				assignment();
			}
			else
			{
				tokenError("Error en statement");
			}
		}
		else if (token == INICIO)
		{
			token = yylex();
			if (checkFirst(bucle_whileT))
			{
				bucle_while();
			}
			else if (checkFirst(bucle_forT))
			{
				bucle_for();
			}
			else if (checkFirst(cond_ifT))
			{
				cond_if();
			}
			else if (checkFirst(functionT))
			{
				funct();
			}
			else
			{
				tokenError("Error en statement");
			}
		}
		else
		{
			tokenError("Error en statement");
		}
	}
	else
	{
		tokenError("Error en statement");
	}
	if (token == FIN)
	{
		token = yylex();
	}
	else
	{
		tokenError("Error en statement");
	}
}

void assignment()
{
	if (token == INICIO)
	{
		token = yylex();
		value();
		if (token == SEPARADOR)
		{
			token = yylex();
			value();
		}
		if (token != FIN)
		{
			tokenError("Error en assignment");
		}
		token = yylex();

	}
	if (token == ASIGNACION)
	{
		token = yylex();
		expression();
	}
	else
	{
		tokenError("Error en assignment");
	}
}

void declaration()
{
	if (token == STRING)
		token = yylex();
	if (token == MATRIXINICIO)
	{
		token = yylex();
		value();
		if (token == SEPARADOR)
		{
			token = yylex();
			value();
		}
		if (token != MATRIXFIN)
		{
			tokenError("Error en declaration");
		}
		token = yylex();
	} 
	else
	{
		tokenError("Error en declaration");
	}
}

void expression()
{
	if (token == IDENTIFICADORFUNC)
	{
		token = yylex();
		if (token == INICIO)
		{
			token = yylex();
			values();
			if (token != FIN)
			{
				tokenError("Error en expression");
			}
			token = yylex();
		}
	}
	else if (token == NEGACIONLOGICA)
	{
		token = yylex();
		value();
	}
	else if (checkFirst(valueT))
	{
		value();
		if (token == SUMA || token == RESTA || token == MULTIPLICACION || token == DIVISION ||
			token == MODULO || token == COMPARACIONIGUALDAD || token == COMPARACIONDESIGUALDAD || token == COMPARACIONMAYOR ||
			token == COMPARACIONMAYORIGUAL || token == COMPARACIONMENOR || token == COMPARACIONMENORIGUAL || token == ANDLOGICO ||
			token == ORLOGICO)
		{
			token = yylex();
			value();
		}		
	}
	else
		tokenError("Error en expression");
}

void value()
{
	if (token == VARIABLE)
	{
		token = yylex();
		if (token == MATRIXINICIO)
		{
			token = yylex();
			expression();
			if (token == SEPARADOR)
			{
				token = yylex();
				value();
			}
			if (token != MATRIXFIN)
			{
				tokenError("Error en value");
			}
			token = yylex();
		}
	}
	else if (token == INICIO)
	{
		token = yylex();
		expression();
		if (token != FIN)
		{
			tokenError("Error en value");
		}
		token = yylex();
	}
	else if ((token == PALABRA) || (token == NUMERO))
	{
		token = yylex();
	}
	else
	{
		tokenError("Error en value");
	}

}

void values()
{
	while (checkFirst(valueT))
	{
		value();
	}
}

void funct()
{
	types();
	if (token != VARIABLE)
		tokenError("Error en function");
	token = yylex();
	if (token != IDENTIFICADORFUNC)
		tokenError("Error en function"); 
	token = yylex();
	if (token != INICIO)
		tokenError("Error en function");
	token = yylex();
	variables();
	if (token != FIN)
		tokenError("Error en function");
	token = yylex();
	statements();
}

void types()
{
	if ((token != FLOAT) && (token != MATRIX) && (token != ARRAY) && (token != STRING))
		tokenError("Error en types");
	token = yylex();
}

void variables()
{
	while (checkFirst(typesT))
	{
		types();
		if (token != VARIABLE)
			tokenError("Error en variables");
		token = yylex();
	}
}

void bucle_for()
{
	if (token != FOR)
		tokenError("Error en bucle_for");
	token = yylex();
	if (token != VARIABLE)
		tokenError("Error en bucle_for");
	token = yylex();
	value();
	if (token != RANGO)
		tokenError("Error en bucle_for");
	token = yylex();
	value();
	if (token != FIN)
		tokenError("Error en bucle_for");
	token = yylex();
	statements();
}

void bucle_while()
{
	if (token != WHILE)
		tokenError("Error en bucle_while");
	token = yylex();
	if (token != INICIO)
		tokenError("Error en bucle_while");
	token = yylex();
	expression();
	if (token != FIN)
		tokenError("Error en bucle_while");;
	token = yylex();
	if (token != FIN)
		tokenError("Error en bucle_while");
	token = yylex();
	statements();
}

void cond_if()
{
	if (token != IF)
		tokenError("Error en cond_if");
	token = yylex();
	if (token != INICIO)
		tokenError("Error en cond_if");
	token = yylex();
	expression();
	if (token != FIN)
		tokenError("Error en cond_if");
	token = yylex();
	if (token != FIN)
		tokenError("Error en cond_if");
	token = yylex();
	if (token != INICIO)
		tokenError("Error en cond_if");
	token = yylex();
	statements();
	if (token != FIN)
		tokenError("Error en cond_if");
	token = yylex();
	if (token != INICIO)
		tokenError("Error en cond_if");
	token = yylex();
	statements();
	if (token != FIN)
		tokenError("Error en cond_if");
	token = yylex();
}

void tokenError(std::string error)
{
	std::cout << '\n' << error << ": token encontrado--> " << token << "\n";
	int test;
	std::cin >> test;
	exit(0);
}

void lexError(std::string error)
{
	printf("%s", error);
	int test;
	std::cin >> test;
	exit(0);
}

bool checkFirst(NonTerminal nonTerminal)
{
	int size = nonTerminal.first.size();
	for (int i = 0; i < size; i++)
	{
		if (token == nonTerminal.first[i]) return true;
	}
	return false;
}

int yylex()
{
	char caracter;
	if (iterPointer >= word.length())
	{
		word.clear();
		if (!(file >> word))
			return 0;
		std::cout << "\nPalabra extraida--> " << word << "\n";
		iterPointer = 0;
	}

	for (int i = iterPointer; i < word.length(); i++)
	{
		caracter = word[i];
		if (stringMode)
		{
			if (caracter == '"')
			{
				stringMode = false;
				iterPointer = i + 1;
				return PALABRA;
			}
			if (i + 1 >= word.length())
			{
				std::string extraData;
				extraData.clear();
				if (!(file >> extraData))
				{
					lexError("Fin de archivo inesperado, string en proceso..");
					return 0;
				}
				word = word + " " + extraData;
				std::cout << "\nNueva palabra concatenada--> " << word << "\n";
			}
		}
		else if (isalpha(caracter))
		{
			iterPointer = i;
			while (i < word.length())
			{
				if (!isalpha(word[i]))
					break;
				i++;
			}
			if (isupper(word[iterPointer]))
			{
				iterPointer = i;
				return IDENTIFICADORFUNC;
			}
			else
			{
				std::string substring = word.substr(iterPointer, (i - iterPointer));
				iterPointer = i;
				if (substring.compare("for") == 0)
				{
					return FOR;
				}
				else if (substring.compare("while") == 0)
				{
					return WHILE;
				}
				else if (substring.compare("if") == 0)
				{
					return IF;
				}
				else if (substring.compare("float") == 0)
				{
					return FLOAT;
				}
				else if (substring.compare("array") == 0)
				{
					return ARRAY;
				}
				else if (substring.compare("matrix") == 0)
				{
					return MATRIX;
				}
				else if (substring.compare("string") == 0)
				{
					return STRING;
				}
				else if (substring.compare("main") == 0)
				{
					return MAIN;
				}
				else
				{
					return VARIABLE;
				}
			}

		}
		else if (isdigit(caracter))
		{
			while (i < word.length())
			{
				if (!isdigit(word[i]) && (word[i] != '.'))
					break;
				i++;
			}
			iterPointer = i;
			return NUMERO;
		}
		else
		{
			switch (caracter)
			{
			case '"':
				stringMode = true;
				break;
			case '=':
				if (i+1 < word.length())
					if (word[i + 1] == '='){
						iterPointer = i + 2;
						return COMPARACIONIGUALDAD;
					}
				iterPointer = i + 1;
				return ASIGNACION;
				break;
			case '-':
				iterPointer = i + 1;
				return RESTA;
				break;
			case '*':
				iterPointer = i + 1;
				return MULTIPLICACION;
				break;
			case '/':
				iterPointer = i + 1;
				return DIVISION;
				break;
			case '%':
				iterPointer = i + 1;
				return MODULO;
				break;
			case '+':
				return SUMA;
				break;
			case ':':
				iterPointer = i + 1;
				return RANGO;
				break;
			case '<':
				if ((i + 1) < word.length())
					if (word[i + 1] == '='){
						iterPointer = i + 2;
						return COMPARACIONMENORIGUAL;
					}
				iterPointer = i + 1;
				return COMPARACIONMENOR;
				break;
			case '>':
				if ((i + 1) < word.length())
					if (word[i + 1] == '='){
						iterPointer = i + 2;
						return COMPARACIONMAYORIGUAL;
					}
				iterPointer = i + 1;
				return COMPARACIONMAYOR;
				break;
			case '!':
				if ((i + 1) < word.length())
					if (word[i + 1] == '='){
						iterPointer = i + 2;
						return COMPARACIONDESIGUALDAD;
					}
				iterPointer = i + 1;
				return NEGACIONLOGICA;
				break;
			case '|':
				if ((i + 1) < word.length())
					if (word[i + 1] == '|'){
						iterPointer = i + 2;
						return ORLOGICO;
					}
				iterPointer = i + 1;
				lexError("Error léxico, | encontrado..");
				return 0;
				break;
			case '&':
				if ((i + 1) < word.length())
					if (word[i + 1] == '&'){
						iterPointer = i + 2;
						return ORLOGICO;
					}
				iterPointer = i + 1;
				lexError("Error léxico, & encontrado..");
				return 0;
				break;
			case ',':
				iterPointer = i + 1;
				return SEPARADOR;
				break;
			case '(':
				iterPointer = i + 1;
				return INICIO;
				break;
			case ')':
				iterPointer = i + 1;
				return FIN;
				break;
			case '[':
				iterPointer = i + 1;
				return MATRIXINICIO;
				break;
			case ']':
				iterPointer = i + 1;
				return MATRIXFIN;
				break;
			default:
				iterPointer = i + 1;
				std::string error = "Error léxico, " + caracter;
				error = error + " encontrado";
				lexError(error);
				return 0;
				break;
			}
		}
	}
	return 0;
}
