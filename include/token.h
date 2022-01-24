/*
 * ===========================================================================
 *
 *       Filename:  token.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  Fri Dec 24 2021
 *       Revision:
 *       Compiler:
 *
 *         Author:  Joe Kanoza
 *   Organization:  ${ORG}
 *
 * ===========================================================================
 */

#pragma once

double primary();
double term();
double expression();


// user-defined type to handle tokens
class Token {
	public:
		char kind; 	//what kind of token
		double value;	//for numbers: a value
		Token(char k) :kind{k}, value{0.0} {}	// construct from one value
		Token(char k, double v) :kind{k}, value{v} {}	// construct from two values
};

class Token_stream {
	public:
		Token_stream();
		Token get();
		void putback(Token t);

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
        case ';':
        case 'q':
        case '(': case ')': case '+': case '-': case '*': case '/':
		case '{': case '}': case '!': case '%':
            return Token{ch};
        case '.':
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);
            double val;
            cin>>val;
            return Token{'8',val};
        }
        default:
            error("Bad token");
    }
}

void Token_stream::putback(Token t)
{
	if(full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '{':
		{
			double d = expression();
			t = ts.get();
			if(t.kind != '}') error("'}' expected");
			return d;
		}
	case '(':
		{
			double d = expression();
			t = ts.get();
			if(t.kind != ')') error("')' expected");
			return d;
		}
	case '8':		// we use '8' to represent a number
		{
			double d = t.value;
			t = ts.get();

			if(t.kind == '!')
			{
				int sum = narrow_cast<int>(d);
				if(sum==0) return 1;
				for(int i = sum-1; i > 0; --i)
				{
					sum *= i;
				}
				return sum;
			}
			else
			{
				ts.putback(t);
				return d;		// return the number's value
			}
		}
	case '-':
		return - primary();
	case '+':
		return primary();

	default:
		error("primary expected");
	}
}

// double factorial()
// {
// 	double left = primary();
// }

double term()
{
	double left = primary();
	Token t = ts.get(); 			// get the next Token from the Token stream

	while (true)
	{
		switch(t.kind)
		{
			case '*':
				left *= primary();
				t = ts.get();
				break;

			case '/':
				{
					double d = primary();
					if(d == 0) error("divide by zero");
					left /= d;
					t = ts.get();
					break;
				}

			case '%':
				{
					double d = primary();
					if(d ==0) error("\% divided by zero");
					left = fmod(left, d);
					t=ts.get();
					break;
				}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double expression()
{
	double left = term();	// read and evaluate a Term
	Token t = ts.get();		// get the next Token from the Token stream

	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();		// evaluate Term and add
			t = ts.get();
			break;

		case '-':
			left-= term();		// evaluate Term and subtract
			t = ts.get();
			break;

		default:
			ts.putback(t); 	// put t back into the token stream
			return left;	// finally: no more + or -; return the answer
		}
	}
}

