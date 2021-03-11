/*! \file triceConfig.h
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#ifndef TRICE_CONFIG_H_
#define TRICE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define TRICE_HEADLINE \
TRICE0( Id(65422), "s:                                                   \ns:                     myProject                     \ns:                                                   \n\n")

///////////////////////////////////////////////////////////////////////////////
//
//#define TRICE_ENTER_CRITICAL_SECTION { // Uncomment for more speed but only if TRICE macros & fifo access cannot
//#define TRICE_LEAVE_CRITICAL_SECTION } // get interrupted by other TRICE macros or fifo access (e.g. interrupts).
//
///////////////////////////////////////////////////////////////////////////////

#define TRICE_FIFO_BYTE_SIZE 2048 //!< must be a power of 2

///////////////////////////////////////////////////////////////////////////////
// select target trice method
#define TRICE_ENCODING TRICE_FLEX_ENCODING

#define TRICE_HARDWARE_ENDIANNNESS TRICE_LITTLE_ENDIANNESS 

//! Set byte order according desired transfer format. Options: TRICE_BIG_ENDIANNESS, TRICE_LITTLE_ENDIANNESS. 
//! TRICE_BIG_ENDIANNESS is network order.
//! If TRICE_TRANSFER_ENDIANNESS is equal to TRICE_HARDWARE_ENDIANNNESS the trice code is smaller and more efficient.
//! When set to TRICE_LITTLE_ENDIANNESS the trice tool -enc format specifier is extended by a letter 'l' (small 'L').
//! Example -enc "pack" -> -encoding "packL".
#define TRICE_TRANSFER_ENDIANNESS TRICE_LITTLE_ENDIANNESS 
//#define TRICE_U8PUSH(v) do{ /*triceU8PushSeggerRTT(v);*/ triceU8Push(v); } while(0) //!< Set trice out channel(s) 
#define TRICE_U32PUSH(v) do{ /*triceU32PushSeggerRTT(v);*/ triceU32Push(v); } while(0) //!< Set trice out channel(s) 
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// uncomment for trice wrap transfer format
// #define TRICE_WRAP_START_BYTE 0xEB // 235
// #define TRICE_WRAP_LOCAL_ADDR 0x60 // to do: also trice tool parameter
// #define TRICE_WRAP_DEST_ADDR  0x60 // to do: also trice tool parameter
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// uncomment for trice UART transfer format
#define TRICE_UART USART2 // set UART number
///////////////////////////////////////////////////////////////////////////////

void triceCheckSetTime( int index ); //!< tests
void triceCheckSetSpace( int index ); //!< tests

#ifdef __cplusplus
}
#endif

#endif /* TRICE_CONFIG_H_ */