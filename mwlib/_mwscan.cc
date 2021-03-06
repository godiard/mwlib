/* Generated by re2c 0.13.4 */
#line 1 "_mwscan.re"
// -*- mode: c++ -*-
// Copyright (c) 2007-2008 PediaPress GmbH
// See README.txt for additional licensing information.

#include <Python.h>

#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

#define RET(x) {found(x); return x;}

typedef enum {
	t_end,
	t_text,
	t_entity,
	t_special,
	t_magicword,
	t_comment,
	t_2box_open,   // [[
	t_2box_close,  // ]]
	t_http_url,
	t_break,
	t_begin_table,
	t_end_table,
	t_html_tag,
	t_style,
	t_pre,
	t_section,
	t_section_end,
	t_item,
	t_colon,
	t_semicolon,
	t_hrule,
	t_newline,
	t_column,
	t_row,
	t_tablecaption,
	t_urllink,
} mwtok;

struct Token
{
	int type;
	int start;
	int len;
};

class Scanner
{
public:

	Scanner(Py_UNICODE *_start, Py_UNICODE *_end) {
		source = start = _start;
		end = _end;
		cursor = start;
		line_startswith_section = -1;
		tablemode=0;
	}

	int found(mwtok val) {
		if (val==t_text && tokens.size()) {
			Token &previous_token (tokens[tokens.size()-1]);
			if (previous_token.type==val) {
				previous_token.len += cursor-start;
				return tokens.size()-1;
			}
		}
		Token t;
		t.type = val;
		t.start = (start-source);
		t.len = cursor-start;			
		tokens.push_back(t);
		return tokens.size()-1;
	}

	bool bol() const {
		return (start==source) || (start[-1]=='\n');
	}

	bool eol() const {
		return *cursor=='\n' || *cursor==0;
	}

	void newline() {
		if (line_startswith_section>=0) {
			tokens[line_startswith_section].type = t_text;
		}
		line_startswith_section = -1;
	}

	inline int scan();

	Py_UNICODE *source;

	Py_UNICODE *start;
	Py_UNICODE *cursor;
	Py_UNICODE *end;
	vector<Token> tokens;

	int line_startswith_section;
	int tablemode;
};


int Scanner::scan()
{
	start=cursor;
	
	Py_UNICODE *marker=cursor;

	Py_UNICODE *save_cursor = cursor;


#define YYCTYPE         Py_UNICODE
#define YYCURSOR        cursor
#define YYMARKER	marker
#define YYLIMIT   (end)
// #define YYFILL(n) return 0;

#line 124 "_mwscan.re"


/*
  the re2c manpage says:
  "The user must arrange for a sentinel token to appear at the end of input"
  \000 is our sentinel token.
*/

#line 157 "_mwscan.re"

	if (!bol()) {
		goto not_bol;
	}

#line 140 "_mwscan.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;

	yych = *YYCURSOR;
	if (yych <= '-') {
		if (yych <= '"') {
			if (yych <= 0x001F) goto yy18;
			if (yych <= ' ') goto yy2;
			if (yych <= '!') goto yy8;
			goto yy18;
		} else {
			if (yych <= ')') {
				if (yych <= '#') goto yy13;
				goto yy18;
			} else {
				if (yych <= '*') goto yy13;
				if (yych <= ',') goto yy18;
				goto yy17;
			}
		}
	} else {
		if (yych <= '<') {
			if (yych <= '9') goto yy18;
			if (yych <= ':') goto yy11;
			if (yych <= ';') goto yy15;
			goto yy18;
		} else {
			if (yych <= 'z') {
				if (yych <= '=') goto yy9;
				goto yy18;
			} else {
				if (yych <= '{') goto yy4;
				if (yych <= '|') goto yy6;
				goto yy18;
			}
		}
	}
yy2:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= 0x001F) goto yy3;
	if (yych <= '!') goto yy47;
	if (yych <= 'z') goto yy3;
	if (yych <= '|') goto yy47;
yy3:
#line 199 "_mwscan.re"
	{RET(t_pre);}
#line 189 "_mwscan.cc"
yy4:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '|') goto yy43;
yy5:
#line 209 "_mwscan.re"
	{goto not_bol;}
#line 196 "_mwscan.cc"
yy6:
	++YYCURSOR;
	if ((yych = *YYCURSOR) <= ',') {
		if (yych == '+') goto yy35;
	} else {
		if (yych <= '-') goto yy38;
		if (yych == '}') goto yy41;
	}
yy7:
#line 177 "_mwscan.re"
	{
		if (tablemode)
			RET(t_column);

		if (*start==' ') {
			cursor = start+1;
			RET(t_pre);
		}
		RET(t_text);
	}
#line 217 "_mwscan.cc"
yy8:
	yych = *++YYCURSOR;
	goto yy7;
