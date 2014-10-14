#include <iostream>
using namespace std;

bool test_elementaries();
bool test_matrix();
bool test_2dtypes();
bool test_2dintersections();

int main()
{
    if( test_elementaries() )
        cerr << "Successfully completed: Elementary types." << std::endl;

    if( test_matrix() )
        cerr << "Successfully completed: Matrix type." << std::endl;

    if( test_2dtypes() )
        cerr << "Successfully completed: 2D types test." << std::endl;

    if( test_2dintersections() )
        cerr << "Successfully completed: 2D intersection test." << std::endl;

    return 0;
}
