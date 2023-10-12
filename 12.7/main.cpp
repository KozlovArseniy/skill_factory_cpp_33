#include <iostream>
using std::cout, std::string, std::endl;


bool IsKPeriodic( const string& str, int k ){
    int str_size = static_cast<int>( str.size() );
    if( k == 1 || k == str_size)
        return true;

    if( str_size % k != 0 )
        return false;

    for( int i = 0; i < k; i++ )
        for( int j = i + k; j < str_size; j += k) {
            //cout<<i <<" "<<j <<endl;
            if (str[i] != str[j])
                return false;
        }

    return true;
}

int main() {
    cout<<IsKPeriodic( "abcabcabcabc", 6 )<<endl;
    return 0;
}
