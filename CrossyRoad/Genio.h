#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <bits/stdc++.h>
#include <string>
#include <math.h>
#include <map>

using namespace std;

typedef SDL_Texture G_Texture;
typedef SDL_Rect G_Rect;
typedef TTF_Font G_Font;
typedef Mix_Music G_Music;
typedef Mix_Chunk G_Sound;



#define G_Keyboard event.key.keysym.sym
#define G_Mouse event.button.button

#define G_motion event.motion
#define G_motion event.motion



enum
{
	GK_UNKNOWN = 0,

	GK_RETURN = '\r',
	GK_ESCAPE = '\033',
	GK_BACKSPACE = '\b',
	GK_TAB = '\t',
	GK_SPACE = ' ',
	GK_EXCLAIM = '!',
	GK_QUOTEDBL = '"',
	GK_HASH = '#',
	GK_PERCENT = '%',
	GK_DOLLAR = '$',
	GK_AMPERSAND = '&',
	GK_QUOTE = '\'',
	GK_LEFTPAREN = '(',
	GK_RIGHTPAREN = ')',
	GK_ASTERISK = '*',
	GK_PLUS = '+',
	GK_COMMA = ',',
	GK_MINUS = '-',
	GK_PERIOD = '.',
	GK_SLASH = '/',
	GK_0 = '0',
	GK_1 = '1',
	GK_2 = '2',
	GK_3 = '3',
	GK_4 = '4',
	GK_5 = '5',
	GK_6 = '6',
	GK_7 = '7',
	GK_8 = '8',
	GK_9 = '9',
	GK_COLON = ':',
	GK_SEMICOLON = ';',
	GK_LESS = '<',
	GK_EQUALS = '=',
	GK_GREATER = '>',
	GK_QUESTION = '?',
	GK_AT = '@',
	/*
	Skip uppercase letters
	*/
	GK_LEFTBRACKET = '[',
	GK_BACKSLASH = '\\',
	GK_RIGHTBRACKET = ']',
	GK_CARET = '^',
	GK_UNDERSCORE = '_',
	GK_BACKQUOTE = '`',
	GK_a = 'a',
	GK_b = 'b',
	GK_c = 'c',
	GK_d = 'd',
	GK_e = 'e',
	GK_f = 'f',
	GK_g = 'g',
	GK_h = 'h',
	GK_i = 'i',
	GK_j = 'j',
	GK_k = 'k',
	GK_l = 'l',
	GK_m = 'm',
	GK_n = 'n',
	GK_o = 'o',
	GK_p = 'p',
	GK_q = 'q',
	GK_r = 'r',
	GK_s = 's',
	GK_t = 't',
	GK_u = 'u',
	GK_v = 'v',
	GK_w = 'w',
	GK_x = 'x',
	GK_y = 'y',
	GK_z = 'z',