yy9:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '=') goto yy33;
	goto yy32;
yy10:
#line 200 "_mwscan.re"
	{
			line_startswith_section = found(t_section);
			return t_section;
		}
#line 231 "_mwscan.cc"
yy11:
	++YYCURSOR;
	if ((yych = *YYCURSOR) <= ')') {
		if (yych == '#') goto yy27;
	} else {
		if (yych <= '*') goto yy27;
		if (yych == ':') goto yy29;
	}
yy12:
#line 205 "_mwscan.re"
	{RET(t_colon);}
#line 243 "_mwscan.cc"
yy13:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy28;
yy14:
#line 204 "_mwscan.re"
	{RET(t_item);}
#line 251 "_mwscan.cc"
yy15:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy26;
yy16:
#line 206 "_mwscan.re"
	{RET(t_semicolon);}
#line 259 "_mwscan.cc"
yy17:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == '-') goto yy19;
	goto yy5;
yy18:
	yych = *++YYCURSOR;
	goto yy5;
yy19:
	yych = *++YYCURSOR;
	if (yych == '-') goto yy21;
yy20:
	YYCURSOR = YYMARKER;
	if (yyaccept <= 0) {
		goto yy3;
	} else {
		goto yy5;
	}
yy21:
	yych = *++YYCURSOR;
	if (yych != '-') goto yy20;
yy22:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych == '-') goto yy22;
#line 207 "_mwscan.re"
	{RET(t_hrule);}
#line 287 "_mwscan.cc"
yy25:
	++YYCURSOR;
	yych = *YYCURSOR;
yy26:
	if (yych == ';') goto yy25;
	goto yy16;
yy27:
	++YYCURSOR;
	yych = *YYCURSOR;
yy28:
	if (yych == '#') goto yy27;
	if (yych == '*') goto yy27;
	goto yy14;
yy29:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= ')') {
		if (yych == '#') goto yy27;
		goto yy12;
	} else {
		if (yych <= '*') goto yy27;
		if (yych == ':') goto yy29;
		goto yy12;
	}
yy31:
	++YYCURSOR;
	yych = *YYCURSOR;
yy32:
	if (yych == '\t') goto yy31;
	if (yych == ' ') goto yy31;
	goto yy10;
yy33:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= 0x001F) {
		if (yych == '\t') goto yy31;
		goto yy10;
	} else {
		if (yych <= ' ') goto yy31;
		if (yych == '=') goto yy33;
		goto yy10;
	}
yy35:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych == '+') goto yy35;
#line 189 "_mwscan.re"
	{
		if (tablemode) 
			RET(t_tablecaption);
		if (*start==' ') {
			cursor = start+1;
			RET(t_pre);
		}
		RET(t_text);
	}
#line 344 "_mwscan.cc"
yy38:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych == '-') goto yy38;
#line 166 "_mwscan.re"
	{
		if (tablemode) 
			RET(t_row);
		if (*start==' ') {
			cursor = start+1;
			RET(t_pre);
		}
		RET(t_text);
	}
#line 359 "_mwscan.cc"
yy41:
	++YYCURSOR;
#line 163 "_mwscan.re"
	{--tablemode; RET(t_end_table);}
#line 364 "_mwscan.cc"
yy43:
	++YYCURSOR;
#line 162 "_mwscan.re"
	{++tablemode; RET(t_begin_table);}
#line 369 "_mwscan.cc"
yy45:
	yych = *++YYCURSOR;
	if (yych <= ',') {
		if (yych == '+') goto yy35;
		goto yy7;
	} else {
		if (yych <= '-') goto yy38;
		if (yych == '}') goto yy41;
		goto yy7;
	}
yy46:
	++YYCURSOR;
	yych = *YYCURSOR;
yy47:
	if (yych <= '!') {
		if (yych <= 0x001F) goto yy20;
		if (yych <= ' ') goto yy46;
	} else {
		if (yych <= 'z') goto yy20;
		if (yych <= '{') goto yy49;
		if (yych <= '|') goto yy45;
		goto yy20;
	}
	yych = *++YYCURSOR;
	goto yy7;
yy49:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '|') goto yy43;
	goto yy20;
}
#line 210 "_mwscan.re"



not_bol:
	cursor = save_cursor;
	marker = cursor;


