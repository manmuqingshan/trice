/*! \file triceConfig.h
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#ifndef TRICE_CONFIG_H_
#define TRICE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


  #define TRICE_MODE 0   // needs TRICE_UART
//#define TRICE_MODE 1   // needs TRICE_RTT_CHANNEL
//#define TRICE_MODE 200 // needs TRICE_UART or TRICE_RTT_CHANNEL

///////////////////////////////////////////////////////////////////////////////
// select RTT or UART for double buffer modes
//
//#define TRICE_RTT_CHANNEL 0 //!< Uncomment and set channel number for SeggerRTT usage
#ifdef TRICE_RTT_CHANNEL
#include "SEGGER_RTT.h"
#define TRICE_WRITE( buf, len ) do{ SEGGER_RTT_Write(TRICE_RTT_CHANNEL, buf, len ); }while(0)
static inline int TriceWriteOutDepth( void ){ return 0; }
#endif

#define TRICE_UART USART2 //!< Uncomment and set UART number for STM32
#ifdef TRICE_UART
#if TRICE_MODE != 0
#define TRICE_WRITE( buf, len ) do{ TriceNonBlockingWrite( buf, len ); }while(0)
#endif
#endif
//
///////////////////////////////////////////////////////////////////////////////


//! Direct output to UART with cycle counter. Trices inside interrupts allowed. Direct TRICE macro execution.
//! UART Command line similar to: `trice log -p COM1 -baud 115200`
#if TRICE_MODE == 0
#define TRICE_PUTCHAR( c ) do{ while( !triceTxDataRegisterEmpty() ); triceTransmitData8( c ); }while(0)
#define TRICE_SINGLE_MAX_SIZE 80 //!< TRICE_SINGLE_MAX_SIZE is the max allowed single trice size. Usually ~40 is enough. This plus TRICE_DATA_OFFSET is stack size!
#define TRICE_HEADLINE \
    TRICE0( Id( 57449), "s:                                          \n" ); \
    TRICE8( Id( 63820), "s:  TRICE_MODE %3d                          \n", TRICE_MODE ); \
    TRICE0( Id( 46700), "s:                                          \ns:     " ); \
    TRICE0( Id( 48724), "att:Direct TRICE write, +cycle, +int" ); \
    TRICE0( Id( 46377), "s:     \ns:                                          \n");
#define TRICE_ENTER /*! Start of TRICE macro */ \
    TRICE_ENTER_CRITICAL_SECTION { \
    ALIGN4 uint8_t co[TRICE_SINGLE_MAX_SIZE+TRICE_DATA_OFFSET]; ALIGN4_END /* This must be capable to hold the longest used TRICE plus 4 (offset). Check TriceDepthMax at runtime. */ \
    uint8_t* tr = co + TRICE_DATA_OFFSET; \
    uint32_t* wTb = (uint32_t*)tr;
#define TRICE_LEAVE { /*! End of TRICE macro */ \
    unsigned tlen = (uint8_t*)wTb - tr; \
    unsigned clen = COBSEncode( co, tr, tlen); \
    co[clen++] = 0; \
    TriceDepthMax = clen < TriceDepthMax ? TriceDepthMax : clen; /* diagnostics */ \
    do { for( unsigned i = 0; i < clen; i++ ){ TRICE_PUTCHAR( co[i] ); } }while(0); \
    } } TRICE_LEAVE_CRITICAL_SECTION
#endif


//! Direct output to RTT with cycle counter. Trices inside interrupts allowed. Direct TRICE macro execution.
//! RTT needs additional tools installed - see RTT documentation.
//! J-LINK Command line similar to: `trice log -args="-Device STM32G071RB -if SWD -Speed 4000 -RTTChannel 0 -RTTSearchRanges 0x20000000_0x1000"`
//! ST-LINK Command line similar to: `trice log -p ST-LINK -args="-Device STM32G071RB -if SWD -Speed 4000 -RTTChannel 0 -RTTSearchRanges 0x20000000_0x1000"`
#if TRICE_MODE == 1
#define TRICE_SINGLE_MAX_SIZE 80 //!< TRICE_SINGLE_MAX_SIZE is the max allowed single trice size. Usually ~40 is enough. This plus TRICE_DATA_OFFSET is stack size!
#define TRICE_HEADLINE \
    TRICE0( Id( 57449), "s:                                          \n" ); \
    TRICE8( Id( 63820), "s:  TRICE_MODE %3d                          \n", TRICE_MODE ); \
    TRICE0( Id( 46700), "s:                                          \ns:     " ); \
    TRICE0( Id( 48724), "att:Direct TRICE write, +cycle, +int" ); \
    TRICE0( Id( 46377), "s:     \ns:                                          \n");
