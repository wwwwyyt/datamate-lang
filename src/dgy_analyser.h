#ifndef _dgy_analyser_h
#define _dgy_analyser_h

#include <stdio.h>
#include "dgy_parser.h"

/** @brief 语义分析层 */
typedef struct
{
        /** @brief 语法分析器 */
        DgyParser parser;

        /** @brief 字节码流 */
        FILE *bcstream;

        /** @brief 词典指针 */
        DgyDict *wordDict;
} DgyAnalyser;

ErrCode dgyAnalyserInit(DgyAnalyser *analyser, DgyDict *wordDict);
ErrCode dgyAnalyserDestroy(DgyAnalyser *analyser);
ErrCode dgyDoAnalyserOnce(DgyAnalyser *analyser, FILE *in);

#endif
