#include "sys.h"

sys::sys()
{


}


void sys::power_off()
{
    QMessageBox re(QMessageBox::Question,"关机","确定要关闭计算机吗？",QMessageBox::Yes|QMessageBox::No);

    if(re.exec() == QMessageBox::Yes)
    {
        QProcess *shutdown = new QProcess();
        shutdown->start("C:/WINDOWS/system32/shutdown.exe -s -t 0");
    }
}

void sys::call_keyboard()
{
    PVOID OldValue;
    BOOL bRet = Wow64DisableWow64FsRedirection (&OldValue);
//    QString csProcess="C:\\Windows\\System32\\osk.exe";
    QString csProcess="C:\\Program Files\\Common Files\\microsoft shared\\ink\\TabTip.exe";
    QString params="";
    ShellExecute(NULL, L"open", (LPCWSTR)csProcess.utf16(), (LPCWSTR)params.utf16(), NULL, SW_SHOWNORMAL);
    if ( bRet )
    {
        Wow64RevertWow64FsRedirection(OldValue);
    }
}

void sys::save()
{}

void sys::load()
{}

void sys::apply()
{}
