#ifndef KEYBOARDCAPTURE_H
#define KEYBOARDCAPTURE_H

#include <QObject>
#include <Windows.h>

// keyboard capture singleton
class KeyboardCapture : public QObject
{
    Q_OBJECT

public:
    static KeyboardCapture* instance();
    static void kill();

    // connect or disconnect the hook procedure, return true if successful
    bool installHookProcedure(bool connected);

signals:
    void keyPressed(uint key);
    void keyReleased(uint key);

private:
    KeyboardCapture();
    ~KeyboardCapture();
    static KeyboardCapture* m_keyboardCapture;

    HHOOK m_hookProcedureHandle;
    static LRESULT CALLBACK hookProcedure(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYBOARDCAPTURE_H
