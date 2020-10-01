#include <iostream>

int main() {
    int x;
    while(std::cin>>x){
         unsigned int y =
                ((0x000000FF & x) << 24 ) |
                ((0x0000FF00 & x) << 8  ) |
                ((0x00FF0000 & x) >> 8  ) |
                ((0xFF000000 & x) >> 24 );
         std::cout << x << " converts to " << (int)y << std::endl;
    }
    return 0;
}