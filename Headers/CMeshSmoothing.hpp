#ifndef MESHEDGECOLLAPSING_CMESHSMOOTHING_HPP
#define MESHEDGECOLLAPSING_CMESHSMOOTHING_HPP

// Includes
#include <vector>

// Forward declaration
class CHalfEdgeMesh ;
class CDPoint ;

class CMeshSmoothing
{
public:
    CMeshSmoothing(CHalfEdgeMesh& pMesh) ;

    virtual ~CMeshSmoothing() ;

    static void TaubinSmoothing(CHalfEdgeMesh& pMesh, int pIterations, float pMu, float pLambda) ;

    static void GaussianSmoothing(CHalfEdgeMesh& pMesh, float pScaleFactor) ;

    void ComputeDisplacements() ;

    CDPoint ComputeVertexDisplacement(int pVertexIndex) ;

    void ApplySmoothing(float pScaleFactor) ;

private:
    CHalfEdgeMesh& mMesh ;
    std::vector<CDPoint> mDisplacements ;
};

#endif //MESHEDGECOLLAPSING_CMESHSMOOTHING_HPP
