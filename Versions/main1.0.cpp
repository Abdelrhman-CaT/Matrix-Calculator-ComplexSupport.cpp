#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>
using namespace std;

void comp_split(string num , float &r, float &i)
{

    string auth = num;
    int len= num.length();
    int sep,n=0,neg=0;

    if(num == "i")
    {
        r=0;
        i=1;
    }
    else if(num == "-i")
    {
        r=0;
        i=-1;
    }

    else
    {
            if(num.find("+") != -1)
    {

        if(num.find("+i")!= -1)
        {
            for(int j=0;j<len;j++)
            {
                if(num[j] == '+' || num[j] == '-')
                {
                    sep=j;
                }
            }
        num.erase(sep);
        r=atof(num.c_str());
        i=1;
        }

        else
        {
            for(int j=0;j<len;j++)
            {
                if(num[j] == '+' || num[j] == '-')
                {
                    sep=j;
                }
            }
            if(num[sep] == '-')
                {
                    neg=1;
                }

            num.erase(sep);
            r = atof(num.c_str());

            for(int j=sep+1;j<len-1;j++)
                {
                    auth[n] = auth[j];
                    n+=1;
                }
            auth.erase(n);
            i = atof(auth.c_str());
            if(neg == 1)
                {
                    i= -i;
                }
        }
    }

    else if(num.find("-") != -1)
    {

        if(num.find("-",1)!=-1)
        {
            for(int j=0;j<len;j++)
            {
                if(num[j] == '-')
                    {
                        sep=j;
                    }
            }

        num.erase(sep);
        r = atof(num.c_str());

        for(int j=sep;j<len-1;j++)
            {
                auth[n] = auth[j];
                n+=1;
            }
        auth.erase(n);

        if(auth == "-")
        {
            i= -1;
        }
        else
        {
            i = atof(auth.c_str());
        }

        }
        else
        {
            if(num.find("i") != -1)
            {
                r=0;
                num.erase(len-1);
                i=atof(num.c_str());
            }
            else
            {
                r=atof(num.c_str());
                i=0;
            }
        }
    }

    else
    {
        if(num.find("i") != -1)
        {
            r=0;
            num.erase(len-1);
            i=atof(num.c_str());
        }
        else
        {
            i=0;
            r=atof(num.c_str());
        }
    }

    }

}

string comp_combine(float r , float i)
{
    int neg=0;
    if(i < 0)
    {
        neg=1;
    }
    ostringstream rr;
    rr << r;
    string re = rr.str();

    ostringstream ii;
    ii << i;
    string im = ii.str();

    if(neg != 1)
    {
        im.insert(0, "+");
    }
    int lenIm = im.length();
    im.insert(lenIm , "i");

    string res = re+im;
    int reslen = res.length();

    if(res.find("1i") != -1)
    {
        if(res[res.find("1i")-1] == '+' || res[res.find("1i")-1] == '-')
        {
           res[res.find("1i")] = 'i';
            res.erase(reslen-1);
            if(res[0] == '0')
                {
                if(res[1]=='+')
                {
                    res = "i";
                }
            else if(res[1] == '-')
            {
                res = "-i";
            }
                }
        }
        else
        {
          if(res[0] == '0')
        {
            if(res[1] != '.')
            {
                float realres , imagres;
                comp_split(res , realres , imagres);
                if(imagres < 0)
                {
                    for(int i=1 ; i<reslen ; i++)
                    {
                    res[i-1] = res[i];
                    }
                res.erase(reslen-1);
                }
                else if(imagres > 0)
                {
                  for(int i=2 ; i<reslen ; i++)
                    {
                    res[i-2] = res[i];
                    }
                res.erase(reslen-2);
                }


            }

        }
        }

    }
    else if(res.find("0i") != -1)
    {
        if(res == "0+0i")
        {
            res = "0";
        }
        else
        {
           if(res[res.find("0i")-1] == '+' || res[res.find("0i")-1] == '-' )
        {
            res.erase(reslen - 3);
        }
        if(res[0] == '0')
        {
            if(res[1] != '.')
            {
               for(int i=2 ; i<reslen ; i++)
            {
                res[i-2] = res[i];
            }
            res.erase(reslen-2);
            }

        }
        }

    }

    else if(res[0] == '0')
    {
        if(res[1] == '+')
        {
            for(int i=2;i<reslen;i++)
            {
                res[i-2] = res[i];
            }
            res.erase(reslen -2);
        }
        else if(res[1] == '-')
        {
            for(int i=1;i<reslen;i++)
            {
                res[i-1] = res[i];
            }
            res.erase(reslen -1);
        }
    }

    return res;
}

