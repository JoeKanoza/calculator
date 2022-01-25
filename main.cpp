#include <token.h>

// Token getToken();

// Token_stream ts = {};

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

