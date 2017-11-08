#include "graphmanager.h"

GraphManager::GraphManager()
{

}

GraphManager::~GraphManager()
{
    _currentElt = nullptr;
    for(auto elt : _graphElts)
    {
        delete elt;
        elt = nullptr;
    }
    _graphElts.clear();
}

void GraphManager::addElts(GraphManager::Elt *elt)
{
    if (_graphElts.size() == 0)
        _currentElt = elt;
    _graphElts.push_back(elt);
}

void GraphManager::addElts(const QString &name, const QImage& image)
{
    Elt* elt = new Elt();
    elt->_name = name;
    elt->_pattern = image;
    addElts(elt);
}

void GraphManager::addElts(const QString &name, const QString &imagePath)
{
    addElts(name, QImage(imagePath));
}

bool GraphManager::removeElts(int idx)
{
    if (idx < 0 || idx > _graphElts.size() - 1)
        return false;

    _graphElts.erase(_graphElts.begin() + idx);
    return true;
}

GraphManager::Elt *GraphManager::getElt(int idx) const
{
    return _graphElts[idx];
}

GraphManager::Elt *GraphManager::getElt(const QString &name) const
{
    for (int i = 0; i < _graphElts.size(); ++i)
        if (_graphElts[i]->_name == name)
            return getElt(i);
}

std::vector<GraphManager::Elt *> GraphManager::getInputElts(const GraphManager::Elt *elt)
{
    return elt->_inputElts;
}

std::vector<GraphManager::Elt *> GraphManager::getOutputElts(const GraphManager::Elt *elt)
{
    return elt->_outputElts;
}

bool GraphManager::connectTo(int idxSrc, int idxDest)
{
    _graphElts[idxSrc]->_outputElts.push_back(_graphElts[idxDest]);
    _graphElts[idxDest]->_inputElts.push_back(_graphElts[idxSrc]);
}

bool GraphManager::connectTo(GraphManager::Elt * const eltSrc, GraphManager::Elt * const eltDest)
{
    eltSrc->_outputElts.push_back(eltDest);
    eltDest->_inputElts.push_back(eltSrc);
}

bool GraphManager::link(int idxSrc, int idxDest)
{
    link(_graphElts[idxSrc], _graphElts[idxDest]);
}

bool GraphManager::link(GraphManager::Elt * const eltSrc, GraphManager::Elt * const eltDest)
{
    eltSrc->_outputElts.push_back(eltDest);
    eltSrc->_inputElts.push_back(eltDest);
    eltDest->_outputElts.push_back(eltSrc);
    eltDest->_inputElts.push_back(eltSrc);
}

bool GraphManager::disconnectFrom(int idxSrc, int idxDest)
{
    disconnectFrom(_graphElts[idxSrc], _graphElts[idxDest]);
}

bool GraphManager::disconnectFrom(GraphManager::Elt * const eltSrc, GraphManager::Elt * const eltDest)
{
    for (auto elt = eltSrc->_outputElts.begin(); elt == eltSrc->_outputElts.end(); ++elt)
        if (*elt == eltDest)
            eltSrc->_outputElts.erase(elt);

    for (auto elt = eltDest->_inputElts.begin(); elt == eltDest->_inputElts.end(); ++elt)
        if (*elt == eltSrc)
            eltDest->_inputElts.erase(elt);
}


bool GraphManager::moveTo(const GraphManager::Elt *elt)
{
    for (auto eltIt : _currentElt->_outputElts)
    {
        if(eltIt == elt)
        {
            setCurrentElt(elt);
            return true;
        }
    }
    return false;
}

bool GraphManager::backTo(const GraphManager::Elt *elt)
{
    for (auto eltIt : _currentElt->_inputElts)
    {
        if(eltIt == elt)
        {
            setCurrentElt(elt);
            return true;
        }
    }
    return false;
}
