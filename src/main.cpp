#include <iostream>
#include <memory>
#include "SQRMatrix.h"
#include "Matrix.h"
#include "LinearMatrix.h"
#include "Cell.h"
#include <cassert>
#include "SparseSQRMatrix.h"

int main() {
    int const def_value = 0;
    int const matrix_size = 10;

    SQRMatrix<LinearMatrix<Cell<int, def_value>>> sqrmatrix;
//    decltype(auto) sqrmatrix = std::make_unique<SQRMatrix<LinearMatrix<Cell<int, def_value>>>>();
//    SparseSQRMatrixIterator<std::tuple<std::size_t, std::size_t, int>> iter{sqrmatrix};
//    auto proxi = SparseSQRMatrix(sqrmatrix);
    auto proxi = SparseSQRMatrix(std::move(sqrmatrix));
    { /* Task's description checks */
        assert(proxi.size() == 0);

        auto a = proxi[0][0];
        assert(a == def_value);
        assert(proxi.size() == 0);

        proxi[100][100] = 314;
        assert(proxi[100][100] == 314);
        assert(proxi.size() == 1);

        proxi[100][100] = def_value;
        assert(proxi[100][100] == def_value);
        assert(proxi.size() == 0);
    }

    int matrix_index = matrix_size - 1;

    for (int i = 0; i < matrix_size; ++i) {
        proxi[i][i] = i;
        proxi[i][matrix_index - i] = matrix_index - i;
    }

    for (int i = 1; i < matrix_index; ++i) {
        for (int j = 1; j < matrix_index; ++j) {
            std::cout << proxi[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << proxi.size() << std::endl;

    std::size_t x = 0;
    std::size_t y = 0;
    int v = 0;
    for(auto cell : proxi) {
        std::tie(x, y, v) = cell;
        std::cout << "[" << x << "," << y << "]" << " = " << v << std::endl;
    }
    return 0;
}