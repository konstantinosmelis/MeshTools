#pragma once
#ifndef MESHEDGECOLLAPSING_CHALFEDGEMESH_HPP
#define MESHEDGECOLLAPSING_CHALFEDGEMESH_HPP

// Includes
#include <vector>
#include <map>
#include <memory>
#include "CDPoint.hpp"

class CHalfEdgeMesh
{
public:
    // Forward declaration of structs
    struct SFace ;
    struct SHalfEdge ;
    struct SVertex ;

    struct SVertex
    {
        int mPointIndex ;
        SHalfEdge* mHalfEdge ;
    };

    struct SFace
    {
        SHalfEdge* mHalfEdge ;
    } ;

    struct SHalfEdge
    {
        SVertex* mDestVertex ;
        SHalfEdge* mNext ;
        SHalfEdge* mTwin ;
        SFace* mFace ;
    } ;

    /**
     * Constructor
     */
    CHalfEdgeMesh(const std::vector<CDPoint>& pVertices, const std::vector<std::vector<int>>& pFaces) ;

    /**
     * Destructor
     */
    virtual ~CHalfEdgeMesh() ;

    /**
     * Get the coordinates of the vertices
     * @return A vector of point coordinates
     */
    std::vector<CDPoint>& GetVertexCoordinates() ;

    /**
     * Get the vertices of the mesh
     * @return A vector of vertices
     */
    std::vector<std::unique_ptr<SVertex>>& GetVertices() ;

    /**
     * Get the faces of the mesh
     * @return A vector of faces
     */
    std::vector<std::unique_ptr<SFace>>& GetFaces() ;

    /**
     * Get the half-edges of the mesh
     * @return A vector of half edges
     */
    std::vector<std::unique_ptr<SHalfEdge>>& GetHalfEdges() ;

private:
    /**
     * Convert CDPoint into SVertex
     */
    void CreateVertices() ;

    /**
     * Create the face
     * @param pFace The triangular face
     */
    void AddFace(const std::vector<int>& pFace) ;

private:
    std::vector<CDPoint> mVertexCoordinates ;
    std::vector<std::unique_ptr<SVertex>> mVertices ; /**< The vertices of the mesh */
    std::vector<std::unique_ptr<SFace>> mFaces ; /**< The faces of the mesh */
    std::vector<std::unique_ptr<SHalfEdge>> mHalfEdges ; /**< The edges of the mesh */
};

#endif //MESHEDGECOLLAPSING_CHALFEDGEMESH_HPP