#line 409 "_mwscan.cc"
{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	yych = *YYCURSOR;
	if (yych <= 'Z') {
		if (yych <= '\'') {
			if (yych <= ' ') {
				if (yych <= 0x0000) goto yy72;
				if (yych == '\n') goto yy63;
				goto yy74;
			} else {
				if (yych <= '!') goto yy66;
				if (yych <= '%') goto yy74;
				if (yych <= '&') goto yy71;
				goto yy69;
			}
		} else {
			if (yych <= ';') {
				if (yych <= '/') goto yy74;
				if (yych <= '9') goto yy59;
				if (yych <= ':') goto yy68;
				goto yy74;
			} else {
				if (yych <= '<') goto yy70;
				if (yych <= '=') goto yy61;
				if (yych <= '@') goto yy74;
				goto yy59;
			}
		}
	} else {
		if (yych <= 'f') {
			if (yych <= '^') {
				if (yych <= '[') goto yy52;
				if (yych == ']') goto yy60;
				goto yy74;
			} else {
				if (yych <= '_') goto yy58;
				if (yych <= '`') goto yy74;
				if (yych <= 'e') goto yy59;
				goto yy56;
			}
		} else {
			if (yych <= 'm') {
				if (yych == 'h') goto yy57;
				if (yych <= 'l') goto yy59;
				goto yy54;
			} else {
				if (yych <= 'z') goto yy59;
				if (yych == '|') goto yy65;
				goto yy74;
			}
		}
	}
yy52:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case '[':	goto yy249;
	case 'f':	goto yy252;
	case 'h':	goto yy251;
	case 'm':	goto yy253;
	default:	goto yy53;
	}
yy53:
#line 256 "_mwscan.re"
	{RET(t_special);}
#line 476 "_mwscan.cc"
yy54:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == 'a') goto yy237;
	goto yy121;
yy55:
#line 225 "_mwscan.re"
	{RET(t_text);}
#line 484 "_mwscan.cc"
yy56:
	yych = *++YYCURSOR;
	if (yych == 't') goto yy229;
	goto yy121;
yy57:
	yych = *++YYCURSOR;
	if (yych == 't') goto yy219;
	goto yy121;
yy58:
	yych = *++YYCURSOR;
	if (yych == '_') goto yy122;
	goto yy121;
yy59:
	yych = *++YYCURSOR;
	goto yy121;
yy60:
	yych = *++YYCURSOR;
	if (yych == ']') goto yy118;
	goto yy53;
yy61:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '=') goto yy116;
	goto yy115;
yy62:
#line 228 "_mwscan.re"
	{
			if (eol()) {
			        if (line_startswith_section>=0) {
				     line_startswith_section=-1;
				     RET(t_section_end);
                                } else {
				     RET(t_text);
                                }
			} else {
				RET(t_text);
			}
		    }
#line 522 "_mwscan.cc"
yy63:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '\n') goto yy111;
#line 241 "_mwscan.re"
	{newline(); RET(t_newline);}
#line 528 "_mwscan.cc"
yy65:
	yych = *++YYCURSOR;
	if (yych <= '*') {
		if (yych == '!') goto yy107;
		goto yy53;
	} else {
		if (yych <= '+') goto yy109;
		if (yych == '|') goto yy107;
		goto yy53;
	}
yy66:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '!') goto yy107;
yy67:
#line 266 "_mwscan.re"
	{RET(t_text);}
#line 545 "_mwscan.cc"
yy68:
	yych = *++YYCURSOR;
	goto yy53;
yy69:
	yych = *++YYCURSOR;
	if (yych == '\'') goto yy102;
	goto yy67;
yy70:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') {
		if (yych == '!') goto yy86;
		if (yych <= '.') goto yy67;
		goto yy87;
	} else {
		if (yych <= 'Z') {
			if (yych <= '@') goto yy67;
			goto yy88;
		} else {
			if (yych <= '`') goto yy67;
			if (yych <= 'z') goto yy88;
			goto yy67;
		}
	}
yy71:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '9') {
		if (yych == '#') goto yy75;
		if (yych <= '/') goto yy67;
		goto yy77;
	} else {
		if (yych <= 'Z') {
			if (yych <= '@') goto yy67;
			goto yy77;
		} else {
			if (yych <= '`') goto yy67;
			if (yych <= 'z') goto yy77;
			goto yy67;
		}
	}
yy72:
	++YYCURSOR;
#line 265 "_mwscan.re"
	{newline(); return t_end;}
#line 591 "_mwscan.cc"
yy74:
	yych = *++YYCURSOR;
	goto yy67;
yy75:
	yych = *++YYCURSOR;
	if (yych <= 'W') {
		if (yych <= '/') goto yy76;
		if (yych <= '9') goto yy82;
	} else {
		if (yych <= 'X') goto yy81;
		if (yych == 'x') goto yy81;
	}
yy76:
	YYCURSOR = YYMARKER;
	if (yyaccept <= 1) {
		if (yyaccept <= 0) {
			goto yy53;
		} else {
			goto yy67;
		}
	} else {
		if (yyaccept <= 2) {
			goto yy103;
		} else {
			goto yy55;
		}
	}
