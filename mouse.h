#ifndef MOUSE_H
#define MOUSE_H

#include <QCursor>
#include <QPoint>
#include <QThread>
#include <QWidget>

#include <windows.h>

// Mouse emulation

class Mouse : public QWidget
{
    Q_OBJECT

public:
    explicit Mouse(QWidget* parent = 0);
    ~Mouse();

    // Left click at a given position (with or without delays)
    void leftClickOnPointTimed(const QPoint& point, const uint msBeforeBetweenAfter[3]);
    void leftClickOnPoint(const QPoint& point);

    // Left click (with or without delays)
    void leftClickTimed(const uint msBeforeBetweenAfter[3]);
    void leftClick();

private:
    void leftClickPress();
    void leftClickRelease();

    INPUT mInput;

    const int mSizeOfInput;
};

#endif // MOUSE_H
