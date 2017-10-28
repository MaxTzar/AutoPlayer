#include "keyboardcapture.h"

KeyboardCapture* KeyboardCapture::m_keyboardCapture = NULL;

KeyboardCapture::KeyboardCapture() :
    QObject(),
    m_hookProcedureHandle(NULL)
{
}

KeyboardCapture::~KeyboardCapture()
{
}

KeyboardCapture* KeyboardCapture::instance()
{
    if (!m_keyboardCapture)
        m_keyboardCapture = new KeyboardCapture();

    return m_keyboardCapture;
}

void KeyboardCapture::kill()
{
    if (m_keyboardCapture)
        m_keyboardCapture->deleteLater();
}

LRESULT CALLBACK KeyboardCapture::hookProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
    // check if wParam and lParam parameters contain information about a keyboard message
    if (nCode == HC_ACTION)
    {
        KBDLLHOOKSTRUCT* keyboardHook = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        switch (wParam)
        {
        case WM_KEYDOWN:
            emit KeyboardCapture::instance()->keyPressed((uint) keyboardHook->vkCode);
            break;
        case WM_KEYUP:
            emit KeyboardCapture::instance()->keyReleased((uint) keyboardHook->vkCode);
            break;
        default:
            break;
        }
    }

    // return the value returned by CallNextHookEx so that
    // other applications that have installed WH_KEYBOARD_LL receive hook notifications.
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

bool KeyboardCapture::installHookProcedure(bool install)
{
    if (install)
    {
        // installs a hook procedure that monitors low-level keyboard input events
        if (m_hookProcedureHandle == NULL)
            m_hookProcedureHandle = SetWindowsHookEx(WH_KEYBOARD_LL, hookProcedure, GetModuleHandle(NULL), 0);
        return (m_hookProcedureHandle != NULL);
    }
    else
    {
        bool unhookSuccess = UnhookWindowsHookEx(m_hookProcedureHandle);
        m_hookProcedureHandle = NULL;
        return unhookSuccess;
    }
}
