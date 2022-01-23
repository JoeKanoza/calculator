#include <token.h>

// Token getToken();

// Token_stream ts = {};

int main(int, char**) {
    try
    {
        double val = 0;
        while(cin)
        {
            cout << "> ";
            Token t = ts.get();
            while(t.kind == ';') t=ts.get();        // eat ';'
            if(t.kind == 'q') {
                keep_window_open();
                return 0;
            }
            ts.putback(t);
            cout<<"= "<<expression()<<'\n';
        }
        keep_window_open();
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

