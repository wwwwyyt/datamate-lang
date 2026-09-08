#ifndef _dgy_parser_h
#define _dgy_parser_h

#include "dgy_all.h"
#include "dgy_lexer.h"
#include "dgy_stack.h"
#include "dgy_dict.h"
#include "dgy_error.h"

enum
{
        MATCH_COMPLETED = -1
};

typedef enum
{
        STATTYPE_UNDEFINED = -1,
        ST_WORD_BEGIN = 0,
        ST_WORD_END,
        ST_MOV,
        ST_SET_REG,
        ST_EXEC,
        ST_IF,
        ST_ELSE,
        ST_ELSE_END,
        ST_HEREIS,
        ST_GOTO,
        ST_LOOP_BEGIN,
        ST_LOOP_CHECK,
        ST_LOOP_END,
        STATTYPE_CNT,
} StatType;

typedef struct
{
        /** @brief 用于语法分析，仅保存符号类型 */
        DgyStack analyStack;

        /** @brief 用于存储词法分析返回的符号信息 */
        DgyStack symbolStack;
} DgyParser;

ErrCode dgyParserInit(DgyParser *parser);
ErrCode dgyParserDestroy(DgyParser *parser);
ErrCode dgyDoParserOnce(DgyParser *parser, FILE *in);

#endif /* _dgy_parser_h */
