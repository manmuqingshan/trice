/*! \file triceConfig.h
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#ifndef TRICE_CONFIG_H_
#define TRICE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define TRICE_BUFFER TRICE_RING_BUFFER
#define TRICE_CONFIG_WARNINGS 0
#define TRICE_DEFERRED_OUTPUT 1
#define TRICE_DEFERRED_TRANSFER_MODE TRICE_SINGLE_PACK_MODE
#define TRICE_DEFERRED_OUT_FRAMING TRICE_FRAMING_NONE
#define TRICE_DEFERRED_UARTA 1
#define TRICE_UARTA
#define TRICE_CGO 1
#define TRICE_CYCLE_COUNTER 0

#ifdef __cplusplus
}
#endif

#endif /* TRICE_CONFIG_H_ */
