using System;

public class Complex
{
    public double x = 0.0;
    public double y = 0.0;
    //构造函数
    public Complex()
    {
        x = y = 0.0;
    }
    //构造函数
    public Complex(double x,double y)
    {
        this.x = x;
        this.y = y;
    }
    //模
    public double Abs()
    {
        return Math.Sqrt(x * x + y * y);
    }
    //辐角
    public double Arg()
    {
        return Math.Atan2(y,x);
    }
    //开 n 次方
    public Complex sqrtn(double n)
    {
        Complex t   =   new Complex();
        double  r   =   x * x + y * y;

        if(r > 0.0)
        {
            n   =   1.0 / n;
            r   =   Math.Pow(r, 0.5 * n);
            double a = Arg() * n;   //辐角
            t.x =   r * Math.Cos(a);
            t.y =   r * Math.Sin(a);
        }
        return t;
    }
    //重载运算符——正号
    public static Complex operator +(Complex c)
    {
        return c;
    }
    //重载运算符——负号
    public static Complex operator -(Complex c)
    {
        return new Complex(-c.x, -c.y);
    }
    //重载运算符——加法
    public static Complex operator +(Complex a, Complex b)
    {
        return new Complex(a.x + b.x, a.y + b.y);
    }
    //重载运算符——加法
    public static Complex operator +(double d, Complex c)
    {
        return new Complex(d + c.x, c.y);
    }
    //重载运算符——加法
    public static Complex operator +(Complex c, double d)
    {
        return new Complex(c.x + d, c.y);
    }
    //重载运算符——减法
    public static Complex operator -(Complex a, Complex b)
    {
        return new Complex(a.x - b.x, a.y - b.y);
    }
    //重载运算符——减法
    public static Complex operator -(double d, Complex c)
    {
        return new Complex(d - c.x, -c.y);
    }
    //重载运算符——减法
    public static Complex operator -(Complex c, double d)
    {
        return new Complex(c.x - d, c.y);
    }
    //重载运算符——乘法
    public static Complex operator *(Complex a, Complex b)
    {
        return new Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    //重载运算符——乘法
    public static Complex operator *(double d, Complex c)
    {
        return new Complex(d * c.x, d * c.y);
    }
    //重载运算符——乘法
    public static Complex operator *(Complex c, double d)
    {
        return new Complex(d * c.x, d * c.y);
    }
    //重载运算符——除法
    public static Complex operator /(Complex a, Complex b)
    {
        double m2 = b.x * b.x + b.y * b.y;
        return new Complex((a.x * b.x + a.y * b.y) / m2, (a.y * b.x - a.x * b.y) / m2);
    }
    //重载运算符——除法
    public static Complex operator /(Complex c,double d)
    {
        return new Complex(c.x / d, c.y / d);
    }
    //重载运算符——除法
    public static Complex operator /(double d,Complex c)
    {
        d /= c.x * c.x + c.y * c.y;
        return new Complex(d * c.x, -d * c.y);
    }
}