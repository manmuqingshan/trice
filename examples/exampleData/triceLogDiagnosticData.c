/*! \file triceLogDiagnosticData.c
\author Thomas.Hoehenleitner [at] seerose.net
*******************************************************************************/

#include "trice.h"

#ifdef __cplusplus
extern "C" {
#endif

#if TRICE_DIAGNOSTICS == 1

//! TriceLogDiagnosticValues shows the max used buffer space. 
void TriceLogDiagnosticValues( void ){

#ifdef SEGGER_RTT
    int RTT0_wrSpaceMin = BUFFER_SIZE_UP - RTT0_writeDepthMax;
    if( (RTT0_wrSpaceMin < TRICE_BUFFER_SIZE) ){
        trice( iD(13071), "WARNING:RTT0_writeDepthMax=%u (BUFFER_SIZE_UP=%u)\n", RTT0_writeDepthMax, BUFFER_SIZE_UP );
    }else{
        trice( iD(13072), "diag:RTT0_writeDepthMax=%u (BUFFER_SIZE_UP=%u)\n", RTT0_writeDepthMax, BUFFER_SIZE_UP );
    }
#endif // #ifdef SEGGER_RTT

    unsigned triceSingleDepthMax = TRICE_DATA_OFFSET + (TriceSingleMaxWordCount<<2); //lint !e845 Info 845: The left argument to operator '<<' is certain to be 0 
    if( triceSingleDepthMax <= TRICE_BUFFER_SIZE ){
        TRice16( iD(13073), "diag:triceSingleDepthMax =%4u of %d (TRICE_BUFFER_SIZE)\n", triceSingleDepthMax, TRICE_BUFFER_SIZE );
    }else{
        TRice16( iD(13074), "err:triceSingleDepthMax =%4u of %d (TRICE_BUFFER_SIZE overflow!)\n", triceSingleDepthMax, TRICE_BUFFER_SIZE );
    }
    
    if( TriceDataOffsetDepthMax < 0 || TriceDataOffsetDepthMax >= TRICE_DATA_OFFSET ){
        TRice16( iD(13075), "err:TriceDataOffsetDepthMax = %d of %d (TRICE_DATA_OFFSET\n", TriceDataOffsetDepthMax, TRICE_DATA_OFFSET );
    }else if( TriceDataOffsetDepthMax != 0 ){
        TRice16( iD(13076), "diag:TriceDataOffsetDepthMax = %d of %d (TRICE_DATA_OFFSET\n", TriceDataOffsetDepthMax, TRICE_DATA_OFFSET );
    }

    if(TriceDynBufTruncateCount != 0){
        trice( iD(13077), "err: TriceDynBufTruncateCount = %u\n", TriceDynBufTruncateCount );
    }
    
#if TRICE_PROTECT == 1

    if(TriceDirectOverflowCount != 0){
        trice( iD(13078), "err: TriceDirectOverflowCount = %u\n", TriceDirectOverflowCount );
    }
    if(TriceDeferredOverflowCount != 0){
        trice( iD(13079), "err: TriceDeferredOverflowCount = %u\n", TriceDeferredOverflowCount );
    }

#endif

    if(TriceErrorCount > 0){
        trice( iD(13080), "err: TriceErrorCount = %u\n", TriceErrorCount );
    }

#if TRICE_BUFFER == TRICE_STACK_BUFFER
#endif // #if TRICE_BUFFER == TRICE_STACK_BUFFER

#if TRICE_BUFFER == TRICE_STATIC_BUFFER
#endif // #if TRICE_BUFFER == TRICE_STATIC_BUFFER
	
#if TRICE_BUFFER == TRICE_DOUBLE_BUFFER
    if( TriceHalfBufferDepthMax <= TRICE_DEFERRED_BUFFER_SIZE/2 ){
        TRice16( iD(13081), "diag:TriceHalfBufferDepthMax =%4u of%5d\n", TriceHalfBufferDepthMax, TRICE_DEFERRED_BUFFER_SIZE/2 );
    }else{
        TRice16( iD(13082), "err:TriceHalfBufferDepthMax =%4u of%5d (overflow!)\n", TriceHalfBufferDepthMax, TRICE_DEFERRED_BUFFER_SIZE/2 );
    }
#endif // #if TRICE_BUFFER == TRICE_DOUBLE_BUFFER

#if TRICE_BUFFER == TRICE_RING_BUFFER
    if( TriceRingBufferDepthMax <= TRICE_DEFERRED_BUFFER_SIZE ){
        trice16( iD(13084), "diag:triceRingBufferDepthMax =%4u of%5d\n", TriceRingBufferDepthMax, TRICE_DEFERRED_BUFFER_SIZE );
    }else{
        trice16( iD(13085), "err:triceRingBufferDepthMax =%4u of%5d (overflow!)\n", TriceRingBufferDepthMax, TRICE_DEFERRED_BUFFER_SIZE );
    }
#endif // #if TRICE_BUFFER == TRICE_RING_BUFFER
}

#endif // #if TRICE_DIAGNOSTICS == 1