yy77:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= ';') {
		if (yych <= '/') goto yy76;
		if (yych <= '9') goto yy77;
		if (yych <= ':') goto yy76;
	} else {
		if (yych <= 'Z') {
			if (yych <= '@') goto yy76;
			goto yy77;
		} else {
			if (yych <= '`') goto yy76;
			if (yych <= 'z') goto yy77;
			goto yy76;
		}
	}
yy79:
	++YYCURSOR;
#line 263 "_mwscan.re"
	{RET(t_entity);}
#line 640 "_mwscan.cc"
yy81:
	yych = *++YYCURSOR;
	if (yych == ';') goto yy76;
	goto yy85;
yy82:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '/') goto yy76;
	if (yych <= '9') goto yy82;
	if (yych == ';') goto yy79;
	goto yy76;
yy84:
	++YYCURSOR;
	yych = *YYCURSOR;
yy85:
	if (yych <= ';') {
		if (yych <= '/') goto yy76;
		if (yych <= '9') goto yy84;
		if (yych <= ':') goto yy76;
		goto yy79;
	} else {
		if (yych <= 'F') {
			if (yych <= '@') goto yy76;
			goto yy84;
		} else {
			if (yych <= '`') goto yy76;
			if (yych <= 'f') goto yy84;
			goto yy76;
		}
	}
yy86:
	yych = *++YYCURSOR;
	if (yych == '-') goto yy94;
	goto yy76;
yy87:
	yych = *++YYCURSOR;
	if (yych <= '@') goto yy76;
	if (yych <= 'Z') goto yy88;
	if (yych <= '`') goto yy76;
	if (yych >= '{') goto yy76;
yy88:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '>') {
		if (yych <= ';') {
			if (yych <= 0x0000) goto yy76;
		} else {
			if (yych <= '<') goto yy76;
			if (yych >= '>') goto yy92;
		}
	} else {
		if (yych <= 'Z') {
			if (yych >= 'A') goto yy88;
		} else {
			if (yych <= '`') goto yy90;
			if (yych <= 'z') goto yy88;
		}
	}
yy90:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '<') {
		if (yych <= 0x0000) goto yy76;
		if (yych <= ';') goto yy90;
		goto yy76;
	} else {
		if (yych != '>') goto yy90;
	}
yy92:
	++YYCURSOR;
#line 259 "_mwscan.re"
	{RET(t_html_tag);}
#line 713 "_mwscan.cc"
yy94:
	yych = *++YYCURSOR;
	if (yych != '-') goto yy76;
yy95:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= ';') {
		if (yych <= 0x0000) goto yy76;
		if (yych != '-') goto yy95;
	} else {
		if (yych == '=') goto yy95;
		if (yych <= '>') goto yy76;
		goto yy95;
	}
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= ';') {
		if (yych <= 0x0000) goto yy76;
		if (yych != '-') goto yy95;
	} else {
		if (yych == '=') goto yy95;
		if (yych <= '>') goto yy76;
		goto yy95;
	}
yy98:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= ';') {
		if (yych <= 0x0000) goto yy76;
		if (yych == '-') goto yy98;
		goto yy95;
	} else {
		if (yych <= '<') goto yy76;
		if (yych != '>') goto yy95;
	}
	++YYCURSOR;
#line 262 "_mwscan.re"
	{RET(t_comment);}
#line 752 "_mwscan.cc"
yy102:
	++YYCURSOR;
	if ((yych = *YYCURSOR) == '\'') goto yy104;
yy103:
#line 257 "_mwscan.re"
	{RET(t_style);}
#line 759 "_mwscan.cc"
yy104:
	yyaccept = 2;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != '\'') goto yy103;
	yych = *++YYCURSOR;
	if (yych != '\'') goto yy76;
	yych = *++YYCURSOR;
	goto yy103;
yy107:
	++YYCURSOR;
#line 243 "_mwscan.re"
	{
		if (tablemode) 
			RET(t_column);
		cursor = start+1;
		RET(t_special);
	}
#line 777 "_mwscan.cc"
yy109:
	++YYCURSOR;
#line 250 "_mwscan.re"
	{
		if (tablemode) 
			RET(t_tablecaption);
		cursor = start+1;
		RET(t_special);
	}
#line 787 "_mwscan.cc"
yy111:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych == '\n') goto yy111;
#line 240 "_mwscan.re"
	{newline(); RET(t_break);}
#line 794 "_mwscan.cc"
yy114:
	++YYCURSOR;
	yych = *YYCURSOR;
yy115:
	if (yych == '\t') goto yy114;
	if (yych == ' ') goto yy114;
	goto yy62;
yy116:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= 0x001F) {
		if (yych == '\t') goto yy114;
		goto yy62;
	} else {
		if (yych <= ' ') goto yy114;
		if (yych == '=') goto yy116;
		goto yy62;
	}
yy118:
	++YYCURSOR;
#line 227 "_mwscan.re"
	{RET(t_2box_close);}
