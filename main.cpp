#include "Headers/CMeshIO.hpp"
#include "Headers/CDPoint.hpp"
#include "Headers/CHalfEdgeMesh.hpp"
#include "Headers/CMeshSmoothing.hpp"

int main()
{
    std::vector<CDPoint> lVertices = {} ;
    std::vector<std::vector<int>> lFaces = {} ;

    CMeshIO::ReadMesh("/home/dinos/Development/C-C++/MeshEdgeCollapsing/pcd.xyz",
                      "/home/dinos/Development/C-C++/MeshEdgeCollapsing/faces.xyz",
                      lVertices,
                      lFaces) ;

    CHalfEdgeMesh lMesh(lVertices, lFaces) ;

    CMeshSmoothing::TaubinSmoothing(lMesh, 8, .7, -.5) ;

    CMeshIO::WriteMesh("/home/dinos/Development/C-C++/MeshEdgeCollapsing/pcd_1.xyz",
                       "/home/dinos/Development/C-C++/MeshEdgeCollapsing/faces_1.xyz",
                       lVertices,
                       lFaces) ;

    return 0;
}
