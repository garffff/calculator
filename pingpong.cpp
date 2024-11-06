#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

bool isc(char a)
{
    if(a == '0' or a == '1' or a == '2' or a == '3' or a == '4' or a == '5' or a == '6' or a == '7' or a == '8' or a == '9') return true;
    return false;
}

bool isznak(char a)
{
    if(a == '+' or a == '-' or a == '*' or a == '/' or a == '(' or a == ')') return true;
    return false;
}

bool istherex(vector<string> vec)
{
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i] == "x" or vec[i] == "exp") return 1;
    }
    return 0;
}

vector<string> vecizstr(string ogs)
{
    string b;
    int j;
    vector<string> fins;
    for(int i = 0; i < ogs.size(); ++i)
    {
        if(isznak(ogs[i]))
        {
            b.clear();
            b += ogs[i];
            fins.push_back(b);
        }
        else if(isc(ogs[i]))
        {
            b.clear();
            j = 0;
            while(isc(ogs[i + j]) or ogs[i + j] == '.' or ogs[i + j] == ',')
            {
                b+= ogs[i+j];
                j++;
            }
            fins.push_back(b);
            i +=j - 1;
        }
        else if(ogs[i] == 's')
        {
            fins.push_back("sin");
            i += 2;
        }
        else if(ogs[i] == 'c')
        {
            if(ogs[i + 1] == 'o')
            {
                fins.push_back("cos");
                i += 2;
            }
            else
            {
                fins.push_back("ctg");
                i+=2;
            }
        }
        else if(ogs[i] == 't')
        {
            fins.push_back("tg");
            i++;
        }
        else if(ogs[i] == 'e')
        {
            fins.push_back("exp");
            i +=2;
        }
        else if(ogs[i] == 'x') fins.push_back("x");
    }
    return fins;
}

double perevod(string a)
{
    double k = 1;
    if(a[0] == '-')
    {
        a.erase(a.begin());
        k = -1;
    }
    double c = 0;
    int f = min(a.find('.'), a.find(','));
    if(f > a.size())
    {
        for(int i = 0; i < a.size(); ++i)
        {
            c += ((double)a[i] - 48)* pow(10, a.size()-1-i);
        }
    }
    else
    {
        for(int i = 0; i < f; ++i)
        {
            c+= ((double)a[i] - 48)* pow(10, f-1-i);
        }
        for(int j = f + 1; j < a.size(); ++j)
        {
            c+= ((double)a[j] - 48)* pow(10, f - j);
        }
    }
    return c * k;
}

void probel(string &ogs)
{
    for(int i = 0; i < ogs.size(); ++i) if(ogs[i] == ' ') ogs.erase(i, 1);
}

bool proverka(string ogs)
{
    int j, n;
    for(int i = 0; i < ogs.size(); ++i)
    {
        if(not (isc(ogs[i]) or isznak(ogs[i]) or ogs[i] == 'c' or ogs[i] == 't' or ogs[i] == 's' or ogs[i] == 'e' or ogs[i] == 'x')) return 0;
        if(isc(ogs[i]))
        {
            j = 0;
            n = 0;
            while(ogs[i + j] == '.' or ogs[i + j] == ',' or isc(ogs[i + j]))
            {
                if(ogs[i + j] == '.' or ogs[i + j] == ',')
                {
                    if(n == 1) return 0;
                    n = 1;
                }
                j++;
                if(i + j == ogs.size()) return 1;
            }
            if(not(isznak(ogs[i + j]) and ogs[i + j] != '(')) return 0;
            i +=j;
        }
        if(ogs[i] == '(')
        {
            if(i + 1 == ogs.size()) return 0;
            else if(isznak(ogs[i + 1]) and ogs[i + 1] != '-') return 0;
        }
        if(ogs[i] == ')')
        {
            if(i + 1 == ogs.size()) return 1;
            else if(not isznak(ogs[i + 1]) or ogs[i + 1] == '(') return 0;
        }
        if(isznak(ogs[i]) and ogs[i] != '(' and ogs[i] != ')' and isznak(ogs[i + 1]) and ogs[i + 1] != '(') return 0;
        if(ogs[i] == 'c')
        {
            if(i + 3 >= ogs.size()) return 0;
            if(not ((ogs[i + 1] == 'o' and ogs[i + 2] == 's') or (ogs[i + 1] == 't' and ogs[i + 2] == 'g'))) return 0;
            if(isznak(ogs[i + 3]) and ogs[i + 3] != '(') return 0;
            i+=2;
        }
        if(ogs[i] == 't')
        {
            if(i + 2 >=  ogs.size()) return 0;
            if(ogs[i + 1] == 'g') i++;
            else return 0;
        }
        if(ogs[i] == 's')
        {
            if(i + 3 >= ogs.size()) return 0;
            if(not (ogs[i + 1] == 'i' and ogs[i + 2] == 'n')) return 0;
            if(isznak(ogs[i + 3]) and ogs[i + 3] != '(') return 0;
            i+=2;
        }
        if(ogs[i] == 'e')
        {
            if(i + 2 >= ogs.size()) return 0;
            if(ogs[i + 1] == 'x' and ogs[i + 2] == 'p') i += 2;
            else return 0;
        }
        if(ogs[i] == 'x')
        {
            if(i + 1 == ogs.size()) return 1;
            if(not(isznak(ogs[i + 1]) and ogs[i + 1] != '(')) return 0;
        }
    }
    return 1;
}

