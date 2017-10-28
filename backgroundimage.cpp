#include "backgroundimage.h"

BackgroundImage::BackgroundImage()
{
}

BackgroundImage::BackgroundImage(QImage&& image)
    :QImage(image)
{

}

BackgroundImage::~BackgroundImage()
{
}

BackgroundImage::box BackgroundImage::findSampleImage(const QImage &image, int threshold)
{
    for( int i = 0; i < this->height(); ++i)
        for( int j = 0; j < this->width(); ++j)
        {
            bool rslt = findSampleImage(image, j, i, threshold);
            if (rslt)
                return box(i, j, i + image.width(), j +image.height());
        }
    return box();
}



bool BackgroundImage::findSampleImage(const QImage & image, int row, int column, int threshold)
{
    for (int i = 0; i < image.height(); ++i)
    {
        for (int j = 0; j < image.width(); ++j)
        {
            QRgb imagePixelColor = image.pixel(j, i);
            QRgb backgroundColor = this->pixel(row + j, column + i);

            int rDelta = qAbs(qRed(imagePixelColor) - qRed(backgroundColor));
            int gDelta = qAbs(qGreen(imagePixelColor) - qGreen(backgroundColor));
            int bDelta = qAbs(qBlue(imagePixelColor) - qBlue(backgroundColor));

            if ((rDelta > threshold) || (gDelta > threshold) || (bDelta > threshold))
                return false;
        }
    }

    return true;
}
