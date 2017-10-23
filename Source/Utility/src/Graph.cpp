#include "../include/Graph.h"
#include <assert.h>
#include <algorithm>
#include <time.h>

namespace Graph
{
    std::istream& operator>>(std::istream& is, stEdge& rhs)
    {
        is>>rhs.from>>rhs.to>>rhs.cost; 
        return is;
    }

    std::istream& operator>>( std::istream& is, Sparse& g )
    {
        is>>g.mDigraph;
        int nValue = 0;
        is>>nValue;
        g.mNodes.resize(nValue);
        for (int i = 0; i < nValue; ++i)
        {
            is>>g.mNodes[i];
        }
        is>>nValue;
        g.mEdges.resize(nValue);
        for (int i = 0; i < nValue; ++i)
        {
            int nEdge = 0;
            is>>nEdge;
            g.mEdges[i].resize(nEdge);
            for (EdgeCon::iterator it = g.mEdges[i].begin(); it != g.mEdges[i].end(); ++it)
            {
                is>>(*it);
            }
        }
        return is;
    }
    std::ostream& operator<<(std::ostream& os, const stEdge& rhs)
    {
        os<<rhs.from<<" "<<rhs.to<<" "<<rhs.cost<<" "; 
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Sparse& g )
    {
        os<<g.mDigraph<<" "<<g.mNodes.size()<<" ";
        for (NodeCon::const_iterator it = g.mNodes.begin(); it != g.mNodes.end(); ++it)
        {
            os<<*it<<" ";
        }
        os<<g.mEdges.size()<<" ";
        for (EdgesCon::const_iterator it = g.mEdges.begin(); it != g.mEdges.end(); ++it)
        {
            os<<(*it).size()<<" ";
            for (EdgeCon::const_iterator itor = (*it).begin(); itor != (*it).end(); ++itor)
            {
                os<<(*itor)<<" ";
            }
        }
        return os;
    }

    Sparse::Sparse( int size, bool digraph ) : mDigraph(digraph) 
    {
        assign(size);
    }

    Sparse::~Sparse()
    {

    }

    void Sparse::addNode( const Node& node )
    {
        assert(node < (Node)mNodes.size() && "!!!! node must less than mNodes.size().");
        if (node >= (Node)mNodes.size())
        {
            return;
        }
        if (mNodes[node] == invalid_node)
        {
            mNodes[node] = node;
            mEdges[node] = EdgeCon();
        }
    }

    void Sparse::addEdge( const Edge& edge )
    {
        //must assure that base line is valid.
        if (edge.from == invalid_node || edge.to == invalid_node)
        {
            return;
        }
        mEdges[edge.from].push_back(edge);
        if (!mDigraph)
        {
            //unique check.????
            mEdges[edge.to].push_back(Edge(edge.to, edge.from, edge.cost));
        }
    }

    void Sparse::assign( int size )
    {
        mNodes.assign(size, invalid_node);
        mEdges.resize(size);
    }

    void Sparse::removeNode( const Node& node )
    {
        if (node >= getSize())
        {
            return;
        }

        mNodes[node] = invalid_node;
        cullInvalidEdge();
    }

    void Sparse::removeEdge( const Node& from, const Node& to )
    {
        if (from >= getSize() || to >= getSize())
        {
            return;
        }

        EdgeCon::iterator it = mEdges[from].begin();
        for (;it != mEdges[from].end();)
        {
            if ((*it).from == from && (*it).to == to)
            {
                it = mEdges[from].erase(it);
                break;
            }else
            {
                ++it;
            }
        }//end - for

        if (!mDigraph)
        {
            it = mEdges[to].begin();
            for (;it != mEdges[to].end(); )
            {
                if ((*it).from == to && (*it).to == from)
                {
                    it = mEdges[to].erase(it);
                    break;
                }else
                {
                    ++it;
                }
            }//end - for
        }//end - if

    }

    void Sparse::removeAllEdge()
    {
        for (EdgesCon::iterator it = mEdges.begin(); it != mEdges.end(); ++it)
        {
            (*it).clear();
        }
    }

    void Sparse::cullInvalidEdge()
    {
        for (EdgesCon::iterator it = mEdges.begin(); it != mEdges.end(); ++it)
        {
            for (EdgeCon::iterator itor = (*it).begin(); itor != (*it).end();)
            {
                if (mNodes[(*itor).from] == invalid_node || mNodes[(*itor).to] == invalid_node)
                {
                    itor = (*it).erase(itor);
                }else
                {
                    ++itor;
                }
            }
        }
    }

    bool Sparse::isEmpty()
    {
        return mNodes.empty();
    }

    void Sparse::clear()
    {
        mNodes.clear();
        mEdges.clear();
    }

