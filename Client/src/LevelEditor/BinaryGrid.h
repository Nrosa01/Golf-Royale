#ifndef BINARY_GRID_H
#define BINARY_GRID_H

#include <stdint.h>
#include "../Network/Serializable.h" //TODO: mover serializable a un sitio mejor
#include <vector>

class BinaryGrid : public Serializable
{
public:
    BinaryGrid(int width, int height);
    BinaryGrid();
    ~BinaryGrid();

    bool isOutOfBounds(int x, int y) const;
    bool getCell(int x, int y) const;
    void setCell(int x, int y, bool value);
    void print() const;
    void saveToFile(const char *fileName);
    virtual void to_bin();
    virtual int from_bin(char *data);
    int getWidth() const;
    int getHeight() const;

private:
    char *binaryMatToBytes(uint16_t &matSize);
    void matFromBytes(char *data, uint8_t xSize, uint8_t ySize);

    std::vector<std::vector<bool>> binMat;
};

#endif