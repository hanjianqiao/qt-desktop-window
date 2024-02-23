#ifndef DESKTOPWINDOW_H
#define DESKTOPWINDOW_H

#include <QWidget>

namespace h {
class DesktopWindow : public QWidget
{
    Q_OBJECT
public:
    static void initialize();
    static DesktopWindow *singleton();

private:
    DesktopWindow();
    ~DesktopWindow();

signals:

private slots:
    void onScreenAdded(QScreen *screen);
    void onScreenRemoved(QScreen *screen);
    void onPrimaryScreenChanged(QScreen *screen);
    void onGeometryChanged(const QRect &geometry);
    void onAvailableGeometryChanged(const QRect &geometry);
    void onPhysicalSizeChanged(const QSizeF &size);
    void onPhysicalDotsPerInchChanged(qreal dpi);
    void onLogicalDotsPerInchChanged(qreal dpi);
    void onVirtualGeometryChanged(const QRect &rect);
    void onPrimaryOrientationChanged(Qt::ScreenOrientation orientation);
    void onOrientationChanged(Qt::ScreenOrientation orientation);
    void onRefreshRateChanged(qreal refreshRate);

private:
    static DesktopWindow *s_instance;

    QPoint m_screenOffset;
};

}

#endif // DESKTOPWINDOW_H