	Graph::Node Sparse::randomNode() const
	{
		NodeCon temp;
		for (NodeCon::const_iterator it = mNodes.begin(); 
			it != mNodes.end(); ++it)
		{
			if (invalid_node != *it)
			{
				temp.push_back(*it);
			}
		}
		if (temp.empty())
		{
			return invalid_node;
		}
		int seed = temp.size();
		srand(time(NULL));
		int pos = rand()%seed;
		return temp[pos];
	}
}


namespace GSearch
{
    using namespace Graph;

    PathSearch::PathSearch( const Sparse& gra, Node src, Node des ): mGraph(gra), 
        mSource(src), mTarget(des), 
        mVisited(gra.getSize(), unvisited), 
        mRoute(gra.getSize(), no_parent_assign)
    {
    }

    PathSearch::~PathSearch()
    {
    }

    RouteCon PathSearch::getPath() const
    {
        RouteCon path;
        if (!mFind || mTarget < 0)
        {
            return path;
        }
        Node nd = mTarget;
        path.push_back(nd);
        while(nd != mSource)
        {
            nd = mRoute[nd];
            path.push_front(nd);
        }
        return path;
    }

    bool PathSearch::isFound() const
    {
        return mFind;
    }

    PathSearchShortest::PathSearchShortest( const Sparse& gra, 
        Node src, Node des ): PathSearch(gra, src, des), 
        mSPT(gra.getSize()), mFrontier(gra.getSize())
    {
    }

    PathSearchShortest::~PathSearchShortest()
    {
    }

    RouteCon PathSearchShortest::getPath() const
    {
        RouteCon path;

        if (mTarget < 0)  return path;

        Node nd = mTarget;

        path.push_back(nd);

        while ((nd != mSource) && (mSPT[nd] != 0))
        {
            nd = mSPT[nd]->from;

            path.push_front(nd);
        }

        return path;
    }

    PathSearchDijkstra::PathSearchDijkstra( const Sparse& gra, 
        Node src, Node des ): PathSearchShortest(gra, src, des), 
        mCostToThis(gra.getSize())
    {

    }

    PathSearchDijkstra::~PathSearchDijkstra()
    {

    }

    bool PathSearchDijkstra::search()
    {
        NodeCon pq;
        pq.push_back(mSource);
        while(!pq.empty())
        {
            Node nextClosetNode = pq[0];
            pq.erase(pq.begin());
            mSPT[nextClosetNode] = mFrontier[nextClosetNode];
            if (nextClosetNode == mTarget)
            {
                return true;
            }

            for (EdgeCon::const_iterator it = mGraph.mEdges[nextClosetNode].begin(); it != mGraph.mEdges[nextClosetNode].end(); ++it)
            {
                double nCost = mCostToThis[nextClosetNode] + (*it).cost;
                Node to = (*it).to;
                if (NULL == mFrontier[to])
                {
                    mCostToThis[to] = nCost;
                    pq.push_back(to);
                    mFrontier[to] = const_cast<Edge*>(&(*it));
                }else if (nCost < mCostToThis[to] && NULL == mSPT[to])
                {
                    mCostToThis[to] = nCost;
                    mFrontier[to] = const_cast<Edge*>(&(*it));
                }
            }//end - for

            std::sort(pq.begin(), pq.end(), PQSort(mCostToThis));
        }
        return false;
    }

    PathSearchAStar::PathSearchAStar( const Sparse& gra, 
        Node src, Node des ): PathSearchShortest(gra, src, des), 
        mGCost(gra.getSize()), mFCost(gra.getSize())
    {
    }

    PathSearchAStar::~PathSearchAStar()
    {
    }

    bool PathSearchAStar::search()
    {
		if (mSource < 0)
		{
			return false;
		}
        NodeCon pq;
        pq.push_back(mSource);
        while(!pq.empty())
        {
            Node nextClosetNode = pq[0];
            pq.erase(pq.begin());
            mSPT[nextClosetNode] = mFrontier[nextClosetNode];
            if (nextClosetNode == mTarget)
            {
                return true;
            }

            for (EdgeCon::const_iterator it = mGraph.mEdges[nextClosetNode].begin(); it != mGraph.mEdges[nextClosetNode].end(); ++it)
            {
                double hCost = 0;
                double gCost = mGCost[nextClosetNode] + (*it).cost;
                Node to = (*it).to;
                if (NULL == mFrontier[to])
                {
                    mFCost[to] = gCost + hCost;
                    mGCost[to] = gCost;
                    pq.push_back(to);
                    mFrontier[to] = const_cast<Edge*>(&(*it));
                }else if (gCost < mGCost[to] && NULL == mSPT[to])
                {
                    mFCost[to] = gCost + hCost;
                    mGCost[to] = gCost;
                    mFrontier[to] = const_cast<Edge*>(&(*it));
                }
            }//end - for

            std::sort(pq.begin(), pq.end(), PQSort(mFCost));
        }
        return false;
    }
}
