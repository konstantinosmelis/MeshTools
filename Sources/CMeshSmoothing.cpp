#include "../Headers/CMeshSmoothing.hpp"
#include "../Headers/CHalfEdgeMesh.hpp"

CMeshSmoothing::CMeshSmoothing(CHalfEdgeMesh& pMesh)
    : mMesh(pMesh)
    , mDisplacements(std::vector<CDPoint>(pMesh.GetVertices().size()))
{}

CMeshSmoothing::~CMeshSmoothing()
{}

void CMeshSmoothing::TaubinSmoothing(CHalfEdgeMesh& pMesh,
                                     int pIterations,
                                     float pMu,
                                     float pLambda)
{
    for (int lIteration = 0; lIteration < pIterations; lIteration++)
    {
        CMeshSmoothing::GaussianSmoothing(pMesh, pMu) ;
        CMeshSmoothing::GaussianSmoothing(pMesh, pLambda) ;
    }
}

void CMeshSmoothing::GaussianSmoothing(CHalfEdgeMesh& pMesh, float pScaleFactor)
{
    CMeshSmoothing lInstance(pMesh) ;
    lInstance.ComputeDisplacements() ;
    lInstance.ApplySmoothing(pScaleFactor) ;
}

void CMeshSmoothing::ComputeDisplacements()
{
    for (int lVertexIndex = 0; lVertexIndex < mMesh.GetVertices().size(); lVertexIndex++)
    {
        mDisplacements[lVertexIndex] = ComputeVertexDisplacement(lVertexIndex) ;
    }
}

CDPoint CMeshSmoothing::ComputeVertexDisplacement(int pVertexIndex)
{
    // Init the result
    CDPoint lResult(0.0) ;
    int lCount = 0 ;

    // Ge the vertex and it's outgoing half-edge
    CHalfEdgeMesh::SVertex* lVertex = mMesh.GetVertices()[pVertexIndex].get() ;
    CHalfEdgeMesh::SHalfEdge* lStartEdge = lVertex->mHalfEdge ;
    CHalfEdgeMesh::SHalfEdge* lCurrentEdge = lStartEdge ;

    // Loop while the current edge is different from the origin edge
    do
    {
        lResult += mMesh.GetVertexCoordinates()[lCurrentEdge->mDestVertex->mPointIndex] - mMesh.GetVertexCoordinates()[pVertexIndex] ;
        lCurrentEdge = lCurrentEdge->mTwin->mNext ;
        lCount++ ;
    }
    while (lCurrentEdge != lStartEdge) ;

    // Return mean coordinate
    return lResult / lCount ;
}

void CMeshSmoothing::ApplySmoothing(float pScaleFactor)
{
    for (int lVertexIndex = 0; lVertexIndex < mMesh.GetVertices().size(); lVertexIndex++)
    {
        mMesh.GetVertexCoordinates()[lVertexIndex] += mDisplacements[lVertexIndex] * pScaleFactor ;
    }
}
