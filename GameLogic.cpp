#include "GameLogic.h"

#include <ctime>
#include <unordered_map>

#include "windows.h"
#include "diff.h"

using namespace std;

HangmanGame::HangmanGame(WINDOWS* WINDOWS, int time) : SDL(WINDOWS), playTime(time) {
    gameplay = true;
    countwin = 0;
    countloss = 0;
}
