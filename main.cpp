#include <iostream>
#include <list>
#include <vector>
#include <string.h>
using namespace std;

#define OPS 5
#define NUM 8

// Finds equalities where the given number can be obtained
// Using 1 to 9 and +-*/ signs
// 1-2+3+4*567*8/9=2018
// 1-2+3/4*5*67*8+9=2018
// 1*2345-6*7*8+9=2018
// 12*34*5+67-89=2018

bool isEqual(bool reverse, int ops[], int result)
{
    int nums[NUM + 1];
    int index = 0;
    int digits = 0;
    int slide;
    int i = 0;
    int opsLength = NUM;
    bool mulDivBegin; // is multiplication & division operations begin
    int mul;
    int div;
    int res;

    int lOps[opsLength]; // Local copy of ops

    for(int j = 0; j < opsLength; ++j)
        lOps[j] = ops[j];

    if(reverse)
        for(int j = NUM + 1; j > 0; --j)
            nums[NUM + 1 - j] = j;
    else
        for(int j = 1; j <= NUM + 1; ++j)
            nums[j - 1] = j;

    // Step 1 - Concatenation Operation

    while(i < opsLength)
    {
        if(lOps[i] == 0)
        {
            nums[index] = nums[index] * 10 + nums[i + 1];
            ++digits;
            if(i == opsLength - 1)
                opsLength = opsLength - digits;
        }
        else
        {
            slide = index + digits;
            if(digits != 0)
            {
                for(int j = slide; j < opsLength; ++j)
                {
                    lOps[j - digits] = lOps[j];
                    nums[j - digits + 1] = nums[j + 1];
                }
                opsLength = opsLength - digits;
                i = index;  
            }
            index = i + 1;
            digits = 0;
        }
        ++i;
    }

    // End of Step 1 - Concatenation

    // Step 2 - Multiplication & Division Operations
    while(true)
    {
        index = 0;
        i = 0;
        slide = 0;
        mulDivBegin = false;

        while(i < opsLength)
        {
            while((lOps[i] == 3 || lOps[i] == 4) && i < opsLength)
            {
                if(mulDivBegin == false)
                {
                    index = i;
                    mulDivBegin = true;
                }
                ++i;
                ++slide;
            }

            if(slide != 0) // First multiplication & division operations found
                break;

            mulDivBegin = false;
            ++i;
        }
        if(slide == 0)  // There is not anymore multiplication/division operands
            break;

        // multiplication & division operations
        // First multiply the multiplicants and multiply the dividents
        // Then divide the multiplication of multiplicants to multiplication of dividents

        i = 0;
        mul = nums[index + i];
        div = 1;

        while(i < slide)
        {
            if(lOps[index + i] == 3)
                mul *= nums[index + i + 1];
            else
                div *= nums[index + i + 1];
            ++i;
        }

        if(mul % div != 0)  // Division results in a floating point number, we are working with integers
            return false;

        nums[index] = mul / div;

        for(int j = index; j < opsLength; ++j)
        {
            lOps[j] = lOps[j + slide];
            nums[j + 1] = nums[j + slide + 1];
        }
        opsLength = opsLength - slide;

    }

    // End of Step 2 - multiplication & division operations

    // Step 3 - addition & subtraction operations

    res = nums[0];
    for(int i = 0; i < opsLength; ++i)
    {
        if(lOps[i] == 1)
            res += nums[i + 1];
        else
            res -= nums[i + 1];
    }

    return res == result;
}

string makeString(bool reverse, int ops[], int number)
{
    string s = "";
    for(int i = 0; i < NUM; ++i)
    {
        int digit = i + 1;
        if(reverse)
            digit = NUM + 1 - i;

        s += to_string(digit);

        if(ops[i] == 1)
            s += "+";
        else if(ops[i] == 2)
            s += "-";
        else if(ops[i] == 3)
            s += "*";
        else if(ops[i] == 4)
            s += "/";
    }
    if(reverse)
        s += "1";
    else
        s += to_string(NUM + 1);;

    s += " = " + to_string(number);
    return s;
}

list<string> solve(bool reverse, int result)
{
    list<string> solutions;

    int ops[NUM];
    memset(ops, 0, NUM * sizeof(ops[0]));  // Operation begin with concatenation
    int index = NUM - 1;

    // All possible operations are considered starting from the last
    // Operand to first operand
    while(true)
    {        
        if(isEqual(reverse, ops, result))
            solutions.push_back(makeString(reverse, ops, result));

        while(ops[index] == OPS - 1) --index;

        if(index == -1)
            return solutions;

        ++ops[index];
        ++index;

        while(index < NUM)
        {
            ops[index] = 0;
            ++index;
        }
        index = NUM - 1;
    }
}

int main()
{
    int dest;
    cout << "Enter destination number : " << endl;
    cin >> dest;

    list<string> solutions = solve(false, dest);

    cout << solutions.size() << " solution(s) : " << endl;

    for(list<string>::iterator sit = solutions.begin(); sit != solutions.end(); ++sit)
        cout << *sit << endl;

    cout << "End of Program!" << endl;
    return 0;
}
