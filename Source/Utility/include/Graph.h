#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <iostream>
#include "UtilityExport.h"

/*
    @. This is maybe some unsafe. due to it is internal && easy for reading.
*/
namespace Graph
{
    enum
    {
        valid_node = 1,
        invalid_node = -1, 
    };

    typedef int Node;
    typedef struct stEdge 
    {
        Graph::Node from;
        Graph::Node to;
        double cost;
        stEdge() : from(0), to(0), cost(1.0){}
        stEdge(Graph::Node a, Graph::Node b) : from(a), to(b), cost(1.0) {}
        stEdge(Graph::Node a, Graph::Node b, double c) : from(a), to(b), cost(c) {}
    }Edge;

    std::istream& operator>>(std::istream& is, stEdge& rhs);
    std::ostream& operator<<(std::ostream& os, const stEdge& rhs);

    static const int DEFAULT_SIZE = 32;
    typedef std::vector<Graph::Node> NodeCon;
	typedef std::list<Graph::Node> RouteCon;
    typedef std::list<Edge> EdgeCon;
    typedef std::vector<EdgeCon> EdgesCon;

    class UTILITY_EXPORT Sparse
    {
    public:
        /*
            @. constructor. specific type of graph && max size
        */
        Sparse(int size = DEFAULT_SIZE, bool digraph = true);
        /*
            @. de-structure.
        */
        ~Sparse();
        /*
            @. be-careful : this action maybe curse data useless.
        */
        void assign(int size);
        /*
            @. addNode.
        */
        void addNode(const Graph::Node& node);
        /*
            @. addEdge.
        */
        void addEdge(const Edge& edge);
        /*
            @. removeNode.
        */
        void removeNode(const Graph::Node& node);
        /*
            @. removeEdge.
        */
        void removeEdge(const Graph::Node& from, const Graph::Node& to);
        /* 
            @. get size of node.
        */
        int getSize() const {return mNodes.size();}
        /*
            @. isEmpty.
        */
        bool isEmpty();
        /*
            @. clear.
        */
        void clear();
        /*
            @. remove all edge.
        */
        void removeAllEdge();
        /* 
            @. culling.
        */
        void cullInvalidEdge();
		/*
			@. gain a random valid node.
		*/
		Node randomNode() const;
    public:
        NodeCon mNodes;
        EdgesCon mEdges;
        bool mDigraph;
    };

    std::istream& operator>>(std::istream& is, Sparse& g);
    std::ostream& operator<<(std::ostream& os, const Sparse& g);
}

namespace GSearch
{
    using namespace Graph;
    enum{
        visited,
        unvisited, 
        no_parent_assign
    };

    class UTILITY_EXPORT PathSearch
    {
    public:
        PathSearch(const Sparse& gra, Graph::Node src, Graph::Node des);
        virtual ~PathSearch();
        virtual bool search() = 0;
        virtual RouteCon getPath() const ;
        bool isFound() const ;
    protected:
        const Sparse& mGraph;
        bool mFind;
        Graph::Node mSource;
        Graph::Node mTarget;
        NodeCon mVisited;
        NodeCon mRoute;
    };

    class UTILITY_EXPORT PathSearchShortest : public PathSearch
    {
    public:
        class PQSort
        {
        public:
            PQSort(const std::vector<double>& data) : mData(data) {}
            bool operator()(int a, int b) const 
            {
                return mData[a] < mData[b];
            }
        protected:
            const std::vector<double>& mData;
        };
    public:
        PathSearchShortest(const Sparse& gra, Graph::Node src, Graph::Node des);
        virtual bool search() = 0;
        virtual RouteCon getPath() const ;
        virtual ~PathSearchShortest();
    protected:
        std::vector<Edge*> mSPT;
        std::vector<Edge*> mFrontier;
    };

    class UTILITY_EXPORT PathSearchDijkstra : public PathSearchShortest
    {
    public:
        PathSearchDijkstra(const Sparse& gra, Graph::Node src, Graph::Node des);
        bool search();
        ~PathSearchDijkstra();
    protected:
        std::vector<double> mCostToThis;
    };

    class UTILITY_EXPORT PathSearchAStar : public PathSearchShortest
    {
    public:
        PathSearchAStar(const Sparse& gra, Graph::Node src, Graph::Node des);
        bool search();
        ~PathSearchAStar();
    protected:
        std::vector<double> mGCost;
        std::vector<double> mFCost;
    };
}
#endif
