//
// Created by guts on 6/24/21.
//

#ifndef GDBUS_CARPLAYINTERFACE_H
#define GDBUS_CARPLAYINTERFACE_H

#include "generate/GDbusCarPlay.h"
#include <stdio.h>

typedef void (*CarPlayInterfaceSendChangeModes_f)(
        const gchar            *arg_screenBorrowId,
        gint                   arg_screenType,
        gint                   arg_screenPriority,
        gint                   arg_screenTake,
        gint                   arg_screenBorrow,
        const gchar            *arg_audioBorrowId,
        gint                   arg_audioType,
        gint                   arg_audioPriority,
        gint                   arg_audioTake,
        gint                   arg_audioBorrow,
        gint                   arg_phone,
        gint                   arg_speech,
        gint                   arg_turnByTurn);

typedef void (*CarPlayInterfaceSendChangeResourceMode_f)(
        const gchar             *arg_borrowID,
        gint                    arg_resourceId,
        gint                    arg_type,
        gint                    arg_priority,
        gint                    arg_takeConstraint,
        gint                    arg_borrowConstraint);

typedef void (*CarPlayInterfaceSendChangeAppState_f)(
        gint                    arg_speech,
        gint                    arg_phone,
        gint                    arg_turnByTurn
        );

typedef void (*CarPlayInterfaceSendRequestUi_f)();

typedef void (*CarPlayInterfaceSendSetNightMode_f)(
        gint                    arg_nightMode);

typedef void (*CarPlayInterfaceSendRequestSiriAction_f)(
        gint                     arg_action);

typedef void (*CarPlayInterfaceSendTouchScreenUpdate_f)(
        gboolean                 arg_press,
        guint16                  arg_x,
        guint16                  arg_y);

// typedef void (*CarPlayInterface_f)();

typedef struct
{
    CarPlayInterfaceSendChangeModes_f           changeMode_f;
    CarPlayInterfaceSendChangeResourceMode_f    changeResourceMode_f;
    CarPlayInterfaceSendChangeAppState_f        changeAppState_f;
    CarPlayInterfaceSendRequestUi_f             requestUi_f;
    CarPlayInterfaceSendSetNightMode_f          setNightMode_f;
    CarPlayInterfaceSendRequestSiriAction_f     requestSiriAction_f;
    CarPlayInterfaceSendTouchScreenUpdate_f     touchScreenUpdate_f;
} CarPlayInterfaceDelegate;

#define CarPlayInterfaceDelegateInit( PTR )	memset( (PTR), 0, sizeof( CarPlayInterfaceDelegate ) );

void CarPlayInterfaceSetDelegate( const CarPlayInterfaceDelegate *inDelegate );

void CarPlayInterfaceInitialized();

#endif //GDBUS_CARPLAYINTERFACE_H
