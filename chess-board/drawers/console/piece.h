#ifndef _CONSOLE_PIECES_H
#define _CONSOLE_PIECES_H

#include <stdio.h>
#include "../../error/error.h"
#include "../../piece/piece.h"

class ConsolePiece : public Piece
{
public:
  ConsolePiece(char id);

  error* Draw() override;
};

#endif /* pieces.h */
