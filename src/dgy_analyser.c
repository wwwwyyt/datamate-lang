#include "dgy_analyser.h"

static void parse_WordBegin(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_WordEnd(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_Mov(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_SimpWord(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void (*_parserFuncList[])(DgyAnalyser *) = {
    parse_WordBegin,
    parse_WordEnd,
    parse_Mov,
    parse_SimpWord,
};

ErrCode dgyDoAnalyserOnce(DgyAnalyser *analyser, FILE *in)
{
        dgyDoParserOnce(&(analyser->parser), in);
        DgyStatement *statement = &(analyser->parser.statement);
        _parserFuncList[statement->type](analyser);
        return CODE_SUCCESS;
}

ErrCode dgyAnalyserInit(DgyAnalyser *analyser)
{
        if (!analyser)
        {
                dgySetErr(ERR_NULLPTR, L"dgyAnalyserInit");
                return CODE_FAILURE;
        }
        memset(analyser, 0, sizeof(DgyAnalyser));
        /* 初始化语法分析器 */
        dgyParserInit(&(analyser->parser));
        /* 初始化字节码流 */
        analyser->bcstream = tmpfile();
        return CODE_SUCCESS;
}

ErrCode dgyAnalyserDestroy(DgyAnalyser *analyser)
{
        if (!analyser)
        {
                dgySetErr(ERR_NULLPTR, L"dgyAnalyserDestroy");
                return CODE_FAILURE;
        }
        /* 销毁语法分析器 */
        dgyParserDestroy(&(analyser->parser));
        return CODE_SUCCESS;
}