string comp_add(string num1 , string num2)    // operator is '+'
{
    float real1,real2,imag1,imag2;
    comp_split(num1 , real1 , imag1);
    comp_split(num2 , real2 , imag2);
    float SumReal=real1+real2;
    float SumImag=imag1+imag2;
    return comp_combine(SumReal , SumImag);
}

string comp_sub(string num1 , string num2)    // operator is '-'
{
    float real1,real2,imag1,imag2;
    comp_split(num1 , real1 , imag1);
    comp_split(num2 , real2 , imag2);
    float SumReal=real1-real2;
    float SumImag=imag1-imag2;
    return comp_combine(SumReal , SumImag);
}

void polar(string num , float &mag , float &ang)     // Works well but gets buggy at num=0 .. update: solved at comp_multiply
{
    float real_num; float imag_num , tan_ang , tan_ratio , pos_angle;
    if(num == "-1")
    {
        mag = 1;
        ang = 180;
    }
    else
    {
        comp_split(num , real_num , imag_num);
        mag = sqrt(pow(real_num ,2) + pow(imag_num , 2));

        tan_ratio = fabs(imag_num / real_num);
        pos_angle = (180/M_PI) * atan(tan_ratio);

            if((real_num <=0) && (imag_num >=0) )
            {
                tan_ang = 180-pos_angle;
            }
            else if((real_num >=0) && (imag_num <=0))
            {
                tan_ang= -1 * pos_angle;
            }
            else if((real_num >=0) && (imag_num >=0))
            {
                tan_ang = pos_angle;
            }
            else if((real_num <=0) && (imag_num <=0))
            {
                tan_ang = -(180-pos_angle);
            }

        ang = tan_ang;
    }

}

void rectangular(float mag , float ang , float &r , float &i)
{
    float ang_rad = (ang/180) * (M_PI);
    float sin_ang , cos_ang;

    sin_ang = sin(ang_rad);
    cos_ang = cos(ang_rad);

    if(fabs(sin_ang) < 0.0001)
    {
        sin_ang =0;
    }
    if(fabs(cos_ang) < 0.0001)
    {
        cos_ang =0;
    }

    r = mag * cos_ang;
    i = mag * sin_ang;
}

string comp_multiply(string num1 , string num2)  // operator is 'x'
{
    float mag_num1 , ang_num1 , mag_num2 , ang_num2;
    float res_real , res_imag;

    if(num1 == "0" || num2 == "0")
    {
        res_real = 0;
        res_imag = 0;
    }

    else
    {

        polar(num1 , mag_num1 , ang_num1);
        polar(num2 , mag_num2 , ang_num2);

        float mag_res = mag_num1 * mag_num2;
        float ang_res = ang_num1 + ang_num2;


        rectangular(mag_res , ang_res , res_real , res_imag);

    }


    return comp_combine(res_real , res_imag);
}

string comp_divide(string num1 , string num2)  // operator is '/'
{
    float mag_num1 , ang_num1 , mag_num2 , ang_num2;
    float res_real , res_imag ;
    string final_res;

    if(num1 == "0" || num2 == "0")
    {
       if(num1 == "0")
        {
            res_real = 0;
            res_imag = 0;
            final_res = comp_combine(res_real , res_imag);
        }
        if(num2 == "0")
        {
            final_res = "Undefined";
        }
    }


    else
    {

        polar(num1 , mag_num1 , ang_num1);
        polar(num2 , mag_num2 , ang_num2);

        float mag_res = mag_num1 / mag_num2;
        float ang_res = ang_num1 - ang_num2;


        rectangular(mag_res , ang_res , res_real , res_imag);
        final_res = comp_combine(res_real , res_imag);

    }
    return final_res;
}

string comp_power(string num , int power)  // operator is '^'
{
    if(power == 1)
    {
        return num;
    }
    if(power == 0)
    {
        float real,imag;
        comp_split(num , real , imag);
        if(imag == 0)
        {
            num = "1";
            return num;
        }
        else
        {
            num="Math Error";
            return num;
        }

    }
    if(power > 0)
    {
        string auth = num;
        for(int i=2;i<=power;i++)
        {
            num = comp_multiply(num , auth);
        }
        return num;
    }
    if(power < 0)
    {
        return comp_divide("1" , comp_power(num , fabs(power)));
    }
}

string comp_square_root(string num1)  // operator is 's'
{
    string res;
    float sres;
    float real, imag;
    comp_split(num1 , real , imag);
    if(imag == 0)
    {
        if(real >= 0)
        {
        sres = sqrt(real);
        ostringstream stringres;
        stringres << sres;
        res = stringres.str();
        return res;
        }
        else
        {
            sres = sqrt(fabs(real));
            ostringstream stringres;
            stringres << sres;
            res = stringres.str() + "i";
            if(res == "1i")
            {
                res = "i";
            }
            return res;
        }
    }
    else
    {
        res = "Math Error";
        return res;
    }
}

