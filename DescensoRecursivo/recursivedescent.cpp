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

	functionT.first.resize(3);
	functionT.first[0] = FLOAT;
	functionT.first[1] = MATRIX;
	functionT.first[2] = ARRAY;

	typesT.first.resize(3);
	typesT.first[0] = FLOAT;
	typesT.first[1] = MATRIX;
	typesT.first[2] = ARRAY;

	variablesT.first.resize(3);
	variablesT.first[0] = FLOAT;
	variablesT.first[1] = MATRIX;
	variablesT.first[2] = ARRAY;

	bucle_forT.first.resize(1);
	bucle_forT.first[0] = FOR;

	bucle_whileT.first.resize(1);
	bucle_whileT.first[0] = WHILE;

	cond_ifT.first.resize(1);
	cond_ifT.first[0] = IF;
	
	//initialize file read	
	if (argc > 1)
	{
		std::string filein(argv[1]);
		file.open(filein, std::ifstream::in);
	}
	else
		exit(1);

	token = yylex();
	mainf();
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
					if (token == FIN)
					{
						token = yylex();
						statements();
						if (token == FIN)
						{
							while (token = yylex() == INICIO)
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
	while (checkFirst(statementsT))
	{
		statement();
	}
}

void statement()
{
	if (token == INICIO)
	{
		if (token = yylex() == VARIABLE)
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
		if (token = yylex() == NUMERO)
		{
			token = yylex();
			if (token == SEPARADOR)
			{
				if (token = yylex() != NUMERO)
				{
					tokenError("Error en assignment");
				}
				token = yylex();
			}
			if (token != FIN)
			{
				tokenError("Error en assignment");
			}
			token = yylex();
		}
		else
		{
			tokenError("Error en assignment");
		}
	}
	if (token == ASIGNACION)
	{
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
		if (token = yylex() == NUMERO)
		{
			if (token = yylex() == SEPARADOR)
			{
				if (token = yylex() == NUMERO)
				{
					token = yylex();
				}
				{
					tokenError("Error en declaration");
				}
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
	else
	{
		tokenError("Error en declaration");
	}
}

void expression()
{
	if (token == IDENTIFICADORFUNC)
	{
		if (token = yylex() == INICIO)
		{
			token = yylex();
			values();
			if (token != FIN)
			{
				tokenError("Error en expression");
			}
		}
	}
	else
	{
		if (checkFirst(valueT))
		{
			value();
			if (!(token == SUMA || token == RESTA || token == MULTIPLICACION || token == DIVISION ||
				token == MODULO || token == COMPARACIONIGUALDAD || token == COMPARACIONDESIGUALDAD || token == COMPARACIONMAYOR ||
				token == COMPARACIONMAYORIGUAL || token == COMPARACIONMENOR || token == COMPARACIONMENORIGUAL || token == ANDLOGICO ||
				token == ORLOGICO))
				tokenError("Error en expression");
		}
		else if (token != NEGACIONLOGICA)
			tokenError("Error en expression");
		token = yylex();
		value();
	}

}

void value()
{
	if (token == NUMERO)
	{
		if (token = yylex() == MATRIXINICIO)
		{
			if (token = yylex() == NUMERO)
			{
				if (token = yylex() == SEPARADOR)
				{
					if (token = yylex() != NUMERO)
					{
						tokenError("Error en value");
						token = yylex();
					}
				}
				if (token != MATRIXFIN)
				{
					tokenError("Error en value");
				}
				token = yylex();
			}
			else
			{
				tokenError("Error en value");
			}
		}
		else
		{
			tokenError("Error en value");
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
	else if (token != VARIABLE || token != PALABRA)
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
	if (token = yylex() != IDENTIFICADORFUNC)
		tokenError("Error en function");
	if (token = yylex() != INICIO)
		tokenError("Error en function");
	token = yylex();
	variables();

	if (token != FIN)
		tokenError("Error en function");
	if (token != FIN)
		tokenError("Error en function");
	token = yylex();
	statements();
}

void types()
{
	if (token != FLOAT && token != MATRIX && token != ARRAY)
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
	if (token =yylex()!= VARIABLE)
		tokenError("Error en bucle_for");
	if (token = yylex() != NUMERO)
		tokenError("Error en bucle_for");
	if (token = yylex() != RANGO)
		tokenError("Error en bucle_for");
	if (token = yylex() != NUMERO)
		tokenError("Error en bucle_for");
	if (token = yylex() != FIN)
		tokenError("Error en bucle_for");
	token = yylex();
	statements();
}

void bucle_while()
{
	if (token != WHILE)
		tokenError("Error en bucle_for");
	if (token = yylex() != INICIO)
		tokenError("Error en bucle_for");
	token = yylex();
	expression();
	if (token != FIN)
		tokenError("Error en bucle_for");;
	if (token = yylex() != FIN)
		tokenError("Error en bucle_for");
	token = yylex();
	statements();
}

void cond_if()
{
	if (token != IF)
		tokenError("Error en bucle_for");
	if (token = yylex() != INICIO)
		tokenError("Error en bucle_for");
	token = yylex();
	expression();
	if (token != FIN)
		tokenError("Error en bucle_for");
	if (token = yylex() != FIN)
		tokenError("Error en bucle_for");
	token = yylex();
	statements();
}

void tokenError(std::string error)
{
	printf("%s: token %i encontrado", error, token);
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
	return 0;
}
