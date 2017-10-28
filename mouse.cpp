#include "mouse.h"

Mouse::Mouse(QWidget* parent)
    : QWidget(parent)
    , mSizeOfInput(sizeof(INPUT))
{
}

Mouse::~Mouse()
{
}

void Mouse::leftClickOnPointTimed(const QPoint& point, const uint msBeforeBetweenAfter[3])
{
    QCursor::setPos(point);
    leftClickTimed(msBeforeBetweenAfter);
}

void Mouse::leftClickOnPoint(const QPoint& point)
{
    QCursor::setPos(point);
    leftClick();
}

void Mouse::leftClickTimed(const uint msBeforeBetweenAfter[3])
{
    QThread::msleep(msBeforeBetweenAfter[0]);
    leftClickPress();
    QThread::msleep(msBeforeBetweenAfter[1]);
    leftClickRelease();
    QThread::msleep(msBeforeBetweenAfter[2]);
}

void Mouse::leftClick()
{
    leftClickPress();
    leftClickRelease();
}

void Mouse::leftClickPress()
{
    ZeroMemory(&mInput, mSizeOfInput);
    mInput.type = INPUT_MOUSE;
    mInput.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &mInput, mSizeOfInput);
}

void Mouse::leftClickRelease()
{
    ZeroMemory(&mInput, mSizeOfInput);
    mInput.type = INPUT_MOUSE;
    mInput.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &mInput, mSizeOfInput);
}
