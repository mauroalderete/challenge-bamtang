#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include "err.h"

const char *ASSETS_PATH = "./assets";
enum COLOR { white, black };

template<typename AssetType>
class Asset {
  char *path;
  char *name;
  AssetType data;
};

template<typename AssetType>
class AssetsHandler {
  private:
    std::unordered_map<char*, Asset<AssetType>> *assets;

  public:
    AssetsHandler() {
      this->assets = new std::unordered_map<char*, Asset<AssetType>>();
    }

    ~AssetsHandler() {
      this->assets.clear();
    }

    error* Append(const char* name, const char* path) {
      return NULL;
    }

    Asset<AssetType>* Get(const char* name) {
      return NULL;
    }

    error* Free(const char* name) {
      return NULL;
    }
};

class Piece {
  private:
    char type;

  public:
    Piece(char type) {
      this->type = type;
    }
};

class Square {
  private:
    COLOR color;
    Piece *piece;

  public:
    Square(COLOR color) {
      this->color = color;
      this->piece = NULL;
    }

    Piece* Put(Piece* piece) {
      Piece *tmp = this->Take();
      this->piece = piece;
      return tmp;
    }

    Piece* Take() {
      Piece *tmp = this->piece;
      this->piece = NULL;
      return tmp;
    }

    bool IsWhite() {
      return this->color == white;
    }

    bool IsBlack() {
      return this->color == black;
    }
};

class Board {
  private:
    std::vector<Square*> squares;
    size_t rows;
    size_t columns;

    void buildBoard() {
      this->squares.clear();
      this->squares.resize(rows*columns, NULL);

      for (int s=0; s < this->squares.size(); s++){
        if ( s % 2 == 0 ) {
          this->squares.at(s) = new Square(white);
        } else {
          this->squares.at(s) = new Square(black);
        }
      }
    }

  public:
    Board(size_t rows, size_t columns) {
      if (rows <= 0) {
        fatal(errorf("A chessboard must be contains 0 rows"));
      }
      if (columns <= 0) {
        fatal(errorf("A chessboard must be contains 0 columns"));
      }

      this->rows = rows;
      this->columns = columns;

      buildBoard();
    }

    size_t Rows() {
      return this->rows;
    }

    size_t Columns() {
      return this->columns;
    }

    size_t Size() {
      return this->squares.size();
    }

    Square* SquareAt(size_t i) {
      if (i >= this->squares.size() ) {
        return NULL;
      }
      return this->squares.at(i);
    }

    ~Board() {
      this->squares.clear();
    }
};

class SquareGrapher {
  protected:
    int resources;

  public:
    virtual error* Draw(Square *square) = 0;
};

class BoardGrapher {
  protected:
    SquareGrapher *gsquare;

  public:
    virtual error* Draw(Board *board) = 0;
};

class ConsoleSquareGrapher: SquareGrapher  {
  public:
    //inyect resource
    ConsoleSquareGrapher(AssetsHandler<int> *images) {

    }

    error* Draw(Square *square) override {
      if (square->IsWhite()) {
        printf(" [ ]");
      } else {
        printf(" [+]");
      }

      return NULL;
    }
};

class ConsoleBoardGrapher: BoardGrapher{
  public:
    ConsoleBoardGrapher(SquareGrapher *gsquare) {
      this->gsquare = gsquare;
    }

    error* Draw(Board *board) override {
      for (int r=0; r < board->Rows(); r++) {
        for (int c=0; c < board->Columns(); c++) {
          Square *s = board->SquareAt(r*board->Rows() + c);
          this->gsquare->Draw(s);
        }
        printf("\n");
      }
      return NULL;
    }
};

error* drawChessBoard( const char *position ) {
  return NULL;
}

error* drawBoard(BoardGrapher *gboard, Board *board) {
  gboard->Draw(board);
  return NULL;
}

int main() {

  printf("Jaque mate!\n");

  const char *initPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
  const size_t boardWidth = 8;
  const size_t boardHeight = 8;

  error *err = drawChessBoard(initPosition);
  if (err!=NULL) {
    fatal(err);
  }

  AssetsHandler<int> *images = new AssetsHandler<int>();
  images->Append("square_white", "./assets/classic/square_white.png");
  images->Append("square_black", "./assets/classic/square_black.png");
  images->Append("p", "./assets/classic/p.png");
  images->Append("r", "./assets/classic/r.png");
  images->Append("b", "./assets/classic/b.png");
  images->Append("n", "./assets/classic/n.png");
  images->Append("q", "./assets/classic/q.png");
  images->Append("k", "./assets/classic/k.png");

  ConsoleSquareGrapher *consoleSquareGrpaher = new ConsoleSquareGrapher(images);
  ConsoleBoardGrapher *consoleBoardGrapher = new ConsoleBoardGrapher((SquareGrapher*)consoleSquareGrpaher);

  Board *board = new Board(boardHeight, boardWidth);

  drawBoard((BoardGrapher*)consoleBoardGrapher, board);

  exit(EXIT_SUCCESS);
}
