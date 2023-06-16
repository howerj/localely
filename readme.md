# LOCALELY

* Author: Richard James Howe
* License: The Unlicense
* Email: <mailto:howe.r.j.89@gmail.com>
* Repo: <https:/github.com/howerj/localely>

This project contains a set of locale independent version of
the functions found within "ctype.h". It is a 
[header only library](https://en.wikipedia.org/wiki/Header-only) (which
all the cool kids are using) that should compile within [C](https://en.wikipedia.org/wiki/C_(programming_language))
and [C++](https://en.wikipedia.org/wiki/C%2B%2B). There are
no external dependencies expect for "assert.h" (asserts
can be disabled with the [NDEBUG macro](https://en.cppreference.com/w/c/error/assert))
unless unit tests are defined.

# API

The following functions are defined:

	extern int C_isascii(const int ch);
	extern int C_isspace(const int ch);
	extern int C_iscntrl(const int ch);
	extern int C_isprint(const int ch);
	extern int C_isblank(const int ch);
	extern int C_isgraph(const int ch);
	extern int C_isupper(const int ch);
	extern int C_islower(const int ch);
	extern int C_isalpha(const int ch);
	extern int C_isdigit(const int ch);
	extern int C_isalnum(const int ch);
	extern int C_ispunct(const int ch);
	extern int C_isxdigit(const int ch);

Which behave like their C standard library counterparts expect they
are not locale dependent and only operate on
[ASCII](https://en.wikipedia.org/wiki/ASCII)/Bytes.

The functions return true (1) if "ch" is within the
class of characters the function name covers and false
(0) otherwise. The original functions in "ctype.h"
return non-zero for a match and zero on non-match.

Optionally available are the functions:

	extern int localely_unit_tests(void);
	int main(void);

Which can be used to conduct unit tests to check the
functionality of the defined functions in a functional
manner and should function. FUNCTION.

"localely\_unit\_tests", if defined, returns zero on success
and negative on failure.

The following table, constructed at great expense and cost
to human life, should help, or at least, it shouldn't hinder
nor hurt you in anyway.

        +----------------------------------+-----------------+------------------------------------------------------------------------------------------------+
        |          ASCII values            |                 |                                                                                                |
        +---------+------------+-----------+   Characters    +-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        |   DEC   |     HEX    |    OCT    |                 | cntrl | print | space | blank | graph | punct | alnum | alpha | upper | lower | digit | xdigit |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 0-8     | \x0-\x8    | \0-\10    | Control codes   |   x   |       |       |       |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 9       | \x9        | \11       | Tab             |   x   |       |   x   |   x   |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 10-13   | \xA-\xD    | \12-\15   | White-space     |   x   |       |   x   |       |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 14-31   | \xE-\x1F   | \16-\37   | Control codes   |   x   |       |       |       |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 32      | \x20       | \40       | Space           |       |   x   |   x   |   x   |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 33-47   | \x21-\x2F  | \41-\57   | !"#$%&'()*+,-./ |       |   x   |       |       |   x   |   x   |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 48-57   | \x30-\x39  | \60-\71   | 0123456789      |       |   x   |       |       |   x   |       |   x   |       |       |       |   x   |   x    |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 58-64   | \x3A-\x40  | \72-\100  | :;<=>?@         |       |   x   |       |       |   x   |   x   |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 65-70   | \x41-\x46  | \101-\106 | ABCDEF          |       |   x   |       |       |   x   |       |   x   |   x   |   x   |       |       |   x    |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 71-90   | \x47-\x5A  | \107-\132 | G to Z          |       |   x   |       |       |   x   |       |   x   |   x   |   x   |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 91-96   | \x5B-\x60  | \133-\140 | [\]^_`          |       |   x   |       |       |   x   |   x   |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 97-102  | \x61-\x66  | \141-\146 | abcdef          |       |   x   |       |       |   x   |       |   x   |   x   |       |   x   |       |   x    |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 103-122 | \x67-\x7A  | \147-\172 | g to z          |       |   x   |       |       |   x   |       |   x   |   x   |       |   x   |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 123-126 | \x7B-\x7E  | \173-\176 | {|}~            |       |   x   |       |       |   x   |   x   |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+
        | 127     | \x7F       | \177      | back sp. / DEL  |   x   |       |       |       |       |       |       |       |       |       |       |        |
        +---------+------------+-----------+-----------------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+--------+

If there is an 'x' is the table then "C\_isX()" returns '1', else
it returns '0'.

And here is an ASCII table for good measure:

        +-----+-----+-----+-------+---------------------------+
        | DEC | HEX | OCT | Glyph | Description               |
        +-----+-----+-----+-------+---------------------------+
        | 0   | 0   | 0   | NUL   | Null                      |
        | 1   | 1   | 1   | SOH   | Start of Header           |
        | 2   | 2   | 2   | STX   | Start of Text             |
        | 3   | 3   | 3   | ETX   | End of Text               |
        | 4   | 4   | 4   | EOT   | End of Transmission       |
        | 5   | 5   | 5   | ENQ   | Enquiry                   |
        | 6   | 6   | 6   | ACK   | Acknowledge               |
        | 7   | 7   | 7   | BEL   | Bell                      |
        | 8   | 8   | 10  | BS    | Backspace                 |
        | 9   | 9   | 11  | HT    | Horizontal Tab            |
        | 10  | a   | 12  | LF    | Line Feed                 |
        | 11  | b   | 13  | VT    | Vertical Tab              |
        | 12  | c   | 14  | FF    | Form Feed                 |
        | 13  | d   | 15  | CR    | Carriage Return           |
        | 14  | e   | 16  | SO    | Shift Out                 |
        | 15  | f   | 17  | SI    | Shift In                  |
        | 16  | 10  | 20  | DLE   | Data Link Escape          |
        | 17  | 11  | 21  | DC1   | Device Control 1          |
        | 18  | 12  | 22  | DC2   | Device Control 2          |
        | 19  | 13  | 23  | DC3   | Device Control 3          |
        | 20  | 14  | 24  | DC4   | Device Control 4          |
        | 21  | 15  | 25  | NAK   | Negative Acknowledge      |
        | 22  | 16  | 26  | SYN   | Synchronize               |
        | 23  | 17  | 27  | ETB   | End of Transmission Block |
        | 24  | 18  | 30  | CAN   | Cancel                    |
        | 25  | 19  | 31  | EM    | End of Medium             |
        | 26  | 1a  | 32  | SUB   | Substitute                |
        | 27  | 1b  | 33  | ESC   | Escape                    |
        | 28  | 1c  | 34  | FS    | File Separator            |
        | 29  | 1d  | 35  | GS    | Group Separator           |
        | 30  | 1e  | 36  | RS    | Record Separator          |
        | 31  | 1f  | 37  | US    | Unit Separator            |
        | 32  | 20  | 40  | space | Space                     |
        | 33  | 21  | 41  | !     | Exclamation mark          |
        | 34  | 22  | 42  | "     | Double quote              |
        | 35  | 23  | 43  | #     | Number                    |
        | 36  | 24  | 44  | $     | Dollar sign               |
        | 37  | 25  | 45  | %     | Percent                   |
        | 38  | 26  | 46  | &     | Ampersand                 |
        | 39  | 27  | 47  | '     | Single quote              |
        | 40  | 28  | 50  | (     | Left parenthesis          |
        | 41  | 29  | 51  | )     | Right parenthesis         |
        | 42  | 2a  | 52  | *     | Asterisk                  |
        | 43  | 2b  | 53  | +     | Plus                      |
        | 44  | 2c  | 54  | ,     | Comma                     |
        | 45  | 2d  | 55  | -     | Minus                     |
        | 46  | 2e  | 56  | .     | Period                    |
        | 47  | 2f  | 57  | /     | Slash                     |
        | 48  | 30  | 60  | 0     | Zero                      |
        | 49  | 31  | 61  | 1     | One                       |
        | 50  | 32  | 62  | 2     | Two                       |
        | 51  | 33  | 63  | 3     | Three                     |
        | 52  | 34  | 64  | 4     | Four                      |
        | 53  | 35  | 65  | 5     | Five                      |
        | 54  | 36  | 66  | 6     | Six                       |
        | 55  | 37  | 67  | 7     | Seven                     |
        | 56  | 38  | 70  | 8     | Eight                     |
        | 57  | 39  | 71  | 9     | Nine                      |
        | 58  | 3a  | 72  | :     | Colon                     |
        | 59  | 3b  | 73  | ;     | Semicolon                 |
        | 60  | 3c  | 74  | <     | Less than                 |
        | 61  | 3d  | 75  | =     | Equality sign             |
        | 62  | 3e  | 76  | >     | Greater than              |
        | 63  | 3f  | 77  | ?     | Question mark             |
        | 64  | 40  | 100 | @     | At sign                   |
        | 65  | 41  | 101 | A     | Capital A                 |
        | 66  | 42  | 102 | B     | Capital B                 |
        | 67  | 43  | 103 | C     | Capital C                 |
        | 68  | 44  | 104 | D     | Capital D                 |
        | 69  | 45  | 105 | E     | Capital E                 |
        | 70  | 46  | 106 | F     | Capital F                 |
        | 71  | 47  | 107 | G     | Capital G                 |
        | 72  | 48  | 110 | H     | Capital H                 |
        | 73  | 49  | 111 | I     | Capital I                 |
        | 74  | 4a  | 112 | J     | Capital J                 |
        | 75  | 4b  | 113 | K     | Capital K                 |
        | 76  | 4c  | 114 | L     | Capital L                 |
        | 77  | 4d  | 115 | M     | Capital M                 |
        | 78  | 4e  | 116 | N     | Capital N                 |
        | 79  | 4f  | 117 | O     | Capital O                 |
        | 80  | 50  | 120 | P     | Capital P                 |
        | 81  | 51  | 121 | Q     | Capital Q                 |
        | 82  | 52  | 122 | R     | Capital R                 |
        | 83  | 53  | 123 | S     | Capital S                 |
        | 84  | 54  | 124 | T     | Capital T                 |
        | 85  | 55  | 125 | U     | Capital U                 |
        | 86  | 56  | 126 | V     | Capital V                 |
        | 87  | 57  | 127 | W     | Capital W                 |
        | 88  | 58  | 130 | X     | Capital X                 |
        | 89  | 59  | 131 | Y     | Capital Y                 |
        | 90  | 5a  | 132 | Z     | Capital Z                 |
        | 91  | 5b  | 133 | [     | Left square bracket       |
        | 92  | 5c  | 134 | \     | Backslash                 |
        | 93  | 5d  | 135 | ]     | Right square bracket      |
        | 94  | 5e  | 136 | ^     | Caret / circumflex        |
        | 95  | 5f  | 137 | _     | Underscore                |
        | 96  | 60  | 140 | `     | Grave / accent            |
        | 97  | 61  | 141 | a     | Small a                   |
        | 98  | 62  | 142 | b     | Small b                   |
        | 99  | 63  | 143 | c     | Small c                   |
        | 100 | 64  | 144 | d     | Small d                   |
        | 101 | 65  | 145 | e     | Small e                   |
        | 102 | 66  | 146 | f     | Small f                   |
        | 103 | 67  | 147 | g     | Small g                   |
        | 104 | 68  | 150 | h     | Small h                   |
        | 105 | 69  | 151 | i     | Small i                   |
        | 106 | 6a  | 152 | j     | Small j                   |
        | 107 | 6b  | 153 | k     | Small k                   |
        | 108 | 6c  | 154 | l     | Small l                   |
        | 109 | 6d  | 155 | m     | Small m                   |
        | 110 | 6e  | 156 | n     | Small n                   |
        | 111 | 6f  | 157 | o     | Small o                   |
        | 112 | 70  | 160 | p     | Small p                   |
        | 113 | 71  | 161 | q     | Small q                   |
        | 114 | 72  | 162 | r     | Small r                   |
        | 115 | 73  | 163 | s     | Small s                   |
        | 116 | 74  | 164 | t     | Small t                   |
        | 117 | 75  | 165 | u     | Small u                   |
        | 118 | 76  | 166 | v     | Small v                   |
        | 119 | 77  | 167 | w     | Small w                   |
        | 120 | 78  | 170 | x     | Small x                   |
        | 121 | 79  | 171 | y     | Small y                   |
        | 122 | 7a  | 172 | z     | Small z                   |
        | 123 | 7b  | 173 | {     | Left curly bracket        |
        | 124 | 7c  | 174 | |     | Vertical bar              |
        | 125 | 7d  | 175 | }     | Right curly bracket       |
        | 126 | 7e  | 176 | ~     | Tilde                     |
        | 127 | 7f  | 177 | DEL   | Delete                    |
        +-----+-----+-----+-------+---------------------------+

# USAGE

The only complication in using this library is how to include
it in your project. In the C file you want to include this
module in you can:

	#include "localely.h"

	int my_amazing_c_code(int ch, struct city c) {
		if (C_isspace(ch))
			destroy(c);
		return 0;
	}
	
And in another C file, perhaps called "localely.c":

	#define LOCALELY_IMPLEMENTATION
	#include "localely.h"

Which will need linking into your project.

Alternatively you can include "localely.h" and define the
following:

	#define LOCALELY_API static inline
	#include "localely.h"

	int my_amazing_c_code(int ch, struct city c) {
		if (C_isspace(ch))
			destroy(c);
		return 0;
	}

And dispense with the separate C file, this makes all of
the C functions exported...static...and also inline, as
one might expect. This could bloat your project as multiple
definitions of the functions are defined.

To make an instance of the unit tests make a C file,
include the header and define the following:

	#define LOCALELY_UNIT_TESTS
	#define LOCALELY_DEFINE_MAIN
	#include "localely.h"

And compile the file, then run it at your own leisure,
run it again to see if it changes, contemplate existence
and perhaps run it a third time before going on holiday.

# LICENSE

This library is released into the Public Domain, or
The Unlicense, Do What Thou Wilt.

# BUGS

For all bugs, rants, and general musings and ravings
please contact me, no known bugs are currently known at
this time, only unknown bugs are known to exist.


