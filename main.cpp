#include "token.h"
#include "token_stream.h"

// Token getToken();

Token_stream ts = {};

int main(int, char**) {
    try
    {
        calculate();
        // keep_window_open();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr <<"runtime error: "<< e.what() << '\n';
        keep_window_open("~~");
        return 1;
    }
    catch(...)
    {
        cerr<<"exception \n";
        keep_window_open("~~");
        return 2;
    }
}

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
	case number:		// we use '8' to represent a number
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
					if(d ==0) error("% divided by zero");
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

void calculate()
{
	while(cin)
		try
		{
			cout << prompt;
			Token t = ts.get();
			while(t.kind == print) t=ts.get();        // eat ';'
			if(t.kind == quit) {
				// keep_window_open();
				return;
			}
			ts.putback(t);
			cout<<result<<expression()<<'\n';
		}
		catch(exception& e)
		{
			cerr<<e.what()<<'\n';
			clean_up_mess();
		}
}

void clean_up_mess()
{
	ts.ignore(print);
}

