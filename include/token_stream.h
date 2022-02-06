/*
 * ===========================================================================
 *
 *       Filename:  token_stream.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Wed Jan 26 2022
 *       Revision:
 *       Compiler:
 *
 *         Author:  Joe Kanoza
 *   Organization:  ${ORG}
 *
 * ===========================================================================
 */

#pragma once


class Token_stream {
	public:
		Token_stream();
		Token get();
		void putback(Token t);
		void ignore(char c);

	private:
		bool full {false};		// is there a Token in the buffer?
		Token buffer {0};		//putback() save uts token here
};

Token_stream::Token_stream()
	:full(false), buffer(0)
{
}

Token Token_stream::get()
{
	if(full)
	{
		full = false;
		return buffer;
	}
    char ch;
    cin>>ch;
    switch(ch){
        case print:
        case quit:
        case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '{':
		case '}':
		case '!':
		case '%':
		case '=':
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin>>val;
            return Token{number,val};
        }
        default:
			if(isalpha(ch))
			{
				string s;
				s += ch;
				while(cin.get(ch)&& (isalpha(ch)||isdigit(ch))) s+=ch;
				cin.putback(ch);
				if(s == declkey) return Token(let); 	//declaration keyword
				if(s == sqrtkey) return Token(sqrt_char);
				return Token{name,s};
			}
        error("Bad token");
    }
	return 0;
}

void Token_stream::putback(Token t)
{
	if(full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)
// c represents the kind of token.
{
	// look first in buffer
	if(full && c==buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	// search for input
	char ch = 0;
	while(cin>>ch)
		if(ch==c)return;
}
