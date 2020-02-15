//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     ALEXANDRA SLEZAKOVA <xsleza20@stud.fit.vutbr.cz>
// $Date:       $2020-02-12
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author ALEXANDRA SLEZAKOVA
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech
//    matic.
//============================================================================//

TEST(MatrixTesting, konstruktor) {
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(2,2));
    EXPECT_NO_THROW(Matrix(10,6));
    EXPECT_NO_THROW(Matrix(20,30));

    EXPECT_ANY_THROW(Matrix(0, 0));
    EXPECT_ANY_THROW(Matrix(1, 0));
    EXPECT_ANY_THROW(Matrix(0, 1));
    EXPECT_ANY_THROW(Matrix(-1, 0));
    EXPECT_ANY_THROW(Matrix(0, -1));
}

TEST(MatrixTesting, matrix1x1set) {
    Matrix matrix = Matrix(1, 1);

    EXPECT_TRUE(matrix.set(0, 0, 5));
    EXPECT_TRUE(matrix.set(0, 0, 20));

    EXPECT_FALSE(matrix.set(2, 2, 5));
    EXPECT_FALSE(matrix.set(0, 2, 2));
    EXPECT_FALSE(matrix.set(2, 0, 5));
    EXPECT_FALSE(matrix.set(-1, 0, 5));
    EXPECT_FALSE(matrix.set(0, -1, 2));
}

TEST(MatrixTesting, matrix3x3set) {
    Matrix matrix = Matrix(3, 3);

    /* nastavenie hodnot na spravne indexy */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_TRUE(matrix.set(i, j, j + 1));
        }
    }

    EXPECT_FALSE(matrix.set(3, 3, 5));
    EXPECT_FALSE(matrix.set(-3, 3, 5));
    EXPECT_FALSE(matrix.set(3, -3, 5));
    EXPECT_FALSE(matrix.set(2, -3, 5));
    EXPECT_FALSE(matrix.set(0, 3, 5));
}

TEST(MatrixTesting, matrix3x2set) {
    Matrix matrix = Matrix(3, 2);

    /* nastavenie hodnot na spravne indexy */
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            EXPECT_TRUE(matrix.set(i, j, j + 1));
        }
    }

    EXPECT_FALSE(matrix.set(0, 2, 5));
    EXPECT_FALSE(matrix.set(1, 3, 5));
    EXPECT_FALSE(matrix.set(3, 1, 5));
    EXPECT_FALSE(matrix.set(-1, 1, 5));
}

TEST(MatrixTesting, matrix4x4set) {
    Matrix matrix = Matrix(4, 4);

    /* nastavenie hodnot na spravne indexy */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            EXPECT_TRUE(matrix.set(i, j, j + 1));
        }
    }

    EXPECT_FALSE(matrix.set(0, 4, 5));
    EXPECT_FALSE(matrix.set(-1, 3, 5));
    EXPECT_FALSE(matrix.set(3, -1, 5));
}

TEST(MatrixTesting, matrix1x1setvector) {
    Matrix matrix = Matrix(1, 1);

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2},
    }));

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {0},
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2},
            {2, 1}
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2},
            {3}
    }));
}

TEST(MatrixTesting, matrix3x3setvector) {
    Matrix matrix = Matrix(3, 3);

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4},
            {5, 6, 7},
            {-3, -2, 1}
    }));

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 1, 3},
            {1, 2, 2},
            {3, 2}
    }));

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2},
            {3}
    }));


    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 1, 3, 4},
            {1, 2, 2},
            {3, 2, 1, 5}
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 1, 3},
            {1, 2, 2},
            {3, 2, 1, 5}
    }));
}


TEST(MatrixTesting, matrix4x4setvector) {
    Matrix matrix = Matrix(4, 4);

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4, 5},
            {5, 6, 7, 4},
            {-3, -2, 1, 0},
            {2, 3, 4, 5},
    }));

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4, 5},
            {5, 6, 7, 4},
            {-3, -2, 1, 0},
            {2, 3, 4, 5},
    }));

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4, 5},
            {5, 6, 7},
            {-3, -2, 1, 0},
            {2, 3, 4, 5},
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4, 5},
            {5, 6, 7, 4, 5},
            {-3, -2, 1},
            {2, 3, 4, 5, 6},
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 4, 5, 6},
            {5, 6, 7, 4, 5},
            {-3, -2, 1},
            {2, 3, 4, 5, 6},
    }));
}



TEST(MatrixTesting, matrix3x2setvector) {
    Matrix matrix = Matrix(3, 2);

    EXPECT_TRUE(matrix.set(std::vector<std::vector<double>> {
            {2, 3},
            {5, 6},
            {-3, -2}
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 3, 3, 5},
            {3, 1, 3},
            {3, 2, 5}
    }));

    EXPECT_FALSE(matrix.set(std::vector<std::vector<double>> {
            {2, 3},
            {3, 1, 3, 4},
            {3, 2, 5}
    }));
}