#line 817 "_mwscan.cc"
yy120:
	++YYCURSOR;
	yych = *YYCURSOR;
yy121:
	if (yych <= 'Z') {
		if (yych <= '/') goto yy55;
		if (yych <= '9') goto yy120;
		if (yych <= '@') goto yy55;
		goto yy120;
	} else {
		if (yych <= '_') {
			if (yych <= '^') goto yy55;
			goto yy120;
		} else {
			if (yych <= '`') goto yy55;
			if (yych <= 'z') goto yy120;
			goto yy55;
		}
	}
yy122:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'E':	goto yy126;
	case 'F':	goto yy125;
	case 'N':	goto yy124;
	case 'S':	goto yy127;
	case 'T':	goto yy123;
	default:	goto yy121;
	}
yy123:
	yych = *++YYCURSOR;
	if (yych == 'O') goto yy216;
	goto yy121;
yy124:
	yych = *++YYCURSOR;
	if (yych == 'E') goto yy146;
	if (yych == 'O') goto yy147;
	goto yy121;
yy125:
	yych = *++YYCURSOR;
	if (yych == 'O') goto yy138;
	goto yy121;
yy126:
	yych = *++YYCURSOR;
	if (yych == 'N') goto yy135;
	goto yy121;
yy127:
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'A') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'R') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
yy133:
	++YYCURSOR;
	if ((yych = *YYCURSOR) <= 'Z') {
		if (yych <= '/') goto yy134;
		if (yych <= '9') goto yy120;
		if (yych >= 'A') goto yy120;
	} else {
		if (yych <= '_') {
			if (yych >= '_') goto yy120;
		} else {
			if (yych <= '`') goto yy134;
			if (yych <= 'z') goto yy120;
		}
	}
yy134:
#line 224 "_mwscan.re"
	{RET(t_magicword);}
#line 894 "_mwscan.cc"
yy135:
	yych = *++YYCURSOR;
	if (yych != 'D') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy138:
	yych = *++YYCURSOR;
	if (yych != 'R') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'O') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy146:
	yych = *++YYCURSOR;
	if (yych == 'W') goto yy203;
	goto yy121;
yy147:
	yych = *++YYCURSOR;
	switch (yych) {
	case 'C':	goto yy150;
	case 'E':	goto yy149;
	case 'G':	goto yy151;
	case 'T':	goto yy148;
	default:	goto yy121;
	}
yy148:
	yych = *++YYCURSOR;
	if (yych <= 'H') {
		if (yych == 'C') goto yy186;
		goto yy121;
	} else {
		if (yych <= 'I') goto yy187;
		if (yych == 'O') goto yy188;
		goto yy121;
	}
yy149:
	yych = *++YYCURSOR;
	if (yych == 'D') goto yy175;
	goto yy121;
yy150:
	yych = *++YYCURSOR;
	if (yych == 'C') goto yy159;
	if (yych == 'O') goto yy160;
	goto yy121;
yy151:
	yych = *++YYCURSOR;
	if (yych != 'A') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'L') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'L') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'R') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'Y') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy159:
	yych = *++YYCURSOR;
	if (yych == '_') goto yy174;
	goto yy121;
yy160:
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'O') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'V') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'R') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy174:
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy175:
	yych = *++YYCURSOR;
	if (yych != 'I') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'S') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'I') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'O') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy186:
	yych = *++YYCURSOR;
	if (yych == '_') goto yy202;
	goto yy121;
yy187:
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy191;
	goto yy121;
yy188:
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy191:
	yych = *++YYCURSOR;
	if (yych != 'L') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'O') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'V') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'R') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy202:
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy203:
	yych = *++YYCURSOR;
	if (yych != 'S') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'E') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'T') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'I') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'O') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'L') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'I') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'N') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'K') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy216:
	yych = *++YYCURSOR;
	if (yych != 'C') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '_') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '_') goto yy133;
	goto yy121;
yy219:
	yych = *++YYCURSOR;
	if (yych != 't') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'p') goto yy121;
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych == ':') goto yy223;
	if (yych != 's') goto yy121;
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != ':') goto yy121;
yy223:
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych <= '_') {
		if (yych <= ':') {
			if (yych <= '&') {
				if (yych == '#') goto yy226;
				if (yych <= '$') goto yy76;
			} else {
				if (yych <= '\'') goto yy76;
				if (yych == '*') goto yy76;
			}
		} else {
			if (yych <= '?') {
				if (yych == '=') goto yy226;
				if (yych <= '>') goto yy76;
			} else {
				if (yych <= '@') goto yy76;
				if (yych <= 'Z') goto yy226;
				if (yych <= '^') goto yy76;
			}
		}
	} else {
		if (yych <= 0x00D6) {
			if (yych <= '~') {
				if (yych <= '`') goto yy76;
				if (yych <= 'z') goto yy226;
				if (yych <= '}') goto yy76;
			} else {
				if (yych == 0x00C4) goto yy226;
				if (yych <= 0x00D5) goto yy76;
			}
		} else {
			if (yych <= 0x00E4) {
				if (yych == 0x00DC) goto yy226;
				if (yych <= 0x00E3) goto yy76;
			} else {
				if (yych <= 0x00F6) {
					if (yych <= 0x00F5) goto yy76;
				} else {
					if (yych != 0x00FC) goto yy76;
				}
			}
		}
	}
