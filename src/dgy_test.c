#include "dgy_test.h"
#include "dgy_builtin.h"

static void test_lexer(void)
{
        DgyStack buffer;
        dgyStackInit(&buffer, 16);
        dgyDoLexerOnce(stdin, &buffer);
        dgyStackDump(&buffer, -1, -1);
}

static void test_parser(void)
{
        DgyParser parser;
        dgyParserInit(&parser);

        dgyStackDump(&parser.symbolStack, 0, -1);

        dgyDoParserOnce(&parser, stdin);

        dgyParserDestroy(&parser);
}

void dgyUnitTest(void)
{
        if (0)
        {
                test_lexer();
                test_parser();
        }
        test_parser();
}
