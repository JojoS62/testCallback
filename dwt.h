#pragma once

static inline uint32_t getDwtCyccnt(void)
{
    return DWT->CYCCNT;
}
 
static inline void resetDwtCyccnt(void)
{
    DWT->CYCCNT = 0; // reset the counter
}
 
static inline void enableDwtCyccnt(void)
{
    CoreDebug->DEMCR = CoreDebug->DEMCR | CoreDebug_DEMCR_TRCENA_Msk;       // TRCENA = 1
    DWT->CTRL = DWT->CTRL | DWT_CTRL_CYCCNTENA_Msk;                         // enable the counter (CYCCNTENA = 1)
    DWT->CYCCNT = 0;                                                        // reset the counter
}

static inline void disableDwtCyccnt(void)
{
    DWT->CTRL = DWT->CTRL &~ DWT_CTRL_CYCCNTENA_Msk;                         // enable the counter (CYCCNTENA = 1)
    CoreDebug->DEMCR = CoreDebug->DEMCR & ~CoreDebug_DEMCR_TRCENA_Msk;       // TRCENA = 1
}