#ifndef _dgy_ir_h
#define _dgy_ir_h

#include "dgy_parser.h"

typedef struct
{
        StatType type;
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
                        i32 *args;
                        i32 tar;
                } Exec;
                struct
                {
                        i32 *cond;
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
                struct
                {
                        i32 label;
                } Goto;
                // LoopBegin
                struct
                {
                        i32 *cond;
                } LoopCheck;
                // LoopEnd
        } data;
} DgyIRNode;

#endif /* _dgy_ir_h */