TEST(MatrixTesting, matrix1x1get) {
    Matrix matrix = Matrix(1, 1);

    EXPECT_TRUE(matrix.get(0, 0) == 0);

    EXPECT_ANY_THROW(matrix.get(-1, 0));
    EXPECT_ANY_THROW(matrix.get(1, 0));
    EXPECT_ANY_THROW(matrix.get(0, -1));
    EXPECT_ANY_THROW(matrix.get(2, 3));
    EXPECT_ANY_THROW(matrix.get(-1, -2));
}

TEST(MatrixTesting, matrix3x3get) {
    Matrix matrix = Matrix(3, 3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_NO_THROW(matrix.get(i, j));
        }
    }

    EXPECT_ANY_THROW(matrix.get(-1, 3));
    EXPECT_ANY_THROW(matrix.get(-1, 0));
    EXPECT_ANY_THROW(matrix.get(3, 0));
    EXPECT_ANY_THROW(matrix.get(0, -1));
    EXPECT_ANY_THROW(matrix.get(2, 3));
}

TEST(MatrixTesting, matrix3x2get) {
    Matrix matrix = Matrix(3, 2);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            EXPECT_NO_THROW(matrix.get(i, j));
        }
    }

    EXPECT_ANY_THROW(matrix.get(-1, 3));
    EXPECT_ANY_THROW(matrix.get(-1, 0));
    EXPECT_ANY_THROW(matrix.get(3, 0));
    EXPECT_ANY_THROW(matrix.get(0, -1));
    EXPECT_ANY_THROW(matrix.get(2, 3));
}

TEST(MatrixTesting, porovnanie) {
    Matrix matrix2x3 = Matrix(2, 3);
    Matrix matrix3x2 = Matrix(3, 2);
    Matrix matrix3x2i = Matrix(3, 2);
    Matrix matrix1x1 = Matrix();
    Matrix matrix4x4 = Matrix(4, 4);
    Matrix matrix4x4i = Matrix(4, 4);
    Matrix matrix2x2 = Matrix(2, 2);

    matrix3x2.set(std::vector<std::vector<double>> {
            {2, 3},
            {1, 9},
            {8, 5}
    });

    matrix3x2i.set(std::vector<std::vector<double>> {
            {2, 3},
            {1, 0},
            {8, 5}
    });

    Matrix matrix = Matrix(3, 2);
    EXPECT_TRUE(matrix4x4 == matrix4x4i);
    EXPECT_FALSE(matrix3x2 == matrix);
    EXPECT_FALSE(matrix3x2i == matrix);
    EXPECT_ANY_THROW(matrix2x3 == matrix);
    EXPECT_ANY_THROW(matrix1x1 == matrix);
    EXPECT_ANY_THROW(matrix2x2 ==(matrix2x3));
}

