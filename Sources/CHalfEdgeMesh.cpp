#include "../Headers/CHalfEdgeMesh.hpp"

CHalfEdgeMesh::CHalfEdgeMesh(const std::vector<CDPoint>&            pVertices,
                             const std::vector<std::vector<int>>&   pFaces)
    : mVertexCoordinates(pVertices)
{
    CreateVertices() ;

    for (const std::vector<int>& lFace : pFaces)
    {
        AddFace(lFace) ;
    }
}

CHalfEdgeMesh::~CHalfEdgeMesh()
{
    mFaces.clear() ;
    mVertices.clear() ;
    mVertexCoordinates.clear() ;
    mHalfEdges.clear() ;
}

std::vector<CDPoint>& CHalfEdgeMesh::GetVertexCoordinates()
{
    return mVertexCoordinates ;
}

std::vector<std::unique_ptr<CHalfEdgeMesh::SVertex>>& CHalfEdgeMesh::GetVertices()
{
    return mVertices ;
}

std::vector<std::unique_ptr<CHalfEdgeMesh::SFace>>& CHalfEdgeMesh::GetFaces()
{
    return mFaces ;
}

std::vector<std::unique_ptr<CHalfEdgeMesh::SHalfEdge>>& CHalfEdgeMesh::GetHalfEdges()
{
    return mHalfEdges ;
}

void CHalfEdgeMesh::CreateVertices()
{
    // Loop through vertices
    for (int lVertexIndex = 0; lVertexIndex < mVertexCoordinates.size(); lVertexIndex++)
    {
        // Create pointer and store it
        std::unique_ptr<SVertex> lVertex = std::make_unique<SVertex>() ;
        lVertex->mPointIndex = lVertexIndex ;
        mVertices.push_back(std::move(lVertex)) ;
    }
}

void CHalfEdgeMesh::AddFace(const std::vector<int>& pFace)
{
    // Create pointer to the face
    std::unique_ptr<SFace> lFace = std::make_unique<SFace>() ;

    // Create 3 half-edges
    SHalfEdge* lHalfEdge1 = new SHalfEdge() ;
    SHalfEdge* lHalfEdge2 = new SHalfEdge() ;
    SHalfEdge* lHalfEdge3 = new SHalfEdge() ;

    lHalfEdge1->mDestVertex = mVertices[pFace[1]].get() ;
    lHalfEdge2->mDestVertex = mVertices[pFace[2]].get() ;
    lHalfEdge3->mDestVertex = mVertices[pFace[0]].get() ;

    lHalfEdge1->mNext = lHalfEdge2 ;
    lHalfEdge2->mNext = lHalfEdge3 ;
    lHalfEdge3->mNext = lHalfEdge1 ;

    lHalfEdge1->mFace = lFace.get() ;
    lHalfEdge2->mFace = lFace.get() ;
    lHalfEdge3->mFace = lFace.get() ;

    // Connect vertices of the face the half-edges
    mVertices[pFace[0]]->mHalfEdge = lHalfEdge1 ;
    mVertices[pFace[1]]->mHalfEdge = lHalfEdge2 ;
    mVertices[pFace[2]]->mHalfEdge = lHalfEdge3 ;

    // Connect edge to face
    lFace->mHalfEdge = lHalfEdge1 ;

    // Store the half edges
    mHalfEdges.emplace_back(lHalfEdge1) ;
    mHalfEdges.emplace_back(lHalfEdge2) ;
    mHalfEdges.emplace_back(lHalfEdge3) ;

    // Store the face
    mFaces.emplace_back(std::move(lFace)) ;
}
