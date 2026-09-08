#ifndef _dgy_stack_h
#define _dgy_stack_h

#include "dgy_all.h"
#include "dgy_error.h"

typedef struct
{
        cell_t *stack; /* 禁止直接修改 */
        i32 sp;        /* 禁止直接修改 */
        size_t size;   /* 禁止直接修改 */
} DgyStack;

/** @brief  */
ErrCode dgyStackInit(DgyStack *s, size_t size);

/** @brief  */
ErrCode dgyStackResize(DgyStack *s, size_t newSize);

/** @brief  */
ErrCode dgyStackDestroy(DgyStack *s);

/** @brief  */
ErrCode dgyStackPop(DgyStack *s);

/** @brief  */
ErrCode dgyStackPush(DgyStack *s, cell_t data);

/** @brief 将栈清空 */
ErrCode dgyStackClear(DgyStack *s);

/** @brief  */
ErrCode dgyStackItemAt(const DgyStack *s, i32 idx, cell_t *data);

/** @brief  */
ErrCode dgyStackTop(const DgyStack *s, cell_t *data);

/** @brief 判断栈是否为空 */
bool dgyStackIsEmpty(const DgyStack *s);

/** @brief  */
ErrCode dgyStackDump(const DgyStack *s, i32 start, i32 end);

#endif /* _dgy_stack_h */
