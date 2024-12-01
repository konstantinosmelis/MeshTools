#pragma once
#ifndef MESHEDGECOLLAPSING_CMESHIO_HPP
#define MESHEDGECOLLAPSING_CMESHIO_HPP

// Includes
#include <string>
#include <vector>
#include <fstream>

#include "CDPoint.hpp"

/**
 * @class CMeshIO
 * Mesh reading toolbox
 */
class CMeshIO
{
public:
    /**
     * Read a point cloud
     * @param[in]  pPath   The path of the pcd in ascii format
     * @param[out] pPoints The output point vector
     * @param[out] pFaces  The output face vector
     */
    static void ReadMesh(const std::string& pVertexPath, const std::string& pFacePath, std::vector<CDPoint>& pVertices, std::vector<std::vector<int>>& pFaces)
    {
        CMeshIO::ReadVertices(pVertexPath, pVertices) ;
        CMeshIO::ReadFaces(pFacePath, pFaces) ;
    }

    static void WriteMesh(const std::string& pVertexPath, const std::string& pFacePath, std::vector<CDPoint>& pVertices, std::vector<std::vector<int>>& pFaces)
    {
        CMeshIO::WriteVertices(pVertexPath, pVertices) ;
        CMeshIO::WriteFaces(pFacePath, pFaces) ;
    }

    /**
     * Read vertices
     * @param[in]  pPath The path to the file
     * @param[out] pData The vector to store the data
     */
    static void ReadVertices(const std::string& pPath, std::vector<CDPoint>& pData)
    {
        // Open file
        std::ifstream lFile ;
        lFile.open(pPath) ;

        // Init the vertex data
        std::vector<double> lVertexData(3) ;

        // Read
        while(lFile >> lVertexData[0] >> lVertexData[1] >> lVertexData[2])
        {
            pData.emplace_back(lVertexData[0], lVertexData[1], lVertexData[2]) ;
        }

        // Close file
        lFile.close() ;
    }

    /**
     * Read face data
     * @param[in]  pPath The path to the file
     * @param[out] pData The vector to store the data
     */
    static void ReadFaces(const std::string& pPath, std::vector<std::vector<int>>& pData)
    {
        // Open file
        std::ifstream lFile ;
        lFile.open(pPath) ;

        // Init the vertex data
        std::vector<int> lFaceData(3) ;

        // Read
        while(lFile >> lFaceData[0] >> lFaceData[1] >> lFaceData[2])
        {
            pData.push_back(lFaceData) ;
        }

        // Close file
        lFile.close() ;
    }

    /**
     * Write vertices into a file
     * @param pPath
     * @param pData
     */
    static void WriteVertices(const std::string& pPath, const std::vector<CDPoint>& pData)
    {
        // Open file
        std::ofstream lFile ;
        lFile.open(pPath) ;

        for (const CDPoint& lPoint : pData)
        {
            lFile << lPoint.GetX() << lPoint.GetY() << lPoint.GetZ() << std::endl ;
        }

        // Close file
        lFile.close() ;
    }

    /**
     * Write faces into a file
     * @param pPath
     * @param pData
     */
    static void WriteFaces(const std::string& pPath, const std::vector<std::vector<int>>& pData)
    {
        // Open file
        std::ofstream lFile ;
        lFile.open(pPath) ;

        for (const std::vector<int>& lFace : pData)
        {
            lFile << lFace[0] << " " << lFace[1] << " " << lFace[2] << std::endl ;
        }

        // Close file
        lFile.close() ;
    }
};

#endif //MESHEDGECOLLAPSING_CMESHIO_HPP
