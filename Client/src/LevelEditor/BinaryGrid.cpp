#include "BinaryGrid.h"
#include <iostream>
#include <cstring>

BinaryGrid::BinaryGrid(int width, int height) : Serializable(), binMat(height, std::vector<bool>(width, false))
{
}

BinaryGrid::BinaryGrid() : Serializable(), binMat(0, std::vector<bool>(0, false)){}

BinaryGrid::~BinaryGrid() {}

bool BinaryGrid::isOutOfBounds(int x, int y) const
{
    return x < 0 || x >= (int)binMat.size() || y < 0 || y >= (int)binMat[0].size();
}

bool BinaryGrid::getCell(int x, int y) const
{
    if (isOutOfBounds(x,y))
        return false;

    return binMat.at(x).at(y);
}

void BinaryGrid::setCell(int x, int y, bool value)
{
    if (isOutOfBounds(x,y))
        return;

    binMat.at(x).at(y) = value;
}

void BinaryGrid::print() const
{
    for (size_t y = 0; y < binMat.size(); y++)
    {
        for (size_t x = 0; x < binMat[0].size(); x++)
        {
            std::cout << (binMat[y][x] ? "1" : "0");
        }
        std::cout << std::endl;
    }
}

void BinaryGrid::saveToFile(const char *fileName)
{
    to_bin();

    FILE *file = fopen(fileName, "wb");
    fwrite(_data, sizeof(char), _size, file);
    fclose(file);
}

void BinaryGrid::to_bin()
{
    if (binMat.empty() || binMat[0].empty() || binMat.size() > 255 || binMat[0].size() > 255)
        return;

    uint8_t xSize = binMat.size();
    uint8_t ySize = binMat[0].size();
    uint16_t matSize = 0;
    char *matBuffer = binaryMatToBytes(matSize);

    alloc_data(sizeof(xSize) + sizeof(ySize) + matSize);
    char *tmp = _data;

    memcpy(tmp, &xSize, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    memcpy(tmp, &ySize, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    memcpy(tmp, matBuffer, matSize);

    free(matBuffer);
}

int BinaryGrid::from_bin(char *data)
{
    uint8_t xSize = 0;
    uint8_t ySize = 0;
    char *ptr = data;

    memcpy(&xSize, ptr, sizeof(uint8_t));
    ptr += sizeof(uint8_t);
    memcpy(&ySize, ptr, sizeof(uint8_t));
    ptr += sizeof(uint8_t);
    matFromBytes(ptr, xSize, ySize);

    return 0;
}

int BinaryGrid::getWidth() const
{
    return binMat[0].size();
}

int BinaryGrid::getHeight() const
{
    return binMat.size();
}

char *BinaryGrid::binaryMatToBytes(uint16_t &matSize)
{
    if (binMat.empty() || binMat[0].empty() || binMat.size() > 255 || binMat[0].size() > 255)
        return nullptr;

    matSize = (binMat.size() * binMat[0].size() + 8) / 8;
    matSize = (matSize == 0) ? 1 : matSize;
    char *buffer = (char *)malloc(matSize);
    memset(buffer, 0, matSize);
    uint8_t ySize = binMat.size();
    uint8_t xSize = binMat[0].size();

    for (size_t y = 0; y < ySize; y++)
    {
        for (size_t x = 0; x < xSize; x++)
            if (binMat[y][x])
                buffer[(y * xSize + x) / 8] |= (1 << (7 - ((y * xSize + x) % 8)));
    }

    return buffer;
}

void BinaryGrid::matFromBytes(char *data, uint8_t xSize, uint8_t ySize)
{
    uint8_t temp = xSize;
    xSize = ySize;
    ySize = temp;

    binMat.resize(ySize);
    for (size_t i = 0; i < binMat.size(); i++)
        binMat[i].resize(xSize);

    for (size_t y = 0; y < ySize; y++)
        for (size_t x = 0; x < xSize; x++)
            binMat[y][x] = (data[(y * xSize + x) / 8] & (1 << (7 - ((y * xSize + x) % 8)))) != 0;
}