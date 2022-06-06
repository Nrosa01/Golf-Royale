#include "BinaryMatrixSerializer.h"
#include <iostream>
#include <fstream>

__uint32_t BinaryMatrixSerializer::WriteMatrix(vec<vec<bool>> binMat, const char *fileName)
{
    if (binMat.empty() || binMat[0].empty())
        return -1;

    if (binMat.size() != 32 || binMat[0].size() != 32)
        return -1;

    uint32_t serializedMat = 0;
    uint8_t matrixSizeX = 32;
    uint8_t matrixSizeY = 32;

    // Store matrix in a 32-bit integer reading left to right, top to bottom
    for (uint8_t i = 0; i < matrixSizeX; ++i)
        for (uint8_t j = 0; j < matrixSizeY; ++j)
        {
            auto bit = binMat[i][j] ? 1 : 0;
            if(bit)
                std::cout << "Bit found at position: " << (int)i << " " << (int)j << std::endl;
            serializedMat |= binMat[i][j] << (i * matrixSizeY + j);
        }

    // Write matrix to file
    // std::ofstream file(fileName, std::ios::out | std::ios::binary);
    // if (file.is_open())
    // {
    //     file.write((char*)&serializedMat, sizeof(serializedMat));
    //     file.close();
    // }
    // else
    //     return -1;

    return serializedMat;
}

__uint32_t BinaryMatrixSerializer::ReadMatrix(vec<vec<bool>> &binMat, const char *fileName)
{
    binMat = vec<vec<bool>>(32, vec<bool>(32, 0));

    uint32_t serializedMat = 0;
    uint8_t matrixSizeX = 32;
    uint8_t matrixSizeY = 32;

    // Read matrix from file
    std::ifstream file(fileName, std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        file.read((char *)&serializedMat, sizeof(serializedMat));
        file.close();
    }
    else
        return -1;

    // Store matrix in a 32-bit integer reading left to right, top to bottom
    for (uint8_t i = 0; i < matrixSizeX; ++i)
        for (uint8_t j = 0; j < matrixSizeY; ++j)
            binMat[i][j] = (serializedMat >> (i * matrixSizeY + j)) & 1;

    return serializedMat;
}