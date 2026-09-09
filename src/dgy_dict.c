#include "dgy_dict.h"

static ErrCode resize(size_t newSize, DgyDict *dict)
{
        if (!dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgy_dict: resize");
                return CODE_FAILURE;
        }
        // 分配空间 - DgyDict.dict
        DictItem *newDict = (DictItem *)realloc(dict->dict, newSize * sizeof(DictItem));
        if (newDict == NULL)
        {
                wprintf(L"dgy_dict: resize: realloc() failed");
                return CODE_FAILURE;
        }
        dict->dict = newDict;
        dict->size = newSize;
        return CODE_SUCCESS;
}

ErrCode dgyDictInit(DgyDict *dict, size_t size)
{
        if (!dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictInit");
                return CODE_FAILURE;
        }
        memset(dict, 0, sizeof(DgyDict));
        dict->size = size;
        dict->top = 0;
        dict->dict = (DictItem *)malloc(dict->size * sizeof(DictItem));
        if (dict->dict == NULL)
        {
                fwprintf(stderr, L"dgyDictInit: malloc() failed: %ls\n", strerror(errno));
                return CODE_FAILURE;
        }
        return CODE_SUCCESS;
}

ErrCode dgyDictAdd(DgyDict *dict, const wchar_t *name, i32 entry, i32 level)
{
        if (!name || !dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictAdd");
                return CODE_FAILURE;
        }
        size_t nameLen = wcslen(name);
        DictItem newItem;
        // 分配空间 - DictItem.name
        newItem.name = (wchar_t *)malloc(nameLen * sizeof(wchar_t));
        wcscpy(newItem.name, name);
        newItem.entry = entry;
        newItem.level = level;
        if (dict->top == dict->size / 2 && (CODE_SUCCESS != resize(2 * dict->size, dict)))
        {
                return CODE_FAILURE;
        }
        dict->dict[(dict->top)++] = newItem;
        return CODE_SUCCESS;
}

static i32 searchItemByEntry(const DgyDict *dict, i32 entry)
{
        i32 itemIdx = -1;
        for (i32 i = dict->top - 1; i >= 0; --i)
        {
                DictItem item = dict->dict[i];
                if (item.entry == entry)
                {
                        itemIdx = i;
                        break;
                }
        }
        return itemIdx;
}

i32 dgyDictSearchIn(const DgyDict *dict, const wchar_t *name, i32 parentEntry)
{
        if (!name || !dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictSearchIn");
                return -1;
        }
        i32 entry = -1;
        if (parentEntry == -1)
        {
                for (i32 i = dict->top - 1; i >= 0; --i)
                {
                        DictItem item = dict->dict[i];
                        if (item.level == 0 &&
                            wcscmp(item.name, name) == 0)
                        {
                                entry = item.entry;
                                break;
                        }
                }
        }
        else if (parentEntry >= 0)
        {
                i32 itemIdx = searchItemByEntry(dict, parentEntry);
                if (itemIdx >= 0)
                {
                        i32 parentLevel = dict->dict[itemIdx].level;
                        for (i32 i = itemIdx + 1; dict->dict[i].level < parentLevel; ++i)
                        {
                                DictItem item = dict->dict[i];
                                if (item.level == parentLevel + 1 &&
                                    wcscmp(item.name, name) == 0)
                                {
                                        entry = item.entry;
                                        /* Don't break */
                                }
                        }
                }
        }
        return entry;
}

i32 dgyDictSearchEx(const DgyDict *dict, const wchar_t *name, i32 parentEntry)
{
        if (!name || !dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictSearchIn");
                return -1;
        }
        i32 entry = -1;
        if (parentEntry >= 0)
        {
                i32 itemIdx = searchItemByEntry(dict, parentEntry);
                if (itemIdx >= 0)
                {
                        i32 parentLevel = dict->dict[itemIdx].level;
                        for (i32 i = itemIdx - 1; i >= 0; --i)
                        {
                                DictItem item = dict->dict[i];
                                if (item.level == parentLevel &&
                                    wcscmp(item.name, name) == 0)
                                {
                                        entry = item.entry;
                                        break;
                                }
                        }
                }
        }
        return entry;
}

ErrCode dgyDictDestroy(DgyDict *dict)
{
        if (!dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictDestroy");
                return CODE_FAILURE;
        }
        for (i32 i = 0; i < dict->top; ++i)
        {
                // 释放空间 - DictItem.name
                free(dict->dict[i].name);
                memset(&(dict->dict[i]), 0, sizeof(DictItem));
        }
        // 释放空间 - DgyDict.dict
        free(dict->dict);
        memset(dict, 0, sizeof(DgyDict));
        return CODE_SUCCESS;
}

ErrCode dgyDictDump(const DgyDict *dict)
{
        if (!dict)
        {
                dgySetErr(ERR_NULLPTR, L"dgyDictDump");
                return CODE_FAILURE;
        }
        for (i32 i = 0; i < dict->top; ++i)
        {
                DictItem item = dict->dict[i];
                wprintf(L"%ls : %d\n", item.name, item.entry);
        }
        return CODE_SUCCESS;
}
