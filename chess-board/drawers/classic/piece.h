#ifndef _CLASSIC_PIECES_H
#define _CLASSIC_PIECES_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../piece/piece.h"


class ClassicPiece : Piece
{
public:
  ClassicPiece(char id);

  error* Draw() override;
};

#endif /* pieces.h */