string eval(string num1 , char operator_ , string num2="0");    // prototyping for evaluation function

// ---------------------------------------------------------------------------------------------------------------

int num_of_rows(string mat)
{
    int len = mat.length();
    int c=1;

    for(int i=1;i<len-1;i++)
    {
        if(mat[i] == ';')
        {
            c+=1;
        }
    }
    return c;
}

int num_of_columns(string mat)
{
    int len = mat.length();
    int j;


    if(mat[1] == ';')
    {
        return 0;
    }

    else if(mat[2] == ';')
    {
        return 1;
    }


    if(num_of_rows(mat) == 1)
    {
        j=len-1;
    }
    else
    {
        for(int i=1 ; i<len-1 ; i++)
        {
            if(mat[i] == ';')
            {
                j = i;
                break;
            }
        }
    }

    int c=0;
    for(int i=1 ; i<j ; i++)
    {
        if(mat[i] == ' ')
        {
            c+=1;
        }
    }
    return c+1;

}

bool mat_verify(string mat)
{
    int len=mat.length();
    float spaces =0;
    int columns = num_of_columns(mat);
    int rows = num_of_rows(mat);

    if(mat[0] != '[' || mat[len-1] != ']')
    {
        return 0;
    }

    for(int i=1 ;i<len-1 ;i++)
    {
        if(mat[i] == ' ')
        {
            spaces+=1;
        }
    }

    if(spaces/rows == columns-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

bool op_verify(string o)
{
    if(o == "+" || o == "-" || o == "*" || o == "^" || o == "T" || o == "D" || o == "I" || o == "/" )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool is_square(string mat)
{
    if(num_of_rows(mat) == num_of_columns(mat))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool verified_for_add_and_sub(string mat1 , string mat2)
{
    if(num_of_rows(mat1) == num_of_rows(mat2) && num_of_columns(mat1) == num_of_columns(mat2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool verified_for_multiply(string mat1 , string mat2)
{
    if(num_of_columns(mat1) == num_of_rows(mat2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// ----------------------------------------------------------------------------------------------------------------










int main()
{
    string mat1,mat2;
    string operate;

    getline(cin , mat1);
    if(!mat_verify(mat1))
    {
        cout << "ERROR";
        return 0;
    }

    getline(cin , operate);
    if(!op_verify(operate))
       {
           cout << "ERROR";
           return 0;
       }

    if(operate == "+")
    {
        getline(cin , mat2);
        if(!mat_verify(mat2))
        {
            cout << "ERROR";
            return 0;
        }
        if(!verified_for_add_and_sub(mat1 , mat2))
        {
            cout << "ERROR";
            return 0;
        }
        else
        {
            // calculate
        }
    }

    else if(operate == "-")
    {
        getline(cin , mat2);
        if(!mat_verify(mat2))
        {
            cout << "ERROR";
            return 0;
        }
        if(!verified_for_add_and_sub(mat1 , mat2))
        {
            cout << "ERROR";
            return 0;
        }
        else
        {
            // calculate
        }
    }

    else if(operate == "*")
    {
        getline(cin , mat2);
        if(!mat_verify(mat2))
        {
            cout << "ERROR";
            return 0;
        }
        if(!verified_for_multiply(mat1 , mat2))
        {
            cout << "ERROR";
            return 0;
        }
        else
        {
            // calculate
        }
    }

    else if(operate == "/")
    {
        getline(cin , mat2);
        if(!mat_verify(mat2))
        {
            cout << "ERROR";
            return 0;
        }

        // get the inverse of mat2 , then verify it if it can be multiplied with mat1

    }

    else if(operate == "^")
    {
        int power;
        if(!is_square(mat1))
        {
            cout << "ERROR";
                return 0;
        }

        cin >> power;
        if(power <= 0)
        {
            cout << "ERROR";
            return 0;
        }
        else
        {
            // calculate
        }

    }

    else if(operate == "I")
    {
        if(!is_square(mat1))
        {
            cout << "ERROR";
                return 0;
        }
        else
        {
            // calculate
        }
    }

    else if(operate == "D")
    {

    }

    else if(operate == "T")
    {

    }



return 0;
}


string eval(string num1 , char operator_ , string num2)
{
    switch(operator_)
    {
    case '+':
        return comp_add(num1 , num2);
        break;

    case '-':
        return comp_sub(num1 , num2);
        break;

    case 'x':
        return comp_multiply(num1 , num2);
        break;

    case '/':
        return comp_divide(num1 , num2);
        break;

    case '^':
        return comp_power(num1 , atof(num2.c_str()));
        break;

    case 's':
        return comp_square_root(num1);
        break;
    }
}













