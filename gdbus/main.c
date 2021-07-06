#include <stdio.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#include "CarPlayInterface.h"

typedef int32_t		AirPlayTriState;
#define kAirPlayTriState_NotApplicable		0
#define kAirPlayTriState_False				-1
#define kAirPlayTriState_True				1

typedef int32_t		AirPlayTransferType;
#define kAirPlayTransferType_NotApplicable				0
#define kAirPlayTransferType_Take						1 // Transfer ownership permanently.
#define kAirPlayTransferType_Untake						2 // Release permanent ownership.
#define kAirPlayTransferType_Borrow						3 // Transfer ownership temporarily.
#define kAirPlayTransferType_Unborrow					4 // Release temporary ownership.

typedef int32_t		AirPlayTransferPriority;
#define kAirPlayTransferPriority_NotApplicable				0
#define kAirPlayTransferPriority_NiceToHave					100 // Transfer succeeds only if constraint is <= Anytime.
#define kAirPlayTransferPriority_UserInitiated				500 // Transfer succeeds only if constraint is <= UserInitiated.

typedef int32_t		AirPlayConstraint;
#define kAirPlayConstraint_NotApplicable			0
#define kAirPlayConstraint_Anytime					100  // Resource may be taken/borrowed at any time.
#define kAirPlayConstraint_UserInitiated			500  // Resource may be taken/borrowed if user initiated.
#define kAirPlayConstraint_Never					1000 // Resource may never be taken/borrowed.


typedef int8_t		AirPlaySpeechMode;
#define kAirPlaySpeechMode_NotApplicable			0
#define kAirPlaySpeechMode_None						-1 // No speech-related states are active.
#define kAirPlaySpeechMode_Speaking					1  // Device is speaking to the user.
#define kAirPlaySpeechMode_Recognizing				2  // Device is recording audio to recognize speech from the user.

static  void _sendGenericChangeModeRequest(
        const char                      *arg_screenBorrowId,
        AirPlayTransferType             arg_screenType,
        AirPlayTransferPriority         arg_screenPriority,
        AirPlayConstraint               arg_screenTake,
        AirPlayConstraint               arg_screenBorrow,
        const char                      *arg_audioBorrowId,
        AirPlayTransferType             arg_audioType,
        AirPlayTransferPriority         arg_audioPriority,
        AirPlayConstraint               arg_audioTake,
        AirPlayConstraint               arg_audioBorrow,
        AirPlayTriState                 arg_phone,
        AirPlaySpeechMode               arg_speech,
        AirPlayTriState                 arg_turnByTurn)
{
    printf("2_sendGenericChangeModeRequest %s %d\n", arg_screenBorrowId, arg_screenType);
}

static void _touchScreenUpdate( bool inPress, uint16_t inX, uint16_t inY )
{

}

int main() {
    printf("Hello, World!\n");

    CarPlayInterfaceDelegate    delegate;

    CarPlayInterfaceDelegateInit(&delegate);
    delegate.changeMode_f = _sendGenericChangeModeRequest;
    delegate.touchScreenUpdate_f = _touchScreenUpdate;
    CarPlayInterfaceSetDelegate(&delegate);

    CarPlayInterfaceInitialized();
    return 0;
}
