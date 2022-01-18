// Generate PPM #1
// A simple program that generates a .ppm, .txt, and prints the ppm to the console

# include <fstream>
# include <iostream>

using namespace std ;

int main() {
    ofstream myPPM ;
    ofstream textPPM ;
    myPPM.open( "example.ppm" ) ;
    textPPM.open( "example.txt" ) ;

    int nx = 200 ;
    int ny = 100 ;

    myPPM   << "P3\n" << nx << " " << ny << "\n255\n" ;
    textPPM << "P3\n" << nx << " " << ny << "\n255\n" ;
    cout    << "P3\n" << nx << " " << ny << "\n255\n" ;

    for ( int j = ny - 1 ; j >= 0 ; j-- ){
        for ( int i = 0 ; i < nx ; i++ ){
            float r = float( i ) / float( nx ) ;
            float g = float( j ) / float( ny ) ;
            float b = 0.2 ;
            
            int ir = int( 255.99 * r ) ;
            int ig = int( 255.99 * g ) ;
            int ib = int( 255.99 * b ) ;
            
            myPPM << ir << " " << ig << " " << ib << "\n" ;
            textPPM << ir << " " << ig << " " << ib << "\n" ;
            cout << ir << " " << ig << " " << ib << "\n" ;
            
        }
    }
    
    textPPM.close() ;
    myPPM.close() ;

    return 0 ;
}