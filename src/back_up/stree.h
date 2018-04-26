#ifndef STREE_H
#define STREE_H
#include <memory>
#include "bgeometry.h"
#include <vector>

namespace bgeo {

class STreeVert
{
public:
    STreeVert() {}

    std::vector<DPoint> vPoint;
    int level;
    double dis = 0;
    bool leaf = false;
};
class STreeEdge
{
public:
    STreeEdge() {}
};

//boost::adjacency_list<>
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, STreeVert,STreeEdge > STree;

// 节点描述符
typedef boost::graph_traits<STree>::vertex_descriptor   STreeVertexDescriptor;
// 边描述符
typedef boost::graph_traits<STree>::edge_descriptor     STreeEdgeDescriptor;

// 下面是邻接链表的一些遍历器
typedef boost::graph_traits<STree>::vertex_iterator     STreeVertexIterator;
typedef boost::graph_traits<STree>::edge_iterator      STreeEdgeIterator;
typedef boost::graph_traits<STree>::adjacency_iterator  STreeAdjacencyIterator;
typedef boost::graph_traits<STree>::out_edge_iterator   STreeOutEdgeIterator;




}
#endif // STREE_H
