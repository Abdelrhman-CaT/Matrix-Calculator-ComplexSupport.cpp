#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <sstream>
#define float double
using namespace std;

void comp_split(string num , double &r, double &i)
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

string comp_combine(double r , double i)
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
                double realres , imagres;
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
    double real1,real2,imag1,imag2;
    comp_split(num1 , real1 , imag1);
    comp_split(num2 , real2 , imag2);
    double SumReal=real1+real2;
    double SumImag=imag1+imag2;
    return comp_combine(SumReal , SumImag);
}

string comp_sub(string num1 , string num2)    // operator is '-'
{
    double real1,real2,imag1,imag2;
    comp_split(num1 , real1 , imag1);
    comp_split(num2 , real2 , imag2);
    double SumReal=real1-real2;
    double SumImag=imag1-imag2;
    return comp_combine(SumReal , SumImag);
}

void polar(string num , double &mag , double &ang)     // Works well but gets buggy at num=0 .. update: solved at comp_multiply
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

void rectangular(double mag , double ang , double &r , double &i)
{
    double ang_rad = (ang/180) * (M_PI);
    double sin_ang , cos_ang;

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
    double mag_num1 , ang_num1 , mag_num2 , ang_num2;
    double res_real , res_imag;

    if(num1 == "0" || num2 == "0")
    {
        res_real = 0;
        res_imag = 0;
    }

    else
    {

        polar(num1 , mag_num1 , ang_num1);
        polar(num2 , mag_num2 , ang_num2);

        double mag_res = mag_num1 * mag_num2;
        double ang_res = ang_num1 + ang_num2;


        rectangular(mag_res , ang_res , res_real , res_imag);

    }


    return comp_combine(res_real , res_imag);
}

string comp_divide(string num1 , string num2)  // operator is '/'
{
    double mag_num1 , ang_num1 , mag_num2 , ang_num2;
    double res_real , res_imag ;
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

        double mag_res = mag_num1 / mag_num2;
        double ang_res = ang_num1 - ang_num2;


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
        double real,imag;
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
    double sres;
    double real, imag;
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


int find_dubchar(string mat , char x ,int r)   // finds the r occurrence for the char x in the string mat
{
    int len = mat.length();
    int r1=num_of_rows(mat);
    int c1=num_of_columns(mat);
    int q;
    int k=1;
    string row ="";

    for(int i=1;i<=r;i++)
    {
        for(int j=k ; j<len ; j++)
        {
            if(mat[j] == x)
            {
                q=j;
                break;
            }
        }
        k=q+1;
    }
   return q;
}

void row_indexes(string mat, int r, int &start , int &ending)
{
    int len = mat.length();
    int nr = num_of_rows(mat);
    if(mat.find(";") == -1)
    {
        start = 1;
        ending= len-1;
    }
    else
    {
        if(r==1)
        {
            start =1;
            ending = find_dubchar(mat , ';' , 1);
        }
        else if(r==nr)
        {
            start = find_dubchar(mat , ';' , nr-1) +1;
            ending= len-1;
        }
        else
        {
            start = find_dubchar(mat , ';' , r-1)+1;
            ending =find_dubchar(mat , ';' , r);
        }
    }

}

string mat_row(string mat , int r)
{
    int s,e;
    string res="";
    row_indexes(mat , r ,s ,e);
    for(int i=s;i<e;i++)
    {
        res+=mat[i];
    }
    return res;
}

string element_extract(string mat , int r , int e)
{
    string row = mat_row(mat , r);
    int len= row.length();
    int number_of_spaces=0;
    for(int i=0 ; i< len ; i++)
    {
        if(row[i] == ' ')
        {
            number_of_spaces+=1;
        }
    }
    int number_of_elements = number_of_spaces+1;
    string res="";

    if(e==number_of_elements)
    {
        if(e==1)
        {
            res = row;
        }
        else
        {
            for(int i= find_dubchar(row , ' ' , number_of_spaces)+1 ; i<len ; i++)
            res+=row[i];
        }
    }
    else if(e==1)
    {
        for(int i=0 ; i<find_dubchar(row , ' ' , 1) ; i++)
        {
            res+=row[i];
        }
    }
    else
    {
        for(int i= find_dubchar(row , ' ' , e-1)+1 ; i< find_dubchar(row , ' ' , e) ; i++)
        {
            res+=row[i];
        }
    }


    return res;
}

string mat_coln(string mat , int c)
{
    int rows = num_of_rows(mat);
    string coln="";
    for(int i=1 ; i<= rows ; i++)
    {
        coln+=element_extract(mat , i , c) + " ";
    }

    int len=coln.length();
    coln.erase(len-1);
    return coln;
}

string mat_add(string mat1 , string mat2)
{
    int r= num_of_rows(mat1);
    int c= num_of_columns(mat1);
    string res="[",calc;

    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            calc = eval(element_extract(mat1 , i , j) , '+' , element_extract(mat2 , i , j));
            res+=calc+" ";
        }
        int resll=res.length();
        res.erase(resll-1);
        res+=";";
    }
    int len=res.length();
    res.erase(len-1);
    res+="]";

    return res;

}

