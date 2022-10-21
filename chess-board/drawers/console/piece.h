#ifndef _CONSOLE_PIECE_H
#define _CONSOLE_PIECE_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../piece/piece.h"

class ConsolePiece : public Piece
{
public:
  ConsolePiece(char id);

  error* Draw() override;
};

#endif /* piece.h */
