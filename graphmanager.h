#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <vector>
#include <memory>

#include <QString>
#include <QImage>

class GraphManager
{
public:
    struct Elt
    {
        QString _name;
        QImage _pattern;
        std::vector<Elt*> _inputElts;
        std::vector<Elt*> _outputElts;
    };

    GraphManager();
    ~GraphManager();

    void addElts(Elt* elt);
    void addElts(const QString& name, const QImage& image);
    void addElts(const QString& name, const QString& imagePath);

    bool removeElts(int idx);

    Elt* getElt(int idx)const;
    Elt* getElt(const QString& name)const;

    std::vector<Elt*> getInputElts(const Elt* elt);
    std::vector<Elt*> getOutputElts(const Elt* elt);

    bool connectTo(int idxSrc, int idxDest);
    bool connectTo(Elt* const eltSrc, Elt* const eltDest);

    bool link(int idxSrc, int idxDest);
    bool link(Elt* const eltSrc, Elt* const eltDest);

    bool disconnectFrom(int idxSrc, int idxDest);
    bool disconnectFrom(Elt* const eltSrc, Elt* const eltDest);

    inline void setCurrentElt(const Elt* elt);
    inline const Elt* getCurrentElt() const;

    bool moveTo(const Elt* elt);
    bool backTo(const Elt* elt);

private:

    std::vector<Elt*> _graphElts;
    const Elt* _currentElt;
};

void GraphManager::setCurrentElt(const GraphManager::Elt* elt) {_currentElt = elt;}
const GraphManager::Elt* GraphManager::getCurrentElt() const{ return _currentElt;}

#endif // GRAPHMANAGER_H
