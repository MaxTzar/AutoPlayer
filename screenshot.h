#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QApplication>
#include <QGuiApplication>
#include <QImage>
#include <QPixmap>
#include <QScreen>
#include <QtWidgets/QDesktopWidget>

class Screenshot
{
public:
    Screenshot();
    QImage takeScreenshot();

private:
    QScreen* m_screen;
};

#endif // SCREENSHOT_H
