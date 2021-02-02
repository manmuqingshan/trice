/*! \file triceSeggerRTT.h
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#ifndef TRICE_SEGGER_RTT_H_
#define TRICE_SEGGER_RTT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void triceU32PushSeggerRTT(uint32_t v);
void triceU8PushSeggerRTT(uint8_t v);

#ifdef __cplusplus
}
#endif

#endif /* TRICE_SEGGER_RTT_H_ */