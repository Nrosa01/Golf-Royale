#ifndef BINARYMATRIXSERIALIZER_H
#define BINARYMATRIXSERIALIZER_H

#include <vector>
#include <sys/types.h>

template <class T>
using vec = std::vector<T>;

namespace BinaryMatrixSerializer
{
    extern __uint32_t WriteMatrix(vec<vec<bool>> binMat, const char* fileName);
    extern __uint32_t ReadMatrix(vec<vec<bool>>& binMat, const char* fileName);
};

#endif