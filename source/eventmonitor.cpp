#include <QDebug>
#include "eventmonitor.h"
#include <X11/Xlibint.h>


void EventMonitor::run()
{
    qWarning() << "EventMonitor run";
    Display * display = nullptr;
    Display * display_datalink = nullptr;
    XRecordContext context;
    XRecordRange * range = nullptr;


    display = XOpenDisplay( nullptr );
    XRecordClientSpec clients = XRecordAllClients;
    range = XRecordAllocRange();
    if( !range ) {
        qWarning() << "range";
        return;
    }
    memset( range, 0, sizeof( XRecordRange ) );
    range->device_events.first = ButtonPress;
    range->device_events.last  = ButtonRelease;

    context = XRecordCreateContext( display, 0, &clients, 1, &range, 1 );
    if( !context ) {
        qWarning() << "XRecordCreateContext！";
        return;
    }
    XSync( display, true );

    display_datalink = XOpenDisplay( nullptr );
    if( !display_datalink) {
        qWarning() << "display_datalink";
        return;
    }
    XSync( display_datalink, true );
    if( !XRecordEnableContext( display, context, eventCB, nullptr ) )
        qWarning() << "XRecordEnableContext";
        return;
}

void EventMonitor::eventCB(XPointer ptr, XRecordInterceptData* data)
{
        handleRecordEvent(data, getInstance());
}

void EventMonitor::handleRecordEvent(XRecordInterceptData* data, EventMonitor &pEM)
{
        if (data->category == XRecordFromServer) {
            xEvent * event = (xEvent *)data->data;
            switch (event->u.u.type) {
                case ButtonPress:
                    if (filterWheelEvent(event->u.u.detail)) {

                        emit pEM.buttonPress(event->u.keyButtonPointer.rootX,
                                             event->u.keyButtonPointer.rootY);
                    }
                    break;
                case MotionNotify:
                    qDebug() << "MotionNotify";
                    break;
                case ButtonRelease:
                    if (filterWheelEvent(event->u.u.detail)) {

                        emit pEM.buttonRelease(event->u.keyButtonPointer.rootX,
                                             event->u.keyButtonPointer.rootY);
                    }
                    break;
                case KeyPress:
                    qDebug() << "KeyPress";
                    break;
                case KeyRelease:

                    break;
                default:
                    break;
            }
        }

        fflush(stdout);
        XRecordFreeData(data);
}

bool EventMonitor::filterWheelEvent(int detail)
{
        return detail != WheelUp && detail != WheelDown && detail != WheelLeft && detail != WheelRight;
}
