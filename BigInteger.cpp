#include <bits/stdc++.h>
using namespace std;

class BigInt
{
    string s;
    ///////////ABSOLUTE////////////////
    string abs(string s)
    {
        if (s[0] == '-')
        {
            reverse(s.begin(), s.end());
            s.pop_back();
            reverse(s.begin(), s.end());
        }
        return s;
    }
    ///////////////////////NEGATIVE///////////////
    string negative(string s)
    {
        if (s[0] == '-')
        {
            reverse(s.begin(), s.end());
            s.pop_back();
            reverse(s.begin(), s.end());
        }
        else
        {
            reverse(s.begin(), s.end());
            s.push_back('-');
            reverse(s.begin(), s.end());
        }
        return s;
    }
    //////////////////////ADDITION///////////////////
    string add(string s1, string s2)
    {
        int carry = 0;
        string ans = "";
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        int i = 0;
        int j = 0;

        while (i < s1.length() && j < s2.length())
        {
            int num = (s1[i] - '0') + (s2[j] - '0') + carry;
            carry = num / 10;
            ans.push_back(num % 10 + '0');
            i++;
            j++;
        }
        while (i < s1.length())
        {
            int num = (s1[i] - '0') + carry;
            carry = num / 10;

            ans.push_back(num % 10 + '0');
            i++;
        }
        while (j < s2.length())
        {
            int num = (s2[j] - '0') + carry;
            carry = num / 10;

            ans.push_back(num % 10 + '0');
            j++;
        }
        if (carry + '0' > '0')
        {
            ans.push_back(carry + '0');
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
    //////////////////////MULTIPLY (SINGLE DIGIT)///////////////////
    string singleMultiply(string s, char c)
    {
        string ans = "";
        int carry = 0;
        int n = s.length();

        for (int i = n - 1; i >= 0; i--)
        {
            int num = (c - '0') * (s[i] - '0') + carry;

            ans.push_back(num % 10 + '0');
            carry = num / 10;
        }
        if (carry + '0' > '0')
        {
            ans.push_back(carry + '0');
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
    //////////////////////MULTIPLY/////////////////////
    string multiply(string s1, string s2)
    {

        string final = "";
        int n = s1.length();
        int m = s2.length();

        if (s1 == "0" || s2 == "0")
        {
            return "0";
        }

        int cnt = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            char c = s1[i];

            string temp = singleMultiply(s2, c);

            for (int j = 0; j < cnt; j++)
            {
                temp.push_back('0');
            }

            final = add(final, temp);
            cnt++;
        }

        return final;
    }
    //////////////////////SUBTRACTION///////////////////
    string subtract(string s1, string s2)
    {
        int flag = 0;
        if (s2.length() >= s1.length())
        {
            if ((s2.length() > s1.length()) || (s2 > s1))
            {
                swap(s1, s2);
                flag = 1;
            }
        }
        int n = s1.length();
        int m = s2.length();

        int i = n - 1;
        int j = m - 1;
        string s = "";
        int borrowed = 0;

        while (i >= 0 && j >= 0)
        {
            int num1 = s1[i--] - '0';
            int num2 = s2[j--] - '0';

            if (num1 >= num2 + borrowed)
            {
                num1 -= num2 + borrowed;
                s.push_back(num1 + '0');
                borrowed = 0;
                continue;
            }

            num1 += 10;
            num1 -= num2;
            if (borrowed == 0)
            {
                s.push_back(num1 + '0');
                borrowed = 1;
                continue;
            }

            num1 -= 1;
            s.push_back(num1 + '0');
        }

        while (i >= 0)
        {
            int num1 = s1[i--] - '0';

            if (num1 >= borrowed)
            {
                num1 -= borrowed;
                borrowed = 0;
                s.push_back(num1 + '0');
                continue;
            }
            num1 += 9;
            s.push_back(num1 + '0');
        }

        while (s.length() > 1 && s.back() == '0')
        {
            s.pop_back();
        }
        if (flag)
        {
            s.push_back('-');
        }
        reverse(s.begin(), s.end());
        return s;
    }
    /////////// DIVIDE /////////////////////
    string divide(string num, string dem)
    {
        if (num.length() < dem.length())
        {
            return "0";
        }

        if (num.length() == dem.length())
        {
            if (dem > num)
            {
                return "0";
            }
        }

        string temp = dem;
        int cnt = 0;
        while (temp.length() < num.length())
        {
            temp.push_back('0');
            cnt++;
        }
        if (temp > num)
        {
            cnt--;
            temp.pop_back();
        }

        int divisor = 1;
        string initial = temp;
        while (1)
        {
            if (temp.length() > num.length())
            {
                break;
            }

            if (temp.length() == num.length())
            {
                if (temp > num)
                {
                    break;
                }
            }
            temp = add(temp, initial);
            divisor++;
        }
        divisor--;
        temp = subtract(temp, initial);

        string ans = "";
        ans.push_back(divisor + '0');

        for (int i = 0; i < cnt; i++)
        {
            ans.push_back('0');
        }

        num = subtract(num, temp);

        ans = add(ans, divide(num, dem));

        return ans;
    }
    //////////////////////MODULUS/////////////////////
    string mod(string num, string dem)
    {
        if (num.length() < dem.length())
        {
            return num;
        }

        if (num.length() == dem.length())
        {
            if (dem > num)
            {
                return num;
            }
        }
        string temp = dem;
        while (temp.length() < num.length())
        {
            temp.push_back('0');
        }
        if (temp > num)
        {
            temp.pop_back();
        }

        string initial = temp;
        while (1)
        {
            if (temp.length() > num.length())
            {
                break;
            }

            if (temp.length() == num.length())
            {
                if (temp > num)
                {
                    break;
                }
            }
            temp = add(temp, initial);
        }
        temp = subtract(temp, initial);

        num = subtract(num, temp);

        return mod(num, dem);
    }
    ///////////////Factorial/////////////////////
    string fact(string str)
    {
        if (str == "0" || str == "1")
            return "1";

        string two = subtract(str, "1");

        return multiply(str, fact(two));
    }

public:
    BigInt() //Constructor
    {
        s = "0";
    }
    ////////////// + operator overload///////////////
    BigInt operator+(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        int flag = 1;
        string s3;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
            s3 = add(s, s2);
            s3 = multiply(s3, "-1");
            num.s = s3;
            return num;
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
            s3 = subtract(s, s2);
            num.s = s3;
            return num;
        }
        if (s[0] == '-')
        {
            s = abs(s);
            s3 = subtract(s2, s);
            num.s = s3;
            return num;
        }
        s3 = add(s, s2);
        num.s = s3;
        return num;
    }
    BigInt operator++() //pre-increment
    {
        BigInt num;
        if (s[0] == '-')
        {
            s = subtract("1", s);
            num.s = s;
            return num;
        }
        s = add(s, "1");
        num.s = s;
        return num;
    }
    BigInt operator++(int) //post-increment
    {
        BigInt num;
        num.s = s;
        operator++();
        return num;
    }
    BigInt operator+=(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        int flag = 1;
        string s3;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
            s3 = add(s, s2);
            s3 = multiply(s3, "-1");
            num.s = s3;
            return num;
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
            s3 = subtract(s, s2);
            num.s = s3;
            return num;
        }
        if (s[0] == '-')
        {
            s = abs(s);
            s3 = subtract(s2, s);
            num.s = s3;
            return num;
        }
        s3 = add(s, s2);
        num.s = s3;
        return num;
    }
    ////////////// * operator overload///////////////
    BigInt operator*(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        int flag = 0;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
        }
        else if (s[0] == '-')
        {
            s = abs(s);
            flag = 1;
        }
        else if (s2[0] == '-')
        {
            s2 = abs(s2);
            flag = 1;
        }
        string s3 = multiply(s, s2);
        if (flag && s3 != "0")
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    BigInt operator*=(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        int flag = 0;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
        }
        else if (s[0] == '-')
        {
            s = abs(s);
            flag = 1;
        }
        else if (s2[0] == '-')
        {
            s2 = abs(s2);
            flag = 1;
        }
        string s3 = multiply(s, s2);
        if (flag && s3 != "0")
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    ////////////// /(divide)operator overload///////////////
    BigInt operator/(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        if (s2 == "0")
        {
            num.s = "inf";
            return num;
        }

        int flag = 0;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
        }
        else if (s[0] == '-')
        {
            s = abs(s);
            flag = 1;
        }
        else if (s2[0] == '-')
        {
            s2 = abs(s2);
            flag = 1;
        }
        string s3 = divide(s, s2);
        if (flag && s3 != "0")
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    BigInt operator/=(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        if (s2 == "0")
        {
            num.s = "inf";
            return num;
        }

        int flag = 0;
        if (s[0] == '-' && s2[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
        }
        else if (s[0] == '-')
        {
            s = abs(s);
            flag = 1;
        }
        else if (s2[0] == '-')
        {
            s2 = abs(s2);
            flag = 1;
        }
        string s3 = divide(s, s2);
        if (flag && s3 != "0")
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    ////////////// %(mod)operator overload///////////////
    BigInt operator%(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        if (s2 == "0")
        {
            num.s = "inf";
            return num;
        }
        int flag = 0;

        if (s[0] == '-')
        {
            flag = 1;
            s = abs(s);
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
        }
        string s3 = mod(s, s2);
        if (flag)
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    BigInt operator%=(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        if (s2 == "0")
        {
            num.s = "inf";
            return num;
        }
        int flag = 0;

        if (s[0] == '-')
        {
            flag = 1;
            s = abs(s);
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
        }
        string s3 = mod(s, s2);
        if (flag)
        {
            s3 = negative(s3);
        }
        num.s = s3;
        return num;
    }
    ////////////////////// - operator overload //////////////
    BigInt operator-(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        string s3;
        if (s2[0] == '-' && s[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
            s3 = subtract(s2, s);
            num.s = s3;
            return num;
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
            s3 = add(s, s2);
            num.s = s3;
            return num;
        }
        if (s[0] == '-')
        {
            s = abs(s);
            s3 = add(s, s2);
            s3 = negative(s3);
            num.s = s3;
            return num;
        }
        s3 = subtract(s, s2);
        num.s = s3;
        return num;
    }
    BigInt operator--() //pre-decrement
    {
        BigInt num;
        if (s[0] == '-')
        {
            s = abs(s);
            s = add(s, "1");
            s = negative(s);
            num.s = s;
            return num;
        }
        s = subtract(s, "1");
        num.s = s;
        return num;
    }
    BigInt operator--(int) //post-decrement
    {
        BigInt num;
        num.s = s;
        operator--();
        return num;
    }
    BigInt operator-=(BigInt &n)
    {
        BigInt num;
        string s2 = n.s;
        string s3;
        if (s2[0] == '-' && s[0] == '-')
        {
            s = abs(s);
            s2 = abs(s2);
            s3 = subtract(s2, s);
            num.s = s3;
            return num;
        }
        if (s2[0] == '-')
        {
            s2 = abs(s2);
            s3 = add(s, s2);
            num.s = s3;
            return num;
        }
        if (s[0] == '-')
        {
            s = abs(s);
            s3 = add(s, s2);
            s3 = negative(s3);
            num.s = s3;
            return num;
        }
        s3 = subtract(s, s2);
        num.s = s3;
        return num;
    }
    BigInt fact()
    {
        BigInt num;
        num.s = fact(s);

        return num;
    }

    //////// (<,>,>=,<=,==)comparison operators overload///////////////////
    bool operator>(BigInt &n)
    {

        if (s[0] == '-' && n.s[0] == '-')
        {
            s = abs(s);
            n.s = abs(n.s);
            if (s.length() < n.s.length())
            {
                return true;
            }
            if (s.length() == n.s.length() && s < n.s)
            {
                return true;
            }
            return false;
        }
        if (s[0] == '-')
        {
            return false;
        }
        if (n.s[0] == '-')
        {
            return true;
        }
        if (s.length() > n.s.length())
        {
            return true;
        }
        if (s.length() == n.s.length() && s > n.s)
        {
            return true;
        }
        return false;
    }
    bool operator<(BigInt &n)
    {
        if (s[0] == '-' && n.s[0] == '-')
        {
            s = abs(s);
            n.s = abs(n.s);
            if (s.length() > n.s.length())
            {
                return true;
            }
            if (s.length() == n.s.length() && s > n.s)
            {
                return true;
            }
            return false;
        }
        if (s[0] == '-')
        {
            return true;
        }
        if (n.s[0] == '-')
        {
            return false;
        }
        if (s.length() < n.s.length())
        {
            return true;
        }
        if (s.length() == n.s.length() && s < n.s)
        {
            return true;
        }
        return false;
    }
    bool operator>=(BigInt &n)
    {
        if (s[0] == '-' && n.s[0] == '-')
        {
            s = abs(s);
            n.s = abs(n.s);
            if (s.length() < n.s.length())
            {
                return true;
            }
            if (s.length() == n.s.length() && s <= n.s)
            {
                return true;
            }
            return false;
        }
        if (s[0] == '-')
        {
            return false;
        }
        if (n.s[0] == '-')
        {
            return true;
        }
        if (s.length() > n.s.length())
        {
            return true;
        }
        if (s.length() == n.s.length() && s >= n.s)
        {
            return true;
        }
        return false;
    }
    bool operator<=(BigInt &n)
    {
        if (s[0] == '-' && n.s[0] == '-')
        {
            s = abs(s);
            n.s = abs(n.s);
            if (s.length() > n.s.length())
            {
                return true;
            }
            if (s.length() == n.s.length() && s >= n.s)
            {
                return true;
            }
            return false;
        }
        if (s[0] == '-')
        {
            return true;
        }
        if (n.s[0] == '-')
        {
            return false;
        }
        if (s.length() < n.s.length())
        {
            return true;
        }
        if (s.length() == n.s.length() && s <= n.s)
        {
            return true;
        }
        return false;
    }
    bool operator==(BigInt &n)
    {
        if (s == n.s)
        {
            return true;
        }
        return false;
    }
    /////////////////////////cin cout overload//////////////////////////
    friend ostream &operator<<(ostream &out, const BigInt &n); // cout << overload
    friend istream &operator>>(istream &in, BigInt &n);        // cin >> overload
};

ostream &operator<<(ostream &out, const BigInt &n) // cout << overload
{
    out << n.s;
    return out;
}
istream &operator>>(istream &in, BigInt &n) //cin >> overload
{
    in >> n.s;
    return in;
}

int main()
{
    BigInt n1;
    cout << 1 << endl;
    cin >> n1;
    cout << n1.fact() << endl;
    return 0;
}