yy226:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '_') {
		if (yych <= ':') {
			if (yych <= '&') {
				if (yych == '#') goto yy226;
				if (yych >= '%') goto yy226;
			} else {
				if (yych <= '\'') goto yy228;
				if (yych != '*') goto yy226;
			}
		} else {
			if (yych <= '?') {
				if (yych == '=') goto yy226;
				if (yych >= '?') goto yy226;
			} else {
				if (yych <= '@') goto yy228;
				if (yych <= 'Z') goto yy226;
				if (yych >= '_') goto yy226;
			}
		}
	} else {
		if (yych <= 0x00D6) {
			if (yych <= '~') {
				if (yych <= '`') goto yy228;
				if (yych <= 'z') goto yy226;
				if (yych >= '~') goto yy226;
			} else {
				if (yych == 0x00C4) goto yy226;
				if (yych >= 0x00D6) goto yy226;
			}
		} else {
			if (yych <= 0x00E4) {
				if (yych == 0x00DC) goto yy226;
				if (yych >= 0x00E4) goto yy226;
			} else {
				if (yych <= 0x00F6) {
					if (yych >= 0x00F6) goto yy226;
				} else {
					if (yych == 0x00FC) goto yy226;
				}
			}
		}
	}
yy228:
#line 223 "_mwscan.re"
	{RET(t_http_url);}
#line 1221 "_mwscan.cc"
yy229:
	yych = *++YYCURSOR;
	if (yych != 'p') goto yy121;
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != ':') goto yy121;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych <= '=') {
		if (yych <= '&') {
			if (yych <= '"') goto yy76;
			if (yych == '%') goto yy76;
		} else {
			if (yych <= '\'') goto yy76;
			if (yych <= ':') goto yy234;
			if (yych <= '<') goto yy76;
		}
	} else {
		if (yych <= '_') {
			if (yych <= '>') goto yy76;
			if (yych <= 'Z') goto yy234;
			if (yych <= '^') goto yy76;
		} else {
			if (yych <= '{') {
				if (yych <= '`') goto yy76;
			} else {
				if (yych <= '|') goto yy76;
				if (yych >= 0x007F) goto yy76;
			}
		}
	}
yy234:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '=') {
		if (yych <= '&') {
			if (yych <= '"') goto yy236;
			if (yych != '%') goto yy234;
		} else {
			if (yych <= '\'') goto yy236;
			if (yych <= ':') goto yy234;
			if (yych >= '=') goto yy234;
		}
	} else {
		if (yych <= '_') {
			if (yych <= '>') goto yy236;
			if (yych <= 'Z') goto yy234;
			if (yych >= '_') goto yy234;
		} else {
			if (yych <= '{') {
				if (yych >= 'a') goto yy234;
			} else {
				if (yych <= '|') goto yy236;
				if (yych <= '~') goto yy234;
			}
		}
	}
yy236:
#line 221 "_mwscan.re"
	{RET(t_http_url);}
#line 1285 "_mwscan.cc"
yy237:
	yych = *++YYCURSOR;
	if (yych != 'i') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'l') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 't') goto yy121;
	yych = *++YYCURSOR;
	if (yych != 'o') goto yy121;
	yyaccept = 3;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych != ':') goto yy121;
	yych = *++YYCURSOR;
	if (yych == '@') goto yy76;
	goto yy244;
yy243:
	++YYCURSOR;
	yych = *YYCURSOR;
yy244:
	if (yych <= '9') {
		if (yych <= '\'') {
			if (yych == '!') goto yy243;
			if (yych <= '"') goto yy76;
			goto yy243;
		} else {
			if (yych <= ')') goto yy76;
			if (yych == ',') goto yy76;
			goto yy243;
		}
	} else {
		if (yych <= '?') {
			if (yych == '=') goto yy243;
			if (yych <= '>') goto yy76;
			goto yy243;
		} else {
			if (yych <= 'Z') {
				if (yych >= 'A') goto yy243;
			} else {
				if (yych <= ']') goto yy76;
				if (yych <= '~') goto yy243;
				goto yy76;
			}
		}
	}
	yych = *++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '.') {
			if (yych <= ',') goto yy76;
		} else {
			if (yych <= '/') goto yy76;
			if (yych >= ':') goto yy76;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy246;
			if (yych <= '^') goto yy76;
		} else {
			if (yych <= '`') goto yy76;
			if (yych >= '{') goto yy76;
		}
	}