TEST(MatrixTesting, sucet) {
    Matrix matrix2x3 = Matrix(2, 3);
    Matrix matrix3x2 = Matrix(3, 2);
    Matrix matrix3x2i = Matrix(3, 2);
    Matrix matrix1x1 = Matrix();

    matrix3x2.set(std::vector<std::vector<double>> {
            {2, 3},
            {1, 9},
            {8, 5}
    });

    Matrix matrix = Matrix(3, 2);
    EXPECT_NO_THROW(matrix3x2 + matrix);
    EXPECT_NO_THROW(matrix3x2i + matrix);
    EXPECT_ANY_THROW(matrix2x3 + matrix);
    EXPECT_ANY_THROW(matrix1x1 + matrix);

    Matrix matrix2x2 = Matrix(2, 2);
    Matrix matrix2x2i = Matrix(2, 2);
    Matrix result = Matrix(2, 2);

    matrix2x2.set(std::vector<std::vector<double>> {
            {3, 5},
            {8, 1},
    });

    matrix2x2i.set(std::vector<std::vector<double>> {
            {7, -4},
            {2, 3},
    });

    result.set(std::vector<std::vector<double>> {
            {10, 1},
            {10, 4},
    });
    EXPECT_EQ(matrix2x2 + matrix2x2i, result);

    Matrix matrix4x4 = Matrix(4, 4);
    Matrix matrix4x4i = Matrix(4, 4);
    Matrix result4x4 = Matrix(4, 4);

    matrix4x4.set(std::vector<std::vector<double>> {
            {3, 5, 1, 1},
            {8, 1, 1, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1}
    });

    matrix4x4i.set(std::vector<std::vector<double>> {
            {7, -4, 1, 1},
            {2, 3, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
    });

    result4x4.set(std::vector<std::vector<double>> {
            {10, 1, 2, 2},
            {10, 4, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
    });
    EXPECT_EQ(matrix4x4 + matrix4x4i, result4x4);
}

TEST(MatrixTesting, nasobenie) {
    Matrix matrix = Matrix(1, 1);

    Matrix matrix2x3 = Matrix(2, 3);
    Matrix matrix3x2 = Matrix(3, 2);
    Matrix matrix3x3 = Matrix(3, 3);
    Matrix matrix1x1 = Matrix();
    Matrix matrix1x1i = Matrix(1, 1);

    Matrix matrix2x2 = Matrix(2, 2);
    Matrix matrix2x2i = Matrix(2, 2);
    Matrix result = Matrix(2, 2);

    matrix2x2.set(std::vector<std::vector<double>> {
            {1, 2},
            {3, 4},
    });

    matrix2x2i.set(std::vector<std::vector<double>> {
            {5, 6},
            {7, 8},
    });

    result.set(std::vector<std::vector<double>> {
            {19, 22},
            {43, 50},
    });
    EXPECT_EQ(matrix2x2 * matrix2x2i, result);

    EXPECT_NO_THROW(matrix2x3 * matrix3x2);
    EXPECT_NO_THROW(matrix1x1 * matrix);
    EXPECT_NO_THROW(matrix1x1i * matrix);
    EXPECT_ANY_THROW(matrix2x3 * matrix);
    EXPECT_ANY_THROW(matrix3x2 * matrix);
    EXPECT_ANY_THROW(matrix3x3 * matrix);

    Matrix matrix4x4 = Matrix(4, 4);
    Matrix matrix4x4i = Matrix(4, 4);
    Matrix result4x4 = Matrix(4, 4);

    matrix4x4.set(std::vector<std::vector<double>> {
            {3, 5, 1, 1},
            {8, 1, 1, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1}
    });

    matrix4x4i.set(std::vector<std::vector<double>> {
            {7, -4, 1, 1},
            {2, 3, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
    });

    result4x4.set(std::vector<std::vector<double>> {
            {32, 4, 4, 4},
            {59, -28, 9, 9},
            {0, 0, 0, 0},
            {10, 0, 2, 2},
    });
    EXPECT_EQ(matrix4x4 * matrix4x4i, result4x4);
}

TEST(MatrixTesting, nasobenieSkalarom) {
    Matrix matrix2x3 = Matrix(2, 3);
    Matrix matrix3x2 = Matrix(3, 2);
    Matrix matrix1x1 = Matrix();

    matrix3x2.set(std::vector<std::vector<double>> {
            {2, 3},
            {1, 9},
            {8, 5}
    });

    matrix1x1.set(std::vector<std::vector<double>> {
            {2},
    });

    matrix2x3.set(std::vector<std::vector<double>> {
            {2, 3, 4},
            {1, 9, 5},
            {8, 5, 3}
    });

    /* porovnanie vysledku nasobenia matice */
    Matrix matrix2x2 = Matrix(2, 2);
    matrix2x2.set(std::vector<std::vector<double>> {
            {1, 0},
            {-3, 2},
    });

    Matrix result = Matrix(2, 2);
    result.set(std::vector<std::vector<double>> {
            {2, 0},
            {-6, 4},
    });
    EXPECT_EQ(matrix2x2 * 2.0, result);

    Matrix matrix4x4 = Matrix(4, 4);
    matrix4x4.set(std::vector<std::vector<double>> {
            {3, 5, 1, 1},
            {8, 1, 1, 1},
            {0, 0, 0, 0},
            {1, 1, 1, 1}
    });
    EXPECT_EQ(matrix4x4 * 1.0, matrix4x4);

    EXPECT_NO_THROW(matrix1x1 * 2.3);
    EXPECT_NO_THROW(matrix2x3 * 4.0);
    EXPECT_NO_THROW(matrix3x2 * 5.0);
}

TEST(MatrixTesting, riesenieSustavy) {
    Matrix matrix2x2 = Matrix(2, 2);
    matrix2x2.set(std::vector<std::vector<double>> {
            {1, 2},
            {4, 3},
    });

    std::vector<double> b = {5, 15};
    EXPECT_NO_THROW(matrix2x2.solveEquation(b));

    /* matica nie je stvorcova */
    Matrix matrix = Matrix(3, 2);
    EXPECT_ANY_THROW(matrix.solveEquation({3, 4 ,5}));

    /* matica nie je stvorcova a pocet prvkov na pravej strane neodpoveda poctu riadkov */
    Matrix matrix2x3 = Matrix(2, 3);
    matrix2x3.set(std::vector<std::vector<double>> {
            {1, 2, 4},
            {4, 3, 3},
    });

    EXPECT_ANY_THROW(matrix2x3.solveEquation({1, 2, 3}));

    matrix = Matrix(3, 3);
    EXPECT_ANY_THROW(matrix.solveEquation({0, 0, 0}));

    /* singularna matica */
    matrix2x2.set(std::vector<std::vector<double>> {
            {-4, 8},
            {2, -4},
    });
    EXPECT_ANY_THROW(matrix2x2.solveEquation({0, 0}));

    matrix = Matrix(1, 1);
    matrix.set(std::vector<std::vector<double>> {
            {1},
    });
    EXPECT_NO_THROW(matrix.solveEquation({1}));

    matrix = Matrix(4, 4);
    matrix.set(std::vector<std::vector<double>> {
            {1, 1, 1, 1},
            {1, 1, -1, -1},
            {1, -1, 1, -1},
            {1, -1, -1, 1}
    });
    std::vector<double> result = {4, 3, 2, 1};
    EXPECT_EQ(matrix.solveEquation({10, 4, 2, 0}), result);

}

/*** Konec souboru white_box_tests.cpp ***/