double oper(double a, double b, string c)
{
    if(c == "+") return a+b;
    else if(c == "-") return a-b;
    else if(c == "*") return a*b;
    return a/b;
}

void replac(string a, int k1, int k2, vector<string> &vec)
{
    vec.erase(vec.begin() + k1, vec.begin() + k2);
    vec[k1] = a;
}

int finder(vector<string> vec, string a)
{
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i] == a) return i;
    }
    return pow(2, 7);
}

void eras(vector<string> &vec, int k)
{
    string b;
    for(int i = k; i < vec.size() - 1; ++i)
    {
        b = vec[i];
        vec[i] = vec[i + 1];
        vec[i + 1] = b;
    }
    vec.pop_back();
}

string uprosh(vector<string> &fins)
{
    if(fins[0] == "-")
    {
        fins[1] = "-" + fins[1];
        eras(fins, 0);
    }
    while(fins.size() > 1)
    {
        for(int j = 0; j < fins.size() - 1; ++j)
        {
            if(fins[j] == "sin" or fins[j] == "cos" or fins[j] == "tg" or fins[j] == "ctg")
            {
                if(fins[j] == "sin")
                {
                    eras(fins, j);
                    fins[j] = to_string(sin(perevod(fins[j])));
                }
                else if(fins[j] == "cos")
                {
                    eras(fins, j);
                    fins[j] = to_string(cos(perevod(fins[j])));
                }
                else if(fins[j] == "tg")
                {
                    eras(fins, j);
                    fins[j] = to_string(tan(perevod(fins[j])));
                }
                else
                {
                    eras(fins, j);
                    fins[j] = to_string(1 / tan(perevod(fins[j])));
                }
            }
        }
        for(int j = 0; j < fins.size() - 1; ++j)
        {
            if(fins[j] == "*" or fins[j] == "/")
            {
                replac(to_string(oper(perevod(fins[j - 1]), perevod(fins[j+1]), fins[j])), j - 1, j + 1, fins);
                j -= 1;
            }
        }
        for(int j = 0; j < fins.size() - 1; ++j)
        {
            if(fins[j] == "+" or fins[j] == "-")
            {
                replac(to_string(oper(perevod(fins[j - 1]), perevod(fins[j+1]), fins[j])), j - 1, j + 1, fins);
                j -= 1;
            }
        }
    }
    return fins[0];
}

void skob(vector<string> &fins)
{
    vector<string> buf;
    while(finder(fins, "(") < fins.size())
    {
        for(int i = finder(fins, ")") - 2; i >= 0; i--)
        {
            if(fins[i] == "(")
            {
                buf.clear();
                for(int k = i + 1; k <= finder(fins, ")") - 1; ++k)
                {
                    buf.push_back(fins[k]);
                }
                fins.erase(fins.begin() + i, fins.begin() + finder(fins, ")"));
                fins[i] = uprosh(buf);
            }
        }
    }
}

int main()
{
    string ogs;
    getline(cin, ogs);
    probel(ogs);
    cout << ogs << endl;
    if(proverka(ogs) == false)
    {
        cout << "INVALID SYNTAX";
        return 0;
    }
    vector<string> fins = vecizstr(ogs);
    cout << "original vector:" << endl;
    for(int i = 0; i < fins.size(); ++i) cout << fins[i] << ", ";
    if(istherex(fins))
    {
        double x;
        cout << endl << "Insert x:" << endl;
        cin >> x;
        for(int i = 0; i < fins.size(); ++i)
        {
            if(fins[i] == "x") fins[i] = to_string(x);
            if(fins[i] == "exp") fins[i] = to_string(exp(x));
        }
    }
    skob(fins);
    cout << "without skobochek:" << endl;
    for(int i = 0; i < fins.size(); ++i)
    {
        cout << fins[i] << ", ";
    }
    uprosh(fins);
    auto otvet = fins[0];
    cout << endl << "final answer" << endl << otvet;
    return 0;
}
