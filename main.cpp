#include "token.h"

// Token getToken();

// Token_stream ts = {};

int main(int, char**) {
    try
    {
        double val = 0;
        while(cin)
        {
            Token t = ts.get();

            if(t.kind == 'q') break;
            if(t.kind == ';')
                cout<<"="<<val<<'\n';
            else
                ts.putback(t);
            val = expression();
        }
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr <<"runtime error: "<< e.what() << '\n';
    }
}