string mat_sub(string mat1 , string mat2)
{
    int r= num_of_rows(mat1);
    int c= num_of_columns(mat1);
    string res="[",calc;

    for(int i=1;i<=r;i++)
    {
        for(int j=1;j<=c;j++)
        {
            calc = eval(element_extract(mat1 , i , j) , '-' , element_extract(mat2 , i , j));
            res+=calc+" ";
        }
        int resll=res.length();
        res.erase(resll-1);
        res+=";";
    }
    int len=res.length();
    res.erase(len-1);
    res+="]";

    return res;
}

string rowcoln_element(string rowcoln , int num)
{
   int len = rowcoln.length();
   int num_spaces =0;
   int start , ending;
   string res="";
   for(int i=0;i<len ;i++)
   {
       if(rowcoln[i] == ' ')
       {
           num_spaces+=1;
       }
   }
   int num_elements = num_spaces+1;


   if(num == num_elements)
   {
       if(num == 1)
       {
           start = 0;
           ending = len;
       }
       else
       {
            start = find_dubchar(rowcoln , ' ' , num_spaces)+1;
            ending= len;
       }
   }
   else if(num == 1)
   {
       start = 0;
       ending= find_dubchar(rowcoln , ' ' , 1);
   }
   else
   {
       start = find_dubchar(rowcoln , ' ' , num-1)+1;
       ending= find_dubchar(rowcoln , ' ' , num);
   }

   for(int i=start ; i< ending ; i++)
       {
           res+=rowcoln[i];
       }

   return res;
}

string rowXcolumn(string mat1 , string mat2 , int r , int c)
{

    int n1rows = num_of_rows(mat1);
    int n2rows = num_of_rows(mat2);  // equals num of columns for mat1
    int n2coln = num_of_columns(mat2);

    string row = mat_row(mat1 , r);
    string coln=mat_coln(mat2 , c);
    string x="0";

    for(int i=1 ; i<= n2rows ; i++)
    {
        x=eval(x , '+' , eval(rowcoln_element(row , i) , 'x' , rowcoln_element(coln , i)));
    }

    return x;
}

string mat_multiply(string mat1 , string mat2)
{
    int rows1 = num_of_rows(mat1);
    int coln2 = num_of_columns(mat2);

    string x;
    string res="[";

    for(int i=1 ; i<=rows1  ;i++)
    {
        for(int j=1 ; j<=coln2  ;j++)
        {
            res+=rowXcolumn(mat1 , mat2 , i , j)+" ";
            if(j == coln2)
            {
                res.erase(res.length()-1);
                res+=";";
            }
        }
    }
    res.erase(res.length()-1);
    res+="]";
    return res;
}

string mat_power(string mat , int power)
{
    string auth = mat;
    string res="";

    if(power == 1)
    {
        return mat;
    }
    else if(power == 2)
    {
        mat=mat_multiply(mat , auth);
        return mat;
    }
    else
    {
        for(int i=1 ; i< power ; i++)
        {
            mat = mat_multiply(mat , auth);
        }
        return mat;
    }
}

string mat_trans(string mat)
{
    string res = "[";
    int ncol = num_of_columns(mat);
    for(int i=1 ; i<= ncol ; i++)
    {
        res += mat_coln(mat , i)+";";
    }
    res.erase(res.length()-1);
    res+="]";
    return res;
}

// -----------------------------------------------------------------------------------------------

