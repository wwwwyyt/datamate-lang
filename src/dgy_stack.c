#include "dgy_stack.h"

ErrCode dgyStackInit(DgyStack *s, size_t size)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackInit");
                return CODE_FAILURE;
        }
        memset(s, 0, sizeof(DgyStack));
        s->size = size;
        s->stack = (cell_t *)malloc(s->size * sizeof(cell_t));
        if (s->stack == NULL)
        {
                fwprintf(stderr, L"dgyStackInit: malloc() failed: %ls\n", strerror(errno));
                return CODE_FAILURE;
        }
        return CODE_SUCCESS;
}

ErrCode dgyStackResize(DgyStack *s, size_t newSize)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackResize");
                return CODE_FAILURE;
        }
        cell_t *newStack = (cell_t *)realloc(s->stack, newSize * sizeof(cell_t));
        if (newStack == NULL)
        {
                fwprintf(stderr, L"dgyStackResize: realloc() failed: %ls\n", strerror(errno));
                return CODE_FAILURE;
        }
        s->stack = newStack;
        s->size = newSize;
        return CODE_SUCCESS;
}

ErrCode dgyStackDestroy(DgyStack *s)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackDestroy");
                return CODE_FAILURE;
        }
        free(s->stack);
        memset(s, 0, sizeof(DgyStack));
        return CODE_SUCCESS;
}

ErrCode dgyStackPop(DgyStack *s)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackPop");
                return CODE_FAILURE;
        }
        if (s->sp == 0)
        {
                dgySetErr(ERR_UNDERFLOW, L"dgyStackPop");
                return CODE_FAILURE;
        }
        --(s->sp);
        if (s->sp == s->size / 4 && (CODE_SUCCESS != dgyStackResize(s, s->size / 2)))
        {
                dgyGetErr();
                return CODE_FAILURE;
        }
        return CODE_SUCCESS;
}

ErrCode dgyStackPush(DgyStack *s, cell_t data)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackPush");
                return CODE_FAILURE;
        }
        if (s->sp == s->size / 2 && (CODE_SUCCESS != dgyStackResize(s, 2 * s->size)))
        {
                dgyGetErr();
                return CODE_FAILURE;
        }
        s->stack[(s->sp)++] = data;
        return CODE_SUCCESS;
}

ErrCode dgyStackGetItemAt(const DgyStack *s, i32 idx, cell_t *data, i32 *absi)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackGetItemAt");
                return CODE_FAILURE;
        }
        if (idx >= 0)
        {
                *data = s->stack[idx];
                if (absi)
                {
                        *absi = idx;
                }
        }
        else if (s->sp + idx >= 0)
        {
                *data = s->stack[s->sp + idx];
                if (absi)
                {
                        *absi = s->sp + idx;
                }
        }
        else
        {
                dgySetErr(ERR_OUT_OF_BOUNDS, L"dgyStackGetItemAt");
                return CODE_FAILURE;
        }
        return CODE_SUCCESS;
}

ErrCode dgyStackTop(const DgyStack *s, cell_t *data)
{
        return dgyStackGetItemAt(s, -1, data, NULL);
}

bool dgyStackIsEmpty(const DgyStack *s)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackIsEmpty");
                return true;
        }
        return s->sp == 0;
}

ErrCode dgyStackClear(DgyStack *s)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackClear");
                return CODE_FAILURE;
        }
        if (CODE_SUCCESS != dgyStackResize(s, 16))
        {
                dgyGetErr();
                return CODE_FAILURE;
        }
        s->sp = 0;
        return CODE_SUCCESS;
}

/** @brief 用于在调试时以十六进制展示栈的内容
 *  @param s 栈的对象
 *  @param start 起始位置索引，小于 0 时从索引 0 处开始
 *  @param end 结束位置索引，小于 0 时打印到栈顶前
 */
ErrCode dgyStackDump(const DgyStack *s, i32 start, i32 end)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStackDump");
                return CODE_FAILURE;
        }
        i32 si, ei;
        if (start < 0 && end < 0)
        {
                si = 0;
                ei = s->sp;
        }
        else if (start < 0 && end >= 0)
        {
                si = 0;
                ei = end;
        }
        else if (start >= 0 && end < 0)
        {
                si = start;
                ei = s->sp;
        }
        else
        {
                si = start;
                ei = end;
        }
        wprintf(L"-----打印栈-----\n");
        for (i32 i = si; i < ei; ++i)
        {
                if (i >= 0 && i < s->size)
                {
                        wprintf(L"0x%llX ", s->stack[i].data.uint);
                }
                else
                {
                        dgySetErr(ERR_OUT_OF_BOUNDS, L"dgyStackDump");
                        return CODE_FAILURE;
                }
        }
        wprintf(L"\n");
        wprintf(L"----------------\n");
        return CODE_SUCCESS;
}