#define TRICE_ENTER /*! Start of TRICE macro */ \
    TRICE_ENTER_CRITICAL_SECTION { \
    ALIGN4 uint8_t co[TRICE_SINGLE_MAX_SIZE+TRICE_DATA_OFFSET]; ALIGN4_END /* This must be capable to hold the longest used TRICE plus 4 (offset). Check TriceDepthMax at runtime. */ \
    uint8_t* tr = co + TRICE_DATA_OFFSET; \
    uint32_t* wTb = (uint32_t*)tr;
#define TRICE_LEAVE { /*! End of TRICE macro */ \
    unsigned tlen = (uint8_t*)wTb - tr; \
    unsigned clen = COBSEncode( co, tr, tlen); \
    co[clen++] = 0; \
    TriceDepthMax = clen < TriceDepthMax ? TriceDepthMax : clen; /* diagnostics */ \
    TRICE_WRITE( co, clen ); \
    } } TRICE_LEAVE_CRITICAL_SECTION
#endif


//! Double Buffering output to RTT or UART with cycle counter. Trices inside interrupts allowed. Fast TRICE macro execution. 
//! UART Command line similar to: `trice log -p COM1 -baud 115200`
//! RTT Command line similar to: `trice l -args="-Device STM32F030R8 -if SWD -Speed 4000 -RTTChannel 0 -RTTSearchRanges 0x20000000_0x1000"`
#if TRICE_MODE == 200
#define TRICE_HEADLINE \
    TRICE0( Id( 57449), "s:                                          \n" ); \
    TRICE8( Id( 61754), "s:  TRICE_MODE %3d                          \n", TRICE_MODE ); \
    TRICE0( Id( 46700), "s:                                          \ns:     " ); \
    TRICE0( Id( 39557), "att:Double buff, multi, +cycle, +int" ); \
    TRICE0( Id( 46377), "s:     \ns:                                          \n");
#define TRICE_ENTER /*! Start of TRICE macro */ \
    TRICE_ENTER_CRITICAL_SECTION
#define TRICE_LEAVE /*! End of TRICE macro */ \
    TRICE_LEAVE_CRITICAL_SECTION
#define TRICE_READ_AND_TRANSLATE_INTERVAL_MS 10
#define TRICE_HALF_BUFFER_SIZE 800 //!< This is the size of each of both buffers 
#define TRICE_READ_AND_TRANSFER TriceMultiReadAndWrite
#endif


//! Double Buffering output to UART without cycle counter. No trices inside interrupts allowed. Super fast TRICE macro execution. 
//! Command line similar to: `trice log -p COM1 -baud 115200`
#if TRICE_MODE == 201
#define TRICE_HEADLINE \
    TRICE0( Id( 57449), "s:                                          \n" ); \
    TRICE8( Id( 51851), "s:  TRICE_MODE %3d                          \n", TRICE_MODE ); \
    TRICE0( Id( 46700), "s:                                          \ns:     " ); \
    TRICE0( Id( 60240), "att: Double buff UART, ~cycle, ~int " ); \
    TRICE0( Id( 46377), "s:     \ns:                                          \n");
#define TRICE_CYCLE_COUNTER 0 //! no cycle counter for speed
#define TRICE_ENTER /*! Start of TRICE macro */
#define TRICE_LEAVE /*! End of TRICE macro */
#define TRICE_READ_AND_TRANSLATE_INTERVAL_MS 10
#define TRICE_HALF_BUFFER_SIZE 800 //!< This is the size each of of both buffers
#define TRICE_READ_AND_TRANSFER TriceMultiReadAndWrite
#endif



//  #ifdef TRICE_NO_CODE_GENERATION
//  #define TRICE_ENCODING TRICE_NOCODE_ENCODING //!< Select target trice transfer encoding.
//  #else
//  #define TRICE_ENCODING TRICE_COBSR_ENCODING //!< Select target trice transfer encoding.
//  #endif

//  #define TRICE_U8PUSH(v)  do{ /*triceU8PushSeggerRTT(v);  */ triceU8Push(v); } while(0) //!< Set trice out channel(s) 
//  #define TRICE_U32PUSH(v) do{ /*triceU32PushSeggerRTT(v); */ triceU32Push(v); } while(0) //!< Set trice out channel(s) 

//#define UART_LL_STM32 //!< set UART hardware dependency
//#define TRICE_UART USART2 //!< set UART number if UART is used



// Enabling next line results in XTEA encryption  with the key.
//#define ENCRYPT XTEA_KEY( ea, bb, ec, 6f, 31, 80, 4e, b9, 68, e2, fa, ea, ae, f1, 50, 54 ); //!< -password MySecret


#ifdef __cplusplus
}
#endif

#endif /* TRICE_CONFIG_H_ */
