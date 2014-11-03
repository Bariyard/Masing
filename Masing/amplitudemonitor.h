#ifndef AMPLITUDEMONITOR_H
#define AMPLITUDEMONITOR_H

#include <QWidget>

class AmplitudeMonitor : public QWidget
{
    Q_OBJECT

public:
    AmplitudeMonitor(QWidget *parent = 0);
    ~AmplitudeMonitor();

    void setAmpLevel(float *data,int size);
    inline float getAmp(){return m_amplevel;}

private:
    void paintEvent(QPaintEvent *event);

private:
    float m_amplevel;
    float *in_data;
};

#endif // AMPLITUDEMONITOR_H