yy246:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '@') {
		if (yych <= '.') {
			if (yych >= '-') goto yy246;
		} else {
			if (yych <= '/') goto yy248;
			if (yych <= '9') goto yy246;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy246;
			if (yych >= '_') goto yy246;
		} else {
			if (yych <= '`') goto yy248;
			if (yych <= 'z') goto yy246;
		}
	}
yy248:
#line 219 "_mwscan.re"
	{RET(t_http_url);}
#line 1369 "_mwscan.cc"
yy249:
	++YYCURSOR;
#line 226 "_mwscan.re"
	{RET(t_2box_open);}
#line 1374 "_mwscan.cc"
yy251:
	yych = *++YYCURSOR;
	if (yych == 't') goto yy274;
	goto yy76;
yy252:
	yych = *++YYCURSOR;
	if (yych == 't') goto yy266;
	goto yy76;
yy253:
	yych = *++YYCURSOR;
	if (yych != 'a') goto yy76;
	yych = *++YYCURSOR;
	if (yych != 'i') goto yy76;
	yych = *++YYCURSOR;
	if (yych != 'l') goto yy76;
	yych = *++YYCURSOR;
	if (yych != 't') goto yy76;
	yych = *++YYCURSOR;
	if (yych != 'o') goto yy76;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy76;
	yych = *++YYCURSOR;
	if (yych == '@') goto yy76;
	goto yy261;
yy260:
	++YYCURSOR;
	yych = *YYCURSOR;
yy261:
	if (yych <= '9') {
		if (yych <= '\'') {
			if (yych == '!') goto yy260;
			if (yych <= '"') goto yy76;
			goto yy260;
		} else {
			if (yych <= ')') goto yy76;
			if (yych == ',') goto yy76;
			goto yy260;
		}
	} else {
		if (yych <= '?') {
			if (yych == '=') goto yy260;
			if (yych <= '>') goto yy76;
			goto yy260;
		} else {
			if (yych <= 'Z') {
				if (yych >= 'A') goto yy260;
			} else {
				if (yych <= ']') goto yy76;
				if (yych <= '~') goto yy260;
				goto yy76;
			}
		}
	}
	yych = *++YYCURSOR;
	if (yych <= '@') {
		if (yych <= '.') {
			if (yych <= ',') goto yy76;
		} else {
			if (yych <= '/') goto yy76;
			if (yych >= ':') goto yy76;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy263;
			if (yych <= '^') goto yy76;
		} else {
			if (yych <= '`') goto yy76;
			if (yych >= '{') goto yy76;
		}
	}
yy263:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '@') {
		if (yych <= '.') {
			if (yych >= '-') goto yy263;
		} else {
			if (yych <= '/') goto yy265;
			if (yych <= '9') goto yy263;
		}
	} else {
		if (yych <= '_') {
			if (yych <= 'Z') goto yy263;
			if (yych >= '_') goto yy263;
		} else {
			if (yych <= '`') goto yy265;
			if (yych <= 'z') goto yy263;
		}
	}
yy265:
#line 218 "_mwscan.re"
	{RET(t_urllink);}
#line 1467 "_mwscan.cc"
yy266:
	yych = *++YYCURSOR;
	if (yych != 'p') goto yy76;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy76;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych <= '=') {
		if (yych <= '&') {
			if (yych <= '"') goto yy76;
			if (yych == '%') goto yy76;
		} else {
			if (yych <= '\'') goto yy76;
			if (yych <= ':') goto yy271;
			if (yych <= '<') goto yy76;
		}
	} else {
		if (yych <= '_') {
			if (yych <= '>') goto yy76;
			if (yych <= 'Z') goto yy271;
			if (yych <= '^') goto yy76;
		} else {
			if (yych <= '{') {
				if (yych <= '`') goto yy76;
			} else {
				if (yych <= '|') goto yy76;
				if (yych >= 0x007F) goto yy76;
			}
		}
	}
yy271:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '=') {
		if (yych <= '&') {
			if (yych <= '"') goto yy273;
			if (yych != '%') goto yy271;
		} else {
			if (yych <= '\'') goto yy273;
			if (yych <= ':') goto yy271;
			if (yych >= '=') goto yy271;
		}
	} else {
		if (yych <= '_') {
			if (yych <= '>') goto yy273;
			if (yych <= 'Z') goto yy271;
			if (yych >= '_') goto yy271;
		} else {
			if (yych <= '{') {
				if (yych >= 'a') goto yy271;
			} else {
				if (yych <= '|') goto yy273;
				if (yych <= '~') goto yy271;
			}
		}
	}
yy273:
#line 220 "_mwscan.re"
	{RET(t_urllink);}