string omit_firstrow(string mat)
{
    int matlen= mat.length();
    string row = mat_row(mat , 1);
    int len = row.length();
    string res="[";

    for(int i=len+2 ; i< matlen ; i++)
    {
        res+=mat[i];
    }
    return res;
}

string omit_element_fromRow(string row , int n)
{
    string element = rowcoln_element(row , n);
    int elelen = element.length();
    int len = row.length();
    int numspaces = 0;
    int start,ending;
    string res="";
    for(int i=0;i<len ; i++)
    {
        if(row[i] == ' ')
        {
            numspaces+=1;
        }
    }
    int num_elements = numspaces+1;


    if(n == 1)
    {
        for(int i=elelen+1 ; i< len ; i++)
        {
            res+=row[i];
        }
    }
    else if(n == num_elements)
    {
        for(int i=0 ; i< len-elelen ; i++)
        {
            res+=row[i];
        }
        res.erase(res.length()-1);
    }
    else
    {
        start = find_dubchar(row , ' ' ,n-1);
        ending= find_dubchar(row , ' ' ,n);

        string res1 = row.substr(0,start);
        string res2 = row.substr(ending,len-ending);
        res = res1+res2;
    }

    return res;
}

string A[100];
string mat_minor(string mat, int numcoln)
{
    string res="[";
    string newmat=omit_firstrow(mat);
    int rowsnum = num_of_rows(newmat);
    for(int i=0 ; i<rowsnum ; i++)
    {
        A[i] = mat_row(newmat , i+1);
        A[i] = omit_element_fromRow(A[i] , numcoln);
        res+=A[i]+";";
    }
res.erase(res.length()-1);
res+="]";
return res;
}

string det2(string mat)
{
    return eval(eval(rowcoln_element(mat_row(mat , 1),1), 'x' ,rowcoln_element(mat_row(mat,2),2)),'-', eval(rowcoln_element(mat_row(mat,1),2),'x',rowcoln_element(mat_row(mat,2),1)));
}

string det3(string mat)
{
    string x;
    string res="0";

    for(int i=1 ; i<=3 ; i++)
    {
        x= eval( element_extract(mat , 1 , i) , 'x' , det2(mat_minor(mat , i)));

        if(i%2)
        {
            x=eval(x , 'x' , "-1");
        }
        res = eval(res ,'+',x);
    }
return res;
}

string det(string mat)
{
    string x; string res="0";
    if(num_of_rows(mat) == 2)
    {
        return det2(mat);
    }
    else if(num_of_rows(mat) == 3)
    {
        return det3(mat);
    }
    else
    {
        for(int i=1 ; i<=num_of_rows(mat) ; i++)
        {
            x= eval( element_extract(mat , 1 , i) , 'x' , det(mat_minor(mat , i)));

            if(i%2)
            {
                x=eval(x , 'x' , "-1");
            }
            res = eval(res ,'+',x);
        }
        return res;
    }
}

string numXmat(string mat , string num)
{
    int numrow=num_of_rows(mat);
    string x; string res="[";
    for(int i=1 ; i<=numrow ; i++)
    {
        string row="";
        for(int j=1 ; j<=numrow ; j++)
        {
            x=eval( element_extract(mat , i , j) , 'x' , num );
            row+= x+" ";
        }
        row.erase(row.length()-1);
        res+=row+";";
    }
    res.erase(res.length()-1);
    res+="]";
    return res;

}


int main()
{



/*
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
            cout << mat_add(mat1 , mat2);
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
            cout << mat_sub(mat1 , mat2);
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
            cout << mat_multiply(mat1 , mat2);
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
            cout << mat_power(mat1 , power);
        }

    }

    else if(operate == "I")
    {
        if(!is_square(mat1))
        {
            cout << "ERROR";
                return 0;
        }
        else if(num_of_rows(mat1)== 1)
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
        if(!is_square(mat1))
        {
            cout << "ERROR";
            return 0;
        }
        else if(num_of_rows(mat1)== 1)
        {
            cout << "ERROR";
            return 0;
        }
        else
        {
            cout << det(mat1);
        }
    }

    else if(operate == "T")
    {
        cout << mat_trans(mat1);
    }
*/

return 0;
}

string eval(string num1 , char operator_ , string num2)
{
    if(num1 == "-0")
    {
        num1 = "0";
    }
    if(num2 == "-0")
    {
        num2 == "0";
    }
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













