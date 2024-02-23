#include <QWindow>
#include <QGuiApplication>
#include <qt_windows.h>
#include "desktopwindow.h"

namespace h {
DesktopWindow::DesktopWindow()
    : QWidget{nullptr}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setStyleSheet("winDesk--DesktopWindow {background: transparent;}");

    // qDebug() << "必须获取winID()才能使widget变成native window，官方文档里说的几种方法不太好用" << wid;
    WId wid = winId();
    qDebug() << "wid:" << wid;

    // Message to `Progman` to spawn a `WorkerW`
    int WM_SPAWN_WORKER = 0x052C;
    // find `Progman`
    HWND hProgman= FindWindow(L"Progman", nullptr);
    // instruct program to create a `WorkerW` between wallpaper and icons
    SendMessageTimeout(
        hProgman,
        WM_SPAWN_WORKER,
        NULL,
        NULL,
        SMTO_NORMAL,
        1000,
        NULL);
    // find the newly created `WorkerW`
    static HWND hWorkerW = nullptr;
    EnumWindows([](HWND topHandle, LPARAM topParamHandle) {
        HWND shellDllDefView = FindWindowEx(topHandle, nullptr, L"SHELLDLL_DefView", nullptr);
        if (shellDllDefView != nullptr) {
            hWorkerW = topHandle; //FindWindowEx(nullptr, topHandle, "WorkerW", nullptr);
        }
        return TRUE;
    }, NULL);
    // windows在多显示器的情况行，这将是一个直接包括所有显示器大小的窗口
    HWND deskHWnd = hWorkerW;
    QWindow* deskTopNativeWindow = QWindow::fromWinId(reinterpret_cast<WId>(deskHWnd));//以指定HWND创建窗口的静态函数
    QWindow *whnd = windowHandle();
    whnd->setParent(deskTopNativeWindow);

    m_screenOffset = QPoint(0, 0) - deskTopNativeWindow->mapToGlobal(QPoint(0, 0));

    // 更新位置，覆盖所有的显示器
    whnd->setGeometry(deskTopNativeWindow->geometry());
    whnd->setPosition(QPoint(0, 0));
    resize(whnd->size());

    QObject::connect(qApp, &QGuiApplication::screenAdded, this, &DesktopWindow::onScreenAdded);
    QObject::connect(qApp, &QGuiApplication::screenRemoved, this, &DesktopWindow::onScreenRemoved);
    QObject::connect(qApp, &QGuiApplication::primaryScreenChanged, this, &DesktopWindow::onPrimaryScreenChanged);

}


void DesktopWindow::onScreenAdded(QScreen *screen){

}
void DesktopWindow::onScreenRemoved(QScreen *screen){

}
void DesktopWindow::onPrimaryScreenChanged(QScreen *screen){

}
void DesktopWindow::onGeometryChanged(const QRect &geometry){

}
void DesktopWindow::onAvailableGeometryChanged(const QRect &geometry){

}
void DesktopWindow::onPhysicalSizeChanged(const QSizeF &size){

}
void DesktopWindow::onPhysicalDotsPerInchChanged(qreal dpi){

}
void DesktopWindow::onLogicalDotsPerInchChanged(qreal dpi){

}
void DesktopWindow::onVirtualGeometryChanged(const QRect &rect){

}
void DesktopWindow::onPrimaryOrientationChanged(Qt::ScreenOrientation orientation){

}
void DesktopWindow::onOrientationChanged(Qt::ScreenOrientation orientation){

}
void DesktopWindow::onRefreshRateChanged(qreal refreshRate){

}

}
