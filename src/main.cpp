#include <iostream>
#include <memory>
#include "SQRMatrix.h"
#include "Matrix.h"
#include "Row.h"
#include "Cell.h"

int main() {
    int const def_value = 0;
    int const matrix_size = 10;

    auto matrix = std::make_unique<SQRMatrix<Row<Cell<int, def_value>>>>();

    return 0;
}