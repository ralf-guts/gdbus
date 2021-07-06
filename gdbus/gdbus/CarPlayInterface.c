//
// Created by guts on 6/24/21.
//

#include "CarPlayInterface.h"

static  CarPlayInterfaceDelegate gCarPlayInterfaceDelegate;

//=================================================================================================================
// register interface
//=================================================================================================================

void CarPlayInterfaceSetDelegate( const CarPlayInterfaceDelegate *inDelegate )
{
    gCarPlayInterfaceDelegate = *inDelegate;
}

//=================================================================================================================
// interface com.hsae.airplay
//=================================================================================================================

gboolean sendChangeModes(Airplay                *object,
                         GDBusMethodInvocation  *invocation,
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
                         gint                   arg_turnByTurn)
{
    printf("sendChangeModes! %s %d %d\n", arg_screenBorrowId, arg_screenType, arg_audioType);

    gCarPlayInterfaceDelegate.changeMode_f(arg_screenBorrowId, arg_screenType, arg_screenPriority, arg_screenTake, arg_screenBorrow,
                                           arg_audioBorrowId, arg_audioType, arg_audioPriority, arg_audioTake, arg_audioBorrow, arg_phone, arg_speech, arg_turnByTurn);

    airplay_complete_send_change_modes(object, invocation);

    return TRUE;
}

gboolean sendChangeResourceMode(Airplay                 *object,
                                GDBusMethodInvocation   *invocation,
                                const gchar             *arg_borrowID,
                                gint                    arg_resourceId,
                                gint                    arg_type,
                                gint                    arg_priority,
                                gint                    arg_takeConstraint,
                                gint                    arg_borrowConstraint)
{
    printf("sendChangeResourceMode borrowId is %s type is %d.\n", arg_borrowID, arg_type);
    airplay_complete_send_change_resource_mode(object, invocation);

    return TRUE;
}

gboolean sendChangeAppState(Airplay                 *object,
                            GDBusMethodInvocation   *invocation,
                            gint                    arg_phone,
                            gint                    arg_speech,
                            gint                    arg_turnByTurn)
{
    printf("sendChangeAppState phone is %d speech is %d.\n", arg_phone, arg_speech);
    airplay_complete_send_change_app_state(object, invocation);

    return TRUE;
}

gboolean sendRequestUi(Airplay                 *object,
                       GDBusMethodInvocation   *invocation)
{
    printf("sendRequestUi.\n");
    airplay_complete_send_request_ui(object, invocation);

    return TRUE;
}

gboolean sendSetNightMode(Airplay                 *object,
                          GDBusMethodInvocation   *invocation,
                          gint                    arg_nightMode)
{
    printf("sendSetNightMode mode is %d.\n", arg_nightMode);
    airplay_complete_send_set_night_mode(object, invocation);

    return TRUE;
}

gboolean sendRequestSiriAction(Airplay                  *object,
                               GDBusMethodInvocation    *invocation,
                               gint                     arg_action)
{
    printf("sendRequestSiriAction action is %d.\n", arg_action);
    airplay_complete_send_request_siri_action(object, invocation);

    return TRUE;
}

gboolean sendTouchScreenUpdate(Airplay                  *object,
                               GDBusMethodInvocation    *invocation,
                               gboolean                 arg_press,
                               guint16                  arg_x,
                               guint16                  arg_y)
{
    printf("sendTouchScreenUpdate press is %d (%d, %d).\n", arg_press, arg_x, arg_y);
    airplay_complete_send_touch_screen_update(object, invocation);

    return TRUE;
}

//=================================================================================================================
// interface com.hsae.iap2
//=================================================================================================================

void sendStartCallStateUpdates()
{
    printf("sendStartCallStateUpdates!\n");
}

//=================================================================================================================
// gdbus setup
//=================================================================================================================

static void airplay_name_acquired_handler(GDBusConnection   *connection,
                                          const gchar       *name,
                                          gpointer          user_data)
{
    printf("airplay_name_acquired_handler!\n");

    Airplay *object;
    GError  **error = NULL;

    object = airplay_skeleton_new();
    g_signal_connect(object, "handle-send-change-modes", G_CALLBACK(sendChangeModes), user_data);
    g_signal_connect(object, "handle-send-change-resource-mode", G_CALLBACK(sendChangeResourceMode), user_data);
    g_signal_connect(object, "handle-send-change-app-state", G_CALLBACK(sendChangeAppState), user_data);
    g_signal_connect(object, "handle-send-request-ui", G_CALLBACK(sendRequestUi), user_data);
    g_signal_connect(object, "handle-send-set-night-mode", G_CALLBACK(sendSetNightMode), user_data);
    g_signal_connect(object, "handle-send-request-siri-action", G_CALLBACK(sendRequestSiriAction), user_data);
    g_signal_connect(object, "handle-send-touch-screen-update", G_CALLBACK(sendTouchScreenUpdate), user_data);

    if (!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(object), connection, "/com/hsae/carplay", error)) {
        printf("exports airplay_name_acquired_handler at object_path on connection failed.\n");
    }
}

static void iap2_name_acquired_handler(GDBusConnection   *connection,
                                       const gchar       *name,
                                       gpointer          user_data)
{
    printf("iap2_name_acquired_handler!\n");

    Iap2    *object;
    GError  **error = NULL;

    object = iap2_skeleton_new();
    g_signal_connect(object, "handle-send-start-call-state-updates", G_CALLBACK(sendStartCallStateUpdates), user_data);

    if (!g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(object), connection, "/com/hsae/carplay", error)) {
        printf("exports iap2_name_acquired_handler at object_path on connection failed.\n");
    }
}

void CarPlayInterfaceInitialized() {
    guint       AirPlayOwnerId;
    guint       iAP2OwnerId;
    GMainLoop   *loop;

    AirPlayOwnerId = g_bus_own_name(G_BUS_TYPE_SESSION, "com.hsae.airplay", G_BUS_NAME_OWNER_FLAGS_NONE, NULL,
                                    airplay_name_acquired_handler, NULL, NULL, NULL);
    if (!AirPlayOwnerId)
        printf("owning AirPlay bus names failed.\n");

    iAP2OwnerId = g_bus_own_name(G_BUS_TYPE_SESSION, "com.hsae.iap2", G_BUS_NAME_OWNER_FLAGS_NONE, NULL,
                                 iap2_name_acquired_handler, NULL, NULL, NULL);
    if (!iAP2OwnerId)
        printf("owning iAP2 bus names failed.\n");

    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    g_bus_unown_name(AirPlayOwnerId);
    g_bus_unown_name(iAP2OwnerId);

    g_main_loop_unref(loop);
}