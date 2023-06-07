#include <gtest/gtest.h>
#include "fillZoneAlgorithm.h"
#include <memory>
#include <fstream>

TEST(CycleFillZone, Case1)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}

TEST(CycleFillZone, Case2)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}


TEST(CycleFillZone, Case3)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}

TEST(CycleFillZone, Case4)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {1,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}

TEST(CycleFillZone, Case5)
{
    using namespace std;
    vector<vector<char>> input{
        {1,0,0,0,0,0,0,0,1,0},
        {1,0,1,0,0,0,1,0,1,0},
        {1,0,1,0,0,0,1,0,1,0},
        {1,0,1,0,0,0,1,0,1,0},
        {1,0,1,0,0,0,0,0,1,0},
        {1,0,1,0,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {1,1,1,1,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}

//Вертикальные тесты

TEST(CycleFillZone, Case6)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {1,0,0,0,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,1,1,1,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {0,0,0,0,0,0,1,0,0,0},
        {1,0,0,0,0,0,0,0,0,0}
        };


    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);
    ASSERT_EQ(predResult, result);
}

TEST(CycleFillZone, Case7)
{
    using namespace std;
    vector<vector<char>> input{
        {0,0,0,1,0,0,0,0,1,0},
        {0,1,1,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0,0},
        {0,0,1,1,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,1},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1},
        {0,0,0,0,0,0,1,0,0,0},
        {1,0,0,1,0,0,0,0,0,0}
        };

    vector<vector<char>> predResult{
        {0,0,0,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,1,1},
        {0,1,1,1,0,0,1,0,0,1},
        {0,1,1,1,0,0,1,0,0,1},
        {0,1,1,1,0,0,1,0,0,1},
        {0,1,1,1,0,0,1,0,0,0},
        {1,1,1,1,0,0,0,0,0,0}
        };

    ofstream file1("OUT.txt");

    for (int i=0; i < input.size(); i++)
    {
        for (int j = 0; j < input.at(i).size(); j++)
        {
            file1 << (int)input.at(i).at(j) << " ";
        }
        file1 << endl;
    }
    
    file1 << endl << endl;


    for (int i=0; i < predResult.size(); i++)
    {
        for (int j = 0; j < predResult.at(i).size(); j++)
        {
            file1 << (int)predResult.at(i).at(j) << " ";
        }
        file1 << endl;
    }
    
    file1 << endl << endl;




    unique_ptr<FillZoneBehavior> fillZoneBehavior = make_unique<CycleFillZone>();
    vector<vector<char>> result = fillZoneBehavior->fillZone(input);

    for (int i=0; i < result.size(); i++)
    {
        for (int j = 0; j < result.at(i).size(); j++)
        {
            file1 << (int)result.at(i).at(j) << " ";
        }
        file1 << endl;
    }
    file1.close();
    ASSERT_EQ(predResult, result);
    
}