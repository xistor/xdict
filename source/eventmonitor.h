#ifndef EVENTMONITOR_H
#define EVENTMONITOR_H

#include <QThread>

#include <X11/Xlib.h>
#include <X11/extensions/record.h>

#define Button1			1
#define Button2			2
#define Button3			3
#define WheelUp			4
#define WheelDown		5
#define WheelLeft		6
#define WheelRight		7
#define XButton1		8
#define XButton2		9


class EventMonitor : public QThread
{
    Q_OBJECT

typedef void(*eventCallback)(XPointer ptr, XRecordInterceptData* data);

public:

static EventMonitor& getInstance(){
        static EventMonitor instance;
        return instance;
    }

signals:
    void buttonPress(int x, int y);
    void buttonRelease(int x, int y);

protected:
    void run() override;
    static void eventCB(XPointer ptr, XRecordInterceptData* data);
    static void handleRecordEvent(XRecordInterceptData *, EventMonitor &eventMonitor);
    static bool filterWheelEvent(int detail);

private:


};

#endif // EVENTMONITOR_H
