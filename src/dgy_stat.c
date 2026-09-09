#include "dgy_stat.h"

ErrCode dgyStatInit(DgyStatement *s)
{
        if (!s)
        {
                dgySetErr(ERR_NULLPTR, L"dgyStatInit");
                return CODE_FAILURE;
        }
        memset(s, 0, sizeof(DgyStatement));
        s->type = CELL_UNDEFINED;
        return CODE_SUCCESS;
}
