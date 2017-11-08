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
    int i = 0;
    int j = 0;
    for(  i = 0; i < this->height() - image.height(); ++i)
        for(  j = 0; j < this->width() - image.width(); ++j)
        {
            bool rslt = findSampleImage(image, j, i, threshold);
            if (rslt)
                return box(i, j, i + image.height(), j +image.width());
        }
    return box();
}



bool BackgroundImage::findSampleImage(const QImage & image, int row, int column, int threshold)
{
    float error = 0.1;
    int ctR = 0;
    int ctF = 0;
    for (int i = 0; i < image.height(); i += 2)
    {
        for (int j = 0; j < image.width() - i; j += 2)
        {
            QRgb imagePixelColor = image.pixel(j, i);
            QRgb backgroundColor = this->pixel(row + j, column + i);

            int rDelta = qAbs(qRed(imagePixelColor) - qRed(backgroundColor));
            int gDelta = qAbs(qGreen(imagePixelColor) - qGreen(backgroundColor));
            int bDelta = qAbs(qBlue(imagePixelColor) - qBlue(backgroundColor));

            if ((rDelta > threshold) || (gDelta > threshold) || (bDelta > threshold))
                ++ctF;
            else
                ++ctR;
            if(ctR == 0)
                return false;
            float errorComp = (float(ctF)/float(ctR));
            if ( errorComp > error)
                return false;
        }
    }

    return true;
}
