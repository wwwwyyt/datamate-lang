#ifndef _dgy_stack_h
#define _dgy_stack_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dgy_type.h"
#include "dgy_cell.h"
#include "dgy_error.h"

typedef struct
{
        cell_t *stack; /* 禁止直接修改 */
        i32 sp;        /* 禁止直接修改 */
        size_t size;   /* 禁止直接修改 */
} DgyStack;

/** @brief 初始化栈 */
ErrCode dgyStackInit(DgyStack *s, size_t size);

/** @brief 重新设置栈的大小 */
ErrCode dgyStackResize(DgyStack *s, size_t newSize);

/** @brief 销毁栈 */
ErrCode dgyStackDestroy(DgyStack *s);

/** @brief 弹出栈顶下方的第一个元素 */
ErrCode dgyStackPop(DgyStack *s);

/** @brief 将元素压入栈顶 */
ErrCode dgyStackPush(DgyStack *s, cell_t data);

/** @brief 将栈清空 */
ErrCode dgyStackClear(DgyStack *s);

/** @brief 获取索引为 idx 的元素
 *
 * 索引可以为正或负，正索引从栈底开始，向上增长，栈底索引为 0；
 * 负索引从栈顶开始，向下增长，栈顶索引为 -1
 * @param s 栈对象
 * @param idx 索引
 * @param data 目标指针，如果成功，索引为 idx 的元素会存入 data 指向的地址
 * @param absi 绝对索引指针，不为 NULL 时，元素的绝对索引会存入 absi 指向的地址
 */
ErrCode dgyStackGetItemAt(const DgyStack *s, i32 idx, cell_t *data, i32 *absi);

/** @brief 获取栈顶下方的第一个元素 */
ErrCode dgyStackTop(const DgyStack *s, cell_t *data);

/** @brief 判断栈是否为空 */
bool dgyStackIsEmpty(const DgyStack *s);

/** @brief 调试用，打印栈中元素 */
ErrCode dgyStackDump(const DgyStack *s, i32 start, i32 end);

#endif /* _dgy_stack_h */
