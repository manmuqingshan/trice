/*! \file triceConfig.h
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#ifndef TRICE_CONFIG_H_
#define TRICE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRICE_BUFFER TRICE_DOUBLE_BUFFER
#define TRICE_DEFERRED_TRANSFER_MODE TRICE_MULTI_PACK_MODE
#define TRICE_DEFERRED_OUTPUT 1
#define TRICE_DEFERRED_OUT_FRAMING TRICE_FRAMING_COBS
#define TRICE_DEFERRED_UARTA 1
#define TRICE_UARTA
#define TRICE_CGO 1
#define TRICE_CYCLE_COUNTER 0

#ifdef __cplusplus
}
#endif

#endif /* TRICE_CONFIG_H_ */
