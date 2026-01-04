#include <iostream>
#include <vector>
#include <string>
#include "Game.h"


struct TestResult {
    std::string name;
    bool ok;
};


static void printFail(const std::string& msg) {
    std::cout << "  FAIL: " << msg << "\n";
}

// -------- Tests --------

static bool testCastlingKingside() {
    Game game;

    std::vector<movement> seq = {
        {7, 6, 5, 7},
        {1, 0, 2, 0},
        {6, 6, 5, 6},
        {2, 0, 3, 0},
        {7, 5, 6, 6},
        {3, 0, 4, 0},
        {7, 4, 7, 6}
    };

    for (const auto& m : seq) {
        if (!game.play(m)){
            printFail("castling sequence should be valid");
            return false;
        }
    }

    if(game.getBoard().getPiece(7,6)->getType() != PieceType::King || game.getBoard().getPiece(7,5)->getType() != PieceType::Rook){
        printFail("castling result unexpected");
        return false;
    }

    return true;
}

static bool testPromotion() {
    Game game;

    std::vector<movement> seq = {
        {6, 0, 5, 0}, {1, 1, 2, 1},
        {5, 0, 4, 0}, {2, 1, 3, 1},
        {4, 0, 3, 1}, {1, 7, 2, 7},
        {3, 1, 2, 1}, {2, 7, 3, 7},
        {2, 1, 1, 1}, {0, 1, 2, 2},
        {1, 1, 0, 1}  // promoción
    };

    for (const auto& m : seq) {
        if (!game.play(m)){
            printFail("promotion sequence should be valid");
            return false;
        }
    }

    if(game.getBoard().getPiece(0,1)->getType() != PieceType::Queen){
        printFail("promotion result unexpected");
        return false;
    }

    return true;
}

static bool testKingInCheck() {
    Game game;

    std::vector<movement> seq = {
        {6, 0, 5, 0}, {1, 1, 2, 1},
        {5, 0, 4, 0}, {2, 1, 3, 1},
        {4, 0, 3, 1}, {1, 7, 2, 7},
        {3, 1, 2, 1}, {2, 7, 3, 7},
        {2, 1, 1, 1}, {0, 1, 2, 2},
        {1, 1, 0, 1}, {0, 2, 1, 1},
        {6, 1, 5, 1}, {1, 3, 2, 3},
        {6, 2, 5, 2}
    };

    for (const auto& m : seq) {
        if (!game.play(m)){
            printFail("game sequence should be valid");
            return false;
        }
    }

    movement final{0, 3, 1, 3};
    if(game.play(final)){
        printFail("final move should be invalid");
        return false;
    }
    
    return true;
}

static bool testEnPassant() {
    Game game;

    std::vector<movement> seq = {
        {6, 0, 4, 0},
        {1, 3, 3, 3},
        {4, 0, 3, 0},
        {3, 3, 4, 3},
        {6, 2, 4, 2},
        {4, 3, 5, 2}
    };

    for (const auto& m : seq) {
        if (!game.play(m)){
            printFail("en passant sequence should be valid");
            return false;
        }
    }
    
    if(game.getBoard().getPiece(4,2) != nullptr){
        printFail("pawn should be captured");
        return false;
    }

    return true;
}

// -------- Runner --------

static std::vector<TestResult> runAllTests() {
    std::vector<TestResult> results;
    results.push_back({"castling kingside", testCastlingKingside()});
    results.push_back({"promotion", testPromotion()});
    results.push_back({"illegal leaves king in check (setup)", testKingInCheck()});
    results.push_back({"en passant", testEnPassant()});
    return results;
}

static int interactiveMode() {
    Game game;
    while (true) {
        game.print();

        std::cout << "\nMovimiento (fromRow fromCol toRow toCol), o -1 para salir:\n> ";
        int fr;
        std::cin >> fr;
        if (!std::cin || fr == -1) break;

        int fc, tr, tc;
        std::cin >> fc >> tr >> tc;

        movement m{fr, fc, tr, tc};
        if (!game.play(m)) {
            std::cout << "Movimiento invalido\n";
        }
    }
    return 0;
}

/**************************************************************************************/
int main() {
    // 0 = correr tests, 1 = modo interactivo
    int mode = 0;

    if (mode == 1) {
        return interactiveMode();
    }

    auto results = runAllTests();

    int passed = 0;
    for (const auto& r : results) {
        std::cout << (r.ok ? "[PASS] " : "[FAIL] ") << r.name << "\n";
        if (r.ok) passed++;
    }

    std::cout << "\n" << passed << "/" << results.size() << " tests passed\n";
    return (passed == (int)results.size()) ? 0 : 1;
}
