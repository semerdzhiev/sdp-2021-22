#include <iostream>
#include <string>

using namespace std;

class Internet {
public:
    virtual void connectTo(string url) = 0;
};

class RealInternet : Internet {
public:
    void connectTo(string url) {
        cout << "Connecting to " << url << endl;
    }
};

class ProxyInternet : Internet {
    RealInternet realInternet;

public:
    void connectTo(string url) {
        if (url == "ijk.com" || url == "sdf.com") {
            throw "Connection declined";
        }

        realInternet.connectTo(url);
    }
};

int main()
{
    ProxyInternet p;
    p.connectTo("ijk.com");

    return 0;
}
