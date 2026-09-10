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

static void parse_Exec(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_If(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_Else(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_ElseEnd(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_Hereis(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_Goto(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_LoopBegin(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_LoopCheck(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void parse_LoopEnd(DgyAnalyser *analyser)
{
        DgyStatement *statement = &(analyser->parser.statement);
}

static void (*_parserFuncList[])(DgyAnalyser *) = {
    /* 必须与 StatType 中的枚举值顺序相同 */
    parse_WordBegin,
    parse_WordEnd,
    parse_Mov,
    parse_SimpWord,
    parse_Exec,
    parse_If,
    parse_Else,
    parse_ElseEnd,
    parse_Hereis,
    parse_Goto,
    parse_LoopBegin,
    parse_LoopCheck,
    parse_LoopEnd,
};

ErrCode dgyDoAnalyserOnce(DgyAnalyser *analyser, FILE *in)
{
        dgyDoParserOnce(&(analyser->parser), in);
        DgyStatement *statement = &(analyser->parser.statement);
        _parserFuncList[statement->type](analyser);
        return CODE_SUCCESS;
}

ErrCode dgyAnalyserInit(DgyAnalyser *analyser, DgyDict *wordDict)
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
        /* 获取词典的指针 */
        analyser->wordDict = wordDict;
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
