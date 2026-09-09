#ifndef _dgy_stat_h
#define _dgy_stat_h

#include <string.h>
#include "dgy_cell.h"
#include "dgy_error.h"

/** @brief 语句的类型 */
typedef enum
{
        STATTYPE_UNDEFINED = -1,
        ST_WORD_BEGIN = 0,
        ST_WORD_END,
        ST_MOV,
        ST_SIMP_WORD,
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

enum
{
        ST_MAX_SYM_CNT = 1024, /* 最大符号数量，用于执行语句、条件表达式 */
};

/** @brief 语句的中间表示 */
typedef struct
{
        /** @brief 语句的类型 */
        StatType type;

        /** @brief 组成语句的符号在符号栈中的索引 */
        union
        {
                struct
                {
                        i32 word;
                } WordBegin;
                struct
                {
                        i32 word;
                } WordEnd;
                struct
                {
                        i32 src;
                        i32 tar;
                } Mov;
                struct
                {
                        i32 word;
                        i32 src;
                } SimpWord;
                struct
                {
                        i32 args[ST_MAX_SYM_CNT];
                        i32 i;
                        i32 tar;
                } Exec;
                struct
                {
                        i32 cond[ST_MAX_SYM_CNT];
                        i32 i;
                } If;
                // Else
                // ElseEnd
                struct
                {
                        i32 label;
                } Hereis;
                struct
                {
                        i32 label;
                } Goto;
                // LoopBegin
                struct
                {
                        i32 cond[ST_MAX_SYM_CNT];
                        i32 i;
                } LoopCheck;
                struct
                {
                        i32 times; /* 存放计数循环的次数的符号 */
                        i32 type;  /* 条件匹配类型: 不成立 0 / 成立 1 / 无条件 2 */
                } LoopEnd;
        } data;
} DgyStatement;

ErrCode dgyStatInit(DgyStatement *s);

#endif /* _dgy_stat_h */