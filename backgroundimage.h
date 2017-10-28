#ifndef BACKGROUNDIMAGE_H
#define BACKGROUNDIMAGE_H

#include <QWidget>

class BackgroundImage : public QImage
{
public:
    struct box
    {
        box(int xmin = -1,int ymin = -1,int xmax = -1, int ymax = -1)
            : _xmin(xmin)
            , _ymin(ymin)
            , _xmax(xmax)
            , _ymax(ymax)
        {}

        bool isValid()
        {
            return (_xmin != -1 && _ymin != -1 && _xmax != -1 && _ymax != -1);
        }

        int _xmin;
        int _ymin;
        int _xmax;
        int _ymax;
    };

    explicit BackgroundImage();
    BackgroundImage(QImage &&image);
    ~BackgroundImage();

    box findSampleImage(const QImage & image, int threshold = 0);

    /* returns true if the sample image is at the position (i, j) in the background image */
    bool findSampleImage(const QImage & image, int row, int column, int pThreshold = 0);

signals:

public slots:
    
};

#endif // BACKGROUNDIMAGE_H
