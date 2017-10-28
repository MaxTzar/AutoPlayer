#include "screenshot.h"

Screenshot::Screenshot():
    m_screen(QGuiApplication::primaryScreen())
{
}

QImage Screenshot::takeScreenshot()
{
    return m_screen->grabWindow(QApplication::desktop()->winId()).toImage();
}