#line 1530 "_mwscan.cc"
yy274:
	yych = *++YYCURSOR;
	if (yych != 't') goto yy76;
	yych = *++YYCURSOR;
	if (yych != 'p') goto yy76;
	yych = *++YYCURSOR;
	if (yych == ':') goto yy278;
	if (yych != 's') goto yy76;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy76;
yy278:
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych != '/') goto yy76;
	yych = *++YYCURSOR;
	if (yych <= '_') {
		if (yych <= ':') {
			if (yych <= '&') {
				if (yych == '#') goto yy281;
				if (yych <= '$') goto yy76;
			} else {
				if (yych <= '\'') goto yy76;
				if (yych == '*') goto yy76;
			}
		} else {
			if (yych <= '?') {
				if (yych == '=') goto yy281;
				if (yych <= '>') goto yy76;
			} else {
				if (yych <= '@') goto yy76;
				if (yych <= 'Z') goto yy281;
				if (yych <= '^') goto yy76;
			}
		}
	} else {
		if (yych <= 0x00D6) {
			if (yych <= '~') {
				if (yych <= '`') goto yy76;
				if (yych <= 'z') goto yy281;
				if (yych <= '}') goto yy76;
			} else {
				if (yych == 0x00C4) goto yy281;
				if (yych <= 0x00D5) goto yy76;
			}
		} else {
			if (yych <= 0x00E4) {
				if (yych == 0x00DC) goto yy281;
				if (yych <= 0x00E3) goto yy76;
			} else {
				if (yych <= 0x00F6) {
					if (yych <= 0x00F5) goto yy76;
				} else {
					if (yych != 0x00FC) goto yy76;
				}
			}
		}
	}
yy281:
	++YYCURSOR;
	yych = *YYCURSOR;
	if (yych <= '_') {
		if (yych <= ':') {
			if (yych <= '&') {
				if (yych == '#') goto yy281;
				if (yych >= '%') goto yy281;
			} else {
				if (yych <= '\'') goto yy283;
				if (yych != '*') goto yy281;
			}
		} else {
			if (yych <= '?') {
				if (yych == '=') goto yy281;
				if (yych >= '?') goto yy281;
			} else {
				if (yych <= '@') goto yy283;
				if (yych <= 'Z') goto yy281;
				if (yych >= '_') goto yy281;
			}
		}
	} else {
		if (yych <= 0x00D6) {
			if (yych <= '~') {
				if (yych <= '`') goto yy283;
				if (yych <= 'z') goto yy281;
				if (yych >= '~') goto yy281;
			} else {
				if (yych == 0x00C4) goto yy281;
				if (yych >= 0x00D6) goto yy281;
			}
		} else {
			if (yych <= 0x00E4) {
				if (yych == 0x00DC) goto yy281;
				if (yych >= 0x00E4) goto yy281;
			} else {
				if (yych <= 0x00F6) {
					if (yych >= 0x00F6) goto yy281;
				} else {
					if (yych == 0x00FC) goto yy281;
				}
			}
		}
	}
yy283:
#line 222 "_mwscan.re"
	{RET(t_urllink);}
#line 1637 "_mwscan.cc"
}
#line 267 "_mwscan.re"

}


PyObject *py_scan(PyObject *self, PyObject *args) 
{
	PyObject *arg1;
	if (!PyArg_ParseTuple(args, "O:mwscan.scan", &arg1)) {
		return 0;
	}
	PyUnicodeObject *unistr = (PyUnicodeObject*)PyUnicode_FromObject(arg1);
	if (unistr == NULL) {
		PyErr_SetString(PyExc_TypeError,
				"parameter cannot be converted to unicode in mwscan.scan");
		return 0;
	}

	Py_UNICODE *start = unistr->str;
	Py_UNICODE *end = start+unistr->length;
	

	Scanner scanner (start, end);
	Py_BEGIN_ALLOW_THREADS
	while (scanner.scan()) {
	}
	Py_END_ALLOW_THREADS
	Py_XDECREF(unistr);
	
	// return PyList_New(0); // uncomment to see timings for scanning

	int size = scanner.tokens.size();
	PyObject *result = PyList_New(size);
	if (!result) {
		return 0;
	}
	
	for (int i=0; i<size; i++) {
		Token t = scanner.tokens[i];
		PyList_SET_ITEM(result, i, Py_BuildValue("iii", t.type, t.start, t.len));
	}
	
	return result;
}



static PyMethodDef module_functions[] = {
	{"scan", (PyCFunction)py_scan, METH_VARARGS, "scan(text)"},
	{0, 0},
};



extern "C" {
	DL_EXPORT(void) init_mwscan();
}

DL_EXPORT(void) init_mwscan()
{
	/*PyObject *m =*/ Py_InitModule("_mwscan", module_functions);
}
